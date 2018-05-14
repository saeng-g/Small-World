//
//  Map.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <vector> //std::vector
#include <algorithm> //std::sort
#include "Region.h"

class Map
{
private:
    int num_vertices; //how many vertices the map expects to have
    int curr_vertices; //how many vertices the map currently has
    std::vector<Region*> vertices;
    std::vector< std::vector<int> > edges;
    
public:
    //Constructors
    Map();
    Map(int num_vertices);
    ~Map();
    
    //Accessors:
    int get_num_v();
    int get_curr_v();
    int get_v_size();
    int get_e_size(); //returns inner vector size x outer vector size
    Region* getRegion(int id);
    
    //modifiers
    void add_vertex(Region* region);
    void add_edge(int id_from_vertex, int id_to_vertex);
    void add_edge(Region* from_region, Region* to_region);
    void sort_vertex(); //sorts Region objects in vertices by id
    void setup_geoMarkers(); //sets following Region attributes: beside_mt, coastal;
    
    //is_edge: checks if there's an edge connecting vertex1 to vertex2
    bool is_edge(Region* from_region, Region* to_region);
    
    /*
     * mapCheck: checks if Map object is valid or invalid;
     * see cpp for detail*
     */
    bool map_check();
    
    //printing
    void printMap();
    void printBorderList();

};

#endif /* MAP_H */
