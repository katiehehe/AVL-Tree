//
// Created by Katie He on 2/11/25.
//

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node
{
    string name;
    string id;
    int height;
    Node* left;
    Node* right;

    Node(string name, string id)
    {
        this->name = name;
        this->id = id;
        height = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    static int getHeight(Node* root)
    {
        return root ? root->height : -1;
    }
    static Node* rotateLeft(Node* node)
    {
        Node* child = node->right;
        Node* grandchild = child->left;
        child->left = node;
        node->right = grandchild;
        // update heights
        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
        child->height = 1 + max(getHeight(child->right), getHeight(child->left));
        return child;
    }
    static Node* rotateRight(Node* node)
    {
        Node* child = node->left;
        Node* grandchild = child->right;
        child->right = node;
        node->left = grandchild;
        // update heights
        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
        child->height = 1 + max(getHeight(child->right), getHeight(child->left));
        return child;
    }
    static Node* rotateLeftRight(Node* node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    static Node* rotateRightLeft(Node* node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
};

class AVLTree
{
    Node* head = nullptr;

public:
    bool validInsert(string& name, string& id);
    bool insert(string name, string id);
    Node* insertHelper(Node* root, string name, string id);
    bool remove(string& id);
    void updateSuccessorChain(Node* current, Node* successor, Node* successorParent);
    bool removeHelper(Node* parent, Node* current, int dir, string& id);
    string searchId(string& id);
    string searchIdHelper(Node* root, string& id);
    string searchName(string& name);
    void searchNameHelper(Node* root, string& name, vector<string>& out);
    vector<string>& printInorder(vector<string>& list);
    vector<string>& printInorderHelper(Node* root, vector<string>& list);
    vector<string>& printPreorder(vector<string>& list);
    vector<string>& printPreorderHelper(Node* root, vector<string>& list);
    vector<string>& printPostorder(vector<string>& list);
    vector<string>& printPostorderHelper(Node* root, vector<string>& list);
    int printLevelCount();
    void inorderIDs(Node* root, vector<string>& list);
    bool removeInorder(int n);

    // destructor functions
    void deleteTree(Node* root)
    {
        if(root == nullptr)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    ~AVLTree()
    {
        deleteTree(head);
    };
};


#endif //PROJECT1_AVL_H
