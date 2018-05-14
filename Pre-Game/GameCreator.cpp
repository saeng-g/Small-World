//
//  GameCreator.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "GameCreator.h"

using std::cin;
using std::cout;
using std::endl;

//constructor
GameCreator::GameCreator() {
    //initializing response validity indicator
    proper_default = false;
    proper_num = false;
    proper_name = false;
    
    //initializing storage attributes
    response = '0';
    string fileName = "";
    use_default = false;
    num_players = 0;
    loader = nullptr;
    map = nullptr;
}

//destructor
GameCreator::~GameCreator() {
    delete loader;
    delete map;
    loader = nullptr;
    map = nullptr;
}


void GameCreator::askUserInputs() {
    
    while (!proper_default) {
        cout << "Would you like to use the default maps? (y/n)" << endl;
        cin >> response;
        
        if (response == 'y') { //use default maps
            proper_default = true; //proper response for use of default maps
            proper_num = false;
            use_default = true;
            
            while (!proper_num) {
                cout << "Please indicate the number of players: " << endl;
                cin >> num_players;
                if (num_players >= 2 && num_players <= 5) {
                    proper_num = true;
                    loader = new MapLoader(num_players, true); //create maploader (default)
                }
                else {
                    num_players = 0;
                    cout << "Default maps are only available for 2 to 5 players." << endl;
                    
                    //go back to outer loop
                    proper_default = false;
                    proper_num = true;
                }
            }
            
        }
        
        else if (response == 'n') { //don't use default maps
            proper_default = true; //proper response for (non)use of default maps
            proper_name = false;
            use_default = false;
            
            while (!proper_name) {
                cout << "Please indicate the map file you'd like to use: " << endl;
                cin >> fileName;
                
                FILE* fileCheck;
                fileCheck = std::fopen (fileName.c_str(), "r");
                if (!fileCheck) {
                    cout << "File does not exist" << endl;
                    
                    //go back to outer loop
                    proper_default = false;
                    proper_name = true;
                }
                else {
                    proper_name = true;
                    loader = new MapLoader(fileName); //create maploader (user-defined)
                }
                std::fclose(fileCheck);
                fileCheck = nullptr;
            }
        }
        
        else { //improper response for default maps
            cout << "Improper input. Please type either 'y' for yes or 'n' for no." << endl;
            //proper_default = false;
        }
        
        //making sure the map is good
        if (proper_num && proper_default) {
            try {
                map = loader->load();
            }
            catch (std::exception e) {
                proper_num = false;
                proper_default = false;
                proper_name = false;
                cout << "There was error in the loading the map file. "
                << "Returning to the map selection."
                << endl;
            }
            if (!map->map_check()) {
                proper_num = false;
                proper_default = false;
                proper_name = false;
                cout << "The map was loaded but this map is not a playable map. "
                << "Please try a different map that is a connected graph (non-directional)."
                << endl;
            }
        }
    }
}

void GameCreator::makeGame() {
    game = new SmallWorldGame(num_players);
    game->setMap(map);
    if (use_default) {
        cout << "A Small World Game has been created using a default map for "
            << num_players << " players.\n" << endl;
    }
    else {
        cout << "A Small World Game has been created using a custom map for "
            << num_players << " called \"" << fileName << "\".\n" << endl;
    }
}

SmallWorldGame* GameCreator::getGame() {
    return game;
}
