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
  /** The is the constructor
* This is the documentation block for the constructor.
*/


  dominos_t::dominos_t()
    {	
//MyContactListener myContactListenerInstance;
  

m_world->SetContactListener(&myContactListenerInstance);

///Bumper balls the shrink and push the ball away
{
b2BodyDef bod,bod2,bod3;
bod.position = b2Vec2(0.0f,29.0f);

b2CircleShape circle;
	circle.m_p.Set(0,0);
	circle.m_radius = 1.0f;
b2FixtureDef fixtureDef;
fixtureDef.shape = &circle;
fixtureDef.density = 0.1;
fixtureDef.restitution = 5;

///Creating bumper ball 1
reflector = m_world->CreateBody(&bod);
int myint=301;
reflector->SetUserData((void*)myint);
reflector->CreateFixture(&fixtureDef);

///Creating bumper ball 2
bod2.position = b2Vec2(3.0f, 26.0f);
reflector2 = m_world->CreateBody(&bod2);
int myint2=301;
reflector2->SetUserData((void*)myint2);
reflector2->CreateFixture(&fixtureDef);

///Creating bumper ball 3
bod3.position = b2Vec2(3.0f, 32.0f);
reflector3 = m_world->CreateBody(&bod3);
int myint3=301;
reflector3->SetUserData((void*)myint3);
reflector3->CreateFixture(&fixtureDef);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Breaking object 1, an edge piece that is broken when it collides with the ball
{
b2BodyDef bod;

b2EdgeShape boundary;
boundary.Set(b2Vec2(-4,20),b2Vec2(-2,20));
breakingobj=m_world->CreateBody(&bod);
breakingobj->CreateFixture(&boundary,0.0f);
int myint = 500;
breakingobj->SetUserData((void*)myint);
}

///Breaking object 2, an edge piece that is broken when it collides with the ball
{
b2BodyDef bod;

b2EdgeShape boundary;
boundary.Set(b2Vec2(4,38),b2Vec2(6,38));
breakingobj2=m_world->CreateBody(&bod);
breakingobj2->CreateFixture(&boundary,0.0f);
int myint = 501;
breakingobj2->SetUserData((void*)myint);
}

///breaking object 3,an edge piece that is broken when it collides with the ball
{
b2BodyDef bod;

b2EdgeShape boundary;
boundary.Set(b2Vec2(4,18),b2Vec2(6,18));
breakingobj3=m_world->CreateBody(&bod);
breakingobj3->CreateFixture(&boundary,0.0f);
int myint = 502;
breakingobj3->SetUserData((void*)myint);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


///Darkhole, a transporter that transports the ball to top right corner when the ball collides with it
{
b2BodyDef bd;
darkhole=m_world->CreateBody(&bd);
b2EdgeShape boundary;

boundary.Set(b2Vec2(10.5,23.5),b2Vec2(13,21));
darkhole->CreateFixture(&boundary,0.0f);
int myint = 201;
darkhole->SetUserData((void*)myint);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

///Ball releaser, the place from which the ball is released when the ball enters the Darkhole
{
b2BodyDef bd;
ballreleaser=m_world->CreateBody(&bd);
b2EdgeShape boundary;

boundary.Set(b2Vec2(-15,40),b2Vec2(-13,42));
ballreleaser->CreateFixture(&boundary,0.0f);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Outer boundary of the entire pinball simulation
{
b2BodyDef bd;
curve=m_world->CreateBody(&bd);
b2EdgeShape boundary;

boundary.Set(b2Vec2(6.3,42),b2Vec2(-15,42));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-15,42),b2Vec2(-15,0));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(12,0),b2Vec2(15,0));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(15,0),b2Vec2(15,25));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(15,25),b2Vec2(14.8,27));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(14.8,27),b2Vec2(14.5,29));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(14.5,29),b2Vec2(14.1,31));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(14.1,31),b2Vec2(13.4,33));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(13.4,33),b2Vec2(12.4,35));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(12.4,35),b2Vec2(11.0,37));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(11.0,37),b2Vec2(9.4,39));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(9.4,39),b2Vec2(7.5,41));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(7.5,41),b2Vec2(6.3,42));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-15,40),b2Vec2(-13,38));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-13,42),b2Vec2(-11,40));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(13,26),b2Vec2(7,20));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(13,21),b2Vec2(10,18));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-15,28),b2Vec2(-7,24));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-10,21),b2Vec2(-10,17));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-10,21),b2Vec2(-7,19.5));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-15,-4.8),b2Vec2(15,-4.8));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(15,-4.8),b2Vec2(15,0));
curve->CreateFixture(&boundary,0.0f);
boundary.Set(b2Vec2(-15,-4.8),b2Vec2(-15,0));
curve->CreateFixture(&boundary,0.0f);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

///Spinner, an obstacle with spins rapidy on colliding with file
{
b2Body* body;
{
b2BodyDef bDef;
bDef.type = b2_dynamicBody;
bDef.position = b2Vec2(-10, 30);
body = m_world->CreateBody(&bDef);

b2PolygonShape shape;
const float32 density = 10;

shape.SetAsBox(2, 0.01);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 2, b2Vec2(0,0), 0);
body->CreateFixture(&shape, density);

shape.SetAsBox(2, 0.01, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 2, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);
int myint=101;
body->SetUserData((void*)myint);

}
///The hinge on with the spinner rotates about
b2Body* b4;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;
bd.position.Set(-10,30);
b4 = m_world->CreateBody(&bd);
b4->CreateFixture(&shape, 3.0f);
}

b2RevoluteJointDef jd;
b2Vec2 anchor;
anchor.Set(-10,30);
jd.Initialize(body, b4, anchor);
m_world->CreateJoint(&jd);
}


/// Spinner 2, an obstacle with spins rapidy on colliding with file
{
b2Body* body;
{
b2BodyDef bDef;
bDef.type = b2_dynamicBody;
bDef.position = b2Vec2(-7.5, 38);
body = m_world->CreateBody(&bDef);

b2PolygonShape shape;
const float32 density = 2;

shape.SetAsBox(2, 0.01);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 2, b2Vec2(0,0), 0);
body->CreateFixture(&shape, density);

int myint=101;
body->SetUserData((void*)myint);

}
///The hinge on with the spinner rotates about

b2Body* b4;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;
bd.position.Set(-7.5, 38);
b4 = m_world->CreateBody(&bd);
b4->CreateFixture(&shape, 3.0f);
}

b2RevoluteJointDef jd;
b2Vec2 anchor;
anchor.Set(-7.5f, 38.0f);
jd.Initialize(body, b4, anchor);
m_world->CreateJoint(&jd);
}

///Small Spinner 1, the smaller spinners inside the left tube
{
b2Body* body;
{
b2BodyDef bDef;
bDef.type = b2_dynamicBody;
bDef.position = b2Vec2(-13, 24);
body = m_world->CreateBody(&bDef);

b2PolygonShape shape;
const float32 density = 4;

shape.SetAsBox(1, 0.01);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 1, b2Vec2(0,0), 0);
body->CreateFixture(&shape, density);

shape.SetAsBox(1, 0.01, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 1, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);
int myint=90;
body->SetUserData((void*)myint);
}
///The hinge on with the spinner rotates about
b2Body* b4;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;
bd.position.Set(-13, 24);
b4 = m_world->CreateBody(&bd);
b4->CreateFixture(&shape, 3.0f);
}

b2RevoluteJointDef jd;
b2Vec2 anchor;
anchor.Set(-13.0f, 24.0f);
jd.Initialize(body, b4, anchor);
m_world->CreateJoint(&jd);
}

///Small Spinner 2, the smaller spinners inside the left tube
{
b2Body* body;
{
b2BodyDef bDef;
bDef.type = b2_dynamicBody;
bDef.position = b2Vec2(-12, 19);
body = m_world->CreateBody(&bDef);

b2PolygonShape shape;
const float32 density = 4;

shape.SetAsBox(1, 0.01);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 1, b2Vec2(0,0), 0);
body->CreateFixture(&shape, density);

shape.SetAsBox(1, 0.01, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);

shape.SetAsBox(0.01, 1, b2Vec2(0,0), 0.8);
body->CreateFixture(&shape, density);
int myint=90;
body->SetUserData((void*)myint);
}
///The hinge on with the spinner rotates about
b2Body* b4;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;
bd.position.Set(-12, 19);
b4 = m_world->CreateBody(&bd);
b4->CreateFixture(&shape, 3.0f);
}

b2RevoluteJointDef jd;
b2Vec2 anchor;
anchor.Set(-12.0f, 19.0f);
jd.Initialize(body, b4, anchor);
m_world->CreateJoint(&jd);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Vertical support for the left flipper 
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Left trianglular bumper
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
///Right triangle bumper
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Top right seperator , makes way for new ball
{

b2PolygonShape boxShape;
boxShape.SetAsBox(0.2,8);
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
///Bottom right seperator , seperates launcher from main body
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



//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Vertical ball lifter
{

b2PolygonShape boxShape;
boxShape.SetAsBox(0.05,0.70);
b2FixtureDef boxFixtureDef;
boxFixtureDef.shape = &boxShape;	
boxFixtureDef.restitution=0;
b2BodyDef bd;


bd.type = b2_dynamicBody;
bd.angle = 80* DEGTORAD;
bd.position.Set(12.40f, 1.1f);
vermov= m_world->CreateBody(&bd);
int myint=109;
vermov->SetUserData((void*)myint);

vermov->CreateFixture(&boxFixtureDef);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Stopper to stop launcher from flying off
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Launcher to launch ball
{

b2PolygonShape boxShape;
boxShape.SetAsBox(0.8,2);
b2FixtureDef boxFixtureDef;
boxFixtureDef.shape = &boxShape;
boxFixtureDef.density=5.0f;	
b2BodyDef bd;
bd.type = b2_dynamicBody;
bd.angle = 0* DEGTORAD;
bd.position.Set(13.8f, 2.0f);
launcher= m_world->CreateBody(&bd);
int myint=111;
launcher->SetUserData((void*)myint);
launcher->CreateFixture(&boxFixtureDef);

}
///Diagnol support for the left flipper
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


///Diagnol support for right flipper
{
b2PolygonShape boxShape;
boxShape.SetAsBox(4.0,0.4);
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


///Left guard so that ball doesnt drop
{
b2PolygonShape boxShape;
boxShape.SetAsBox(2.2,0.2);
b2FixtureDef boxFixtureDef;
boxFixtureDef.shape = &boxShape;	
b2BodyDef bd;
bd.angle = -40* DEGTORAD;
bd.position.Set(-13.5f, 16.0f);
temp1 = m_world->CreateBody(&bd);
int myint=116;
temp1->SetUserData((void*)myint);
temp1->CreateFixture(&boxFixtureDef);



}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///Left flipper
{
b2PolygonShape boxShape;
boxShape.SetAsBox(2.8,0.4);
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
///Right flipper
{
b2PolygonShape boxShape;
boxShape.SetAsBox(2.8,0.4);
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
///////////////////////////////////////////////////////////////////
///Ball
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
///////////////////////////////////////////////////////////////////
///Chain, the conveyor belt system that restores ball to new game position
b2BodyDef boda;
boda.position = b2Vec2(-12.3f,-1.0f);

///Gear 1 , the leftmost gear used in the conveyor belt
b2Body* gear1;
b2CircleShape circle;
	circle.m_p.Set(0,0);
	circle.m_radius = 2.0f;
b2FixtureDef fixtureDef;
fixtureDef.shape = &circle;
fixtureDef.density = 5;
fixtureDef.restitution = 0;
fixtureDef.friction=1000.0f;
boda.type=b2_dynamicBody;
gear1 = m_world->CreateBody(&boda);
int myint=601;
gear1->SetUserData((void*)myint);
gear1->CreateFixture(&fixtureDef);

{
b2Body* b6;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;

bd.position.Set(-12.3f,-1.0f);
b6 = m_world->CreateBody(&bd);
b6->CreateFixture(&shape, 3.0f);
}

b2RevoluteJointDef jd;
jd.enableMotor = true;
jd.motorSpeed = 3;
jd.maxMotorTorque = 100.0f;
b2Vec2 anchor;
anchor.Set(-12.3f,-1.0f);
jd.Initialize(gear1, b6, anchor);
m_world->CreateJoint(&jd);
b2BodyDef bodb;
bodb.type=b2_dynamicBody;
bodb.position = b2Vec2(8.6f,-1.0f);

///Gear 2 , the middle gear used in the conveyor belt
b2Body* gear2;

	circle.m_p.Set(0,0);
	circle.m_radius = 2.0f;


gear2 = m_world->CreateBody(&bodb);


gear2->CreateFixture(&fixtureDef);
b2BodyDef bodc;
b2Body* b7;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;

bd.position.Set(8.6f,-1.0f);
b7= m_world->CreateBody(&bd);
b7->CreateFixture(&shape, 3.0f);
}


anchor.Set(8.6f,-1.0f);
jd.Initialize(gear2, b7, anchor);
m_world->CreateJoint(&jd);
bodc.position = b2Vec2(-3.8f,-1.0f);
bodc.type=b2_dynamicBody;

 gear2->ApplyAngularImpulse(-3000.0f,true);

///Gear 3 , the rightmost gear used in the conveyor belt
b2Body* gear3;
circle.m_radius = 2.0f;
gear3 = m_world->CreateBody(&bodc);


gear3->CreateFixture(&fixtureDef);
b2Body* b8;
{
b2PolygonShape shape;
shape.SetAsBox(0.025f, 0.025f);

b2BodyDef bd;

bd.position.Set(-3.8f,-1.0f);
b8= m_world->CreateBody(&bd);
b8->CreateFixture(&shape, 3.0f);
}


//gear3->ApplyAngularImpulse(-3000.0f,true);
anchor.Set(-3.8f,-1.0f);
jd.Initialize(gear3, b8, anchor);
m_world->CreateJoint(&jd);
gear3->ApplyAngularImpulse(-3000.0f,true);
}
	b2Vec2 vs[100];

	///Create the main chain
b2FixtureDef chainfd;

b2PolygonShape chainshape;
float wid=0.5,heig=0.2;
chainshape.SetAsBox(wid, heig);
chainfd.shape = &chainshape;
chainfd.density=1.5f;
chainfd.friction=1000.0f;
chainfd.restitution=0;
b2BodyDef chainDef;
chainDef.type = b2_dynamicBody;
///Top horizontal part of the chain
for (int i = 0; i < 23; ++i)
{
vs[i].Set(-12.5f+(2*wid)*i,1.0f);
chainDef.position.Set(-12.0f+(2*wid)*i,1.0f);
conveyer[i]=m_world->CreateBody(&chainDef);
conveyer[i]->CreateFixture(&chainfd);
}

///Rightmost vertical part of the chain 
chainshape.SetAsBox(heig, wid);
 for (int i = 0; i < 4; ++i)
{
vs[i+23].Set(10.5f,1.0f-i*(2*wid));
chainDef.position.Set(10.5f,0.5f-i*(2*wid));
conveyer[i+23]=m_world->CreateBody(&chainDef);
conveyer[i+23]->CreateFixture(&chainfd);
}

///Lower horizontal part of the chain
chainshape.SetAsBox(wid, heig);
 for (int i = 0; i < 23; ++i)
{
vs[27+i].Set(10.0f-(2*wid)*i,-3.0f);
chainDef.position.Set(10.0f-(2*wid)*i,-3.0f);
conveyer[i+27]=m_world->CreateBody(&chainDef);
conveyer[i+27]->CreateFixture(&chainfd);	
}


///Leftmost vertical part of the chain
chainshape.SetAsBox(heig, wid);
 for (int i = 0; i < 4; ++i)
{
    vs[50+i].Set(-12.5f,-3.0f+(2*wid)*i);
chainDef.position.Set(-12.5f,-2.5f+(2*wid)*i);
conveyer[i+50] = m_world->CreateBody(&chainDef);
conveyer[i+50]->CreateFixture(&chainfd);
}
///Setting ids to all chain links
for(int j=0; j<54; j++){
	int myint=99;
    conveyer[j]->SetUserData((void*)myint);
}

///Adding Revolute joint between chain units
b2RevoluteJointDef jointDef3;
 for(int i=1;i<54;i++)
{
jointDef3.Initialize(conveyer[i-1], conveyer[i],vs[i]);
m_world->CreateJoint(&jointDef3);
}

///Adding Revolute joint between last and first chain unit
jointDef3.Initialize(conveyer[0], conveyer[53],vs[0]);
m_world->CreateJoint(&jointDef3);

//--------------------------------------------------------------------------------------------------------------------------------------------
///Revolute joint for left flipper 
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
revoluteJointDef.upperAngle = 20 * DEGTORAD;
revoluteJointDef.enableMotor = true;
revoluteJointDef.motorSpeed = 3;
revoluteJointDef.maxMotorTorque = 100.0f;
//revoluteJointDef.motorSpeed = -90 * DEGTORAD;//90 degrees per second
lflip = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
}
///Revolute joint for right flipper 
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
revoluteJointDef.upperAngle = 20 * DEGTORAD;
revoluteJointDef.enableMotor = true;
revoluteJointDef.motorSpeed = -3;
revoluteJointDef.maxMotorTorque = 100.0f;
//revoluteJointDef.motorSpeed = -90 * DEGTORAD;//90 degrees per second
rflip = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
}

///Prismatic joint between vertical ball lifter and the right seperator
{


b2PrismaticJointDef prismaticJointDef;
prismaticJointDef.bodyA = rightsep2;
prismaticJointDef.bodyB = vermov;
prismaticJointDef.collideConnected = false;
prismaticJointDef.localAxisA.Set(0,1);
prismaticJointDef.localAnchorA.Set( -1.2,0);//a little outside the bottom right corner
prismaticJointDef.localAnchorB.Set( -.5,0);//bottom left corner
prismaticJointDef.enableLimit = true;
prismaticJointDef.lowerTranslation = -3.2;
prismaticJointDef.upperTranslation = 3.2;
prismaticJointDef.enableMotor = true;
prismaticJointDef.maxMotorForce = 10000;
up= (b2PrismaticJoint*)m_world->CreateJoint( &prismaticJointDef );
}


}

    

    void dominos_t::keyboard(unsigned char key)
    {
        switch (key)
{
case 'a':///Keypress a for left flipper
lflipper->ApplyAngularImpulse(2000.0f,true);
break;
case 'd':///Keypress d for right flipper
rflipper->ApplyAngularImpulse(-2000.0f,true);
break;
case 'l': ///Keypress l for launcher
launcher->ApplyLinearImpulse( b2Vec2(0,1100),launcher->GetWorldCenter() ,true);
break;


case 'f':///Keypress f to move the verical ball lifter up
up->SetMotorSpeed(2.5f);
break;
case 'v':///Keypress v to move the verical ball lifter down
up->SetMotorSpeed(-2.5f);
break;


}
    }
    
  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

