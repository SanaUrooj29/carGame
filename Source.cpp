#include <iostream>
#include <chrono>
#include <thread>
#include "Header.h"
#include "linkedList.h"
#include "map.h"
#include "priorityQueue.h"
#include "queue.h"

using namespace std;

void countdown() {
    for (int i = 3; i > 0; --i) {
        cout << "                                   " << i << " ";
        this_thread::sleep_for(chrono::seconds(1)); //sleep for 1 second
        system("cls");
    }
    cout << endl << "                                   GO!" << endl;
}

int main(){

	GameMapManual gamemap;
    GameMap automatic;


    int choice,lvl;
    string name;

    do {

        gamemap.constructGameMap();
        gamemap.connectNodes();

        //menu options
        cout << "                                   Menu:" << endl;
        cout << "                                   1. Start Game" << endl;
        cout << "                                   2. View Leaderboard" << endl;
        cout << "                                   3. Exit" << endl;

        //user input
       do {
           cout << "                                   Enter your choice (1-3): ";
            cin >> choice;
            if (choice < 1 || choice>3) {
                cout << "                                   Invalid choice. Please try again." << endl;
            }
        } while (choice < 1 || choice>3);

        cout << endl << endl;
        system("cls");

        switch (choice) {
        case 1:
            int subChoice;
            cout << "                                   Choose game type:" << endl;
            cout << "                                   1. Manual" << endl;
            cout << "                                   2. Automatic" << endl;
            do {
                cout << "                                   Enter your choice (1-2): ";
            cin >> subChoice;
            if (choice < 1 || choice>2) {
                cout << "                                   Invalid choice. Please try again." << endl;
            }
            } while (choice < 1 || choice>2);
            system("cls");

            switch (subChoice) {
            case 1:
                cout << "                                   Choose Level:" << endl;
                cout << "                                   1. Easy" << endl;
                cout << "                                   2. Medium" << endl;
                cout << "                                   3. Hard" << endl;

                do {
                    cout << "                                   Enter your choice (1-3): ";
                    cin >> lvl;
                    if (choice < 1 || choice>3) {
                        cout << "                                   Invalid choice. Please try again." << endl;
                    }
                } while (choice < 1 || choice>3);

                system("cls");
                if (lvl == 1) {
                    gamemap.setLevel("easy");
                }
                else if (lvl == 2) {
                    gamemap.setLevel("medium");

                }
                else if (lvl == 3) {
                    gamemap.setLevel("hard");

                }

                cout << "                                   Enter Your Name : ";
                cin >> name;
                gamemap.setName(name);

                countdown();
                gamemap.powerups();
                gamemap.obstacles();
                gamemap.displayMap();
                gamemap.ManualGame(0, 0, 7, 7); //fixed
                break;
            case 2:
               // startAutomaticGame();
             
                automatic.constructGameMap();
                automatic.connectNodes();
                automatic.displayMap();
              automatic.shortestPath(0, 0);
               automatic.displayMap();
               automatic.move();

                break;
            default:
                cout << "                                   Invalid choice. Please try again." << endl;
            }

            break;
        case 2:
           // viewLeaderboard();
            break;
        case 3:
            cout << "                                   Exiting" << endl;
            break;
        default:
            cout << "                                   Invalid choice. Please try again." << endl;
        }

    } while (choice != 3);
	
}