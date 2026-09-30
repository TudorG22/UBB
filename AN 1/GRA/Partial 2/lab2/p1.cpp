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

    vector<int> dist(n, -1), parinte(n, -1);
    queue<int> q;
    dist[sursa] = 0;
    q.push(sursa);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int vecin : g[node]) {
            if (dist[vecin] == -1) {
                dist[vecin] = dist[node] + 1;
                parinte[vecin] = node;
                q.push(vecin);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        if (dist[i] == -1) {
            cout << "nu exista drum\n";
            continue;
        }

        vector<int> drum;
        for (int node = i; node != -1; node = parinte[node]) {
            drum.push_back(node);
        }

        for (int j = (int)drum.size() - 1; j >= 0; --j) {
            cout << drum[j] << (j == 0 ? '\n' : ' ');
        }
    }

    return 0;
}
