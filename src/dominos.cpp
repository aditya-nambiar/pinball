/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  dominos_t::dominos_t()
    {		
		
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2Vec2 vs[10];
			vs[0].Set(15.0f, 0.0f);
			vs[1].Set(15.0f, 42.0f);
			vs[2].Set(-15.0f, 42.0f);
			vs[3].Set(-15.0f, 0.0f);
			
			b2ChainShape loop;
			loop.CreateLoop(vs, 5);
			b2FixtureDef fd;
			fd.shape = &loop;
			fd.density = 0.0f;
			ground->CreateFixture(&fd);
		}
		
		{
			b2PolygonShape shp;
			b2Vec2 vertices[4];
			vertices[0].Set(0.0f, 6.5f);
			vertices[1].Set(-0.5f,6.5f);
			vertices[2].Set(-0.5f, 0.0f);
			vertices[3].Set(-0.0f, 0.5f);
			
			
			shp.Set(vertices, 4);

			b2FixtureDef fd;
			fd.shape = &shp;
			fd.density = 5.0f;
				
			b2BodyDef bd;
			bd.position.Set(-12.0f, 10.0f);
			lflipstatv = m_world->CreateBody(&bd);
			lflipstatv->CreateFixture(&fd);
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,9);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.0f, 19.0f);
				rightsep1= m_world->CreateBody(&bd);
				rightsep1->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,3.5);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.0f, 3.7f);
				rightsep2= m_world->CreateBody(&bd);
				rightsep2->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,1.0);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(-14.5f, 1.8f);
				hormov= m_world->CreateBody(&bd);
				hormov->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,12.5);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 90* DEGTORAD;
				bd.position.Set(-2.0f, 1.0f);
				horz= m_world->CreateBody(&bd);
				horz->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,0.95);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.angle = 85* DEGTORAD;
				bd.position.Set(11.70f, 0.5f);
				vermov= m_world->CreateBody(&bd);
				vermov->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,0.2);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.2f, 6.0f);
				stopper= m_world->CreateBody(&bd);
				stopper->CreateFixture(&boxFixtureDef);
			
		}
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.8,2);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;
				boxFixtureDef.density=5.0f;			
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.8f, 5.0f);
				launcher= m_world->CreateBody(&bd);
				launcher->CreateFixture(&boxFixtureDef);
			
		}
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.5,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -20* DEGTORAD;
			bd.position.Set(-9.5f, 9.0f);
			lflipstatd = m_world->CreateBody(&bd);
			lflipstatd->CreateFixture(&boxFixtureDef);
		}
		{
			b2PolygonShape shp;
			b2Vec2 vertices[4];
			vertices[0].Set(0.1f, 6.5f);
			vertices[1].Set(-0.5f,6.5f);
			vertices[2].Set(-0.5f, 0.5f);
			vertices[3].Set(0.1f, 0.0f);
			
			
			shp.Set(vertices, 4);

			b2FixtureDef fd;
			fd.shape = &shp;
			fd.density = 5.0f;
				
			b2BodyDef bd;
			bd.position.Set(12.0f, 9.9f);
			rflipstatv = m_world->CreateBody(&bd);
			rflipstatv->CreateFixture(&fd);
		}
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.5,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = 20* DEGTORAD;
			bd.position.Set(9.0f, 9.0f);
			rflipstatd = m_world->CreateBody(&bd);
			rflipstatd->CreateFixture(&boxFixtureDef);
		}
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(4.5,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -60* DEGTORAD;
			bd.position.Set(13.0f, 36.0f);
			temp = m_world->CreateBody(&bd);
			temp->CreateFixture(&boxFixtureDef);
		}
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(2.6,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -60* DEGTORAD;
			bd.position.Set(-13.5f, 19.0f);
			temp1 = m_world->CreateBody(&bd);
			temp1->CreateFixture(&boxFixtureDef);
			
			
			
		}
	
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.0,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;
					
			b2BodyDef bd;
			boxFixtureDef.density=5.0f;	
			bd.type = b2_dynamicBody;
			bd.angle = -30* DEGTORAD;
			bd.position.Set(-3.0f, 8.0f);
			lflipper = m_world->CreateBody(&bd);
			lflipper->CreateFixture(&boxFixtureDef);
		}
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.0,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;	
			boxFixtureDef.density=5.0f;			
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.angle = 30* DEGTORAD;
			bd.position.Set(3.0f, 8.0f);
			rflipper = m_world->CreateBody(&bd);
			rflipper->CreateFixture(&boxFixtureDef);
		}
		{
			
		    b2BodyDef bd;
		    bd.type = b2_dynamicBody;
		    bd.position.Set(13.5, 9);
		    

		

		    b2CircleShape circle;
		    circle.m_radius = 0.54f;

		    b2FixtureDef fixtureDef;
		    fixtureDef.shape = &circle;
		    fixtureDef.density = 1.0f;
		    fixtureDef.friction = 0.f;
		    fixtureDef.restitution = 0.2f;
		   
			ball= m_world->CreateBody(&bd);
		    ball->CreateFixture(&fixtureDef);
		}
		{
		//the motorised joint
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = lflipstatd;
		revoluteJointDef.bodyB = lflipper;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorB.Set(-3.0,0);
	
		revoluteJointDef.localAnchorA.Set(3.5,0);
		revoluteJointDef.enableLimit = true;
		revoluteJointDef.lowerAngle = -15 * DEGTORAD;
		revoluteJointDef.upperAngle =  20 * DEGTORAD;
		revoluteJointDef.enableMotor = true;
		revoluteJointDef.motorSpeed = 3;
		revoluteJointDef.maxMotorTorque = 100.0f;
		//revoluteJointDef.motorSpeed = -90 * DEGTORAD;//90 degrees per second
		lflip = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
		}
		{
		//the motorised joint
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = rflipstatd;
		revoluteJointDef.bodyB = rflipper;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorB.Set(3.0,0);
	
		revoluteJointDef.localAnchorA.Set(-3.5,0);
		revoluteJointDef.enableLimit = true;
		revoluteJointDef.lowerAngle = -15 * DEGTORAD;
		revoluteJointDef.upperAngle =  20 * DEGTORAD;
		revoluteJointDef.enableMotor = true;
		revoluteJointDef.motorSpeed = -3;
		revoluteJointDef.maxMotorTorque = 100.0f;
		//revoluteJointDef.motorSpeed = -90 * DEGTORAD;//90 degrees per second
		rflip = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
		}
		
	    {
	    	
			
		  b2PrismaticJointDef prismaticJointDef;
		  prismaticJointDef.bodyB = hormov;
		  prismaticJointDef.bodyA = horz;
		  prismaticJointDef.collideConnected = false;
		  prismaticJointDef.localAxisA.Set(0,1);
		  prismaticJointDef.localAnchorB.Set( 0,-1);//a little outside the bottom right corner
		  prismaticJointDef.localAnchorA.Set( 0,0);//bottom left corner
		  prismaticJointDef.enableLimit = true;
		  prismaticJointDef.lowerTranslation = -12;
		  prismaticJointDef.upperTranslation = 14;
		  prismaticJointDef.enableMotor = true;
		  prismaticJointDef.maxMotorForce = 10000000;
		 right= (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
	    }
	    {
	    	
			
		  b2PrismaticJointDef prismaticJointDef;
		  prismaticJointDef.bodyA = rightsep2;
		  prismaticJointDef.bodyB = vermov;
		  prismaticJointDef.collideConnected = false;
		  prismaticJointDef.localAxisA.Set(0,1);
		  prismaticJointDef.localAnchorA.Set( -1.2,0);//a little outside the bottom right corner
		  prismaticJointDef.localAnchorB.Set( -.5,0);//bottom left corner
		  prismaticJointDef.enableLimit = true;
		  prismaticJointDef.lowerTranslation = -12.0;
		  prismaticJointDef.upperTranslation = 3.0;
		  prismaticJointDef.enableMotor = true;
		  prismaticJointDef.maxMotorForce = 10000;
		  up= (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
	    }
		

	}
	
    

    void dominos_t::keyboard(unsigned char key)
    {
        switch (key)
		{
			case 'a':
			lflipper->ApplyAngularImpulse(2000.0f,true); 
			break;
			case 'd':
			rflipper->ApplyAngularImpulse(-2000.0f,true); 
			break;
			case 'l':
			launcher->ApplyLinearImpulse( b2Vec2(0,1100),launcher->GetWorldCenter() ,true);
			break;
			case 'q':
			right->SetMotorSpeed(2.0f);
			break;
			case 'w':
			right->SetMotorSpeed(-2.0f);
			break;
			case 'f':
			up->SetMotorSpeed(2.0f);
			break;
			case 'v':
			up->SetMotorSpeed(-2.0f);
			break;
			
	
		}
    }
    
    //~ void dominos_t::keyboardUp(unsigned char key)
    //~ {
        //~ switch (key) 
        //~ {
        //~ case 'a':
				//~ lflip->SetMotorSpeed(-3.0);
				//~ break;
        //~ }
    //~ }

  
  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
