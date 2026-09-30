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

    int n;
    fin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a[i][j];
        }
    }

    int grad = 0;
    for (int j = 0; j < n; ++j) {
        grad += a[0][j];
    }

    bool regulat = true;
    for (int i = 1; i < n; ++i) {
        int grad_curent = 0;
        for (int j = 0; j < n; ++j) {
            grad_curent += a[i][j];
        }
        if (grad_curent != grad) {
            regulat = false;
        }
    }

    fout << (regulat ? "DA" : "NU") << '\n';
    return 0;
}
