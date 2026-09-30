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
    int flux = 0;

    while (true) {
        vector<int> par_node(V, -1), par_edge(V, -1);
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

        flux += add;
    }

    fout << flux << '\n';
    return 0;
}
