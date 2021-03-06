/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <iostream>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include "MULTIPOLY_APPLICATION.h"
#include "GRAPHIC_WINDOW_ANDROID.h"
#include "GRAPHIC_RENDERER.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "AUDIO_SYSTEM.h"
#include <unistd.h>
#include <time.h>

extern unsigned int __page_size=getpagesize();


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))


/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLContext shared_context;
    int32_t width;
    int32_t height;
    struct saved_state state;
    MULTIPOLY_APPLICATION * application;
};

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */

    //LOGI("native-activity engine_init_display\n");
     
    /*const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_BUFFER_SIZE, 32,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };*/

    const EGLint RGBX_8888_ATTRIBS[] =
    {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_BUFFER_SIZE, 32,
    EGL_DEPTH_SIZE, 8,
    EGL_NONE
    };

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLContext shared_context;

    engine->application = new MULTIPOLY_APPLICATION();
    engine->application->setApplicationName( "testAndroid" );

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if ( !eglInitialize(display, 0, 0) ) {

        LOGW("native-activity Unable to eglInitialize");
    }

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    if ( !eglChooseConfig(display, RGBX_8888_ATTRIBS, &config, 1, &numConfigs) ) {

        LOGW("native-activity Unable to eglChooseConfig");
    }

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    if ( !eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format) ) {

        LOGW("native-activity Unable to eglGetConfigAttrib");
    }

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);

    //LOGW("native-activity  surface %d", surface);

    const EGLint context_option[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_option);
    shared_context = eglCreateContext(display, config, context, context_option);

    //LOGW("native-activity  context %d", context);

    if ( eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("native-activity Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    // Initialize GL state.
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    GRAPHIC_WINDOW_ANDROID * window = new GRAPHIC_WINDOW_ANDROID();
    window->SetHeight( h );
    window->SetWidth( w );
    window->Context = context;
    window->SharedContext = shared_context;
    window->Surface = surface;
    window->Display = display;
    
    window->Initialize();
    
    engine->application->SetApplicationWindow( *window );

    JNIEnv* jni;

    engine->app->activity->vm->AttachCurrentThread(&jni, NULL);

    LOGW( "native-activity asset_manager_object jni , %d\n", jni );

    jclass activityClass = jni->FindClass("android/app/NativeActivity");
    activityClass = reinterpret_cast<jclass>(jni->NewGlobalRef( activityClass ));

    LOGW( "native-activity asset_manager_object activityClass, %d\n", activityClass );

    jmethodID getAssets = jni->GetMethodID( activityClass, "getAssets", "()Landroid/content/res/AssetManager;");
    //getAssets = reinterpret_cast<jmethodID>(jni->NewGlobalRef( getAssets ));
    LOGW( "native-activity getAssets jni , %d\n", getAssets );
    
    jobject asset_manager_object = jni->CallObjectMethod( engine->app->activity->clazz, getAssets );
    asset_manager_object = reinterpret_cast<jobject>(jni->NewGlobalRef( asset_manager_object ) );

    LOGW( "native-activity asset_manager_object asset_manager_object , %d\n", asset_manager_object );

    AAssetManager * AssetManager = AAssetManager_fromJava( jni, asset_manager_object );
    AAssetDir * AssetDirectory = AAssetManager_openDir( AssetManager, "" );

    const char * filename = AAssetDir_getNextFileName( AssetDirectory );

    LOGE( "native-activity asset_manager_object AssetDirectory , %d first file name %s\n", AssetDirectory, filename );

    AUDIO_SYSTEM::GetInstance().Initialize();

    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().SetJNIActivityEnvAndClass( jni, engine->app->activity->clazz );
    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetVibrator().Initialize();

    engine->application->GetDefaultFileystem().SetJNIEnv( jni );
    engine->application->GetDefaultFileystem().SetAssetManager( AssetManager );
    engine->application->GetDefaultFileystem().SetAssetDirectory( AssetDirectory );
    engine->application->Initialize();

    engine->animating = 1;

    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine) {
    if (engine->display == NULL) {
        // No display.
        return;
    }

    // Just fill the screen with a color.
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GRAPHIC_RENDERER::GetInstance().BeginFrame();
    GRAPHIC_RENDERER::GetInstance().Render();
    GRAPHIC_RENDERER::GetInstance().EndFrame();

    glFlush();

    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    struct engine* engine = (struct engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {

        static float last_x = 0;
        static float last_y = 0;
        
        engine->animating = 1;
        engine->state.x = AMotionEvent_getX(event, 0);
        engine->state.y = AMotionEvent_getY(event, 0);

        int deltaX, deltaY;
        
        deltaX = engine->state.x - last_x;
        deltaY = engine->state.y - last_y;
        
        last_x = engine->state.x;
        last_y = engine->state.y;
                
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( (float)deltaX / engine->width, (float)deltaY / engine->height);
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( (float) engine->state.x / engine->width, 1.0f - (float)engine->state.y / engine->height);
        PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( (float)engine->state.x, (float)engine->state.y );

        //LOGE( "MOuuFFE      %f  %f", (float)deltaX / engine->width, (float)deltaY / engine->height );
        //LOGE( "MOuuFFE2     %f  %f", (float)engine->state.x / engine->width, -(float)engine->state.y / engine->height );
        //LOGE( "MOuuFFE3     %f  %f", (float)engine->state.x, (float)engine->state.y );

        if ( AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN ) {
            LOGE( "KLIK AKEY_EVENT_ACTION_DOWN");
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonClicked();
        }

        if ( AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_UP ) {
            LOGE( "KLIK AKEY_EVENT_ACTION_UP ");
            PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonReleased();
        }

        return 1;
    }
    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;

    //LOGI("engine_handle_cmd\n");
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                        engine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;

    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                            &event, 1) > 0) {
                        /*LOGI("accelerometer: x=%f y=%f z=%f",
                                event.acceleration.x, event.acceleration.y,
                                event.acceleration.z);*/

                        //engine.application->SetDisplacement( event.acceleration.y* 0.1f, 0.0f, event.acceleration.x* 0.1f);
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating) {
            // Done with events; draw next animation frame.
            static clock_t begin_time = clock();
            // do something
            clock_t current_clock = clock();  

            float delta = ((current_clock - begin_time) * (1000000 / CLOCKS_PER_SEC ));
            delta = delta * 0.000001f;
            begin_time = current_clock;

            //LOGI("NDK DELTA : %f", delta );

            CORE_APPLICATION::GetApplicationInstance().Update( delta );

            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engine);
        }
    }
}
//END_INCLUDE(all)