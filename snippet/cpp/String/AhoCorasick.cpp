#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

int atoc(char a) {
    return a - 'a';
}

class OutputNode {
public:
    OutputNode* prev;
    int serial;

    OutputNode(int serial) {
        this->prev = nullptr;
        this->serial = serial;
    }

};

class Node {
public:
    vector<Node*> children;

    Node* fail;
    OutputNode* output;
    int terminal;

    Node() {
        children.assign(27, nullptr);
        fail = nullptr;
        output = nullptr;
        terminal = -1;
    };

    void insert(const string& s, int serial, int pos = 0) {
        if (pos == s.size()) {
            terminal = serial;
        }
        else {
            int nxt = atoc(s[pos]);

            if (children[nxt] == nullptr) {
                children[nxt] = new Node();
            }
            children[nxt]->insert(s, serial, pos + 1);
        }
    }
};

void calcFail(Node* root) {
    queue<Node*> q;

    root->fail = root;
    q.push(root);

    while (q.size()) {
        auto here = q.front();
        q.pop();

        for (int e = 0; e < 26; e++) {
            auto there = here->children[e];
            if (there == nullptr) {
                continue;
            }

            if (here == root) {
                there->fail = root;
            }
            else {
                auto cur = here->fail;
                while (cur != root && cur->children[e] == nullptr) {
                    cur = cur->fail;
                }

                if (cur->children[e] != nullptr) {
                    cur = cur->children[e];
                }
                there->fail = cur;
            }

            if (there->terminal != -1) {
                there->output = new OutputNode(there->terminal);
                there->output->prev = there->fail->output;
            }
            else {
                there->output = there->fail->output;
            }

            q.push(there);

        }
    }
}

bool ahoCorasick(const string& str, Node* trie) {
    Node* state = trie;
    vector<int> ret;

    for (int i = 0; i < str.size(); i++) {
        int c = atoc(str[i]);

        while (state != trie && state->children[c] == nullptr) {
            state = state->fail;
        }

        if (state->children[c] != nullptr) {
            state = state->children[c];
        }
        auto cur = state->output;
        while (cur != nullptr) {
            return true;
        }
    }

    return false;
}
