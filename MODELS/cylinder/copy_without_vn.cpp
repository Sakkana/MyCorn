#include <bits/stdc++.h>

const int vertex_num = 3, texture_vertex_num = 2, index_num = 3;
std::string line;
std::string prefix;
double point[5]; 

// transformation from 3D to 2D

std::vector<std::string> split_slash(std::string &s, const char split);
void op();

int main() {
    op();
    return 0;
}

std::vector<std::string> split_slash(std::string &s, const char split) {
    std::string model = s + split;
    std::vector<std::string> res;

    int pos = model.find(split);
    while (pos != model.npos) {
        std::string t = model.substr(0, pos);
        res.push_back(t);
        model = model.substr(pos + 1, model.size());
        pos = model.find(split);
    }
    return res;
}

void op() {
    std::string input_file = "cylinder.obj";
    std::string output_file = "ofile.txt";

    std::ifstream fin;
    std::fstream fout;

    fin.open(input_file);
    fout.open(output_file, std::ios::app);

    fout.setf(std::ios::showpoint);


    // filter the head
    while (std::getline(fin, line)) {

        // filter the head
        if (!(line[0] == 'v' || line[0] == 'f')) {
            fout << line << std::endl;
            continue;
        }

        if (line[0] == 'v' && line[1] == ' ') {
            // split the line to 3 coords in string style
            std::istringstream bottle(line);
            bottle >> prefix;

            fout << prefix << ' ';
            for (int i = 0; i < vertex_num; ++ i) {
                bottle >> point[i];
                fout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << point[i];
                if (i != vertex_num - 1) fout << ' ';
            }
            fout << std::endl;
        } else if (line[0] == 'v' && line[1] == 't') {
            std::istringstream bottle(line);
            bottle >> prefix;

            fout << prefix << ' ';
            for (int i = 0; i < texture_vertex_num; ++ i) {
                bottle >> point[i];
                fout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << point[i];
                if (i != texture_vertex_num - 1) fout << ' ';
            }
            fout << std::endl;
        } else if (line[0] == 'v' && line[1] == 'n') {
            continue;
        } else if (line[0] == 'f' && line[1] == ' ') {
            std::istringstream bottle(line);
            bottle >> prefix;

            fout << prefix << ' ';

            for (int i = 0; i < index_num; ++ i) {
                std::string t;
                bottle >> t;
                std::vector<std::string> v = split_slash(t, '/');
                for (int i = 0; i < index_num - 1; ++ i) {
                    fout << v[i];
                    if (i != index_num - 2) fout << '/';
                }
                if (i != index_num - 1) fout << ' ';
            }
            fout << std::endl;
        }
    }

}