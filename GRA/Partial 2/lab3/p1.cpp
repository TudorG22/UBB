#include <fstream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if (!fin || !fout) {
        return 1;
    }

    int V, E, S;
    fin >> V >> E >> S;

    vector<vector<pair<int, int>>> g(V);
    for (int i = 0; i < E; ++i) {
        int x, y, w;
        fin >> x >> y >> w;
        g[x].push_back({y, w});
    }

    const long long INF = (1LL << 60);
    vector<long long> dist(V, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        if (d != dist[node]) {
            continue;
        }

        for (const auto& edge : g[node]) {
            int to = edge.first;
            int cost = edge.second;
            if (dist[node] + cost < dist[to]) {
                dist[to] = dist[node] + cost;
                pq.push({dist[to], to});
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            fout << "INF";
        } else {
            fout << dist[i];
        }
        fout << (i + 1 == V ? '\n' : ' ');
    }

    return 0;
}
