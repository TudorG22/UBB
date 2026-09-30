#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> g;
vector<int> degree_nodes;
vector<int> color_now, color_best;
int best_colors;

bool can_color(int node, int c) {
    for (int vecin : g[node]) {
        if (color_now[vecin] == c) {
            return false;
        }
    }
    return true;
}

int select_node() {
    int chosen = -1;
    int best_sat = -1;
    int best_deg = -1;

    for (int i = 0; i < N; ++i) {
        if (color_now[i] != -1) continue;

        vector<int> used(best_colors, 0);
        int sat = 0;
        for (int vecin : g[i]) {
            if (color_now[vecin] != -1 && !used[color_now[vecin]]) {
                used[color_now[vecin]] = 1;
                sat++;
            }
        }

        if (sat > best_sat || (sat == best_sat && degree_nodes[i] > best_deg)) {
            best_sat = sat;
            best_deg = degree_nodes[i];
            chosen = i;
        }
    }

    return chosen;
}

void backtrack(int used_colors) {
    if (used_colors >= best_colors) {
        return;
    }

    int node = select_node();
    if (node == -1) {
        best_colors = used_colors;
        color_best = color_now;
        return;
    }

    for (int c = 0; c < used_colors; ++c) {
        if (can_color(node, c)) {
            color_now[node] = c;
            backtrack(used_colors);
            color_now[node] = -1;
        }
    }

    color_now[node] = used_colors;
    backtrack(used_colors + 1);
    color_now[node] = -1;
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

    fin >> N >> M;
    g.assign(N, {});
    degree_nodes.assign(N, 0);
    for (int i = 0; i < M; ++i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
        degree_nodes[x]++;
        degree_nodes[y]++;
    }

    color_now.assign(N, -1);
    color_best.assign(N, -1);
    best_colors = N;

    backtrack(0);

    fout << best_colors << '\n';
    for (int i = 0; i < N; ++i) {
        fout << color_best[i] << (i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
