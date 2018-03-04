//
//  MapLoader.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef MapLoader_h
#define MapLoader_h

#include <stdio.h>
#include <string>
#include "Map.h"

class MapLoader {
private:
    int num_players;
    bool use_default;
    std::string file_name;
public:
    //constructors and destructor
    MapLoader();
    MapLoader(int num_players, bool use_default = true); //if using default, indicate num_players
    MapLoader(std::string file_name);
    ~MapLoader();
    
    Map* load();
    int typeConverter(std::string type);
};
#endif /* MapLoader_h */
