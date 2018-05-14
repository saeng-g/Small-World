//
//  MapLoader.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cerr;

MapLoader::MapLoader() { };

MapLoader::MapLoader(int num_players, bool use_default) {
    bool num_check = (num_players >= 2) && (num_players <= 5);
    if (!num_check) { //number of players is not 2 to 5
        cerr << "Default maps only available for 2 to 5 players\n";
        throw 5;
    }
    this->num_players = num_players;
    this->use_default = true;
    
    switch (num_players) {
        case 2:
            this->file_name = "/Users/Ky/Desktop/School/COMP345/SmallWorldGame/DerivedData/2player.txt";
            break;
        case 3:
            this->file_name = "/Users/Ky/Desktop/School/COMP345/SmallWorldGame/DerivedData/3player.txt";
            break;
        case 4:
            this->file_name = "/Users/Ky/Desktop/School/COMP345/SmallWorldGame/DerivedData/4player.txt";
            break;
        case 5:
            this->file_name = "/Users/Ky/Desktop/School/COMP345/SmallWorldGame/DerivedData/5player.txt";
            break;
        default:
            this->file_name = "/Users/Ky/Desktop/School/COMP345/SmallWorldGame/DerivedData/5player.txt"; //if for some reason, num_players is not 2 ~ 5, use 5 as default
    }
};

MapLoader::MapLoader(string file_name) {
    num_players = -1;
    use_default = false;
    this->file_name = file_name;
};

MapLoader::~MapLoader() { };

Map* MapLoader::load() throw (int) {
    std::ifstream reader;
    reader.open(file_name);
    
    if(!reader)
    {
        cerr << "Error while opening file\n";
        throw 5;
    }
    
    //all correctly formatted file should have the validation id: VALIDATIONID.20KK345SWmITLtMiMaCLe18
    string validation ("VALIDATIONID.20KK345SWmITLtMiMaCLe18");
    string first_line;
    getline(reader, first_line);
    
    if (validation.compare(first_line) != 0) { //error if not valid
        cerr << "Invalid file. Cannot extract map information from this file.\n";
        throw 5;
    }
    
    else {
        //all correctly formmated file should have the number of total vectors included in second line
        int num_vectors = 0;
        reader >> num_vectors;
        string gb(""); //move to next line
        getline(reader, gb);
        
        Map* map = new Map(num_vectors);
        for (int i = 0; i < num_vectors; i++) {
            //read line
            string line("");
            getline(reader, line);
            
            //decode line
            std::istringstream is(line); //use istringstream to split line
            std::vector<string> split_line((std::istream_iterator<string>(is)), std::istream_iterator<string>());
            int id = std::stoi(split_line[0],nullptr);
            int type = typeConverter(split_line[1]);
            
            Region* region = new Region(id, type); //new region created
            
            try { //in case incorrect format or error in file
                //setting special region attributes
                region->setLostTribe(std::stoi(split_line[2],nullptr));
                region->setMine(std::stoi(split_line[3],nullptr));
                region->setMagic(std::stoi(split_line[4],nullptr));
                region->setCavern(std::stoi(split_line[5],nullptr));
                if (split_line[6].compare("b") == 0) {
                    region->setIsBorder(1);
                }
                else if (split_line[6].compare("c") == 0) {
                    region->setIsBorder(0);
                }
                else {
                    cerr << "Incorrect input @ border.\n"; //catch erroneous border input
                    throw 5;
                }
            } catch (std::exception e) { //catch corrupted or erroneous inputs
                cerr << "Error while creating region.\n";
                throw 5;
            }
            
            /* for testing:
            std::cout << region->getLostTribe() << std::endl;
            std::cout << region->getMine() << std::endl;
            std::cout << region->getMagic() << std::endl;
            std::cout << region->getCavern() << std::endl;
            std::cout << region->getIsBorder() << std::endl;
            */
            
            map->add_vertex(region); //add vertex to start adding edges
            for (int j = 7; j < split_line.size(); j++) {
                //iterating over remainder of line to add edges
                map->add_edge(i + 1, std::stoi(split_line[j],nullptr));
            }
        }
        reader.close();
        map->setup_geoMarkers();
        return map;
    }
}

int MapLoader::typeConverter(string type) {
    if (type.compare("sea") == 0) {
        return 0;
    }
    else if (type.compare("lake") == 0) {
        return 1;
    }
    else if (type.compare("hill") == 0) {
        return 2;
    }
    else if (type.compare("farmland") == 0) {
        return 3;
    }
    else if (type.compare("swamp") == 0) {
        return 4;
    }
    else if (type.compare("forest") == 0) {
        return 5;
    }
    else if (type.compare("mountain") == 0) {
        return 6;
    }
    else {
        cerr << "Incorrect input @ type.\n";
        exit(EXIT_FAILURE);
    }
}
