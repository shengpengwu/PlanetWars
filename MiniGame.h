#ifndef MINIGAME_H
#define MINIGAME_H

class Lane;
#include <math.h>
#include <iostream>
#include "Model.h"
#include "Player.h"
#include "Unit.h"
#include "Lane.h"

class MiniGame
{
public:
	MiniGame(Node * node, Player * attacker, Player * defender);
    
    Node * node;
    Player * p1; //Attacker
    Player * p2; //Defender

    Lane ** lanes;
    int selectedLane;
    
    void changeLane(int direction);
    void selectLane(int lane);
    void addUnit(Player * p, int type);
	void update();
    void drawGame();
};

#endif