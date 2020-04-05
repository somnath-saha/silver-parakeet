#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trie
{
    struct TNode
    {
        unordered_map<char, TNode *> m;
        bool isEnd;
        TNode(bool end = false) : isEnd(end) {}
    };
    TNode *root;

public:
    Trie() : root(new TNode()) {}
    void _removeWord(string s, int i, TNode *node) {
        if(node==NULL || i>s.size() || i<0) {
            return;
        }
        if(i==s.size()) {
            node->isEnd = false;
            if(node->m.size()==0) {
                delete node;
            }
            return;
        }
        auto& m = node->m;
        auto iter = m.find(s[i]);
        if(iter==m.end()) {
            return;
        }
        else {
            _removeWord(s, i+1, iter->second);
            if(node->m.size()==0 && !node->isEnd) {
                delete node;
            }
        }
    }
    void removeWord(string s) {
        _removeWord(s, 0, root);
    }
    bool findWord(string s)
    {
        TNode *node = root;
        for (char c : s)
        {
            if (node == NULL)
            {
                return false;
            }
            auto &m = node->m;
            auto iter = m.find(c);
            if (iter == m.end())
            {
                return false;
            }
            else
            {
                node = iter->second;
            }
        }
        return node->isEnd;
    }
    void addWord(string s)
    {
        TNode *node = root;
        for (char c : s)
        {
            unordered_map<char, TNode *> &m = node->m;
            auto iter = m.find(c);
            if (iter == m.end())
            {
                node = new TNode();
                m[c] = node;
            }
            else
            {
                node = iter->second;
            }
        }
        node->isEnd = true;
    }
};

int main()
{
    Trie t;
    vector<string> addWords({
                "tes", 
                "test123", 
                //"test", 
                "abcde", 
                "a", 
                "3"});
    vector<string> findWords({
                "tes", 
                "test123", 
                "test", 
                "abcde", 
                "a", 
                "3", 
                "3a", 
                "test2"});
    vector<string> removeWords({
                "test123", 
                "test", 
                "a", 
                "3", 
                "3a", 
                "test2"});
    for (string &s : addWords)
    {
        cout << s << " inserted. " << endl;
        t.addWord(s);
    }
    for (string &s : removeWords)
    {
        cout << s << " removed if present. " << endl;
        t.removeWord(s);
    }
    for (string &s : findWords)
    {
        if (t.findWord(s))
        {
            cout << s << " found.";
        }
        else
        {
            cout << s << " not found.";
        }
        cout << endl;
    }
    return 0;
}