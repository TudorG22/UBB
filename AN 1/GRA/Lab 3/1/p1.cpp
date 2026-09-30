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

    int n, muchii, sursa;
    line_stream >> n >> muchii >> sursa;

    fin.clear();
    fin.seekg(initial_pos);
    return n;
}

int sursa_from_text(ifstream& fin)
{
    streampos initial_pos = fin.tellg();
    string line;
    getline(fin, line);
    istringstream line_stream(line);

    int n, muchii, sursa;
    line_stream >> n >> muchii >> sursa;

    fin.clear();
    fin.seekg(initial_pos);
    return sursa;
}


void dijkstra_to_file(vector<vector<int>> matrix, int n, int s, ofstream& fout){
    
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    vector<int> prev(n, -1);
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
                prev[v] = u;
                q.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i]==INT_MAX) fout << "INF";
        else fout << dist[i];
        if (i < n - 1) {
            fout << " ";
        }
    }
}



int main(int argc, char * argv[])
{
    //calea fisierului de intrare este data in argv[1]
    ifstream fin(argv[1]);
    //calea fisierului de iesire este data in argv[2]
    ofstream fout(argv[2]);
    //implementarea problemei

    int n = nr_of_vertex_from_text(fin);
    int s = sursa_from_text(fin);
    vector<vector<int>> matrix = text_to_ad_matrix(fin, n);

    dijkstra_to_file(matrix, n, s, fout);

    fin.close();
    fout.close();
    return 0;
}
