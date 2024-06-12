#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

using namespace std;

class GraphNodeManual {
public:
    char ui;

    GraphNodeManual* parent;
    string path;
    string type;

    //neighbors
    GraphNodeManual* up;
    GraphNodeManual* down;
    GraphNodeManual* left;
    GraphNodeManual* right;

    //vertices
    int x, y;

    //weighted undirected
    int weight; //uniform cost/hops
    int pathCost;

    GraphNodeManual(int xIndex, int yIndex) {
        ui = '*';

        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
        parent = nullptr;

        x = xIndex;
        y = yIndex;
        type = "normal";

        weight = 1;
        pathCost = 0;
   }

    GraphNodeManual() {
        ui = '*';

        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
        parent = nullptr;

        x = 0;
        y = 0;
        type = "normal";

        weight = 1;
        pathCost = 0;
    }
};

class NodeManual {
public:
    int x, y;
    NodeManual* next;

    NodeManual() {
        next = nullptr;
    }
    NodeManual(int xRand, int yRand) {
        x = xRand;
        y = yRand;
        next = nullptr;

    }
};

class ManualQueue {
private:
    NodeManual* front;
    NodeManual* rear;

public:
    ManualQueue() {
        front = nullptr;
        rear = nullptr;
    }

    ~ManualQueue() {
        while (!isEmpty()) {
            NodeManual* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(NodeManual* newNodeManual) {
        if (isEmpty()) {
            front = rear = newNodeManual;
        }
        else {
            rear->next = newNodeManual;
            rear = newNodeManual;
        }
        newNodeManual->next = nullptr;
    }

    NodeManual* dequeue() {
        if (isEmpty()) {
            return nullptr; // Return null if the queue is empty
        }

        NodeManual* dequeuedNode = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr; // If the queue is now empty, update the rear pointer
        }

        dequeuedNode->next = nullptr; // Disconnect the dequeued node from the queue
        return dequeuedNode;
    }

    void displayPositions() {
        if (isEmpty()) {
          cout << "Nothing to display." << endl;
            return;
        }

        cout << " positions:" << endl;

        // Assuming your queue has a method to get the front element
        NodeManual* current = front;

        // Loop through the queue and display obstacle positions
        while (current != nullptr) {
            cout << "X=" << current->x << ", Y=" << current->y << endl;

            // Move to the next node
            current = current->next;  // Update according to your queue implementation
        }

    }
};

class ScoreNode {
public:
    GraphNodeManual* nodeVisited;
    ScoreNode* next;

    ScoreNode() {
        next = nullptr;
    }
    ScoreNode(GraphNodeManual* node) {
        nodeVisited = node;
        next = nullptr;
    }
};

class ScoreList {
private:
    ScoreNode* head;
    int nodesVisited;
    int powerUpsCollected;
    int obstaclesCollected;

public:
    ScoreList() {
        head = nullptr;
        nodesVisited = 0;
        powerUpsCollected = 0;
        obstaclesCollected = 0;
    }

    void insert(GraphNodeManual* newNode) {
        if (head == nullptr) {
            head = new ScoreNode(newNode);
            if (newNode->type == "obstacle") {
                obstaclesCollected++;
            }
            else if (newNode->type == "powerup") {
                powerUpsCollected++;
            }
            nodesVisited++;
            return;
        }
        else {
            ScoreNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            if (newNode->type == "obstacle") {
                obstaclesCollected++;
            }
            else if (newNode->type == "powerup") {
                powerUpsCollected++;
            }
            curr->next = new ScoreNode(newNode);
            nodesVisited++;
        }
    }

    void displayScoreList() {
        ScoreNode* curr = head;
        while (curr->next != nullptr) {
            cout << "x = " <<  curr->nodeVisited->x << "y = " << curr->nodeVisited->y;
            cout << endl;
            curr = curr->next;
        }
        cout << "Node Visited : " << nodesVisited << endl;
        cout << "Power Ups Collected : " << powerUpsCollected << endl;
        cout << "Obstacles Collected : " << obstaclesCollected << endl;
    }

};


class GameMapManual {
private:
    int rows;
    int cols;

    ManualQueue ObstacleManualQueue; //obstacle queue
    ManualQueue PowerupsManualQueue; //powerup queue
    ScoreList score;

    GraphNodeManual*** map; //game map
    //8x8 game map

    string playerName;
    string level;

public:

    GameMapManual() {
        rows = 8;
        cols = 8;
        map = nullptr;
   }
  
    void setName(string name) {
        playerName = name;
    }
    void setLevel(string lvl) {
        level = lvl;
    }

    void constructGameMap() {

        map = new GraphNodeManual * *[rows];
        for (int i = 0; i < rows; ++i) {
            map[i] = new GraphNodeManual * [cols];
            for (int j = 0; j < cols; ++j) {
                map[i][j] = new GraphNodeManual(i, j);
            }
        }

    }

    // Function to connect nodes upward
    void connectUp(GraphNodeManual* currentNode, GraphNodeManual* neighborNode) {
        currentNode->up = neighborNode;
    }

    // Function to connect nodes downward
    void connectDown(GraphNodeManual* currentNode, GraphNodeManual* neighborNode) {
        currentNode->down = neighborNode;
    }

    // Function to connect nodes to the left
    void connectLeft(GraphNodeManual* currentNode, GraphNodeManual* neighborNode) {
        currentNode->left = neighborNode;
    }

    // Function to connect nodes to the right
    void connectRight(GraphNodeManual* currentNode, GraphNodeManual* neighborNode) {
        currentNode->right = neighborNode;
    }

    void connectNodes() {
        srand(time(0));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int numConnections = (rand() % 3) + 2; //random number between 0 and 3

                    //at least one connection
                    if (numConnections == 0) {
                        numConnections = 1;
                    }

                //Connect randomly
                while (numConnections >= 0) {
                    int direction = rand() % 4; //random number between 0 and 3

                    switch (direction) {
                    case 0: // Connect up
                        if (i > 0 && map[i][j]->up == nullptr) {
                            connectUp(map[i][j], map[i - 1][j]);
                            connectDown(map[i - 1][j], map[i][j]);
                            numConnections--;
                        }
                        else {
                            numConnections--;
                        }
                        break;

                    case 1: // Connect down
                        if (i < rows - 1 && map[i][j]->down == nullptr) {
                            connectDown(map[i][j], map[i + 1][j]);
                            connectUp(map[i + 1][j], map[i][j]);
                            numConnections--;
                        }
                        else {
                            numConnections--;
                        }
                        break;

                    case 2: // Connect left
                        if (j > 0 && map[i][j]->left == nullptr) {
                            connectLeft(map[i][j], map[i][j - 1]);
                            connectRight(map[i][j - 1], map[i][j]);
                            numConnections--;
                        }
                        else {
                            numConnections--;
                        }
                        break;

                    case 3: // Connect right
                        if (j < cols - 1 && map[i][j]->right == nullptr) {
                            connectRight(map[i][j], map[i][j + 1]);
                            connectLeft(map[i][j + 1], map[i][j]);
                            numConnections--;
                        }
                        else {
                            numConnections--;
                        }
                        break;
                    }
                }
            }
        }
    }


    void obstacles() {
        int randomNumberO;
        if (level == "easy") {
            randomNumberO = 0;
        }
        else if (level == "medium") {
            randomNumberO = rand() % 6 + 7; //7-12 obstacles
        }
        else if (level == "hard") {
            randomNumberO = rand() % 6 + 15; //15-20 obstacles
        }
      
        for (int i = 0;i < randomNumberO;i++) {
            int obstaclePositionX = rand() % 8;
            int obstaclePositionY = rand() % 8;

            NodeManual* obstacle = new NodeManual(obstaclePositionX, obstaclePositionY);

            ObstacleManualQueue.enqueue(obstacle);

        }

       // ObstacleManualQueue.displayPositions();
    }

    void powerups() {     

        int randomNumberP = rand() % 6 + 7; //7-12 powerups

        for (int i = 0;i < randomNumberP;i++) {
            int powerupPositionX = rand() % 8;
            int powerupPositionY = rand() % 8;

            NodeManual* powerup = new NodeManual(powerupPositionX, powerupPositionY);

            PowerupsManualQueue.enqueue(powerup);

        }

       // PowerupsManualQueue.displayPositions();
    }

    GraphNodeManual* findNode(int x, int y) {
        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (map[i][j]->x == x && map[i][j]->y == y) {
                        return map[i][j];
                    }
                }
            }
        }
        return nullptr;
    }

    void displayManualGameMap(GraphNodeManual* currentP, GraphNodeManual* oldP) {
        if (currentP->type == "obstacle") {
            cout << RED;
            cout << "                       OOPS you stepped on an Obstacle !!! " << endl;
            cout << RESET;
        }
        else if (currentP->type == "powerup") {
            cout << GREEN;
            cout << "                       PowerUp Collected " << endl;
            cout << RESET;
        }

        oldP->ui = '*';
   
        currentP->ui = '.';
        displayMap();
        if (currentP->type == "obstacle") {
            currentP->type = "normal";
        }
        else if (currentP->type == "powerup") {
            currentP->type = "normal";
        }
        cout << endl;
        cout << endl;
    }
    
    void ManualGame(int sourceX, int sourceY, int destinationX, int destinationY) {

        srand(time(0));

        //user
        int userX = sourceX; //starting the game from source 
        int userY = sourceY;

        GraphNodeManual* userPosition = findNode(userX, userY);
        GraphNodeManual* oldPosition;

        //obstacle
        GraphNodeManual* obstaclePosition;
        NodeManual* obstacleVertices;

        //powerup
        GraphNodeManual* powerupPosition;
        NodeManual* powerupVertices;

        char keyPressed;
        bool destination = false;
        bool positionUpdated = false;

        while (!destination) {
            positionUpdated = false;
            keyPressed = _getch(); //getting real-time key press (#include <conio.h>)

            oldPosition = userPosition;

            if (keyPressed == 72) { //up arrow 
                if (userX > 0) {
                    if (userPosition->up != nullptr) {
                        userX--;
                        positionUpdated = true;
                    }
                }
            }
            else if (keyPressed == 80) {  //down arrow
                if (userX < rows - 1) {
                    if (userPosition->down != nullptr) {
                        userX++;
                        positionUpdated = true;
                    }
                }
            }
            else if (keyPressed == 77) {  //right arrow
                if (userY < cols - 1) {
                    if (userPosition->right != nullptr) {
                        userY++;
                        positionUpdated = true;
                    }
                }
            }
            else if (keyPressed == 75) {  //left arrow 
                if (userY > 0) {
                    if (userPosition->left != nullptr) {
                        userY--;
                        positionUpdated = true;
                    }
                }
            }

            if (positionUpdated) {
                userPosition = findNode(userX, userY);
               
                int displayObstacle = rand() % 2;

                if (displayObstacle == 0) {

                    obstacleVertices = ObstacleManualQueue.dequeue();

                    if (obstacleVertices != nullptr) {
                        obstaclePosition = findNode(obstacleVertices->x, obstacleVertices->y);
                        if (obstaclePosition->type != "powerup") {
                            obstaclePosition->type = "obstacle";

                            if (obstaclePosition != userPosition) {
                                obstaclePosition->ui = '&';
                            }
                        }
                    }
                }

                powerupVertices = PowerupsManualQueue.dequeue();

                if (powerupVertices != nullptr) {
                    powerupPosition = findNode(powerupVertices->x, powerupVertices->y);

                    if (powerupPosition->type != "obstacle") {
                        powerupPosition->type = "powerup";

                        if (powerupPosition != userPosition) {
                            powerupPosition->ui = '$';
                        }
                    }
                }
                system("cls");
                score.insert(userPosition);
                displayManualGameMap(userPosition, oldPosition);
            }

            if (userX == destinationX && userY == destinationY) {
                destination = true;
                score.displayScoreList();
                cout << GREEN;
                cout << "                                   Game End " << endl;
                cout << "                                   You have successfully reached your destination " << endl;
                cout << RESET;
            }
        }
    }
    

    void displayMap() {

        cout << endl << endl << endl << endl;   
        for (int i = 0; i < rows; ++i) {
            cout << "                                   ";
            for (int j = 0; j < cols; ++j) {
                if (map[i][j]->type == "obstacle") {
                    cout << RED;
                    cout << map[i][j]->ui;
                    cout << RESET;
                }
                else if (map[i][j]->type == "powerup") {
                    cout << GREEN;
                    cout << map[i][j]->ui;
                    cout << RESET;
                }
                else {
                    cout << BLUE;
                   cout << map[i][j]->ui;
                   cout << RESET;
                }

                if (map[i][j]->right != nullptr) {
                    cout << CYAN;
                    cout << "--";
                    cout << RESET;
                }
                else {
                    cout << "  ";
                }
            }
            if (i == 0) {
                cout << YELLOW;
                cout << "       Press 'P' for pause";
                cout << RESET;
            }
            if (i == 1) {
                cout << YELLOW;
                cout << "       Player Name : " << playerName;
                cout << RESET;
            }
            cout << endl;
            cout << "                                   ";
            for (int j = 0; j < cols; ++j) {

                if (map[i][j]->down != nullptr) {
                    cout << CYAN;
                    cout << "|  ";
                    cout << RESET;
                }
                else {
                    cout << "   ";
                }
            }
            cout << endl;
        }
    }

    void displayMapCoordinates() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "(" << map[i][j]->x << "," << map[i][j]->y << ")";

                cout << "  ";

            }
            cout << endl;
        }
           
    }

    //set weights
    void setRandomWeights()
    {
        srand(time(0));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (i == 0 && j == 0)
                {
                    map[i][j]->weight = 0;
                }
                else
                {
                    map[i][j]->weight = (rand() % 6) + 1;  //random numbers between 1 n 6                  
                }
                cout << map[i][j]->weight << " ";
            }
            cout << endl;
        }

    }

    /*void dijkstras()
    {


    }*/

    ~GameMapManual() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }
};
