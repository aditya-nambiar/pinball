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
			vs[0].Set(15.0f, -2.0f);
			vs[1].Set(15.0f, 42.0f);
			vs[2].Set(-15.0f, 42.0f);
			vs[3].Set(-15.0f, -2.0f);
			
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
		// {
	// 		b2PolygonShape shp;
	// 		b2Vec2 vertices[2];
	// 		vertices[0].Set(13.0f, -2.0f);
	// 		vertices[1].Set(13.0f,10.5f);
	// 		
	// 		
	// 		
	// 		shp.Set(vertices, 2);
	// 
	// 		b2FixtureDef fd;
	// 		fd.shape = &shp;
	// 		fd.density = 5.0f;
	// 			
	// 		b2BodyDef bd;
	// 		bd.position.Set(12.0f, 10.0f);
	// 		rightsep = m_world->CreateBody(&bd);
	// 		rightsep->CreateFixture(&fd);
	// 	}
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
			vertices[0].Set(0.0f, 6.5f);
			vertices[1].Set(-0.5f,6.5f);
			vertices[2].Set(-0.5f, 0.5f);
			vertices[3].Set(-0.0f, 0.0f);
			
			
			shp.Set(vertices, 4);

			b2FixtureDef fd;
			fd.shape = &shp;
			fd.density = 5.0f;
				
			b2BodyDef bd;
			bd.position.Set(12.0f, 10.0f);
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
			boxShape.SetAsBox(2.5,0.2);
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
			boxShape.SetAsBox(2.5,0.2);
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
		//the motorised joint
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = lflipstatd;
		revoluteJointDef.bodyB = lflipper;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorB.Set(-2.5,0);
	
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
		revoluteJointDef.localAnchorB.Set(2.5,0);
	
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
