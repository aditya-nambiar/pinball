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

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

//structure to store current surface velocity of a fixture

namespace cs296
{
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
  class dominos_t : public base_sim_t
  {
  public:
    dominos_t();
      
    void keyboard(unsigned char key);
    //void keyboardUp(unsigned char key);
	static base_sim_t* create()
	{
		return new dominos_t;
	}
	
	b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;	
	b2Body* m_backarm1;
	b2Body* m_backarm2;
	b2Body* m_frontarm1;
	b2Body* m_bpick1;
	b2Body* m_bpick2;
	b2Body* test_box;
	b2Body* test_ball;
	float32 m_hz;
	float32 m_zeta;
	float32 m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2RevoluteJoint* m_mjoint1;
	b2RevoluteJoint* m_mjoint2;
	b2RevoluteJoint* m_mjoint3;
	b2RevoluteJoint* m_mjoint4;
	b2RevoluteJoint* m_mjoint5;
  };
}
  
#endif
