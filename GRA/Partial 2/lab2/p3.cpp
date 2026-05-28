#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    string input_file = argc > 1 ? argv[1] : "labirint_1.txt";
    string output_file = argc > 2 ? argv[2] : "out.txt";

    ifstream fin(input_file);
    ofstream fout(output_file);
    if (!fin || !fout) {
        return 1;
    }

    vector<string> a;
    string line;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        a.push_back(line);
    }

    int n = (int)a.size();
    int m = 0;
    for (const string& row : a) {
        if ((int)row.size() > m) {
            m = (int)row.size();
        }
    }

    for (string& row : a) {
        while ((int)row.size() < m) {
            row.push_back('1');
        }
    }

    pair<int, int> start = {-1, -1}, finish = {-1, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'S') start = {i, j};
            if (a[i][j] == 'F') finish = {i, j};
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> parinte(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (a[nx][ny] == '1' || dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            parinte[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    if (finish.first != -1 && dist[finish.first][finish.second] != -1) {
        pair<int, int> node = finish;
        while (node != start) {
            if (a[node.first][node.second] == ' ') {
                a[node.first][node.second] = '.';
            }
            node = parinte[node.first][node.second];
        }
    }

    for (const string& row : a) {
        fout << row << '\n';
    }

    return 0;
}
