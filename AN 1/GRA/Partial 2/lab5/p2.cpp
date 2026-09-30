#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

void add_edge(vector<vector<Edge>>& g, int x, int y, int cap) {
    g[x].push_back({y, (int)g[y].size(), cap});
    g[y].push_back({x, (int)g[x].size() - 1, 0});
}

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
    vector<vector<Edge>> g(V);
    for (int i = 0; i < E; ++i) {
        int x, y, c;
        fin >> x >> y >> c;
        add_edge(g, x, y, c);
    }

    int s = 0, t = V - 1;
    vector<int> h(V, 0), excess(V, 0), ptr(V, 0);

    h[s] = V;
    for (auto& e : g[s]) {
        int pushed = e.cap;
        e.cap = 0;
        g[e.to][e.rev].cap += pushed;
        excess[e.to] += pushed;
        excess[s] -= pushed;
    }

    queue<int> q;
    vector<int> inq(V, 0);
    for (int i = 0; i < V; ++i) {
        if (i != s && i != t && excess[i] > 0) {
            q.push(i);
            inq[i] = 1;
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        inq[node] = 0;

        while (excess[node] > 0) {
            if (ptr[node] == (int)g[node].size()) {
                int new_h = 1000000000;
                for (const auto& e : g[node]) {
                    if (e.cap > 0) {
                        new_h = min(new_h, h[e.to]);
                    }
                }
                h[node] = new_h + 1;
                ptr[node] = 0;
                continue;
            }

            Edge& e = g[node][ptr[node]];
            if (e.cap > 0 && h[node] == h[e.to] + 1) {
                int pushed = min(excess[node], e.cap);
                e.cap -= pushed;
                g[e.to][e.rev].cap += pushed;
                excess[node] -= pushed;
                excess[e.to] += pushed;
                if (e.to != s && e.to != t && !inq[e.to] && excess[e.to] > 0) {
                    q.push(e.to);
                    inq[e.to] = 1;
                }
            } else {
                ptr[node]++;
            }
        }
    }

    fout << excess[t] << '\n';
    return 0;
}
