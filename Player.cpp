//
//  Player.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Player.h"

Player::Player()
{
    this->shipArray = new Ship*[Model::getSelf()->numNodes];
    this->myNodes = new Node*[Model::getSelf()->numNodes];
    this->nodesOwned = 0;
}

Player::~Player()
{

}

bool Player::hasNode(Node *node)
{
    for(int i = 0; i < this->nodesOwned; i++)
    {
        if(myNodes[i] == node)
            return true;
    }
    return false;
}

void Player::surrenderNode(Node *node)
{
    bool found;
    for(int i = 0; i < this->nodesOwned; i++)
    {
        if(myNodes[i] == node)
            found = true;
        if(found)
            myNodes[i] = myNodes[i+1];
    }
    node->owner = Model::getSelf()->nullPlayer;
}

void Player::attackNode(Node *attackNode, Node *defendNode)
{
    
}

void Player::conquerNode(Node *node)
{
    if(!hasNode(node))
    {
        if(node->owner != Model::getSelf()->nullPlayer) 
            node->owner->surrenderNode(node);
        myNodes[nodesOwned++] = node;
    }
    node->owner = this;
}

void Player::endTurn()
{
    refreshShips();
}


bool Player::hasShip(Ship * s)
{
    for(int i = 0; i < numShips; i++)
    {
        if(shipArray[i] == s) return true;
    }
    return false;
}

void Player::addShip(Node * n)
{
    if(n->ship != Model::getSelf()->nullShip) return;
    shipArray[numShips] = new Ship(this);
    shipArray[numShips]->loc = n;
    n->ship = shipArray[numShips];
    numShips++;
}

void Player::refreshShips()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->done = false;
}

void Player::draw()
{
    for(int i = 0; i < numShips; i++)
        shipArray[i]->drawAtPosition();
}