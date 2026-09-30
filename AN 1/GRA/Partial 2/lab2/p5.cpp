#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void dfs(int node, const vector<vector<int>>& g, vector<int>& viz) {
    viz[node] = 1;
    cout << node << ' ';
    for (int vecin : g[node]) {
        if (!viz[vecin]) {
            dfs(vecin, g, viz);
        }
    }
}

int main(int argc, char* argv[]) {
    string input_file = argc > 1 ? argv[1] : "graf.txt";
    ifstream fin(input_file);
    if (!fin) {
        return 1;
    }

    int n;
    fin >> n;
    vector<vector<int>> g(n);
    int x, y;
    while (fin >> x >> y) {
        g[x].push_back(y);
    }

    vector<int> viz(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!viz[i]) {
            dfs(i, g, viz);
            cout << '\n';
        }
    }

    return 0;
}
