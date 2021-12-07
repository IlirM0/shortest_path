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
    dijkstra * current_node = this->give_next_unexplored_shortest();
    //std::cout << "hal;p" << '\n';
    while(this->has_unvisited())
    {
        std::cout << "hal;p" << '\n';
        current_node->set_visited_true();
        for (int i = 0; i < current_node->get_node()->get_list_of_destinations().size(); ++i)
        {
            if (!this->get_dijkstra_from_node(current_node->get_node()->get_list_of_destinations().at(i).get_node_destination())->get_visited())
            { // ga naar elke neighbour
                if (this->get_dijkstra_from_node(current_node->get_node()->get_list_of_destinations().at(i).get_node_destination())->get_dist() > (current_node->get_dist() + current_node->get_node()->get_list_of_destinations().at(i).distance()))
                { // kijk of current dist groter is. zo ja, verander.
                    this->get_dijkstra_from_node(current_node->get_node()->get_list_of_destinations().at(i).get_node_destination())->set_distance(current_node->get_dist() + current_node->get_node()->get_list_of_destinations().at(i).distance());
                }
            }
        }
        current_node = this->give_next_unexplored_shortest();
    }

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

dijkstra *dijkstra_list::give_next_unexplored_shortest()
{
    dijkstra * dijkstra_to_send = nullptr;
    for (int i = 0; i < m_dijkstra_list.size(); ++i) {
        if (!m_dijkstra_list.at(i).get_visited())
        {
            if (dijkstra_to_send == nullptr || m_dijkstra_list.at(i).get_dist() < dijkstra_to_send->get_dist())
            {
                dijkstra_to_send = &m_dijkstra_list.at(i);
            }
        }
    }
    return dijkstra_to_send;
}

int dijkstra::get_name()
{
    return m_node->name();
}