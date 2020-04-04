#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trie {
    struct TNode {
        bool isEnd;
        unordered_map<char, TNode*> m;
        TNode(): isEnd(false) {}
    };
    TNode *root;
public:
    Trie(): root(NULL) {}
    Trie(string const& s): root(NULL) {
        addWord(s);
    }
    void _addWord(string const& s, int start, TNode* root) {
        if(s.empty()) {
            return;
        }
        if(root==NULL) {
            root = new TNode();
            root->m[s[0]] = new TNode();
        }
    }
    void addWord(string const& s) {
        if(s.empty()) {
            return;
        }
        _addWord(s, 0, root);
    }
    bool isPresent(const string& s) {
        return false;
    }
};

int main()
{
    Trie t;
    t.isPresent("test");
    return 0;
}
