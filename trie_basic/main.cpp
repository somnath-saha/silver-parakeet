#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trie {
    struct TNode {
        bool isEnd;
        unordered_map<char, TNode*> m;
        TNode(bool end=false): isEnd(end) {}
    };
    TNode *root;
public:
    Trie(): root(NULL) {}
    Trie(string const& s): root(NULL) {
        addWord(s);
    }
    void _addWord(string const& s, int index, TNode* root) {
        if(index>=s.size()) {
            return;
        }
        if(root==NULL) {
            root = new TNode();
            root->m[s[index]] = new TNode();
        }
        else {
            auto& m = root->m;
            auto iter = m.find(s[index]);
            if(iter==m.end()) {
                m[s[index]] = new TNode();
            }
            else {
                _addWord(s, index+1, iter->second);
            }
        }
        if(index==s.size()-1) {
            root->isEnd = true;
        }
    }
    void addWord(string const& s) {
        if(s.empty()) {
            return;
        }
        _addWord(s, 0, root);
    }
    bool _isPresent(const string& s, int index, TNode* root) {
        if(root==NULL || s.size()==0 || root->m.size()==0) {
            return false;
        }
        auto iter = root->m.find(s[index]);
        if(iter==root->m.end()) {
            return false;
        }
        return _isPresent(s, index+1, iter->second);
    }
    bool isPresent(const string& s) {
        return _isPresent(s, 0, root);
    }
};

int main()
{
    Trie t;
    t.addWord("test");
    cout<<(t.isPresent("test") ? "Present" : "Not Present")<<endl;
    cout<<(t.isPresent("test2") ? "Present" : "Not Present")<<endl;
    return 0;
}
