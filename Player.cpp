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
    this->fleet = new Fleet(this);
    this->myNodes = new Node*[Model::getSelf()->numNodes];
    this->nodesOwned = 0;
}

Player::~Player()
{
    delete this->fleet;
}

bool Player::iOwnNode(Node *node)
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
    if(!iOwnNode(node))
    {
        if(node->owner != Model::getSelf()->nullPlayer) 
            node->owner->surrenderNode(node);
        myNodes[nodesOwned++] = node;
    }
    node->owner = this;
}

void Player::endTurn()
{
    fleet->refreshShips();
}

void Player::draw()
{
    fleet->draw();
}