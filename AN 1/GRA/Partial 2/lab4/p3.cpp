#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int freq;
    int min_char;
    int left;
    int right;
    char ch;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2], ios::binary);
    if (!fin || !fout) {
        return 1;
    }

    string text((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    if (!text.empty() && text.back() == '\n') {
        text.pop_back();
    }

    vector<int> fr(256, 0);
    for (unsigned char ch : text) {
        fr[ch]++;
    }

    vector<Node> nodes;
    struct HeapNode {
        int freq;
        int min_char;
        int id;
        bool operator>(const HeapNode& other) const {
            if (freq != other.freq) return freq > other.freq;
            return min_char > other.min_char;
        }
    };

    priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> pq;
    for (int c = 0; c < 256; ++c) {
        if (fr[c] > 0) {
            nodes.push_back({fr[c], c, -1, -1, static_cast<char>(c)});
            pq.push({fr[c], c, (int)nodes.size() - 1});
        }
    }

    int root = -1;
    if (pq.size() == 1) {
        root = pq.top().id;
    } else {
        while (pq.size() > 1) {
            auto a = pq.top();
            pq.pop();
            auto b = pq.top();
            pq.pop();
            nodes.push_back({a.freq + b.freq, min(a.min_char, b.min_char), a.id, b.id, 0});
            pq.push({nodes.back().freq, nodes.back().min_char, (int)nodes.size() - 1});
        }
        root = pq.top().id;
    }

    vector<string> code(nodes.size());
    if (root != -1) {
        vector<pair<int, string>> st = {{root, ""}};
        while (!st.empty()) {
            auto current = st.back();
            st.pop_back();
            int id = current.first;
            string path = current.second;
            if (nodes[id].left == -1) {
                code[id] = path.empty() ? "0" : path;
            } else {
                st.push_back({nodes[id].right, path + "1"});
                st.push_back({nodes[id].left, path + "0"});
            }
        }
    }

    vector<string> cod_char(256);
    int N = 0;
    for (int i = 0; i < (int)nodes.size(); ++i) {
        if (nodes[i].left == -1) {
            cod_char[(unsigned char)nodes[i].ch] = code[i];
            N++;
        }
    }

    fout << N << '\n';
    for (int c = 0; c < 256; ++c) {
        if (fr[c] > 0) {
            fout << static_cast<char>(c) << ' ' << fr[c] << '\n';
        }
    }

    for (unsigned char ch : text) {
        fout << cod_char[ch];
    }
    fout << '\n';

    return 0;
}
