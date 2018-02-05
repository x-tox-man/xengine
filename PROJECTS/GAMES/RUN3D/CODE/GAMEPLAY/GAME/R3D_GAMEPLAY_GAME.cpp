//
//  R3D_GAMEPLAY_GAME.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_GAMEPLAY_GAME.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_PICKING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "PHYSICS_COLLISION_FILTER.h"
#include "R3D_RESOURCES.h"
#include "btInternalEdgeUtility.h"
#include "RUN3D_APPLICATION.h"
#include "PHYSICS_UTILS.h"
#include "RUN3D_APPLICATION.h"

//https://github.com/libgdx/libgdx/issues/2534
//https://pybullet.org/Bullet/phpBB3/viewtopic.php?p=&f=9&t=3052
//https://github.com/bulletphysics/bullet3/issues/288
//btAdjustInternalEdgeContacts

//extern ContactAddedCallback gContactAddedCallback;
//extern ContactStartedCallback gContactStartedCallback;

/*void CustomContactStartedCallback(btPersistentManifold* const &manifold) {
    
    CORE_MATH_VECTOR
        position,
        normal;
    CORE_MATH_RAY_SEGMENT
        ray;
    
    auto player = R3D_APP_PTR->GetGame()->GetLevel()->GetPlayerTable()[0];
    
    const CORE_MATH_VECTOR & pos = ((GAMEPLAY_COMPONENT_POSITION::PTR) player->GetShip()->GetComponent( GAMEPLAY_COMPONENT_TYPE_Position ) )->GetPosition();
    ray.SetOrigin( pos );
    ray.SetDestination(pos + CORE_MATH_VECTOR(0.0f, 0.0f, -2.0f, 0.0f) );
    
    PHYSICS_UTILS::FindCollisionInRayFromWorld( R3D_APP_PTR->GetGame()->GetBulletSystem()->GetDynamicsWorld(), position, normal, ray );
    
    for (int i = 0; i < manifold->getNumContacts(); i++ ) {
        
        if ( fabs( manifold->getContactPoint(i).m_normalWorldOnB.z() - 1.0f ) > 0.001f || fabs( manifold->getContactPoint(i).m_normalWorldOnB.x()  ) > 0.001f || fabs( manifold->getContactPoint(i).m_normalWorldOnB.y()  ) > 0.001f ) {
            
            printf( "%.2f, %.2f, %.2f\n", manifold->getContactPoint(i).m_normalWorldOnB.x(), manifold->getContactPoint(i).m_normalWorldOnB.y(), manifold->getContactPoint(i).m_normalWorldOnB.z() );
            manifold->removeContactPoint( i );
        }
    }
}*/

/*bool CustomMaterialCombinerCallback(btManifoldPoint& cp,    const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
{
    
    if (true)
    {
        //btAdjustInternalEdgeContacts(cp,colObj1Wrap,colObj0Wrap, partId1,index1);
        btAdjustInternalEdgeContacts(cp,colObj1Wrap,colObj0Wrap, partId1,index1, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);
        btAdjustInternalEdgeContacts(cp,colObj0Wrap,colObj1Wrap, partId0,index0, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);
        btAdjustInternalEdgeContacts(cp,colObj1Wrap,colObj0Wrap, partId0,index1, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);
        btAdjustInternalEdgeContacts(cp,colObj0Wrap,colObj1Wrap, partId1,index0, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);
        //btAdjustInternalEdgeContacts(cp,colObj1Wrap,colObj0Wrap, partId1,index1, BT_TRIANGLE_CONVEX_DOUBLE_SIDED+BT_TRIANGLE_CONCAVE_DOUBLE_SIDED);
    }
    
    float friction0 = colObj0Wrap->getCollisionObject()->getFriction();
    float friction1 = colObj1Wrap->getCollisionObject()->getFriction();
    float restitution0 = colObj0Wrap->getCollisionObject()->getRestitution();
    float restitution1 = colObj1Wrap->getCollisionObject()->getRestitution();
    
    if (colObj0Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)
    {
        friction0 = 0.0;//partId0,index0
        restitution0 = 0.f;
    }
    if (colObj1Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)
    {
        if (index1&1)
        {
            friction1 = 0.0f;//partId1,index1
        } else
        {
            friction1 = 0.f;
        }
        restitution1 = 0.f;
    }
    
    cp.m_combinedFriction = 0.0f;
    cp.m_combinedRestitution = 0.0f;
    
    //this return value is currently ignored, but to be on the safe side: return false if you don't calculate friction
    return false;
}*/

void MyNearCallback( btBroadphasePair & collision_pair, btCollisionDispatcher & dispatcher, const btDispatcherInfo & info ) {
    
    if ( (collision_pair.m_pProxy0->m_collisionFilterGroup & PHYSICS_COLLISION_TYPE_SHIP) == PHYSICS_COLLISION_TYPE_SHIP ) {
        
        auto o1 = (btCollisionObject*) collision_pair.m_pProxy0->m_clientObject;
        auto o2 = (btCollisionObject*) collision_pair.m_pProxy1->m_clientObject;
        
        for (int im = 0; im < dispatcher.getNumManifolds(); im++ ) {
            auto mnfd = dispatcher.getManifoldByIndexInternal( im );
            
            for (int cp = 0; cp < mnfd->getNumContacts(); cp++ ) {
                
                /*printf( "local pos %.2f %.2f %.2f\n", mnfd->getContactPoint( cp ).m_localPointA.x(), mnfd->getContactPoint( cp ).m_localPointA.y(), mnfd->getContactPoint( cp ).m_localPointA.z() );
                printf( "position %.2f %.2f %.2f\n", mnfd->getContactPoint( cp ).getPositionWorldOnA().x(), mnfd->getContactPoint( cp ).getPositionWorldOnA().y(), mnfd->getContactPoint( cp ).getPositionWorldOnA().z() );
                printf( "normal %.2f %.2f %.2f\n", mnfd->getContactPoint( cp ).m_normalWorldOnB.x(), mnfd->getContactPoint( cp ).m_normalWorldOnB.y(), mnfd->getContactPoint( cp ).m_normalWorldOnB.z() );
                
                if ( mnfd->getContactPoint( cp ).m_normalWorldOnB.z() < 0.99f ) {
                    
                    mnfd->removeContactPoint( cp );
                    printf( "%d - %d\n", ((GAMEPLAY_COMPONENT_ENTITY::PTR) o1->getUserPointer())->GetHandle().GetIndex(), ((GAMEPLAY_COMPONENT_ENTITY::PTR) o2->getUserPointer())->GetHandle().GetIndex() );
                }*/
            }
        }
    }
    else if ( (collision_pair.m_pProxy1->m_collisionFilterGroup & PHYSICS_COLLISION_TYPE_SHIP) == PHYSICS_COLLISION_TYPE_SHIP ) {
        
        
    }
    
    dispatcher.defaultNearCallback(collision_pair, dispatcher, info );
}

R3D_GAMEPLAY_GAME::R3D_GAMEPLAY_GAME() :
    StateMachine(),
    LevelManager(),
    Scene(),
    Tick( 0 ),
    ThisPlayerIndex( "DefaultPlayer" ),
    TimeMod( 0.0f ),
    BulletSystem( new GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION() ) {
        
}

R3D_GAMEPLAY_GAME::~R3D_GAMEPLAY_GAME() {
    
}

void R3D_GAMEPLAY_GAME::SetPlayers( const std::vector< GAME_PLAYER_MODEL > & players ) {
    
    for (int i = 0; i < players.size(); i++ ) {
        
        GetLevel()->GetPlayerTable()[ players[ i ].Identifier ] = players[ i ].GamePlayer;
        GetLevel()->GetPlayerTable()[ players[ i ].Identifier ]->Initialize();
    }
    
    Delegate->SetPlayers( & GetLevel()->GetPlayerTable() );
}

void R3D_GAMEPLAY_GAME::Initialize( ) {
    
    //gContactAddedCallback = CustomMaterialCombinerCallback;
    //gContactStartedCallback = CustomContactStartedCallback;
    
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_POSITION );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_ANIMATING );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_PICKING );
    Scene.InsertUpdatableSystem( new GAMEPLAY_COMPONENT_SYSTEM_UPDATE_SCRIPT );
    Scene.InsertUpdatableSystem( BulletSystem );
    
    BulletSystem->SetNearCallback( MyNearCallback );
    BulletSystem->SetGravity( -2.81f );
    BulletSystem->Initialize();
    BulletSystem->SetCollisionFilter( new PHYSICS_COLLISION_FILTER() );
    
    Scene.InsertRenderableSystem( new GAMEPLAY_COMPONENT_SYSTEM_RENDERER );
    
    ((GAMEPLAY_COMPONENT_SYSTEM_RENDERER::PTR) Scene.GetRenderableSystemTable()[0])->SetRenderer( &GRAPHIC_RENDERER::GetInstance() );
    
    LevelManager.Initialize();
    
    CORE_FIXED_STATE_InitializeState( StateMachine, R3D_GAMEPLAY_GAME::IDLE_STATE, this );
}

void R3D_GAMEPLAY_GAME::Restart() {
    
    Tick = 0;
    #if DEBUG
        assert( LevelManager.GetCurrentLevel() != NULL );
    #endif
    LevelManager.GetCurrentLevel()->Restart();
    
    StateMachine.ChangeState( GAME_STARTINGSTATE );
    
    TimeMod = 0.0f;
}

void R3D_GAMEPLAY_GAME::SelectLevel( R3D_GAME_LEVEL_INFO::PTR info ) {
    
    if ( LevelManager.GetCurrentLevel() == NULL || !( *info == *LevelManager.GetCurrentLevel()->GetInfo()) ) {
        
        LevelManager.LoadLevel( info );
    }
}

void R3D_GAMEPLAY_GAME::Finalize() {
    
    if ( LevelManager.GetCurrentLevel() != NULL ) {
        
        LevelManager.GetCurrentLevel()->Finalize();
    }
}

void R3D_GAMEPLAY_GAME::Render( GRAPHIC_RENDERER & renderer ) {
    
    Scene.Render( renderer );
}

void R3D_GAMEPLAY_GAME::Update( const float step ) {
    
    StateMachine.DispatchEvent( UPDATE_EVENT( step ) );
}

void R3D_GAMEPLAY_GAME::OnPlayerCompleted( GAMEPLAY_COMPONENT_ENTITY * entity ) {
    
    StateMachine.ChangeState( END_GAME_STATESTATE );
}

//---------------------------------------------------------------------------------------//
//-------------------------- GAME IDLE_STATE ----------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::IDLE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()

//---------------------------------------------------------------------------------------//
//-------------------------- GAME STARTING ----------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::GAME_STARTING )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::GAME_STARTING, UPDATE_EVENT )
    static float t = 0.0f;
    static GRAPHIC_CAMERA local_camera( 1.0f, 1500.0f, 1024.0f, 768.0f, CORE_MATH_VECTOR(), CORE_MATH_QUATERNION() );
    static const CORE_MATH_VECTOR & position = R3D_APP_PTR->GetCamera()->GetPosition();
    static const CORE_MATH_QUATERNION & orientation = R3D_APP_PTR->GetCamera()->GetOrientation();

    if ( t > 1.0f ) {
        
        CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().GAME_STATE )
        
        t = 0.0f;
        
        R3D_APP_PTR->SetCamera( &GetContext().LevelManager.GetCurrentLevel()->GetPlayerTable()[ GetContext().ThisPlayerIndex ]->GetShip()->GetRear() );
    }
    else {
        
        const GRAPHIC_CAMERA & camera = GetContext().LevelManager.GetCurrentLevel()->GetPlayerTable()[GetContext().ThisPlayerIndex]->GetShip()->GetRear();
        
        float p = t;
        
        CORE_MATH_QUATERNION q = camera.GetOrientation() * p + orientation * (1.0f - p);
        q.Normalize();
        
        local_camera.UpdateCamera(camera.GetPosition() * p + position * (1.0f - p), q );
        R3D_APP_PTR->SetCamera( &local_camera );
    }

    t += event.GetEventData();

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::GAME_STARTING )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- GAME STATE    ----------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::GAME_STATE )
    GetContext().GetLevel()->Start();
CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::GAME_STATE, UPDATE_EVENT )

    GetContext().Tick++;
    GetContext().Scene.Update( event.GetEventData() );
    GetContext().InternalUpdateGame( event.GetEventData() );

    GetContext().TimeMod += event.GetEventData();

    auto proxy = R3D_RESOURCES::GetInstance().FindResourceProxy( CORE_HELPERS_UNIQUE_IDENTIFIER( "CheckpointEffect" ) );
    GRAPHIC_SHADER_ATTRIBUTE & time_mod = proxy->GetResource< GRAPHIC_SHADER_EFFECT >()->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );

    time_mod.AttributeValue.Value.FloatValue = sinf( GetContext().TimeMod ) * 0.1f;

    std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, R3D_PLAYER::PTR >::iterator it = GetContext().LevelManager.GetCurrentLevel()->GetPlayerTable().begin();

    while( it != GetContext().LevelManager.GetCurrentLevel()->GetPlayerTable().end() ) {
        
        it->second->GetShip()->Update( event.GetEventData() );
        
        it++;
    }

    GetContext().GetLevel()->Update( event.GetEventData() );

CORE_FIXED_STATE_EndOfStateEvent()

CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::GAME_STATE, PAUSE_EVENT )
    CORE_FIXED_STATE_MACHINE_ChangeState( GetContext().StateMachine, GetContext().PAUSE_STATE);
CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- PAUSE STATE    ---------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::PAUSE_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------//
//-------------------------- END GAME STATE    ------------------------------------------//
//---------------------------------------------------------------------------------------//
CORE_FIXED_STATE_DefineStateEnterEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE )
    GetContext().LevelManager.HandleLevelComplete();
    GetContext().Delegate->OnEndGame();

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE, UPDATE_EVENT )

CORE_FIXED_STATE_EndOfStateEvent()


CORE_FIXED_STATE_DefineStateLeaveEvent( R3D_GAMEPLAY_GAME::END_GAME_STATE )

CORE_FIXED_STATE_EndOfStateEvent()
//---------------------------------------------------------------------------------------//

