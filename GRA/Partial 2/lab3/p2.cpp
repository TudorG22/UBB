#include <algorithm>
#include <fstream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int x;
    int y;
    long long w;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if (!fin || !fout) {
        return 1;
    }

    int V, E;
    fin >> V >> E;

    vector<Edge> edges(E);
    vector<vector<pair<int, long long>>> g(V);
    for (int i = 0; i < E; ++i) {
        fin >> edges[i].x >> edges[i].y >> edges[i].w;
    }

    vector<long long> h(V + 1, 0);
    vector<Edge> ext = edges;
    for (int i = 0; i < V; ++i) {
        ext.push_back({V, i, 0});
    }

    for (int step = 0; step < V; ++step) {
        bool changed = false;
        for (const auto& e : ext) {
            if (h[e.x] + e.w < h[e.y]) {
                h[e.y] = h[e.x] + e.w;
                changed = true;
            }
        }
        if (!changed) {
            break;
        }
    }

    for (const auto& e : ext) {
        if (h[e.x] + e.w < h[e.y]) {
            fout << -1 << '\n';
            return 0;
        }
    }

    vector<Edge> reweighted = edges;
    for (int i = 0; i < E; ++i) {
        reweighted[i].w = edges[i].w + h[edges[i].x] - h[edges[i].y];
        g[edges[i].x].push_back({edges[i].y, reweighted[i].w});
    }

    sort(reweighted.begin(), reweighted.end(), [](const Edge& a, const Edge& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    for (const auto& e : reweighted) {
        fout << e.x << ' ' << e.y << ' ' << e.w << '\n';
    }

    const long long INF = (1LL << 60);
    for (int src = 0; src < V; ++src) {
        vector<long long> dist(V, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (d != dist[node]) {
                continue;
            }
            for (const auto& edge : g[node]) {
                int to = edge.first;
                long long cost = edge.second;
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
                fout << dist[i] - h[src] + h[i];
            }
            fout << (i + 1 == V ? '\n' : ' ');
        }
    }

    return 0;
}
