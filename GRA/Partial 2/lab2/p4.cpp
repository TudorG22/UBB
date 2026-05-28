#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

    int sursa;
    cin >> sursa;

    vector<int> dist(n, -1);
    queue<int> q;
    q.push(sursa);
    dist[sursa] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << ' ' << dist[node] << '\n';
        for (int vecin : g[node]) {
            if (dist[vecin] == -1) {
                dist[vecin] = dist[node] + 1;
                q.push(vecin);
            }
        }
    }

    return 0;
}
