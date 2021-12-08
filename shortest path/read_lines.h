//
// Created by ilir8 on 5-12-2021.
//

#ifndef SHORTEST_PATH_READ_LINES_H
#define SHORTEST_PATH_READ_LINES_H

#include <iostream>
#include <fstream>
#include <vector>

class path
{
private:
    int m_from;
    int m_to;
    int m_distance;
public:
    path(int from, int to, int distance);
    int from();
    int to();
    int distance();
};

std::vector<path>* read_distribute(std::ifstream & file);

path create_path(std::string line);

#endif //SHORTEST_PATH_READ_LINES_H
