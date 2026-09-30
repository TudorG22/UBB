#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string input_file = argc > 1 ? argv[1] : "in.txt";
    string output_file = argc > 2 ? argv[2] : "out.txt";

    ifstream fin(input_file);
    ofstream fout(output_file);
    if (!fin || !fout) {
        return 1;
    }

    const int INF = 1000000000;

    int n;
    fin >> n;
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            fin >> x;
            if (i == j) {
                dist[i][j] = 0;
            } else if (x) {
                dist[i][j] = 1;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                fout << "INF";
            } else {
                fout << dist[i][j];
            }
            fout << (j + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}
