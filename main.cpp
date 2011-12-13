//
//  main.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//


//#ifndef _WIN32
    //#include <OpenGL/OpenGL.h>
   //#include <GLUT/GLUT.h>
//#elif
    #include <GL\freeglut.h>
    #include <GL\GL.h>
//#endif


#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "Model.h"

//MODEL ACCESSORS:: DO NOT ABUSE THESE!!!!
Model * model;
Player ** playerArray;
Map * map;
Node ** nodeArray;
Selector * selector;
Menu * menu;
MiniGame * game;

/////////
//GAME LOGIC FUNCTIONS
/////////
void initGame(int numPlayers, int numNodes)
{    
    //Make sure each player can have a starting node
    if(numNodes < numPlayers+1)
        throw new std::string("LESS NODES THAN PLAYERS");

    //Initialize Game Objects and assign them to main-accessible pointers
    nodeArray =  model->setNumNodes(numNodes);
    playerArray = model->setNumPlayers(numPlayers);
    selector = model->setSelector();
    map = model->setMap();
    game = model->setMiniGame(nodeArray[0], playerArray[0], playerArray[1]);
    menu = model->setMenu();
}

/////////
//GAME STATES
/////////

void pregame(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(model->camCenterX+model->mouseX*-10, model->zoom, model->camCenterY+model->mouseY*10, 
              model->camCenterX, 0, model->camCenterY, 
              0, 0, -1); 
    
	menu->setMenu(TITLE);
	glPushMatrix();
	glScalef(5.0, 1, 5.0);
	menu->draw();
	glPopMatrix();
}

void gameplay(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(model->camCenterX+model->mouseX*-10, model->zoom, model->camCenterY+model->mouseY*10,
              model->camCenterX, 0, model->camCenterY,
              0, 0, -1); 
    
	// Draw different aspects of the game during gameplay:
    if(model->finishTurn)
    {
        map->tick();
        for(int i = 0; i <DEFAULT_NUM_PLAYERS; i++)
            playerArray[i]->endTurn();
        model->finishTurn = false;
    }
	map->draw();
    for(int i = 0; i <DEFAULT_NUM_PLAYERS; i++)
        playerArray[i]->draw();
}

void minigame() { 
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 350.0, 800.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    game->update();
	game->drawGame();
}


/////////
//GL FUNCTIONS
/////////

//Called when mouse dragged (sets mouseX and mouseY from -1 to 1)
void PassiveMotionFunc(int x, int y)
{
    model->mouseX = (-2.0*x/model->width)+1.0;
	model->mouseY = (2.0*y/model->height)-1.0;
}

void MouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
        map->selectSelected();
}

void DisplayFunc()
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Main Viewport
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0 , ((float) model->width) / ((float) model->height), 1.0f , 2000.0);
	glViewport(0 , 0 , model->width, model->height);
    
    //model->state = MINIGAME;
	switch(model->state){
        case TITLE:
            pregame();
            break;
        case GAMEPLAY:
            gameplay();
            break;
        case MINIGAME:
            minigame();
            break;
	}
    
	glutSwapBuffers();
}

void IdleFunc()
{
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    //SHOULD PUT KEY SWITCH STATEMENTS IN INDIVIDUAL STATE CASES
    //(ie each state has its own set of keystrokes)
    switch(model->state){
        case TITLE:
            break;
        case GAMEPLAY:
            break;
        case MINIGAME:
            break;
	}
    
    switch(key)
    {
        case 27: // Press the ESC key to exit the game immediately.
            exit(0);
            break;
        case 'p':
            //Menu::setMenu(META);
            break;
            // For state testing:
        case '1':
            model->state = GAMEPLAY;
            break;
        case '0':
            model->state = TITLE;
            break;
        case '2':
            model->state = MINIGAME;
            break;
            
        case ' ':
            model->finishTurn = true;
            
        case '[': 
            game->changeLane(LEFT);
            break;
        case ']': 
            game->changeLane(RIGHT);
            break;
            
        case 'z':
            game->addUnit(model->playerArray[0], TYPE_WATER);
            break;
        case 'x':
            game->addUnit(model->playerArray[0], TYPE_EARTH);
            break;
        case 'c':
            game->addUnit(model->playerArray[0], TYPE_WIND);
            break;
        case 'v':
            game->addUnit(model->playerArray[0], TYPE_FIRE);
            break;
    }
}

void SpecialFunc(int key, int x, int y)
{
     //if(key == GLUT_KEY_F1){
     //mode = (mode + 1)%NUM_MODES;
     //}
}

//Called on Window Resize
void ReshapeFunc(int w, int h)
{
	if (h <= 0) 
		return;
    model->height = h;
	model->width = w;
}

void initGL(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0 , 0);
	glutInitWindowSize(model->width,model->height);
	glutCreateWindow("Sponge Bob to the Stars!");
	//glutFullScreen();
    
	//One-Time setups
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    
    //Aim Stationary Light
    GLfloat pos[4] = {5.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    GLfloat full[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, full);
    glLightfv(GL_LIGHT0, GL_SPECULAR, full);
    glLightfv(GL_LIGHT0, GL_AMBIENT, full);
	
    //Callback Functions
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
    glutPassiveMotionFunc(PassiveMotionFunc);
    glutMouseFunc(MouseFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(SpecialFunc);
}







int main (int argc, char * argv[])
{
    model = Model::getSelf();
    initGL(argc, argv);
    initGame(model->numPlayers, model->numNodes);
    glutMainLoop();

    std::cout << "Hello, World!\n";
    return 0;
}

