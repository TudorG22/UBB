#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string input_file = argc > 1 ? argv[1] : "in.txt";
    string output_file = argc > 2 ? argv[2] : "out.txt";

    ifstream fin(input_file);
    ofstream fout(output_file);
    if (!fin || !fout) {
        return 1;
    }

    int n;
    fin >> n;

    vector<pair<int, int>> edges;
    int x, y;
    while (fin >> x >> y) {
        --x;
        --y;
        edges.push_back({x, y});
    }

    vector<vector<int>> a(n, vector<int>(n, 0));
    for (const auto& edge : edges) {
        a[edge.first][edge.second] = 1;
        a[edge.second][edge.first] = 1;
    }

    fout << "Matrice de adiacenta\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << a[i][j] << (j + 1 == n ? '\n' : ' ');
        }
    }

    vector<vector<int>> lista(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) {
                lista[i].push_back(j + 1);
            }
        }
    }

    fout << "Lista de adiacenta\n";
    for (int i = 0; i < n; ++i) {
        fout << i + 1 << ":";
        for (int nod : lista[i]) {
            fout << ' ' << nod;
        }
        fout << '\n';
    }

    vector<vector<int>> incidenta(n, vector<int>(static_cast<int>(edges.size()), 0));
    for (int i = 0; i < (int)edges.size(); ++i) {
        incidenta[edges[i].first][i] = 1;
        incidenta[edges[i].second][i] = 1;
    }

    fout << "Matrice de incidenta\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)edges.size(); ++j) {
            fout << incidenta[i][j] << (j + 1 == (int)edges.size() ? '\n' : ' ');
        }
        if (edges.empty()) {
            fout << '\n';
        }
    }

    return 0;
}
