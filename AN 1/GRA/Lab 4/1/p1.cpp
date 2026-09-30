#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <iostream>


using namespace std;

int nr_varfuri_din_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n;
    line_stream >> n;

    fin.clear();
    fin.seekg(initial_pos);
    return n;
}

vector<int> arbore_din_text(int n, ifstream& fin)
{
    string line;
    getline(fin, line);
    getline(fin, line);
    istringstream line_stream(line);

    vector<int> arbore(n);

    for (int i = 0; i < n; i++){
        line_stream >> arbore[i];
    }

    return arbore;

}

vector<int> graduri_din_arbore(const vector<int>& arbore, int n)
{
    vector<int> grad(n, 0);

    for (int i = 0; i < n; i++) {
        if (arbore[i] != -1) {
            grad[i]++;
            grad[arbore[i]]++;
        }
    }

    return grad;
}

vector<vector<int>> lista_adiacenta_din_arbore(const vector<int>& arbore, int n)
{
    vector<vector<int>> adiacenta(n);

    for (int i = 0; i < n; i++) {
        if (arbore[i] != -1) {
            adiacenta[i].push_back(arbore[i]);
            adiacenta[arbore[i]].push_back(i);
        }
    }

    return adiacenta;
}

vector<int> codare_prufer(const vector<int>& arbore, int n)
{
    vector<int> grad = graduri_din_arbore(arbore, n);
    set<int> frunze;
    vector<int> cod;
    int radacina = -1;

    for (int i = 0; i < n; i++) {
        if (arbore[i] == -1) {
            radacina = i;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i != radacina && grad[i] == 1) {
            frunze.insert(i);
        }
    }

    for (int pas = 0; pas < n - 1; pas++) {
        int frunza = *frunze.begin();
        frunze.erase(frunze.begin());

        int parinte = arbore[frunza];
        cod.push_back(parinte);

        grad[frunza] = 0;
        grad[parinte]--;

        if (parinte != radacina && grad[parinte] == 1) {
            frunze.insert(parinte);
        }
    }

    return cod;
}

void scrie_codare(const vector<int>& cod, ofstream& fout)
{
    fout << cod.size() << "\n";

    for (int i = 0; i < (int)cod.size(); i++) {
        if (i > 0) {
            fout << " ";
        }
        fout << cod[i];
    }
    fout << "\n";
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n = nr_varfuri_din_text(fin);
    vector<int> arbore = arbore_din_text(n, fin);
    vector<int> cod = codare_prufer(arbore, n);

    scrie_codare(cod, fout);

    fin.close();
    fout.close();
    return 0;
}
