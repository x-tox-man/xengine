
#include "AUDIO_OGG_LOADER.h"
#include "AUDIO_SOUND.h"
#include "AUDIO_SOUND_CHUNK.h"
#include <vorbis/codec.h>
#include <math.h>

void OGG_InternalInit( AUDIO_SOUND & sound );
void OGG_Clear( AUDIO_SOUND &sound );

void OGG_Init() {
    // https://github.com/xiph/vorbis/blob/master/examples/decoder_example.c#L82
}

void OGG_Reset( AUDIO_SOUND & sound ) {
    
    OGG_Clear( sound );
    sound.GetFile()->Rewind();
    OGG_InternalInit( sound );
}

void OGG_Open( const CORE_FILESYSTEM_PATH & path, AUDIO_SOUND & sound ) {

    ogg_sync_init( &sound.OGGSyncState ); /* Now we can read pages */

    CORE_FILESYSTEM_FILE *file=new CORE_FILESYSTEM_FILE( path );
    file->OpenOutput();
    sound.SetFile( file );

    OGG_InternalInit( sound );
}

void OGG_InternalInit( AUDIO_SOUND & sound ) {
    
    char *buffer;
    int  bytes;
    
    int convsize=4096;
    ogg_int16_t convbuffer[ 4096 ];
    
    int eos=0;
    int i;
    
    /* grab some data at the head of the stream. We want the first page
     (which is guaranteed to be small and only contain the Vorbis
     stream initial header) We need the first page to get the stream
     serialno. */
    
    /* submit a 4k block to libvorbis' Ogg layer */
    buffer=ogg_sync_buffer( &sound.OGGSyncState, 4096 );
    bytes=sound.GetFile()->OutputBytes( buffer, 4096 );
    
    ogg_sync_wrote( &sound.OGGSyncState, bytes );
    
    /* Get the first page. */
    if ( ogg_sync_pageout( &sound.OGGSyncState, &sound.OGGPage ) != 1 ) {
        /* have we simply run out of data?  If so, we're done. */
        if ( bytes<4096 )
            return;
        
        /* error case.  Must not be Vorbis data */
        fprintf( stderr, "Input does not appear to be an Ogg bitstream.\n" );
        exit( 1 );
    }
    
    /* Get the serial number and set up the rest of decode. */
    /* serialno first; use it to set up a logical stream */
    ogg_stream_init( &sound.OGGStreamState, ogg_page_serialno( &sound.OGGPage ) );
    
    /* extract the initial header from the first page and verify that the
     Ogg bitstream is in fact Vorbis data */
    
    /* I handle the initial header first instead of just having the code
     read all three Vorbis headers at once because reading the initial
     header is an easy way to identify a Vorbis bitstream and it's
     useful to see that functionality seperated out. */
    
    vorbis_info_init( &sound.VorbisInfo );
    vorbis_comment_init( &sound.VorbisComment );
    if ( ogg_stream_pagein( &sound.OGGStreamState, &sound.OGGPage )<0 ) {
        /* error; stream version mismatch perhaps */
        fprintf( stderr, "Error reading first page of Ogg bitstream data.\n" );
        exit( 1 );
    }
    
    if ( ogg_stream_packetout( &sound.OGGStreamState, &sound.OGGPacket ) != 1 ) {
        /* no page? must not be vorbis */
        fprintf( stderr, "Error reading initial header packet.\n" );
        exit( 1 );
    }
    
    if ( vorbis_synthesis_headerin( &sound.VorbisInfo, &sound.VorbisComment, &sound.OGGPacket )<0 ) {
        /* error case; not a vorbis header */
        fprintf( stderr, "This Ogg bitstream does not contain Vorbis "
                "audio data.\n" );
        exit( 1 );
    }
    
    /* At this point, we're sure we're Vorbis. We've set up the logical
     (Ogg) bitstream decoder. Get the comment and codebook headers and
     set up the Vorbis decoder */
    
    /* The next two packets in order are the comment and codebook headers.
     They're likely large and may span multiple pages. Thus we read
     and submit data until we get our two packets, watching that no
     pages are missing. If a page is missing, error out; losing a
     header page is the only place where missing data is fatal. */
    
    i=0;
    while ( i<2 ) {
        while ( i<2 ) {
            int result=ogg_sync_pageout( &sound.OGGSyncState, &sound.OGGPage );
            if ( result == 0 )break; /* Need more data */
            /* Don't complain about missing or corrupt data yet. We'll
             catch it at the packet output phase */
            if ( result == 1 ) {
                ogg_stream_pagein( &sound.OGGStreamState, &sound.OGGPage ); /* we can ignore any errors here
                                                                             as they'll also become apparent
                                                                             at packetout */
                while ( i<2 ) {
                    result=ogg_stream_packetout( &sound.OGGStreamState, &sound.OGGPacket );
                    if ( result == 0 )break;
                    if ( result<0 ) {
                        /* Uh oh; data at some point was corrupted or missing!
                         We can't tolerate that in a header.  Die. */
                        fprintf( stderr, "Corrupt secondary header.  Exiting.\n" );
                        exit( 1 );
                    }
                    result=vorbis_synthesis_headerin( &sound.VorbisInfo, &sound.VorbisComment, &sound.OGGPacket );
                    if ( result<0 ) {
                        fprintf( stderr, "Corrupt secondary header.  Exiting.\n" );
                        exit( 1 );
                    }
                    i++;
                }
            }
        }
        /* no harm in not checking before adding more */
        buffer=ogg_sync_buffer( &sound.OGGSyncState, 4096 );
        bytes=sound.GetFile()->OutputBytes( buffer, 4096 );
        if ( bytes == 0 && i<2 ) {
            fprintf( stderr, "End of file before finding all Vorbis headers!\n" );
            exit( 1 );
        }
        ogg_sync_wrote( &sound.OGGSyncState, bytes );
    }
    
    /* Throw the comments plus a few lines about the bitstream we're
     decoding */
    {
        char **ptr=sound.VorbisComment.user_comments;
        while ( *ptr ) {
            fprintf( stderr, "%s\n", *ptr );
            ++ptr;
        }
        fprintf( stderr, "\nBitstream is %d channel, %ldHz\n", sound.VorbisInfo.channels, sound.VorbisInfo.rate );
        fprintf( stderr, "Encoded by: %s\n\n", sound.VorbisComment.vendor );
    }
    
    convsize=4096 / sound.VorbisInfo.channels;
    
    /* OK, got and parsed all three headers. Initialize the Vorbis
     packet->PCM decoder. */
    if ( vorbis_synthesis_init( &sound.VorbisDspState, &sound.VorbisInfo ) == 0 )
    { /* central decode state */
        vorbis_block_init( &sound.VorbisDspState, &sound.VorbisBlock );          /* local state for most of the decode
                                                                                  so multiple block decodes can
                                                                                  proceed in parallel. We could init
                                                                                  multiple vorbis_block structures
                                                                                  for vd here */
        
        /* The rest is just a straight decode loop until end of stream */
        
        sound.SetIsMono( false );
        sound.SetIsCompressed( false );
        sound.SetBufferWidth( 16 );
        sound.SetFrameSize( 16 );
        sound.SetChannels( sound.VorbisInfo.channels );
        sound.SetFrequency( sound.VorbisInfo.rate );
    }
    else {
        fprintf( stderr, "Error: Corrupt header during playback initialization.\n" );
    }
}

bool OGG_Read( AUDIO_SOUND & sound, int chunk_index ) {

    char *buffer;
    int  bytes;

    int convsize=4096;
    ogg_int16_t convbuffer[ 4096 ];

    int eos=0;
    bool
        has_read = false;
    int i;

    while ( !has_read && !eos ) {
        while ( !eos ) {
            int result=ogg_sync_pageout( &sound.OGGSyncState, &sound.OGGPage );
            if ( result == 0 )break; /* need more data */
            if ( result<0 ) { /* missing or corrupt data at this page position */
                fprintf( stderr, "Corrupt or missing data in bitstream; "
                    "continuing...\n" );
            }
            else {
                ogg_stream_pagein( &sound.OGGStreamState, &sound.OGGPage ); /* can safely ignore errors at
                                                            this point */
                void * data = malloc( sound.OGGPage.body_len * 8 * sizeof( ogg_int16_t ) );
                
                sound.GetSoundChunksTable()[chunk_index]->Data = data;
                
                int out_buffer_offset = 0;
                
                while ( 1 ) {
                    result=ogg_stream_packetout( &sound.OGGStreamState, &sound.OGGPacket );

                    if ( result == 0 )break; /* need more data */
                    if ( result<0 ) { /* missing or corrupt data at this page position */
                                        /* no reason to complain; already complained above */
                    }
                    else {
                        /* we have a packet.  Decode it */
                        float **pcm;
                        int samples;

                        if ( vorbis_synthesis( &sound.VorbisBlock, &sound.OGGPacket ) == 0 ) /* test for success! */
                            vorbis_synthesis_blockin( &sound.VorbisDspState, &sound.VorbisBlock );
                        /*
                        **pcm is a multichannel float vector.  In stereo, for
                        example, pcm[0] is left, and pcm[1] is right.  samples is
                        the size of each channel.  Convert the float values
                        (-1.<=range<=1.) to whatever PCM format and write it out */

                        while ( ( samples=vorbis_synthesis_pcmout( &sound.VorbisDspState, &pcm ) )>0 ) {
                            int j;
                            int clipflag=0;
                            int bout=( samples<convsize ? samples : convsize );

                            /* convert floats to 16 bit signed ints (host order) and
                            interleave */
                            for ( i=0; i<sound.VorbisInfo.channels; i++ ) {
                                ogg_int16_t *ptr=convbuffer + i;
                                float  *mono=pcm[ i ];
                                for ( j=0; j<bout; j++ ) {
    #if 1
                                    int val=floor( mono[ j ] * 32767.f + .5f );
    #else /* optional dither */
                                    int val=mono[ j ] * 32767.f + drand48() - 0.5f;
    #endif
                                    /* might as well guard against clipping */
                                    if ( val>32767 ) {
                                        val=32767;
                                        clipflag=1;
                                    }
                                    if ( val<-32768 ) {
                                        val=-32768;
                                        clipflag=1;
                                    }
                                    *ptr=val;
                                    ptr+=sound.VorbisInfo.channels;
                                }
                            }

                            if ( clipflag )
                                fprintf( stderr, "Clipping in frame %ld\n", ( long ) ( sound.VorbisDspState.sequence ) );

                            int size = bout * sound.VorbisInfo.channels * sizeof( ogg_int16_t );
                            memcpy( (char*) data + out_buffer_offset, convbuffer, size );
                            out_buffer_offset += size;
                            
                            has_read = true;
                            //printf( "Read index : %d size : %d\n", chunk_index, bout );

                            vorbis_synthesis_read( &sound.VorbisDspState, bout ); /* tell libvorbis how
                                                                                    many samples we
                                                                                    actually consumed */
                        }
                    }
                }
                
                sound.GetSoundChunksTable()[chunk_index]->Size = out_buffer_offset;

                if ( ogg_page_eos( &sound.OGGPage ) )eos=1;
            }
            break;
        }
        
        if ( !eos && !has_read ) {
            buffer=ogg_sync_buffer( &sound.OGGSyncState, 4096 );
            bytes=sound.GetFile()->OutputBytes( buffer, 4096 );
            ogg_sync_wrote( &sound.OGGSyncState, bytes );
            if ( ( bytes == -1 || bytes == 0 ) && !has_read )eos=1;
        }
    }

    if ( eos == 1 ) {
        /* ogg_page and ogg_packet structs always point to storage in
        libvorbis.  They're never freed or manipulated directly */

        vorbis_block_clear( &sound.VorbisBlock );
        vorbis_dsp_clear( &sound.VorbisDspState );
        
        return true;
    }
    
    return false;
}

void OGG_Close( AUDIO_SOUND & sound ) {

    /* clean up this logical bitstream; before exit we see if we're
    followed by another [chained] */
    
    OGG_Clear( sound );
    sound.GetFile()->Close();
    delete sound.GetFile();
    sound.SetFile( NULL );
}

void OGG_Clear( AUDIO_SOUND &sound ) {
    
    vorbis_block_clear( &sound.VorbisBlock );
    vorbis_dsp_clear( &sound.VorbisDspState );
    ogg_stream_clear( &sound.OGGStreamState );
    vorbis_comment_clear( &sound.VorbisComment );
    vorbis_info_clear( &sound.VorbisInfo );  /* must be called last */
}
