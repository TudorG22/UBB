#include <fstream>
#include <vector>

using namespace std;

void dfs(int node, const vector<vector<int>>& a, vector<int>& viz) {
    viz[node] = 1;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[node][i] && !viz[i]) {
            dfs(i, a, viz);
        }
    }
}

int main(int argc, char* argv[]) {
    string input_file = argc > 1 ? argv[1] : "in.txt";
    string output_file = argc > 2 ? argv[2] : "out.txt";

    ifstream fin(input_file);
    ofstream fout(output_file);
    if (!fin || !fout) {
        return 1;
    }

    int n;
    fin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a[i][j];
        }
    }

    vector<int> viz(n, 0);
    dfs(0, a, viz);

    bool conex = true;
    for (int x : viz) {
        if (!x) {
            conex = false;
        }
    }

    fout << (conex ? "DA" : "NU") << '\n';
    return 0;
}
