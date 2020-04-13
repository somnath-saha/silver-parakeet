#include <iostream>
#include <list>

using namespace std;

/*
	20
5
	7
		10
            15
*/

struct Node {
    int val;
    Node *left, *right, *parent;
    Node(): val(0), left(NULL), right(NULL), parent(NULL) {}
    Node(int x): val(x), left(NULL), right(NULL), parent(NULL) {}
};

class BST {
    Node* root;
    Node* add(int value, Node *root) {
        if(root==NULL) {
            root = new Node(value);
        }
        else if(value<root->val) {
            root->left = add(value, root->left);
            root->left->parent = root;
        }
        else if(value>root->val) {
            root->right = add(value, root->right);
            root->right->parent = root;
        }
        return root;
    }
    public:
    Node* GetNode(int val, Node *root) {
        if(val == root->val) {
            return root;
        }
        else if(val < root->val) {
            return GetNode(val, root->left); 
        }
        else if(val > root->val) {
            return GetNode(val, root->right); 
        }
        return NULL;
    }
    Node* FindNextGreater(int val)
    {
        Node *n = GetNode(val, root);
        return FindNextGreater(n);
    }
    Node* FindNextGreater(Node *n)
    {
        if(n==NULL) {
            return NULL;
        }
        if(n->right) {
            n = n->right;
            while(n->left) {
                n = n->left;
            }
            return n;
        }
        while(n->parent && n==n->parent->right) {
            n = n->parent;
        }
        return n->parent;
    }
    void Print()
    {
        if(root==NULL) {
            cout<<"Empty";
            return;
        }
        list<Node*> q;
        list<bool> level;
        bool state = true;
        q.push_back(root);
        level.push_back(!state);
        while(!q.empty()) {
            Node *temp = q.front();
            q.pop_front();
            if(level.front()!=state) {
                state = !state;
                cout<<endl;
            }
            level.pop_front();
            cout<<temp->val<<" ";
            if(temp->left) {
                q.push_back(temp->left);
                level.push_back(!state);
            }
            if(temp->right) {
                q.push_back(temp->right);
                level.push_back(!state);
            }
        }
        cout<<endl;
    }
    void Insert(int val) {
        root = add(val, root);
    }
};

int main()
{
    /*Node *root = new Node(20);
    Node *n1 = new Node(5);
    Node *n2 = new Node(7);
    Node *n3 = new Node(10);
    Node *n4 = new Node(15);*/
    BST bst;
    bst.Insert(20);
    bst.Insert(5);
    bst.Insert(7);
    bst.Insert(10);
    bst.Insert(15);
    bst.Print();
    cout << (bst.FindNextGreater(15));
    return 0;
}