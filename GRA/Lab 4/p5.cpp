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

vector<Muchie> muchii_din_text(ifstream& fin)
{
    vector<Muchie> muchii;
    string line;

    getline(fin, line); //skip prima linie

    int a, b, c;
    while (getline(fin, line)) {
        istringstream iss(line);
        if (iss >> a >> b >> c) {
            muchii.push_back({a, b, c});
        }
    }

    return muchii;
}

void reuneste_grupe(int grupa1, int grupa2, vector<int>& grup, int n)
{
    for (int i = 0; i < n; i++) {
        if (grup[i] == grupa2) {
            grup[i] = grupa1;
        }
    }
}

vector<Muchie> kruskal(vector<Muchie> q, int n)
{
    vector<int> grup(n);
    for (int v = 0; v < n; v++) {
        grup[v] = v;
    }

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

        int c_u = grup[u];
        int c_v = grup[v];

        if (c_v != c_u) {
            arbore.push_back(muchie);
            reuneste_grupe(c_v, c_u, grup, n);
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
    vector<Muchie> muchii = muchii_din_text(fin);

    vector<Muchie> arbore = kruskal(muchii, n);
    afisare(arbore, fout);

    fin.close();
    fout.close();
    return 0;
}
