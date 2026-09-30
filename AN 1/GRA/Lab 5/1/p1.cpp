#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include <vector>
#include <utility>


using namespace std;

int nr_varfuri_din_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n, m;
    line_stream >> n >> m;

    fin.clear();
    fin.seekg(initial_pos);
    return n;
}

int nr_muchii_din_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n, m;
    line_stream >> n >> m;

    fin.clear();
    fin.seekg(initial_pos);
    return m;
}

vector<vector<pair<int, int>>> lista_adiacenta_din_text(int n, int m, ifstream& fin){
    string line;
    getline(fin, line);

    vector<vector<pair<int, int>>> lista_adiacenta(n);

    for (int i = 0; i < m; i++) {
        getline(fin, line);
        istringstream line_stream(line);

        int x, y, capacitate;
        line_stream >> x >> y >> capacitate;

        lista_adiacenta[x].push_back({y, capacitate});
    }

    return lista_adiacenta;
}

bool exista_drum(vector<vector<int>>& c, vector<vector<int>>& f, int sursa, int destinatie, vector<int>& parinte){
    vector<bool> vizitat(c.size(), false);
    vector<int> q;

    parinte.assign(c.size(), -1);
    q.push_back(sursa);
    vizitat[sursa] = true;

    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];

        for (int v = 0; v < (int)c.size(); v++) {
            if (!vizitat[v] && c[u][v] - f[u][v] > 0) {
                vizitat[v] = true;
                parinte[v] = u;
                q.push_back(v);
            }
        }
    }

    return vizitat[destinatie];
}

int ford_fulkerson(const vector<vector<pair<int, int>>>& lista_adiacenta, int n, int sursa, int destinatie){
    vector<vector<int>> c(n, vector<int>(n, 0));
    vector<vector<int>> f(n, vector<int>(n, 0));
    vector<int> parinte(n);
    int flux_maxim = 0;

    for (int u = 0; u < n; u++) {
        for (pair<int, int> muchie : lista_adiacenta[u]) {
            int v = muchie.first;
            int capacitate = muchie.second;
            c[u][v] += capacitate;
        }
    }
    
    while (exista_drum(c, f, sursa, destinatie, parinte)) {
        int flux_drum = INT_MAX;

        for (int v = destinatie; v != sursa; v = parinte[v]) {
            int u = parinte[v];
            if (c[u][v] - f[u][v] < flux_drum) {
                flux_drum = c[u][v] - f[u][v];
            }
        }

        for (int v = destinatie; v != sursa; v = parinte[v]) {
            int u = parinte[v];
            f[u][v] += flux_drum;
            f[v][u] -= flux_drum;
        }

        flux_maxim += flux_drum;
    }

    return flux_maxim;
}

int main(int, char * argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int n = nr_varfuri_din_text(fin);
    int m = nr_muchii_din_text(fin);
    vector<vector<pair<int, int>>> lista_adiacenta = lista_adiacenta_din_text(n, m, fin);

    int rezultat = ford_fulkerson(lista_adiacenta, n, 0, n - 1);
    fout << rezultat << "\n";

    fin.close();
    fout.close();
    return 0;
}
