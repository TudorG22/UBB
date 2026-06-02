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
    int n;
    fin >> n;
    return n;
}

vector<vector<int>> lista_adiacenta_din_text(int n, ifstream& fin)
{
    vector<vector<int>> lista_adiacenta(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        fin >> x >> y;

        lista_adiacenta[x].push_back(y);
        lista_adiacenta[y].push_back(x);
    }

    return lista_adiacenta;
}

vector<int> codare_prufer(vector<vector<int>> lista_adiacenta, int n)
{
    vector<int> grad(n + 1, 0);
    set<int> frunze;
    vector<int> cod;

    for (int i = 1; i <= n; i++) {
        grad[i] = lista_adiacenta[i].size();
        if (grad[i] == 1) {
            frunze.insert(i);
        }
    }

    for (int i = 0; i < n - 2; i++) {
        int frunza = *frunze.begin();
        frunze.erase(frunze.begin());

        int vecin = -1;
        for (int nod : lista_adiacenta[frunza]) {
            if (grad[nod] > 0) {
                vecin = nod;
                break;
            }
        }

        cod.push_back(vecin);
        grad[frunza] = 0;
        grad[vecin]--;

        if (grad[vecin] == 1) {
            frunze.insert(vecin);
        }
    }

    return cod;
}

void scrie_codare(const vector<int>& cod, ofstream& fout)
{
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
    vector<vector<int>> lista_adiacenta = lista_adiacenta_din_text(n, fin);
    vector<int> cod = codare_prufer(lista_adiacenta, n);

    scrie_codare(cod, fout);

    fin.close();
    fout.close();
}
