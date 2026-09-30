#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>


using namespace std;

int lungime_codare_din_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int m;
    line_stream >> m;

    fin.clear();
    fin.seekg(initial_pos);
    return m;
}

vector<int> codare_din_text(int m, ifstream& fin)
{
    string line;
    getline(fin, line);
    getline(fin, line);
    istringstream line_stream(line);

    vector<int> codare(m);

    for (int i = 0; i < m; i++) {
        line_stream >> codare[i];
    }

    return codare;
}

vector<int> decodare_prufer(const vector<int>& codare, int m)
{
    int n = m + 1;
    vector<int> aparitii(n, 0);
    vector<int> arbore(n, -1);
    set<int> frunze;

    for (int nod : codare) {
        aparitii[nod]++;
    }

    for (int i = 0; i < n; i++) {
        if (aparitii[i] == 0) {
            frunze.insert(i);
        }
    }

    for (int i = 0; i < m; i++) {
        int frunza = *frunze.begin();
        frunze.erase(frunze.begin());

        int parinte = codare[i];
        arbore[frunza] = parinte;

        aparitii[parinte]--;
        if (aparitii[parinte] == 0) {
            frunze.insert(parinte);
        }
    }

    int radacina = *frunze.begin();
    arbore[radacina] = -1;

    return arbore;
}

void scrie_arbore(const vector<int>& arbore, ofstream& fout)
{
    fout << arbore.size() << "\n";

    for (int i = 0; i < (int)arbore.size(); i++) {
        if (i > 0) {
            fout << " ";
        }
        fout << arbore[i];
    }
    fout << "\n";
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int m = lungime_codare_din_text(fin);
    vector<int> codare = codare_din_text(m, fin);
    vector<int> arbore = decodare_prufer(codare, m);

    scrie_arbore(arbore, fout);

    fin.close();
    fout.close();
    return 0;
}
