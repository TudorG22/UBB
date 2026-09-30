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

    int N;
    fin >> N;
    fin.get();

    vector<int> fr(256, 0);
    for (int i = 0; i < N; ++i) {
        string line;
        getline(fin, line);
        char ch = line[0];
        int freq = stoi(line.substr(2));
        fr[(unsigned char)ch] = freq;
    }

    string bits;
    getline(fin, bits);

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

    if (root == -1) {
        return 0;
    }

    if (nodes[root].left == -1) {
        fout << string(nodes[root].freq, nodes[root].ch);
        return 0;
    }

    int node = root;
    for (char bit : bits) {
        node = (bit == '0' ? nodes[node].left : nodes[node].right);
        if (nodes[node].left == -1) {
            fout << nodes[node].ch;
            node = root;
        }
    }

    return 0;
}
