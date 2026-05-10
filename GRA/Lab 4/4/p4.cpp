#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
#include <iostream>


using namespace std;

struct Nod {
    int frecventa;
    int minim_ascii;
    char caracter;
    Nod* stanga;
    Nod* dreapta;
};

struct ComparaNoduri {
    bool operator()(const Nod* n1, const Nod* n2) const
    {
        if (n1->frecventa != n2->frecventa) {
            return n1->frecventa > n2->frecventa;
        }

        return n1->minim_ascii > n2->minim_ascii;
    }
};

int nr_caractere_din_text(ifstream& fin)
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

vector<pair<char, int>> alfabet_din_text(int n, ifstream& fin)
{
    vector<pair<char, int>> alfabet;
    string line;

    getline(fin, line);

    for (int i = 0; i < n; i++) {
        getline(fin, line);
        char ch = line[0];
        int frecventa = stoi(line.substr(2));
        alfabet.push_back({ch, frecventa});
    }

    return alfabet;
}

string cod_din_text(int n, ifstream& fin)
{
    string line;
    getline(fin, line);

    for (int i = 0; i < n; i++) {
        getline(fin, line);
    }

    getline(fin, line);
    return line;
}

Nod* arbore_huffman_din_alfabet(const vector<pair<char, int>>& alfabet)
{
    priority_queue<Nod*, vector<Nod*>, ComparaNoduri> q;

    for (const auto& element : alfabet) {
        Nod* frunza = new Nod{element.second, (unsigned char)element.first, element.first, nullptr, nullptr};
        q.push(frunza);
    }

    while (q.size() > 1) {
        Nod* stanga = q.top();
        q.pop();

        Nod* dreapta = q.top();
        q.pop();

        Nod* parinte = new Nod{
            stanga->frecventa + dreapta->frecventa,
            min(stanga->minim_ascii, dreapta->minim_ascii),
            0,
            stanga,
            dreapta
        };

        q.push(parinte);
    }

    return q.top();
}

string decodifica_textul(Nod* radacina, const string& cod, const vector<pair<char, int>>& alfabet)
{
    if (radacina->stanga == nullptr && radacina->dreapta == nullptr) {
        return string(alfabet[0].second, alfabet[0].first);
    }

    string text_decodat;
    Nod* nod_curent = radacina;

    for (char bit : cod) {
        if (bit == '0') {
            nod_curent = nod_curent->stanga;
        } else {
            nod_curent = nod_curent->dreapta;
        }

        if (nod_curent->stanga == nullptr && nod_curent->dreapta == nullptr) {
            text_decodat += nod_curent->caracter;
            nod_curent = radacina;
        }
    }

    return text_decodat;
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n = nr_caractere_din_text(fin);
    vector<pair<char, int>> alfabet = alfabet_din_text(n, fin);

    fin.clear();
    fin.seekg(0);

    string cod = cod_din_text(n, fin);
    Nod* radacina = arbore_huffman_din_alfabet(alfabet);
    string text_decodat = decodifica_textul(radacina, cod, alfabet);

    fout << text_decodat;

    fin.close();
    fout.close();
    return 0;
}
