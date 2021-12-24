#include <stdexcept>
#include <iostream>
#include <climits>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct AdjacencyVertex {
    vector<int> adjacency_item;
    string vertex_name;
};

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
        { 0,  4,  0,  0,  0,  0,  0,  8,  0 },
        { 4,  0,  8,  0,  0,  0,  0,  11, 0 },
        { 0,  8,  0,  7,  0,  4,  0,  0,  2 },
        { 0,  0,  7,  0,  9,  14, 0,  0,  0 },
        { 0,  0,  0,  9,  0,  10, 0,  0,  0 },
        { 0,  0,  4,  0,  10, 0,  2,  0,  0 },
        { 0,  0,  0,  14, 0,  2,  0,  1,  6 },
        { 8,  11, 0,  0,  0,  0,  1,  0,  7 },
        { 0,  0,  2,  0,  0,  0,  6,  7,  0 }
    };

    try {
        Path path;
        vector<int> path_vec, srcdest(2);
        string str_input;
        path.updateAdjacencyMatrix(adj_matrix);

        cout << ">> PathNav <<\n(C) 2021 Christopher Digno\n"
            << "Petunjuk:\n -> Masukkan dengan format source <spasi> destinasi\n"
            << " -> Banyak vertex yang dapat dipilih adalah " << path.getVertNum() - 1 << '\n'
            << " -> Masukkan 0 saja untuk keluar dari program\n";

        while (true) {
            try {
                int src, dest;
                int vert_num = (int)path.getVertNum();

                cout << "SRC <spasi> DEST: ";
                getline(cin, str_input);

                if (str_input[0] == '0' && str_input.size() == 1) {
                    return 0;
                }

                srcdest = parseString(str_input);

                for (size_t i = 0; i < srcdest.size(); i++) {
                    if ((srcdest[i] < 0) || (srcdest[i] >= vert_num)) {
                        throw invalid_argument("Masukan berada diluar batas!");
                    }
                }

                src = srcdest[0];
                dest = srcdest[1];

                path_vec.clear();
                path_vec = path.getPathVec(src, dest);

                cout << "Perjalanan: " << src << " => ";

                for (size_t i = 0; i < path_vec.size(); i++) {
                    cout << path_vec[i] << ((i != (path_vec.size() - 1)) ? " => " : " ");
                }

                cout << "\nJarak: " << path.getDistance(src, dest);
                cout << '\n';
            }
            catch (exception &e) {
                cout << "Error -> " << e.what() << '\n';
            }
        }
    }
    catch (const exception &e) {
        cout << "Error -> " << e.what() << '\n';
    }
}

/*
2 to 0             12        1 0
2 to 1             8         1
2 to 2             0
2 to 3             7         3
2 to 4             14        5 4
2 to 5             4         5
2 to 6             6         5 6
2 to 7             7         5 6 7
2 to 8             2         8
*/