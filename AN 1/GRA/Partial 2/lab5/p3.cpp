#include <fstream>
#include <stack>
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

    int V, E;
    fin >> V >> E;
    vector<vector<pair<int, int>>> g(V);
    vector<int> grad(V, 0);
    for (int i = 0; i < E; ++i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back({y, i});
        g[y].push_back({x, i});
        grad[x]++;
        grad[y]++;
    }

    int start = 0;
    while (start < V && grad[start] == 0) {
        start++;
    }

    vector<int> used(E, 0), poz(V, 0), circuit;
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int node = st.top();
        while (poz[node] < (int)g[node].size() && used[g[node][poz[node]].second]) {
            poz[node]++;
        }

        if (poz[node] == (int)g[node].size()) {
            circuit.push_back(node);
            st.pop();
        } else {
            auto edge = g[node][poz[node]];
            used[edge.second] = 1;
            st.push(edge.first);
        }
    }

    for (int i = (int)circuit.size() - 1; i >= 0; --i) {
        fout << circuit[i] << (i == 0 ? '\n' : ' ');
    }

    return 0;
}
