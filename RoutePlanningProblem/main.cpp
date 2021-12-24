#include <stdexcept>
#include <iostream>
#include <climits>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// struct Coords {
//     int coordX, coordY;

//     Coords() {
//         coordX = coordY = 0;
//     }
// };

// struct AdjacencyVertex {
//     vector<int> adjacency_item;
//     string vertex_name;
// };

struct VInfo {
    int dist, parent;
    bool is_included;

    VInfo() {
        parent = -1;
        dist = INT_MAX;
        is_included = false;
    }
};

class Path {
private:
    vector<vector<int>> adj_matrix;
    vector<VInfo> vert_info;
    int last_dijkstra_src;

    int _shortestDistance(vector<VInfo> &vert_info) {
        int min = INT_MAX,
            min_in;

        for (size_t i = 0; i < vert_info.size(); i++) {
            if (vert_info[i].is_included == false && vert_info[i].dist < min) {
                min = vert_info[i].dist;
                min_in = i;
            }
        }

        return min_in;
    }

    void _updateDijkstra(int src) {
        if (adj_matrix.empty()) {
            throw invalid_argument("SISTEM: Adjacency Matrix belum diset!!");
        }

        const size_t vert_num = adj_matrix.size();
        vector<VInfo> vert_info(vert_num);
        vert_info[src].dist = 0;

        for (size_t c = 0; c < (vert_num - 1); c++) {
            int next_vertex = _shortestDistance(vert_info);
            vert_info[next_vertex].is_included = true;

            for (size_t i = 0; i < vert_num; i++) {
                if (!vert_info[i].is_included && adj_matrix[next_vertex][i] &&
                    ((vert_info[next_vertex].dist + adj_matrix[next_vertex][i]) < vert_info[i].dist)) {
                    vert_info[i].parent = next_vertex;
                    vert_info[i].dist = vert_info[next_vertex].dist + adj_matrix[next_vertex][i];
                }
            }
        }

        this->vert_info = vert_info;
        last_dijkstra_src = src;
    }

    void _seekPath(int dest, vector<int> &path_vec) {
        if (vert_info[dest].parent != -1) {
            _seekPath(vert_info[dest].parent, path_vec);
            path_vec.push_back(dest);
        }
    }

public:
    Path() {
        adj_matrix.clear();
    }

    void updateAdjacencyMatrix(vector<vector<int>> &adj_matrix) {
        this->adj_matrix = adj_matrix;
    }

    int getDistance(int src, int dest) {
        _updateDijkstra(src);
        return vert_info[dest].dist;
    }

    size_t getVertNum() {
        return (adj_matrix.size());
    }

    vector<int> getPathVec(int src, int dest) {
        vector<int> path_vec;
        if (src != last_dijkstra_src) {
            _updateDijkstra(src);
        }
        _seekPath(dest, path_vec);
        return path_vec;
    }
};

vector<int> parseString(string str) {
    vector<int> ret_vec;
    stringstream ss(str);
    string token_str;
    int token_int;

    while (getline(ss, token_str, ' ')) {
        if (!token_str.empty()) {
            try {
                token_int = stoi(token_str);
                ret_vec.push_back(token_int);
            }
            catch (exception &e) {
                throw invalid_argument("Tidak dapat memasukkan non-angka!");
            }
        }
    }

    if (ret_vec.size() != 2) {
        throw invalid_argument("Masukan harus 2 mengandung nilai integer");
    }

    return ret_vec;
}

int main() {
    vector<vector<int>> adj_matrix = {
        { 0,  0,  21, 0,  0,  32, 17, 10, 0,  0,  20, 0,  0,  0,  0  },
        { 0,  0,  0,  0,  12, 0,  0,  0,  0,  0,  0,  16, 13, 0,  0  },
        { 21, 0,  0,  0,  0,  14, 0,  0,  0,  0,  50, 17, 0,  19, 0  },
        { 0,  0,  0,  0,  34, 0,  0,  0,  0,  0,  17, 0,  0,  0,  36 },
        { 0,  12, 0,  34, 0,  0,  0,  0,  0,  0,  15, 30, 0,  0,  0  },
        { 32, 0,  14, 0,  0,  0,  0,  21, 0,  9,  0,  0,  0,  0,  0  },
        { 17, 0,  0,  0,  0,  0,  0,  0,  28, 0,  14, 0,  0,  0,  40 },
        { 10, 0,  0,  0,  0,  21, 0,  0,  23, 11, 0,  0,  0,  0,  0  },
        { 0,  0,  0,  0,  0,  0,  28, 23, 0,  40, 0,  0,  0,  0,  0  },
        { 0,  0,  0,  0,  0,  9,  0,  11, 40, 0,  0,  0,  0,  27, 0  },
        { 20, 0,  50, 17, 15, 0,  14, 0,  0,  0,  0,  27, 0,  0,  24 },
        { 0,  16, 17, 0,  30, 0,  0,  0,  0,  0,  27, 0,  26, 0,  0  },
        { 0,  13, 0,  0,  0,  0,  0,  0,  0,  0,  0,  26, 0,  24, 0  },
        { 0,  0,  19, 0,  0,  0,  0,  0,  0,  27, 0,  0,  24, 0,  0  },
        { 0,  0,  0,  36, 0,  0,  40, 0,  0,  0,  24, 0,  0,  0,  0  },

    };

    vector<string> vert_names = {
        "Alpha", "Bravo", "Charlie", "Delta",
        "Echo", "Foxtrot", "Golf", "Hotel",
        "India", "Juliett", "Kilo", "Lima",
        "Mike", "November", "Oscar"
    };

    try {
        Path path;
        vector<int> path_vec, srcdest(2);
        string str_input, src_str, dest_str, temp_str;
        bool hit_src, hit_dest;

        path.updateAdjacencyMatrix(adj_matrix);
        int src, dest;

        if (adj_matrix.size() != vert_names.size()) {
            throw invalid_argument("SISTEM: Nama dan Vertex tidak sama besar!");
        }

        cout << ">> PathNav <<\n(C) 2021 Christopher Digno\n"
            << "Selamat datang di Kota Phonetics! Petunjuk:\n"
            << " -> Banyak vertex yang dapat dipilih adalah " << path.getVertNum() << '\n'
            << " -> Nama-nama vertex yang dapat dipilih adalah alfabet fonetis dari Alpha (1) hingga Oscar (15)\n"
            << " -> Masukkan 0 saja untuk keluar dari program\n";

        while (true) {
            try {
                cout << "\nKota Awal: ";
                getline(cin, src_str);
                if (src_str[0] == '0' && src_str.size() == 1) {
                    return 0;
                }

                cout << "Destinasi: ";
                getline(cin, dest_str);
                if (dest_str[0] == '0' && dest_str.size() == 1) {
                    return 0;
                }

                hit_src = hit_dest = false;
                for (size_t i = 0; i < vert_names.size(); i++) {
                    if (src_str == vert_names[i]) {
                        hit_src = true;
                        src = i;
                    }
                    if (dest_str == vert_names[i]) {
                        hit_dest = true;
                        dest = i;
                    }
                }

                if (!hit_dest && !hit_src) {
                    throw invalid_argument("Kota awal dan tujuan tidak dikenali!");
                }
                else if (!hit_src) {
                    throw invalid_argument("Kota awal tidak dikenali!");
                }
                else if (!hit_dest) {
                    throw invalid_argument("Kota tujuan tidak dikenali!");
                }

                if (dest == src) {
                    throw invalid_argument("Kota awal dan Destinasi sama!");
                }

                path_vec.clear();
                path_vec = path.getPathVec(src, dest);

                cout << "Rute Perjalanan : " << vert_names[src] << " => ";

                for (size_t i = 0; i < path_vec.size(); i++) {
                    cout << vert_names[path_vec[i]] << ((i != (path_vec.size() - 1)) ? " => " : " ");
                }

                cout << "\nJarak Perjalanan: " << path.getDistance(src, dest);
                cout << " klik\n";
            }
            catch (exception &e) {
                cout << "(!)-> " << e.what() << '\n';
            }
        }
    }
    catch (const exception &e) {
        cout << "Error -> " << e.what() << '\n';
    }
}