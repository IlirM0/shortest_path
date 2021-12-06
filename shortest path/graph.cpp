//
// Created by ilir8 on 5-12-2021.
//

#include "graph.h"

graph::graph(std::vector<path> &paths)
{
    m_nodes_size = 0;
    for (int i = 0; i < paths.size(); ++i) {
        //for (int j = 0; j < paths.size(); ++j) {
        if (exists(paths.at(i).from()) != nullptr) {
            if (exists(paths.at(i).to()) != nullptr) // to and from exist.
            {
                //std::cout << "to and from exist" << '\n';


                node_destination note_to_add{exists(paths.at(i).to()),
                                             paths.at(i).distance(), paths.at(i).to()}; // create node_destination

                exists(paths.at(i).from())->add_node_destination(
                        note_to_add); // add node destination to the list of the actual node.

            } else // from exists, to not.
            {
                //std::cout << "from exists, to not" << '\n';
                node to_node{paths.at(i).to()};
                m_graph.push_back(to_node);
                m_nodes_size++;

                node_destination note_to_add{exists(paths.at(i).to()),
                                             paths.at(i).distance(), paths.at(i).to()}; // create node_destination

                exists(paths.at(i).from())->add_node_destination(note_to_add);

            }

        } else {
            if (exists(paths.at(i).to()) != nullptr) // to exists, from not.
            {
                //std::cout << "to exists, from not" << '\n';
                node from_node{paths.at(i).from()};
                m_graph.push_back(from_node);
                m_nodes_size++;

                node_destination note_to_add{exists(paths.at(i).to()),
                                             paths.at(i).distance(), paths.at(i).to()}; // create node_destination

                exists(paths.at(i).from())->add_node_destination(note_to_add);
            } else // both dont exists.
            {
                node from_node{paths.at(i).from()};
                m_graph.push_back(from_node);
                m_nodes_size++;

                //std::cout << "both dont exists" << '\n';
                node to_node{paths.at(i).to()};
                m_graph.push_back(to_node);
                m_nodes_size++;

                node_destination note_to_add{exists(paths.at(i).to()),
                                             paths.at(i).distance(), paths.at(i).to()}; // create node_destination

                exists(paths.at(i).from())->add_node_destination(note_to_add);
            }
        }
    //}
    }
}

int node::name()
{
    return m_node_name;
}

node::node(int name) : m_node_name{name}
{}

node *graph::exists(int name)
{
    node * this_node = nullptr;
    for (int i = 0; i < m_graph.size(); ++i) {
        if (name == m_graph.at(i).name())
        {
            this_node = &m_graph.at(i);
        }
    }
    return this_node;
}

void graph::add_node(node add_node)
{
    m_graph.push_back(add_node);
}

void node::add_node_destination(node_destination node_destination_add)
{
    m_list_of_destinations.push_back(node_destination_add);
}

node_destination::node_destination(node *destination_node, int distance, int dest_node_name): m_destination_node{destination_node}, m_distance{distance}, m_dest_node_name{dest_node_name}
{

}

int graph::get_dir_distance(int name_from, int name_to)
{
    if (!element_exists(name_from) && !element_exists(name_to))
    {
        return -2;
    }
    if (exists(name_from) != nullptr)
    {
        if (exists(name_to) != nullptr)
        {
            return exists(name_from)->search_distance(name_to);
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -2;
    }
}

int node::search_distance(int name_to)
{
    for (int i = 0; i < m_list_of_destinations.size(); ++i) {
        //std::cout << "ik kom hier" << '\n';
        if (m_list_of_destinations.at(i).destination_node_name() == name_to)
        {
            //std::cout << "ik kom hier2" << '\n';
            return m_list_of_destinations.at(i).distance();
        }
        else
        {
            //std::cout<< "dest. name: " << m_list_of_destinations.at(i).destination_node_name() << '\n';
            //std::cout<< "dist. : " << m_list_of_destinations.at(i).distance() << '\n';
            //std::cout<< "to name: " << name_to << '\n';
        }
    }
    return -1;
}

int node_destination::distance()
{
    return m_distance;
}

node &node_destination::destination_node()
{
    return *m_destination_node;
}

int graph::size()
{
    return m_nodes_size;
}

int graph::get_name_at(int at)
{
    if (!element_exists(at))
    {
        return -2;
    }
    return m_graph.at(at).name();
}

int node_destination::destination_node_name()
{
    return m_dest_node_name;
}

bool graph::element_exists(int size)
{
    if (size >= m_nodes_size)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::vector<node>* graph::get_graph()
{
    return& m_graph;
}

node &node_destination::get_node_destination()
{
    return * m_destination_node;
}

std::vector<node_destination> &node::get_list_of_destinations()
{
    return m_list_of_destinations;
}