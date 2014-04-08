/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
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
#include <iostream>

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include "cs296_base.hpp"
//structure to store current surface velocity of a fixture
b2PrismaticJoint* up;
//b2Body* ball;

b2Body* darkhole;
b2Body* curve;

namespace cs296
{
int32 score;
bool killball;
bool killball2;
bool smallkaro1;
bool smallkaro2;
bool smallkaro3;
b2Body* ball;
b2Body* reflector;
b2Body* reflector2;
b2Body* reflector3;
b2Body* ballreleaser;
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance - why do we inherit the base_sim_t class?
    ///int scoremax=0;
   
class MyContactListener : public b2ContactListener{

public:
int i;
void MycontactListener(){i=0;}

void BeginContact(b2Contact* contact) {//check if fixture A was a ball
          
	void *yo= contact->GetFixtureA()->GetBody()->GetUserData();
	void *lo= contact->GetFixtureB()->GetBody()->GetUserData();
	int a=*((int*)(&yo));
	int b=*((int*)(&lo));
	if (*((int*)(&yo))==109){
		ball->SetLinearVelocity(b2Vec2(0,0));
		up->SetMotorSpeed(2.5f);
		std::cout<<"enter\n";
		for( long i=0; i<pow(10,8); i++){}
		}
	if(a==103 || a==104){
	score+=15;
	}
	if(a==401 || b==401){
	std::cout << "done\n";
	killball = true;	
	}
	if(a==402 || b==402){
	std::cout << "done\n";
	killball2 = true;	
	}

	if(a==108 || b==108){
	ball->SetLinearVelocity(b2Vec2(4,0));
	}
	if(a==301 || b==301){
	smallkaro1 = true;
	}
	if(a==302 || b==302){
	smallkaro2 = true;
	}
	if(a==303 || b==303){
	smallkaro3 = true;
	}
}
  
void EndContact(b2Contact* contact) {
  
	void *yo= contact->GetFixtureA()->GetBody()->GetUserData();
	void *lo= contact->GetFixtureB()->GetBody()->GetUserData();
	int a =*((int*)(&yo));
	int b=*((int*)(&lo));
	if (a==109){
		for( long i=0; i<pow(10,8); i++){}
		up->SetMotorSpeed(-2.5f);
		std::cout<<"exit\n";
		}
	if(a==108 || b==108){
	ball->SetLinearVelocity(b2Vec2(.2,.2));
	}
 }
};



  class dominos_t : public base_sim_t
  {
  public:
    dominos_t();
    MyContactListener myContactListenerInstance;
b2Body* lflipstatv;
b2Body* lflipstatd;
b2Body* rflipstatv;
b2Body* rflipstatd;
b2Body* lflipper;
b2Body* rflipper;
b2Body* rightsep1;
b2Body* rightsep2;
b2Body* launcher;

b2Body* stopper;
b2Body* temp2;
b2Body* temp1;
b2Body* temp;
b2Body* horz;
b2Body* hormov;
b2Body* vermov;
b2Body* triangle1;
b2Body* triangle2;
b2RevoluteJoint* lflip;
b2RevoluteJoint* rflip;
b2PrismaticJoint* right;

    void keyboard(unsigned char key);
    void keyboardUp(unsigned char key);
static base_sim_t* create()
{
return new dominos_t;
}


  };
}
#endif
