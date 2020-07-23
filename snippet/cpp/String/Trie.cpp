#include <string>
#include <vector>

using namespace std;

class TrieNode {
    vector<TrieNode*> children;
    bool term;

    public:
    

    TrieNode() : term(false) {
        children.assign('Z'-'A'+1, nullptr);
    }

    ~TrieNode() {
        for (auto p : children) {
            if (p != nullptr) {
                delete p;
            }
        }
    }

    void insert(const char* str) {
        if (*str == 0) {
            term = true;
            return;
        }
        int nxt = *str - 'A';
        if (children[nxt] == nullptr) {
            children[nxt] = new TrieNode();
        }
        children[nxt]->insert(str+1);
    }

    TrieNode* find(const char* str) {
        if (*str == 0) {
            return this;
        }
        int nxt = *str - 'A';
        if (children[nxt] == nullptr) {
            return nullptr;
        }
        return children[nxt]->find(str+1);

    }

    bool isTermNode() {
        return term;
    }

    bool hasChildren() {
        for (auto p : children) {
            if (p != nullptr) {
                return true;
            }
        }
        return false;
    }
};