#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
    int original_cap;
};

void add_edge(vector<vector<Edge>>& g, int x, int y, int cap) {
    g[x].push_back({y, (int)g[y].size(), cap, cap});
    g[y].push_back({x, (int)g[x].size() - 1, 0, 0});
}

int maxflow(vector<vector<Edge>> g, int s, int t, vector<int>& dorm_flow, int dorms) {
    int n = (int)g.size();
    int flow = 0;

    while (true) {
        vector<int> par_node(n, -1), par_edge(n, -1);
        queue<int> q;
        q.push(s);
        par_node[s] = s;

        while (!q.empty() && par_node[t] == -1) {
            int node = q.front();
            q.pop();
            for (int i = 0; i < (int)g[node].size(); ++i) {
                if (g[node][i].cap > 0 && par_node[g[node][i].to] == -1) {
                    par_node[g[node][i].to] = node;
                    par_edge[g[node][i].to] = i;
                    q.push(g[node][i].to);
                }
            }
        }

        if (par_node[t] == -1) {
            break;
        }

        int add = 1000000000;
        for (int node = t; node != s; node = par_node[node]) {
            add = min(add, g[par_node[node]][par_edge[node]].cap);
        }

        for (int node = t; node != s; node = par_node[node]) {
            Edge& e = g[par_node[node]][par_edge[node]];
            e.cap -= add;
            g[node][e.rev].cap += add;
        }
        flow += add;
    }

    dorm_flow.assign(dorms, 0);
    for (int i = 0; i < dorms; ++i) {
        for (const auto& e : g[s]) {
            if (e.to == i) {
                dorm_flow[i] = e.original_cap - e.cap;
            }
        }
    }

    return flow;
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

    int N, C, D;
    fin >> N >> C >> D;
    vector<tuple<int, int, int>> edges;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < D; ++i) {
        int x, y, m;
        fin >> x >> y >> m;
        edges.push_back({x, y, m});
        if (dist[x][y] == -1) {
            dist[x][y] = 1;
        }
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    int cand = dist[i][k] + dist[k][j];
                    if (dist[i][j] == -1 || cand < dist[i][j]) {
                        dist[i][j] = cand;
                    }
                }
            }
        }
    }

    int target = N - 1;
    int best_flow = 0;
    vector<int> best_dorms(C, 0);

    for (int T = 1; T <= N - 1; ++T) {
        int total_nodes = (T + 1) * N + 1;
        int source = total_nodes - 1;
        vector<vector<Edge>> g(total_nodes);

        for (int dorm = 0; dorm < C; ++dorm) {
            if (dist[dorm][target] != -1 && dist[dorm][target] <= T) {
                add_edge(g, source, dorm, 1000000000);
            }
        }

        for (int time = 0; time < T; ++time) {
            for (const auto& edge : edges) {
                int x, y, cap;
                tie(x, y, cap) = edge;
                add_edge(g, time * N + x, (time + 1) * N + y, cap);
            }
        }

        vector<int> dorm_flow;
        int flow = maxflow(g, source, T * N + target, dorm_flow, C);
        if (flow > best_flow) {
            best_flow = flow;
            best_dorms = dorm_flow;
        }
    }

    fout << best_flow << '\n';
    for (int i = 0; i < C; ++i) {
        fout << best_dorms[i] << (i + 1 == C ? '\n' : ' ');
    }

    return 0;
}
