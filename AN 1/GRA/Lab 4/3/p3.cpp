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

string text_din_fisier(ifstream& fin)
{
    return string((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
}

vector<int> frecvente_din_text(const string& text)
{
    vector<int> frecvente(256, 0);

    for (char ch : text) {
        frecvente[(unsigned char)ch]++;
    }

    return frecvente;
}

Nod* arbore_huffman_din_frecvente(const vector<int>& frecvente)
{
    priority_queue<Nod*, vector<Nod*>, ComparaNoduri> q;

    for (int i = 0; i < 256; i++) {
        if (frecvente[i] > 0) {
            Nod* frunza = new Nod{frecvente[i], i, (char)i, nullptr, nullptr};
            q.push(frunza);
        }
    }

    if (q.empty()) {
        return nullptr;
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

void coduri_din_arbore(Nod* nod, const string& drum, vector<string>& coduri)
{
    if (nod->stanga == nullptr && nod->dreapta == nullptr) {
        if (drum.empty()) {
            coduri[(unsigned char)nod->caracter] = "0";
        } else {
            coduri[(unsigned char)nod->caracter] = drum;
        }
        return;
    }

    coduri_din_arbore(nod->stanga, drum + "0", coduri);
    coduri_din_arbore(nod->dreapta, drum + "1", coduri);
}

string codifica_textul(const string& text, const vector<string>& coduri)
{
    string codificat;

    for (char ch : text) {
        codificat += coduri[(unsigned char)ch];
    }

    return codificat;
}

void afisare_rezultat(const vector<int>& frecvente, const string& text_codificat, ofstream& fout)
{
    int n = 0;
    for (int i = 0; i < 256; i++) {
        if (frecvente[i] > 0) {
            n++;
        }
    }

    fout << n << "\n";

    for (int i = 0; i < 256; i++) {
        if (frecvente[i] > 0) {
            fout << (char)i << " " << frecvente[i] << "\n";
        }
    }

    fout << text_codificat << "\n";
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    string text = text_din_fisier(fin);
    vector<int> frecvente = frecvente_din_text(text);
    Nod* radacina = arbore_huffman_din_frecvente(frecvente);
    vector<string> coduri(256);

    if (radacina != nullptr) {
        coduri_din_arbore(radacina, "", coduri);
    }

    string text_codificat = codifica_textul(text, coduri);
    afisare_rezultat(frecvente, text_codificat, fout);

    fin.close();
    fout.close();
    return 0;
}
