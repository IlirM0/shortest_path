//
// Created by ilir8 on 6-12-2021.
//

#include "dijkstra.h"
#include <limits>

dijkstra::dijkstra(node * this_node, int distance, node * prev_node): m_node{this_node}, m_distance_from_root_node{distance}, m_previous_node{prev_node}, m_visited{false}
{}

dijkstra_list::dijkstra_list(node &root_node, graph &d_graph): m_root_node{&root_node}
{
    dijkstra temp_dijkstra{&root_node, 0, nullptr};
    //temp_dijkstra.set_visited_true(); //set to visited, since this one doesnt need visiting.
    m_dijkstra_list.push_back(temp_dijkstra);
    //m_need_visit_nodes.push_back(root_node);


    for (int i = 0; i < d_graph.size(); ++i)
    {
        if (&d_graph.get_graph()->at(i) != m_root_node)
        {
            temp_dijkstra = {&d_graph.get_graph()->at(i), std::numeric_limits<int>::max(), nullptr};
            m_dijkstra_list.push_back(temp_dijkstra);
            //m_need_visit_nodes.push_back(d_graph.get_graph()->at(i));
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

//bool dijkstra_list::has_been_visited(node &visited_node)
//{
//    for (int i = 0; i < m_visited_nodes.size(); ++i) {
//        if (&m_visited_nodes.at(i) == &visited_node)
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool dijkstra_list::needs_visiting(node &visited_node)
//{
//    for (int i = 0; i < m_need_visit_nodes.size(); ++i) {
//        if (&m_visited_nodes.at(i) == &visited_node)
//        {
//            return true;
//        }
//    }
//    return false;
//}

void dijkstra_list::dijkstra_routine() // the dijkstra algorithm.
{
    dijkstra * current_dijkstra_node = this->get_dijkstra_from_node(*m_root_node);
    dijkstra * shortest_next_dijkstra = nullptr;

    while(this->has_unvisited())
    {
        for (int i = 0; i < current_dijkstra_node->get_node()->get_list_of_destinations().size(); ++i)
        { // go through the list of destination nodes.
            if (!this->get_dijkstra_from_node(current_dijkstra_node->get_node()->get_list_of_destinations().at(
                    i).get_node_destination())->get_visited()) // if this node has been visited before then ignore it.
            {
                if (shortest_next_dijkstra != nullptr) // if this is not the first thing done (not root node)
                {
                    this->get_dijkstra_from_node(current_dijkstra_node->get_node()->get_list_of_destinations().at(i).get_node_destination())->set_distance(current_dijkstra_node->get_node()->get_list_of_destinations().at(i).distance());
                    //set the distance from root NEED TO ADD THE BASE ROOT DIFF
                }
                if ((current_dijkstra_node->get_node()->get_list_of_destinations().at(i).distance() < shortest_next_dijkstra->get_dist() && !this->get_dijkstra_from_node(current_dijkstra_node->get_node()->get_list_of_destinations().at(i).get_node_destination())->get_visited()) || shortest_next_dijkstra ==
                                                                                                                                           nullptr) // get the shortest distance to neighbour
                {
                    shortest_next_dijkstra = this->get_dijkstra_from_node(current_dijkstra_node->get_node()->get_list_of_destinations().at(i).get_node_destination());
                }
            }

        }
        current_dijkstra_node->set_visited_true();
        current_dijkstra_node = shortest_next_dijkstra;
        shortest_next_dijkstra = nullptr;
    }


//    for (int i = 0; i < m_dijkstra_list.at(0).get_node()->get_list_of_destinations().size(); ++i) {
//        this->get_dijkstra_from_node(*m_dijkstra_list.at(i).get_node())->set_distance(m_dijkstra_list.at(0).get_node()->get_list_of_destinations().at(i).distance());
//        if (m_dijkstra_list.at(0).get_node()->get_list_of_destinations().at(i).distance() < shortest_dijkstra->get_dist() || shortest_dijkstra ==
//                                                                                                                                     nullptr)
//        {
//            shortest_dijkstra = &m_dijkstra_list.at(i);
//        }
//
//
//    }
    //m_dijkstra_list.at(0).get_node()->get_list_of_destinations()





//    for (int i = 0; i < m_dijkstra_list.size(); ++i) // go through all the members of dijkstra list
//    {
//         //go through all the neighbours of the node
//        for (int j = 0; j < m_dijkstra_list.at(i).get_node()->get_list_of_destinations().size(); ++j)
//        {
//            //this->get_dijkstra_neighbour(i,j);
//        }
//    }
}

node *dijkstra::get_node()
{
    return m_node;
}

dijkstra * dijkstra_list::get_dijkstra_at(int node_nr)
{
    return& m_dijkstra_list.at(node_nr);
}

dijkstra *dijkstra_list::get_dijkstra_neighbour(int node_nr, int node_neighbour_nr)
{
    for (int i = 0; i < m_dijkstra_list.size(); ++i) {
        if (m_dijkstra_list.at(i).get_node() == &m_dijkstra_list.at(node_nr).get_node()->get_list_of_destinations().at(node_neighbour_nr).destination_node())
        {
            return &m_dijkstra_list.at(i);
        }
    }
    return nullptr;
//     m_dijkstra_list.at(node_nr).get_node()->get_list_of_destinations().at(node_neighbour_nr);
}

dijkstra *dijkstra_list::get_dijkstra_from_node(node &the_node)
{
    for (int i = 0; i < m_dijkstra_list.size(); ++i) {
        if (m_dijkstra_list.at(i).get_node() == &the_node)
        {
            return &m_dijkstra_list.at(i);
        }
    }

    return nullptr;
}

void dijkstra::set_distance(int distance)
{
    m_distance_from_root_node = distance;
}

void dijkstra::set_previous_node(node *prev_node)
{
    m_previous_node = prev_node;
}

bool dijkstra::get_visited()
{
    return m_visited;
}

void dijkstra::set_visited_true()
{
    m_visited = true;
}

bool dijkstra_list::has_unvisited()
{
    for (int i = 0; i < m_dijkstra_list.size(); ++i) {
        if (!m_dijkstra_list.at(i).get_visited())
        {
            return true;
        }
    }
    return false;
}