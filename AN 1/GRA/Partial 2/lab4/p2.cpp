#include <fstream>
#include <queue>
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

    int M;
    fin >> M;
    vector<int> cod(M);
    for (int i = 0; i < M; ++i) {
        fin >> cod[i];
    }

    int N = M + 1;
    vector<int> aparitii(N, 0), parent(N, -2);
    for (int x : cod) {
        aparitii[x]++;
    }

    priority_queue<int, vector<int>, greater<int>> frunze;
    for (int i = 0; i < N; ++i) {
        if (aparitii[i] == 0) {
            frunze.push(i);
        }
    }

    for (int x : cod) {
        int leaf = frunze.top();
        frunze.pop();
        parent[leaf] = x;
        aparitii[x]--;
        if (aparitii[x] == 0) {
            frunze.push(x);
        }
    }

    int root = -1;
    for (int i = 0; i < N; ++i) {
        if (parent[i] == -2) {
            root = i;
        }
    }
    parent[root] = -1;

    fout << N << '\n';
    for (int i = 0; i < N; ++i) {
        fout << parent[i] << (i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
