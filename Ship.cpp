//
//  Ship.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Ship.h"
#include "Model.h"
bool Ship::compiled = false;
GLuint Ship::displayList;

Ship::Ship(Player * o)
{
    this->shipType = SHIP_TYPE_GENERIC;
    layer = .25;
    owner = o;
    if(!Ship::compiled) compileDL();
}

Ship::~Ship()
{
    
}

void Ship::compileDL()
{
    //Sample compilation of a simple sphere 
    if(Ship::compiled) return;
    displayList = glGenLists(1);
    glNewList(Ship::displayList, GL_COMPILE);
    

    //DRAW SHIP HERE
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glVertex3f(-.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3f(-.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glVertex3f(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(.5*SHIP_SIZE, layer, -.5*SHIP_SIZE);
    glVertex3d(SHIP_SIZE, layer, 0);
    glVertex3d(.5*SHIP_SIZE, layer, .5*SHIP_SIZE);
    glEnd();
    
    glPopMatrix();
    
    glEndList();
    Ship::compiled = true;
}

void Ship::draw()
{
    if(!Ship::compiled) return;   
    if(loc->selected) setColor(0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0);
    else setColor(0.4, 0.4, 0.4, 1.0, 1.0, 1.0, 1.0);
    setGLColor();
    glCallList(Ship::displayList);
}

void Ship::drawAtPosition()
{
    if(loc == Model::getSelf()->nullNode)
    {
        draw();
        return;
    }
    glPushMatrix();
    glTranslated(loc->column*COL_SPACING, 0, loc->row*ROW_SPACING);
    draw();
    glPopMatrix();
}

void Ship::moveToNode(Node *newLoc)
{
    if(done) return;
    if(loc->isNeighborOf(newLoc))
    {
        loc->ship = Model::getSelf()->nullShip;
        loc = newLoc;
        loc->owner = this->owner;
        loc->ship = this;
        done = true;
    }
}

Unit * Ship::deployUnit(int type)
{
    
    return Model::getSelf()->nullUnit;
}
