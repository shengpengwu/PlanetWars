//
//  Map.cpp
//  PlanetWars
//
//  Created by Philip Dougherty on 12/5/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Map.h"

Map::Map(int numNodes)
{
    this->nodeArray = Model::getSelf()->nodeArray;
    this->selector = Model::getSelf()->selector;
    createNodeMap(numNodes);
}

Map::~Map()
{
    delete nodeArray;
    delete selector;
}

Node * Map::getNodeAt(int row, int col)
{
    for(int i = 0; i < Model::getSelf()->numNodes; i++)
    {
        if(nodeArray[i]->row == row && nodeArray[i]->column == col)
            return nodeArray[i];
    }
    
    return Model::getSelf()->nullNode;
}

void Map::selectSelected()
{
    Node *n;
    n = getNodeAt(selector->row, selector->column);
    if(n != Model::getSelf()->nullNode)
    {
        n->select(true);
        if(n->ship != Model::getSelf()->nullShip)
        {
            if(Model::getSelf()->playerArray[0]->hasShip(n->ship))
                Model::getSelf()->selectedShip = n->ship;
        }
        else
        {
            if(Model::getSelf()->selectedShip != NULL)
            {
                Model::getSelf()->selectedShip->moveToNode(n);
                Model::getSelf()->selectedShip = Model::getSelf()->nullShip;
            }
        }
    }
    else
    {
        if(Model::getSelf()->selectedNode != Model::getSelf()->nullNode)
            Model::getSelf()->selectedNode->select(false); 
        Model::getSelf()->selectedShip = Model::getSelf()->nullShip;
    }
}

void Map::linkNodeToNeighbors(Node * node)
{
    int col;
    int row;
    for(int i = 0; i < 6; i++)
    {
        switch (i) {
            case 0:
                col = node->column;
                row = node->row+2;
                break;
            case 1:
                col = node->column+1;
                row = node->row+1;
                break;
            case 2:
                col = node->column+1;
                row = node->row-1;
                break;
            case 3:
                col = node->column;
                row = node->row-2;
                break;
            case 4:
                col = node->column-1;
                row = node->row-1;
                break;
            case 5:
                col = node->column-1;
                row = node->row+1;
                break;
            default:
                throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                break;
        }
        
        for(int j = 0; j < Model::getSelf()->numNodes; j++)
        {
            if(nodeArray[j]->column == col && nodeArray[j]->row == row)
            {
                node->neighborNodes[i] = nodeArray[j];
                nodeArray[j]->neighborNodes[(i+3)%6] = node;
                node->numNeighborNodes++;
                nodeArray[j]->numNeighborNodes++;
            }
        }
    }
}

void Map::createNodeMap(int numNodes)
{
    //  Two important nodes in this algorithm- sourceNode and newNeighbor. 
    //  sourceNode is the node currently looking to add a neighbor (and should already be assigned a location). 
    //  newNeighbor is the node that is looking to be placed, and will be placed next to sourceNode.
    Node* sourceNode;
    Node* nodeToBeAssigned;
    Node* centerNode;
    int nodesLeftToBeAssigned = numNodes;
    
    int rNode; //Random node from copy array
    int rNeighbor; //Random neighbor to be assigned
    int mapDensity;
    int numAssignAttempts;
    bool sourceEligible;
    
    int rowMin = 0;
    int rowMax = 0;
    int colMin = 0;
    int colMax = 0;
    
    Node** copyArray = new Node*[numNodes];
    for(int i = 0; i < numNodes-1; i++)
    {
        copyArray[i] = nodeArray[i];
    }
    centerNode = nodeArray[numNodes-1];
    centerNode->row = 0;
    centerNode->column = 0;
    nodesLeftToBeAssigned--;
    
    bool nodeAssigned = false;
    //Assign each node a location
    while(nodesLeftToBeAssigned > 0)
    {
        //Pick a random node from copyArray
        sourceNode = centerNode;
        numAssignAttempts = 0;
        mapDensity = MAP_DENSITY;
        rNode = (int)(Model::random()*nodesLeftToBeAssigned);
        nodeToBeAssigned = copyArray[rNode];
        nodeAssigned = false;

        while(!nodeAssigned)
        {
            //If already tried more than 5 times, loosen the MAP_DENSITY rule
            if(numAssignAttempts > MAP_DENSITY_STRICTNESS)
            {
                mapDensity++;
                numAssignAttempts = 0;
            }
            
            sourceEligible = ((sourceNode->numNeighborNodes <= mapDensity) && ((rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1));

            //If the current source node is eligible to have a neighbor
            if(sourceEligible)
            {
                //Assign the new node a location coordinate
                switch (rNeighbor) {
                    case 0:
                        nodeToBeAssigned->row = sourceNode->row+2;
                        nodeToBeAssigned->column = sourceNode->column;
                        break;
                    case 1:
                        nodeToBeAssigned->row = sourceNode->row+1;
                        nodeToBeAssigned->column = sourceNode->column+1;
                        break;
                    case 2:
                        nodeToBeAssigned->row = sourceNode->row-1;
                        nodeToBeAssigned->column = sourceNode->column+1;
                        break;
                    case 3:
                        nodeToBeAssigned->row = sourceNode->row-2;
                        nodeToBeAssigned->column = sourceNode->column;
                        break;
                    case 4:
                        nodeToBeAssigned->row = sourceNode->row-1;
                        nodeToBeAssigned->column = sourceNode->column-1;
                        break;
                    case 5:
                        nodeToBeAssigned->row = sourceNode->row+1;
                        nodeToBeAssigned->column = sourceNode->column-1;
                        break;
                    default:
                        throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                        break;
                }
                
                //Uncomment for debugging info
                //std::cout << "SourceNode: " << sourceNode->column << "," << sourceNode->row << std::endl;
                //std::cout << "NeighborNode: " << newNeighbor->column << "," << newNeighbor->row << "\n" << std::endl;
                
                //Link new node to all other neighbors based on coordinate
                linkNodeToNeighbors(nodeToBeAssigned);
                
                //Remove node from copyArray
                for(int i = rNode; i < nodesLeftToBeAssigned-1; i++)
                {
                    copyArray[i] = copyArray[i+1];
                }
                nodesLeftToBeAssigned--;
                
                if(nodeToBeAssigned->row < rowMin)
                    rowMin = nodeToBeAssigned->row;
                if(nodeToBeAssigned->row > rowMax)
                    rowMax = nodeToBeAssigned->row;
                if(nodeToBeAssigned->column < colMin)
                    colMin = nodeToBeAssigned->column;
                if(nodeToBeAssigned->column > colMax)
                    colMax = nodeToBeAssigned->column;
                
                nodeAssigned = true;
            }
            //Otherwise assign a current neighbor of the source node as the new source node
            else
            {
                sourceNode = sourceNode->neighborNodes[sourceNode->getRandomNeighbor()];
                numAssignAttempts++;
            }
        }
    }
    Model::getSelf()->rowMin = rowMin;
    Model::getSelf()->rowMax = rowMax;
    Model::getSelf()->colMin = colMin;
    Model::getSelf()->colMax = colMax;
    Model::getSelf()->setCameraParams();
    
    delete copyArray;
}

void Map::tick()
{
    for(int i = 0; i < Model::getSelf()->numNodes; i++)
        Model::getSelf()->nodeArray[i]->tick();
}

void Map::draw()
{
    selector->set(Model::getSelf()->mouseX, Model::getSelf()->mouseY);
    selector->drawAtPosition();
    for(int i = 0; i < Model::getSelf()->numNodes; i++)
    {
        nodeArray[i]->drawAtPosition();
    }
}

