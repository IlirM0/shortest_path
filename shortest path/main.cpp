#include <iostream>
#include <fstream>
#include <vector>
#include "read_lines.h"
#include "graph.h"
#include "dijkstra.h"

int main() {
    std::ifstream file("test.txt");

    std::vector<path> * paths = read_distribute(file);
    file.close();
    //std::cout << paths->at(0).distance() << '\n';

    graph g{*paths};

    //std::cout << g.get_dir_distance(3,4) << '\n';
    //std::cout << g.get_name_at(4) << '\n';

    dijkstra_list d{g.get_graph()->at(1), g};

    std::cout << "pre-dijkstra: " <<d.get_dijkstra_list()->at(2).get_dist()<< '\n';

    d.dijkstra_routine();

    std::cout << "post-dijkstra: " << d.get_dijkstra_list()->at(2).get_dist()<< '\n';





    return 0;
}
