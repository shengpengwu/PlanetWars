//
//  Fleet.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Fleet.h"
#include "Model.h"

Fleet::Fleet(Player * o)
{
    owner = o;
    this->flagship = new Flagship();
    numShips = 0;
}

Fleet::~Fleet()
{
    delete this->flagship;
}

bool Fleet::hasShip(Ship * s)
{
    for(int i = 0; i < numShips; i++)
    {
        if(shipArray[i] == s) return true;
    }
    return false;
}

void Fleet::addShip(Node * n, Player * o)
{
    if(n->ship != Model::getSelf()->nullShip) return;
    shipArray.resize(shipArray.size()+1);
    shipArray[shipArray.size()-1] = new Ship(o);
    shipArray[shipArray.size()-1]->loc = n;
    n->ship = shipArray[shipArray.size()-1];
    numShips++;
}

void Fleet::refreshShips()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->done = false;
}

void Fleet::draw()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->drawAtPosition();
}