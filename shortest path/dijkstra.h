//
// Created by ilir8 on 6-12-2021.
//

#ifndef SHORTEST_PATH_DIJKSTRA_H
#define SHORTEST_PATH_DIJKSTRA_H

#include "graph.h"

class dijkstra
{
private:
    node * m_node;
    int m_distance_from_root_node;
    node * m_previous_node;
    bool m_visited;

public:
    dijkstra(node * this_node, int distance, node * prev_node);
    int get_dist();
    node * get_node();
    void set_distance(int distance);
    void set_previous_node(node * prev_node);
    bool get_visited();
    void set_visited_true();
};

class dijkstra_list
{
private:
    node * m_root_node;
    std::vector<dijkstra> m_dijkstra_list;
//    std::vector<node> m_visited_nodes;
//    std::vector<node> m_need_visit_nodes;

public:
    dijkstra_list(node& root_node, graph& d_graph);
    std::vector<dijkstra> * get_dijkstra_list();
//    bool has_been_visited(node& visited_node);
//    bool needs_visiting(node& visited_node);
    void dijkstra_routine();
    dijkstra * get_dijkstra_at(int node_nr);
    dijkstra * get_dijkstra_neighbour(int node_nr, int node_neighbour_nr);
    dijkstra * get_dijkstra_from_node(node & the_node);
    bool has_unvisited();
};

#endif //SHORTEST_PATH_DIJKSTRA_H
