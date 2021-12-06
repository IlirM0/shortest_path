//
// Created by ilir8 on 5-12-2021.
//

#include "read_lines.h"

path::path(int from, int to, int distance): m_from{from}, m_to{to}, m_distance{distance}
{}

int path::from()
{
    return m_from;
}
int path::to()
{
    return m_to;
}
int path::distance()
{
    return m_distance;
}

std::vector<path> * read_distribute(std::ifstream & file) {
    auto *paths = new std::vector<path>;
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line))
        {
            if (line[0] == 'a')
            {
                path temp_path = create_path(line);
                //std::cout << "path\nfrom: " << temp_path.from() << "\nto: " << temp_path.to() << "\ndist: " << temp_path.distance() << "\n\n";
                paths->push_back(temp_path);
            }
        }
        return paths;
    }
    return nullptr;
}

path create_path(std::string line)
{
    std::string temp_string;

    int i_from;
    int i_to;
    int i_dist;

    int iteration_variable = 0;
    for (int i = 2; i < line.length(); ++i) {
        if (line[i] == ' ')
        {
            switch (iteration_variable) {
                case 0:
                    i_from = std::stoi(temp_string);
                    break;
                case 1:
                    i_to = std::stoi(temp_string);
                    break;
                case 2:
                    i_dist = std::stoi(temp_string);
                    break;
                default:
                    std::cout<< "ERROR: cant find iteration_variable in create_line function!" << '\n';
                    break;
            }
            temp_string = "";
            iteration_variable++;
        }
        else
        {
            temp_string.push_back(line[i]);
        }
        if (line[i+1] == '\0' && iteration_variable == 2)
        {
            i_dist = std::stoi(temp_string);
        }
    }

    path temp_path{i_from,i_to,i_dist};
    return temp_path;
}