#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Edge {
    int x;
    int y;
    int w;
};

struct DSU {
    vector<int> parent;
    vector<int> sz;

    explicit DSU(int n) : parent(n), sz(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
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
    for (int i = 0; i < E; ++i) {
        fin >> edges[i].x >> edges[i].y >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (a.w != b.w) return a.w < b.w;
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    DSU dsu(V);
    int cost = 0;
    vector<pair<int, int>> sol;
    for (const auto& e : edges) {
        if (dsu.unite(e.x, e.y)) {
            cost += e.w;
            sol.push_back({e.x, e.y});
        }
    }

    fout << cost << '\n';
    fout << sol.size() << '\n';
    for (const auto& edge : sol) {
        fout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}
