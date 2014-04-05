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
	int32 score;
	/*
	 ground            100
     lflipstatv		   102
	 lflipstatd;	   112
	 rflipstatv;       113
	 rflipstatd;       114
	 lflipper;         120
	 rflipper;         117
	 rightsep1;        105
	 rightsep2;        106
	 launcher;         111
	 ball;             118
	 stopper;          110
     temp2;            
	 temp1;            116
	 temp;             115
	 horz;             108
	 hormov;           107
	 vermov;           109
	 triangle1;        103
	 triangle2;        104
	
	*/
  dominos_t::dominos_t()
    {		
		//MyContactListener myContactListenerInstance;
  
		  //in FooTest constructor
		m_world->SetContactListener(&myContactListenerInstance);
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
			int myint=100;
			ground->SetUserData((void*)myint);
			ground->CreateFixture(&fd);
		}
		
		//Spinner
		{
			b2Body* body;
		{
		b2BodyDef bDef;
		bDef.type = b2_dynamicBody;
		bDef.position = b2Vec2(0, 15);
		body = m_world->CreateBody(&bDef);

		b2PolygonShape shape;
		const float32 density = 10;

		shape.SetAsBox(3, 0.01);
		body->CreateFixture(&shape, density);

		shape.SetAsBox(0.01, 3, b2Vec2(0,0), 0);
		body->CreateFixture(&shape, density);

		shape.SetAsBox(3, 0.01, b2Vec2(0,0), 0.8);
		body->CreateFixture(&shape, density);

		shape.SetAsBox(0.01, 3, b2Vec2(0,0), 0.8);
		body->CreateFixture(&shape, density);
		int myint=101;
		body->SetUserData((void*)myint);

		}

		b2Body* b4;
		      {
			b2PolygonShape shape;
			shape.SetAsBox(0.025f, 0.025f);
	  
			b2BodyDef bd;
			bd.position.Set(0, 15);
			b4 = m_world->CreateBody(&bd);
			b4->CreateFixture(&shape, 3.0f);
		      }
	
		      b2RevoluteJointDef jd;
		      b2Vec2 anchor;
		      anchor.Set(0.0f, 15.0f);
		      jd.Initialize(body, b4, anchor);
		      m_world->CreateJoint(&jd);
		}
		//vertical part of left thing not in touch with flipper
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
			bd.position.Set(-12.0f, 9.0f);
			lflipstatv = m_world->CreateBody(&bd);
			int myint=102;
			lflipstatv->SetUserData((void*)myint);
			lflipstatv->CreateFixture(&fd);
		}
		//left triangle
		{
			b2PolygonShape shp;
			b2Vec2 vertices[3];
			vertices[0].Set(0.0f, 0.0f);
			vertices[1].Set(-3.5f,7.0f);
			vertices[2].Set(-3.5f, 2.0f);
			
			
			shp.Set(vertices, 3);

			b2FixtureDef fd;
			fd.shape = &shp;
			fd.density = 5.0f;
			fd.restitution=1.8;
			b2BodyDef bd;
		
			bd.position.Set(-6.0f, 9.0f);
			triangle1 = m_world->CreateBody(&bd);
			int myint=103;
			triangle1->SetUserData((void*)myint);
			triangle1->CreateFixture(&fd);
		}
		//right triangle
		{
			b2PolygonShape shp;
			b2Vec2 vertices[3];
			vertices[0].Set(0.0f, 0.0f);
			vertices[1].Set(3.5f, 2.0f);
			vertices[2].Set(3.5f, 7.0f);
			
			
			shp.Set(vertices, 3);

			b2FixtureDef fd;
			fd.shape = &shp;
			fd.density = 5.0f;
			fd.restitution=1.8;
			b2BodyDef bd;
			bd.position.Set(6.0f, 9.0f);
			triangle2 = m_world->CreateBody(&bd);
			int myint=104;
			triangle2->SetUserData((void*)myint);
			triangle2->CreateFixture(&fd);
		}
		//top right seperator , makes way for new ball
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,9);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.0f, 18.0f);
				rightsep1= m_world->CreateBody(&bd);
				int myint=105;
				rightsep1->SetUserData((void*)myint);
				rightsep1->CreateFixture(&boxFixtureDef);
			
		}
		//bottom right seperator , seperates launcher from main body
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,3.1);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.0f, 3.1f);
				rightsep2= m_world->CreateBody(&bd);
				int myint=106;
				rightsep2->SetUserData((void*)myint);
				rightsep2->CreateFixture(&boxFixtureDef);
			
		}
		//point that moves on the horizontal plank
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,0.25);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(-14.5f, 1.8f);
				hormov= m_world->CreateBody(&bd);
				int myint=107;
				hormov->SetUserData((void*)myint);
				hormov->CreateFixture(&boxFixtureDef);
			
		}
		//horizontal plank on the bottom 
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,12.5);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 90* DEGTORAD;
				bd.position.Set(-2.0f, 1.0f);
				horz= m_world->CreateBody(&bd);
				int myint=108;
				horz->SetUserData((void*)myint);
				horz->CreateFixture(&boxFixtureDef);
			
		}
		//tilted plank to lift ball back to new position--------id 111
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,0.95);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;	
				boxFixtureDef.restitution=0;
				b2BodyDef bd;
				
				//void * tp= &myint;
                //vermov->SetUserData(this);
				bd.type = b2_dynamicBody;
				bd.angle = 80* DEGTORAD;
				bd.position.Set(11.70f, 0.5f);
				vermov= m_world->CreateBody(&bd);
				int myint=109;
				vermov->SetUserData((void*)myint);
				
				vermov->CreateFixture(&boxFixtureDef);
			
		}
		//stopper to stop launcher from flying of
		{
			
				b2PolygonShape boxShape;
				boxShape.SetAsBox(0.2,0.2);
			    b2FixtureDef boxFixtureDef;
			    boxFixtureDef.shape = &boxShape;			
				b2BodyDef bd;
				bd.angle = 0* DEGTORAD;
				bd.position.Set(13.2f, 5.5f);
				stopper= m_world->CreateBody(&bd);
				int myint=110;
				stopper->SetUserData((void*)myint);
				stopper->CreateFixture(&boxFixtureDef);
			
		}
		//launcher to launch ball
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
				int myint=111;
				launcher->SetUserData((void*)myint);
				launcher->CreateFixture(&boxFixtureDef);
			
		}
		//diagnol part of left thing in touch with flipper
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.5,0.4);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -20* DEGTORAD;
			bd.position.Set(-9.5f, 8.0f);
			lflipstatd = m_world->CreateBody(&bd);
			int myint=112;
			lflipstatd->SetUserData((void*)myint);
			lflipstatd->CreateFixture(&boxFixtureDef);
		}
		//vertical part of right thing not in touch with flipper
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
			bd.position.Set(12.0f, 8.9f);
			rflipstatv = m_world->CreateBody(&bd);
			int myint=113;
			rflipstatv->SetUserData((void*)myint);
			rflipstatv->CreateFixture(&fd);
		}
		//diagnol part of right thing in touch with flipper
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.5,0.4);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = 20* DEGTORAD;
			bd.position.Set(9.0f, 8.0f);
			rflipstatd = m_world->CreateBody(&bd);
			int myint=114;
			rflipstatd->SetUserData((void*)myint);
			rflipstatd->CreateFixture(&boxFixtureDef);
		}
		//right top so that ball comes to main area
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(4.5,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -60* DEGTORAD;
			bd.position.Set(13.0f, 36.0f);
			temp = m_world->CreateBody(&bd);
			int myint=115;
			temp->SetUserData((void*)myint);
			temp->CreateFixture(&boxFixtureDef);
		}
		//left guard so that ball doesnt drop
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(2.6,0.2);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;			
			b2BodyDef bd;
			bd.angle = -60* DEGTORAD;
			bd.position.Set(-13.5f, 18.0f);
			temp1 = m_world->CreateBody(&bd);
			int myint=116;
			temp1->SetUserData((void*)myint);
			temp1->CreateFixture(&boxFixtureDef);
			
			
			
		}
		// left flipper
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.0,0.4);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;
					
			b2BodyDef bd;
			boxFixtureDef.density=5.0f;	
			bd.type = b2_dynamicBody;
			bd.angle = -30* DEGTORAD;
			bd.position.Set(-3.0f, 7.0f);
			lflipper = m_world->CreateBody(&bd);
			int myint=120;
			lflipper->SetUserData((void*)myint);
			lflipper->CreateFixture(&boxFixtureDef);
		}
		//right flipper
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(3.0,0.4);
		    b2FixtureDef boxFixtureDef;
		    boxFixtureDef.shape = &boxShape;	
			boxFixtureDef.density=5.0f;			
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.angle = 30* DEGTORAD;
			bd.position.Set(3.0f, 7.0f);
			rflipper = m_world->CreateBody(&bd);
			int myint=117;
			rflipper->SetUserData((void*)myint);
			rflipper->CreateFixture(&boxFixtureDef);
		}
		//ball
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
			ball->SetUserData(this);
			int myint=118;
			ball->SetUserData((void*)myint);
		    ball->CreateFixture(&fixtureDef);
		}
		//left flipper joint
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
		//right flipper joint
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
		//prismatic joint b/w horizontal bar and point
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
		//prismatic joint b/w tilt and right seperator
	    {
	    	
			
		  b2PrismaticJointDef prismaticJointDef;
		  prismaticJointDef.bodyA = rightsep2;
		  prismaticJointDef.bodyB = vermov;
		  prismaticJointDef.collideConnected = false;
		  prismaticJointDef.localAxisA.Set(0,1);
		  prismaticJointDef.localAnchorA.Set( -1.2,0);//a little outside the bottom right corner
		  prismaticJointDef.localAnchorB.Set( -.5,0);//bottom left corner
		  prismaticJointDef.enableLimit = true;
		  prismaticJointDef.lowerTranslation = -13.0;
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
			right->SetMotorSpeed(4.0f);
			break;
			case 'w':
			right->SetMotorSpeed(-4.0f);
			break;
			case 'f':
			up->SetMotorSpeed(2.5f);
			break;
			case 'v':
			up->SetMotorSpeed(-2.5f);
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
