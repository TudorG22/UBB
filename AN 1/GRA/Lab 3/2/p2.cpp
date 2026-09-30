#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <utility>

using std::getline;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::pair;
using std::priority_queue;
using std::streampos;
using std::string;
using std::vector;
using std::greater;

//utils
vector<vector<int>> text_to_ad_matrix(ifstream& fin, int n)
{
    vector<vector<int>> matrix(n, vector<int>(n, INT_MAX));

    string line;

    getline(fin, line); //skip prima linie

    int a, b, c;
    while (getline(fin, line)) {
        istringstream iss(line);
        if (iss >> a >> b >> c) {
            matrix[a][b] = c;
        }
    }

    return matrix;
}

int nr_of_vertex_from_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n, muchii;
    line_stream >> n >> muchii;

    fin.clear();
    fin.seekg(initial_pos);
    return n;
}

vector<vector<int>> extra_vertex_from_ad_matrix(vector<vector<int>> matrix, int n)
{
    vector<vector<int>> extra_matrix(n + 1, vector<int>(n + 1, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            extra_matrix[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        extra_matrix[n][i] = 0;
    }

    return extra_matrix;
}

vector<int> bellman_ford(vector<vector<int>> matrix, int n, int s)
{
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    for (int k = 0; k < n - 1; k++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (int v = 0; v < n; v++) {
                if (matrix[u][v] == INT_MAX) continue;
                if (dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INT_MAX) continue;
        for (int v = 0; v < n; v++) {
            if (matrix[u][v] == INT_MAX) continue;
            if (dist[u] + matrix[u][v] < dist[v]) {
                return {};
            }
        }
    }

    return dist;
}

vector<int> dijkstra(vector<vector<int>> matrix, int n, int s){
    
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});

    while (!q.empty()){
        int current_dist = q.top().first;
        int u = q.top().second;
        q.pop();

        if (current_dist != dist[u]) continue;

        for (int v = 0; v < n; v++) {
            if (matrix[u][v] == INT_MAX) continue;
            int alt = dist[u] + matrix[u][v];
            if (alt < dist[v]){
                dist[v] = alt;
                q.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<vector<int>> reweighted_matrix(vector<vector<int>> matrix, int n, vector<int> h)
{
    vector<vector<int>> new_matrix(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INT_MAX) continue;
            new_matrix[i][j] = matrix[i][j] + h[i] - h[j];
        }
    }

    return new_matrix;
}

void johnson_to_file(vector<vector<int>> matrix, int n, ofstream& fout)
{
    vector<vector<int>> bf_matrix = extra_vertex_from_ad_matrix(matrix, n);
    vector<int> h = bellman_ford(bf_matrix, n + 1, n);

    if (h.empty()) {
        fout << -1;
        return;
    }

    vector<vector<int>> new_matrix = reweighted_matrix(matrix, n, h);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (new_matrix[i][j] == INT_MAX) continue;
            fout << i << " " << j << " " << new_matrix[i][j] << "\n";
        }
    }

    for (int i = 0; i < n; i++) {
        vector<int> dist = dijkstra(new_matrix, n, i);

        for (int j = 0; j < n; j++) {
            if (dist[j] == INT_MAX) fout << "INF";
            else fout << dist[j] - h[i] + h[j];
            fout << " ";
        }
        if (i < n - 1) {
            fout << "\n";
        }
    }
}



// ---- main ----
int main(int, char * argv[])
{
    //calea fisierului de intrare este data in argv[1]
    ifstream fin(argv[1]);
    //calea fisierului de iesire este data in argv[2]
    ofstream fout(argv[2]);
    //implementarea problemei

    int n = nr_of_vertex_from_text(fin);
    vector<vector<int>> matrix = text_to_ad_matrix(fin, n);

    johnson_to_file(matrix, n, fout);

    fin.close();
    fout.close();
    return 0;
}
