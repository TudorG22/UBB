#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <utility>
#include <algorithm>
#include <iostream>


using namespace std;

//utils
vector<vector<int>> text_to_ad_matrix(ifstream& fin, int n)
{
    vector<vector<int>> matrix(n, vector<int>(n, INT_MAX));

    string line;

    getline(fin, line); //skip prima linie

    int a, b, c;
    while (getline(fin, line)) {
        istringstream iss(line);
        if (iss >> a >> b >> c) {
            matrix[a][b] = c;
            matrix[b][a] = c;
        }
    }

    return matrix;
}

int nr_of_vertex_from_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n, muchii;
    line_stream >> n >> muchii;

    fin.clear();
    fin.seekg(initial_pos);
    return n;
}


struct Muchie {
    int u;
    int v;
    int cost;
};

vector<Muchie> muchii_din_matrice(vector<vector<int>> matrix, int n)
{
    vector<Muchie> muchii;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != INT_MAX) {
                muchii.push_back({i, j, matrix[i][j]});
            }
        }
    }

    return muchii;
}

int grupa(int varf, vector<int> componenta)
{
    return componenta[varf];
}

void reuneste_grupe(int grupa1, int grupa2, vector<int>& componenta, int n)
{
    for (int i = 0; i < n; i++) {
        if (componenta[i] == grupa2) {
            componenta[i] = grupa1;
        }
    }
}

vector<Muchie> kruskal(vector<vector<int>> matrix, int n)
{
    vector<int> componenta(n);
    for (int v = 0; v < n; v++) {
        componenta[v] = v;
    }

    vector<Muchie> q = muchii_din_matrice(matrix, n);
    sort(q.begin(), q.end(), [](const Muchie& m1, const Muchie& m2) {
        return m1.cost < m2.cost;
    });

    vector<Muchie> arbore;

    for (const auto& muchie : q) {
        if ((int)arbore.size() == n - 1) {
            break;
        }

        int u = muchie.u;
        int v = muchie.v;

        int c_u = grupa(u, componenta);
        int c_v = grupa(v, componenta);

        if (c_v != c_u) {
            arbore.push_back(muchie);
            reuneste_grupe(c_v, c_u, componenta, n);
        }
    }

    return arbore;
}

void afisare(vector<Muchie> arbore, ofstream& fout)
{
    int cost_total = 0;

    for (const Muchie& muchie : arbore) {
        cost_total += muchie.cost;
    }

    fout << cost_total << "\n";
    fout << arbore.size() << "\n";

    for (const auto& muchie : arbore) {
        fout << muchie.u << " " << muchie.v << "\n";
    }
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n = nr_of_vertex_from_text(fin);
    vector<vector<int>> matrix = text_to_ad_matrix(fin, n);

    vector<Muchie> arbore = kruskal(matrix, n);
    afisare(arbore, fout);

    fin.close();
    fout.close();
    return 0;
}
