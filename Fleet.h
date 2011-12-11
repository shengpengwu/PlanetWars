//
//  Fleet.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_FLEET
#define H_FLEET

class Player;
class Ship;
class Flagship;

#include <vector>
#include "Player.h"
#include "Flagship.h"
#include "Ship.h"

using namespace std;

class Fleet
{
public:
    Flagship * flagship;
    Player * owner;
    vector<Ship *> shipArray;
    int numShips;
    
    Fleet(Player * o);
    ~Fleet();
    
    bool hasShip(Ship * s);
    
    void addShip(Node * n, Player * o);
    void refreshShips();
    
    void draw();
};
#endif