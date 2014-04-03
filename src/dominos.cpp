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
			vs[0].Set(10.0f, 0.0f);
			vs[1].Set(8.0f, 40.0f);
			vs[2].Set(0.0f, 45.0f);
			vs[3].Set(-8.0f, 40.0f);
			vs[4].Set(-10.0f, 0.0f);

			b2ChainShape loop;
			loop.CreateLoop(vs, 5);
			b2FixtureDef fd;
			fd.shape = &loop;
			fd.density = 0.0f;
			ground->CreateFixture(&fd);
		}
		
		// Flippers
		{
			b2Vec2 p1(-2.0f, 10.0f), p2(2.0f, 10.0f);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			bd.position = p1;
			b2Body* leftFlipper = m_world->CreateBody(&bd);

			bd.position = p2;
			b2Body* rightFlipper = m_world->CreateBody(&bd);

			b2PolygonShape box;
			box.SetAsBox(1.75f, 0.1f);

			b2FixtureDef fd;
			fd.shape = &box;
			fd.density = 1.0f;

			leftFlipper->CreateFixture(&fd);
			rightFlipper->CreateFixture(&fd);

			b2RevoluteJointDef jd;
			jd.bodyA = ground;
			jd.localAnchorB.SetZero();
			jd.enableMotor = true;
			jd.maxMotorTorque = 1000.0f;
			jd.enableLimit = true;

			jd.motorSpeed = 0.0f;
			jd.localAnchorA = p1;
			jd.bodyB = leftFlipper;
			jd.lowerAngle = -30.0f * b2_pi / 180.0f;
			jd.upperAngle = 5.0f * b2_pi / 180.0f;
			m_leftJoint = (b2RevoluteJoint*)m_world->CreateJoint(&jd);

			jd.motorSpeed = 0.0f;
			jd.localAnchorA = p2;
			jd.bodyB = rightFlipper;
			jd.lowerAngle = -5.0f * b2_pi / 180.0f;
			jd.upperAngle = 30.0f * b2_pi / 180.0f;
			m_rightJoint = (b2RevoluteJoint*)m_world->CreateJoint(&jd);
		}

	}
	
    

    void dominos_t::keyboard(unsigned char key)
    {
        switch (key)
		{
		
			
	
		}
    }

  
  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
