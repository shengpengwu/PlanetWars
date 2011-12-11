//
//  Player.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_PLAYER
#define H_PLAYER

class Fleet;
#include "Model.h"
#include "Fleet.h"
#include "Node.h"

class Player
{
public:    
    Fleet * fleet;
    Node ** myNodes;
    Node * home;
    int nodesOwned;
    
    bool iOwnNode(Node *node);
    void surrenderNode(Node *node);
    void attackNode(Node *attackNode, Node *defendNode);
    void conquerNode(Node *node);
    void endTurn();
    
    int dark_resources;
    
    Player();
    ~Player();
    
    void draw();
};

#endif