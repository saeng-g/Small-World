//
//  Map.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "Map.h"
#include <iostream> //std::cerr

//comparator for sort_vertex()
struct Region_Comp {
    bool operator() (Region* r1, Region* r2) {
        return (r1->getID() < r2->getID());
    }
} comp;

//dupicate check


//constructors & destructors
Map::Map() { }
Map::Map(int num_vertices) {
    this->num_vertices = num_vertices;
    curr_vertices = 0;
    edges.resize(num_vertices, std::vector<int>(num_vertices, 0));
}
Map::~Map() {};

//Accessors
int Map::get_num_v() { return num_vertices; }
int Map::get_curr_v() { return curr_vertices; }
int Map::get_v_size() { return (int) vertices.size(); }
int Map::get_e_size() { return (int) (edges.size() * edges[0].size()); }
Region* Map::getRegion(int id) {
    return vertices[id - 1];
}

//V, E manipulation
void Map::add_vertex(Region* region) {
    bool duplicate = false; //check if region already exists
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == region) {
            duplicate = true;
        }
    }
    if (duplicate == false) {
        vertices.push_back(region);
        curr_vertices++;
    }
}
void Map::add_edge(int from_vertex, int to_vertex) {
    edges[from_vertex - 1][to_vertex - 1] = 1;
    edges[to_vertex - 1][from_vertex - 1] = 1;
}
void Map::add_edge(Region* from_region, Region* to_region) {
    add_edge(from_region->getID(), to_region->getID());
}
void Map::sort_vertex() {
    std::sort(vertices.begin(), vertices.end(), comp);
}

//check (A, B) in E
bool Map::is_edge(Region* from_region, Region* to_region) {
    int from_id = from_region->getID() - 1, to_id = to_region->getID() - 1;
    if (edges[from_id][to_id] == 1 && edges[to_id][from_id] == 1) {
        return true;
    }
    else if (edges[from_id][to_id] == 0 && edges[to_id][from_id] == 0) {
        return false;
    }
    else {
        std::cerr << "Error with edge configuration" << std::endl;
        return false;
    }
}

void Map::setup_geoMarkers() {
    for (int i = 1; i < num_vertices; i++) {
        if (vertices[i]->getType() == Region::MOUNTAIN) {
            for (int j = 1; j < num_vertices; j++) {
                if (edges[i][j] == 1)
                    vertices[j]->setBesideMt(true);
            }
        }
        else if ( (vertices[i]->getType() == Region::SEA)
                 || (vertices[i]->getType() == Region::LAKE) ) {
            for (int j = 1; j < num_vertices; j++) {
                if (edges[i][j] == 1)
                    vertices[j]->setCoastal(true);
            }
        }
    }
}

/*
 * mapCheck: checks if Map object is valid or invalid
 * NOTE: map can be implemented regardless of validity
 * For a map to be valid,
 *  1) it must have at least 2 nodes.
 *  2) Every node must be connected to at least one edge
 *  3) If (A, B) is an edge, (B, A) must be an edge
 *  4) current # of vertices must equal expected # of vertices
 */
bool Map::map_check(){
    bool first_check = false;
    bool second_check = false;
    bool third_check = false;
    bool fourth_check = false;
    if (num_vertices >= 2) { //first qualification
        first_check = true;
        for (int i = 0; i < num_vertices; i++) {
            second_check = true;
            bool vertex_check = false;
            for (int j = 0; j < num_vertices; j++) {
                if (edges[i][j] == 1) { //second qualification
                    if (edges [j][i] != 1) //third qualification
                        return false;
                    third_check = true;
                    vertex_check = true;
                }
                
                /* For TESTING :
                std::cout << i << ", " << j << ": "
                << first_check << second_check << vertex_check << third_check << std::endl;
                 */
                
            }
            second_check = vertex_check && second_check;
        }
        if (num_vertices == curr_vertices) //fourth qualification
            fourth_check = true;
    }
    return first_check && second_check && third_check && fourth_check;
}

//printMap()

void Map::printMap() {
    using std::cout;
    using std::endl;
    
    cout << "LEGEND: " << endl;
    cout << "m = mine, g = magic, c = cavern" << endl;
    cout << "h = holes-in-the-ground, o = hero, d = dragon" << endl;
    cout << "f = fortress, e(#) = number of encampments(#)" << endl;
    cout << endl;
    
    for (int i = 0; i < num_vertices; i++) {
        vertices[i]->getRegionInfo();
        vertices[i]->getOwnerInfo();
        
        cout << "\tEdges:\t";
        for (int j = 0; j < num_vertices; j++) {
            if (is_edge(vertices[i], vertices[j])) {
                cout << j + 1 << "\t";
            }
        }
        cout << "\n" << endl;
    }
    printBorderList();
}

void Map::printBorderList() {
    //iterates through vertices and appends ID onto list
    std::cout << "Border regions: ";
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i]->getIsBorder()) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n" << std::endl;
}

