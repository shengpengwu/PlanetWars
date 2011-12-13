#include "MiniGame.h"

MiniGame::MiniGame(Node * planet, Player * attacker, Player * defender)
{
    node = planet;
    p1 = attacker;
    p2 = defender;
	attackShip = new Ship();
	defendShip = new Ship();
    
    lanes = new Lane*[NUM_LANES];
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i] = new Lane(attackShip, defendShip);
    }
    selectedLane = 0;
    lanes[selectedLane]->setSelected(true);

	srand ( time(NULL) );
	counter = 0;	

}

void MiniGame::changeLane(int direction)
{
    if(direction == LEFT && selectedLane != 0)
        selectLane(selectedLane-1);
    else if(direction == RIGHT && selectedLane != 4)
        selectLane(selectedLane+1);
}

void MiniGame::selectLane(int lane)
{
    lanes[selectedLane]->setSelected(false);
    selectedLane = lane;
    lanes[selectedLane]->setSelected(true);
}

void MiniGame::addUnit(Player * p, int type) {
    Unit * u = p->deployUnit(node, type);
    if(u != Model::getSelf()->nullUnit)
    {
        lanes[selectedLane]->deployUnit(u, (p == p1));
    }
}

void MiniGame::update() {
    for(int i = 0; i < NUM_LANES; i++)
    {
        lanes[i]->tick();
    }

	generateUnits();

}


void MiniGame::drawGame() {
    //Draw Lanes
    for(int i = 0; i < NUM_LANES; i++)
    {
        glPushMatrix();
        glTranslated((double)((LANE_WIDTH*i)-(LANE_WIDTH*(int)(NUM_LANES/2))), 0.0, 0.0);
        lanes[i]->draw();
        glPopMatrix();
    }

	//glBegin(GL_QUADS);
 //   glVertex3f(-10, -1, 10);
	//glVertex3f(10, -1, 10);
	//glVertex3f(10, -1, 10);
	//glVertex3f(-10, -1, 10);
	//glEnd();

	//glBegin(GL_QUADS);
 //   glVertex3f(-10, -1, 60);
	//glVertex3f(10, -1, 60);
	//glVertex3f(10, -1, 70);
	//glVertex3f(-10, -1, 70);
	//glEnd();

}

void MiniGame::generateUnits() {

	int randLane;
	int randType;
	randLane = rand() % NUM_LANES;
	randType = rand() % 4;


	if(counter == 0) {
		Unit* temp = new Unit();

		switch(randType) {
		case 0:
			temp->setType(0);
			break;
		case 1:
			temp->setType(1);
			break;
		case 2:
			temp->setType(2);
			break;
		case 3:
			temp->setType(3);
			break;
		}
		lanes[randLane]->deployUnit(temp, false);
	}

	counter++;

	if(counter == 60) {
		counter = 0;
	}


}


