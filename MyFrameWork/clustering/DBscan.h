//
// Created by hossein on 12/2/17.
//

#ifndef WORK_DBSCAN_H
#define WORK_DBSCAN_H
/* Copyright 2015 Gagarine Yaikhom (MIT License) */
#include <climits>
#include <iostream>
#include "Pulse.h"
#include <vector>
using namespace std;

#define UNCLASSIFIED -1
#define NOISE -2

#define CORE_POINT 1
#define NOT_CORE_POINT 0

#define SUCCESS 0
#define FAILURE -3

#define epsilon 2
#define minpts 3
typedef struct node_s node_t;
struct node_s {
    int index;
    node_t *next;
};
typedef struct epsilon_neighbours_s epsilon_neighbours_t;
struct epsilon_neighbours_s {
    int num_members;
    node_t *head, *tail;
};
class DBscan {
public:
    DBscan();

    node_t * create_node( int index);
    
    int append_at_end( int index, epsilon_neighbours_t *en);

    epsilon_neighbours_t * get_epsilon_neighbours( int index, vector<Pulse>&points);
    
    void  destroy_epsilon_neighbours(epsilon_neighbours_t *en);
    
    void  runDBScan(vector<Pulse> &points);
    
    int  expand( int index,  int cluster_id,vector<Pulse>&points);

    int  spread( int index, epsilon_neighbours_t *seeds,  int cluster_id,vector<Pulse>&points);


};



#endif //WORK_DBSCAN_H
