#include <bits/stdc++.h>
#define PI 3.141593

const int vertex_num = 3, texture_vertex_num = 2, index_num = 3;
const double INF = 999.0;
std::string line;
std::string prefix;
double point[5]; 

double max_coord[3] = {-INF, -INF, -INF}, min_coord[3] = {INF, INF, INF};

// transformation from 3D to 2D

std::vector<std::string> split_slash(std::string &s, const char split);
void write_cover_params();
void get_param();
void cal();

int main() {
    get_param();
    cal();
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

void get_param() {
    std::string input_file = "corn5.obj";
    std::string output_file = "v1.obj";

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

                // 获取包围盒参数
                max_coord[i] = std::max(max_coord[i], point[i]);
                min_coord[i] = std::min(min_coord[i], point[i]);

                // normalization
                point[i] -= (max_coord[i] + min_coord[i]) / 2;      // 平移到中心点
                point[i] /= max_coord[i] - min_coord[i];
            }

            std::swap(point[1], point[2]);

            for (int i = 0; i < vertex_num; ++ i) {
                if (i == 0) {
                    point[i] = (PI + std::atan2(point[2], point[0])) / (PI * 2);
                } else if (i == 1) {
                    point[i] = (1 + point[1]) / 2;
                } else {
                    point[i] = 1.0;
                }

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

    write_cover_params();

    fin.close();
    fout.close();
}

void cal() {
    std::string input_file = "corn5.obj";
    std::string output_file = "v2.obj";

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

#if 0
                // 获取包围盒参数
                max_coord[i] = std::max(max_coord[i], point[i]);
                min_coord[i] = std::min(min_coord[i], point[i]);
#endif
                // normalization
                point[i] -= (max_coord[i] + min_coord[i]) / 2;      // 平移到中心点
                point[i] /= max_coord[i] - min_coord[i];
            }

            std::swap(point[1], point[2]);

            for (int i = 0; i < vertex_num; ++ i) {
                if (i == 0) {
                    point[i] = (PI + std::atan2(point[2], point[0])) / (PI * 2);
                } else if (i == 1) {
                    point[i] = (1 + point[1]) / 2;
                } else {
                    point[i] = 1.0;
                }

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

    fin.close();
    fout.close();
}

void write_cover_params() {
    std::string output_file_cover = "cover_params.txt";
    std::fstream fout_cover;
    fout_cover.open(output_file_cover, std::ios::app);

    fout_cover << "MAX:" << std::endl;
    for (int i = 0; i < 3; ++ i) {
        fout_cover << std::setiosflags(std::ios::fixed) << std::setprecision(6) << max_coord[i] << ' ';
    }
    fout_cover << std::endl;

    fout_cover << "MIN:" << std::endl;
    for (int i = 0; i < 3; ++ i) {
        fout_cover << std::setiosflags(std::ios::fixed) << std::setprecision(6) << min_coord[i] << ' ';
    }
    fout_cover << std::endl;

    fout_cover.close();
}