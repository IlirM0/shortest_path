//
// Created by ilir8 on 6-12-2021.
//

#include "dijkstra.h"
#include <limits>

dijkstra::dijkstra(node * this_node, int distance, node * prev_node): m_node{this_node}, m_distance_from_root_node{distance}, m_previous_node{prev_node}
{}

dijkstra_list::dijkstra_list(node &root_node, graph &d_graph): m_root_node{&root_node}
{
    dijkstra temp_dijkstra{&root_node, 0, nullptr};
    m_dijkstra_list.push_back(temp_dijkstra);
    m_need_visit_nodes.push_back(root_node);

    for (int i = 0; i < d_graph.size(); ++i)
    {
        if (&d_graph.get_graph()->at(i) != m_root_node)
        {
            temp_dijkstra = {&d_graph.get_graph()->at(i), std::numeric_limits<int>::max(), nullptr};
            m_dijkstra_list.push_back(temp_dijkstra);
            m_need_visit_nodes.push_back(d_graph.get_graph()->at(i));
        }
    }
}

std::vector<dijkstra> *dijkstra_list::get_dijkstra_list()
{
    return &m_dijkstra_list;
}

int dijkstra::get_dist()
{
    return m_distance_from_root_node;
}

bool dijkstra_list::has_been_visited(node &visited_node)
{
    for (int i = 0; i < m_visited_nodes.size(); ++i) {
        if (&m_visited_nodes.at(i) == &visited_node)
        {
            return true;
        }
    }
    return false;
}

bool dijkstra_list::needs_visiting(node &visited_node)
{
    for (int i = 0; i < m_need_visit_nodes.size(); ++i) {
        if (&m_visited_nodes.at(i) == &visited_node)
        {
            return true;
        }
    }
    return false;
}

void dijkstra_list::dijkstra_routine() // the dijkstra algorithm.
{
    for (int i = 0; i < m_dijkstra_list.size(); ++i) // go through all the members of dijkstra list
    {
        // go through all the neighbours of the node
//        for (int j = 0; j < m_dijkstra_list.at(i).get_node()->get_list_of_destinations().size(); ++j) {
//            m_dijkstra_list.at(i).get_node()->get_list_of_destinations().at(j).distance()
//        }



    }
}

node *dijkstra::get_node()
{
    return m_node;
}
