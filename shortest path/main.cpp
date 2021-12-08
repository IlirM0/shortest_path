#include <iostream>
#include <fstream>
#include <vector>
#include "read_lines.h"
#include "graph.h"
#include "dijkstra.h"

int main() {
    //std::ifstream file("USA-road-d.NY.txt");
    std::ifstream file("test.txt");
    std::vector<path> *paths = read_distribute(file);
    file.close();


    //std::cout << paths->at(0).distance() << '\n';

    graph g{*paths};


    //std::cout << g.get_dir_distance(3,4) << '\n';
    //std::cout << g.get_name_at(4) << '\n';

    dijkstra_list d{g.get_graph()->at(3), g};

    //std::cout << d.get_root_node_name() << '\n';

//    std::cout << "OUTSIDE test: "<< d.get_dijkstra_from_node(g.exists(g.get_graph()->at(0).get_list_of_destinations().at(0).destination_node_name()))->get_name()<< '\n';
//
//    for (int j = 0; j < g.get_graph()->size(); ++j) {
//        std::cout << "test name: " << g.get_graph()->at(j).name() << '\n';
//        for (int i = 0; i < g.get_graph()->at(j).get_list_of_destinations().size(); ++i) {
//            std::cout << "test: "<< g.get_graph()->at(j).get_list_of_destinations().at(i).destination_node_name() << '\n';
//        }
//    }



    //std::cout << "pre-dijkstra name node: " << d.get_dijkstra_list()->at(0).get_node()->get_list_of_destinations().at(1).destination_node_name()<< '\n';
//    std::cout << "NAME: " <<d.get_dijkstra_list()->at(2).get_name()<< '\n';
//    std::cout << "pre-dijkstra: " <<d.get_dijkstra_list()->at(2).get_dist()<< '\n';

    d.dijkstra_routine();

//    std::cout << "post-dijkstra: " << d.get_dijkstra_list()->at(2).get_dist()<< '\n';
//
//    for (int i = 0; i < d.get_dijkstra_list()->size(); ++i) {
//        std::cout << "curr node: " << d.get_dijkstra_list()->at(i).get_name() << '\n';
//        std::cout << "prev node: " << d.get_dijkstra_list()->at(i).get_previous_node_name() << '\n';
//
//    }

    d.give_path_to_root(2);


    return 0;
}
