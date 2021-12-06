//
// Created by ilir8 on 5-12-2021.
//

#ifndef SHORTEST_PATH_GRAPH_H
#define SHORTEST_PATH_GRAPH_H

#include <vector>
#include "read_lines.h"

class node_destination;
class node;
class graph;

class node_destination
{
private:
    node * m_destination_node;
    int m_dest_node_name;
    int m_distance;

public:
    node_destination(node * destination_node,int distance, int dest_node_name);
    int destination_node_name();
    int distance();
    node& get_node_destination();
    node &destination_node();
};

class node
{
private:
    int m_node_name;
    std::vector<node_destination> m_list_of_destinations;
public:
    int name();
    node(int name);
    void add_node_destination(node_destination node_destination_add);
    int search_distance(int name_to);
    std::vector<node_destination>& get_list_of_destinations();
};

class graph
{
private:
    std::vector<node> m_graph;
    int m_nodes_size;
public:
    void add_node(node add_node);
    graph(std::vector<path>& paths);
    node * exists(int name);
    int size();
    int get_dir_distance(int name_from, int name_to);
    int get_name_at(int at);
    bool element_exists(int size);
    std::vector<node>* get_graph();
};




#endif //SHORTEST_PATH_GRAPH_H
