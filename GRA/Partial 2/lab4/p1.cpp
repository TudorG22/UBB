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

    int N;
    fin >> N;
    vector<int> parent(N), copii(N, 0);
    for (int i = 0; i < N; ++i) {
        fin >> parent[i];
        if (parent[i] != -1) {
            copii[parent[i]]++;
        }
    }

    priority_queue<int, vector<int>, greater<int>> frunze;
    for (int i = 0; i < N; ++i) {
        if (copii[i] == 0) {
            frunze.push(i);
        }
    }

    vector<int> cod;
    vector<int> eliminat(N, 0);
    while (!frunze.empty()) {
        int leaf = frunze.top();
        frunze.pop();
        if (eliminat[leaf]) {
            continue;
        }
        eliminat[leaf] = 1;
        if (parent[leaf] == -1) {
            break;
        }
        cod.push_back(parent[leaf]);
        copii[parent[leaf]]--;
        if (copii[parent[leaf]] == 0) {
            frunze.push(parent[leaf]);
        }
    }

    fout << cod.size() << '\n';
    for (int i = 0; i < (int)cod.size(); ++i) {
        fout << cod[i] << (i + 1 == (int)cod.size() ? '\n' : ' ');
    }
    if (cod.empty()) {
        fout << '\n';
    }

    return 0;
}
