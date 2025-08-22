//
// Created by Katie He on 2/11/25.
//

#include "AVL.h"

// checks if the name and id are both valid
bool AVLTree::validInsert(string& name, string& id) {
    if(name.empty())
    {
        return false;
    }
    for(char c : name)
    {
        // std::isalpha checks if the character is an alphabetic character (https://en.cppreference.com/w/cpp/string/byte/isalpha)
        if(!isalpha(c) && c != ' ')
            return false;
    }
    if(id.length() != 8)
        return false;
    for(char c : id)
    {
        // std::isdigit checks if the character is a decimal digit (https://en.cppreference.com/w/cpp/string/byte/isdigit)
        if(!isdigit(c))
            return false;
    }
    return true;
}

// inserts a node with the specified name and id and returns the root node
Node* AVLTree::insertHelper(Node* root, string name, string id)
{
    if(root == nullptr)
        return new Node(name, id);
    else if(id < root->id)
        root->left = insertHelper(root->left, name, id);
    else
        root->right = insertHelper(root->right, name, id);
    // update height
    root->height = 1 + max(Node::getHeight(root->left), Node::getHeight(root->right));
    int balance = Node::getHeight(root->left) - Node::getHeight(root->right);
    if(balance == -2)
    {
        // cout << "right heavy" << endl;
        int balanceChild = Node::getHeight(root->right->left) - Node::getHeight(root->right->right);
        if(balanceChild == 1)
        {
            // cout << "right left" << endl;
            return Node::rotateRightLeft(root);
        }
        else
        {
            // cout << "left" << endl;
            return Node::rotateLeft(root);
        }
    }
    else if(balance == 2)
    {
        // cout << "left heavy" << endl;
        int balanceChild = Node::getHeight(root->left->left) - Node::getHeight(root->left->right);
        if(balanceChild == -1)
        {
            // cout << "left right" << endl;
            return Node::rotateLeftRight(root);
        }
        else
        {
            // cout << "right" << endl;
            return Node::rotateRight(root);
        }
    }
    return root;
}

// deletes inorder successor and updates heights from current->right and downward
void AVLTree::updateSuccessorChain(Node* current, Node* successor, Node* successorParent)
{
    // if we have reached the successor
    if(successor->left == nullptr)
    {
        // update the current node
        current->id = successor->id;
        current->name = successor->name;
        successorParent->left = successor->right;
        delete successor;
    }
    else
    {
        // continue down the successor chain
        updateSuccessorChain(current, successor->left, successor);
    }
    // backtrack to update the height of the parent node
    successorParent->height = 1 + max(Node::getHeight(successorParent->left), Node::getHeight(successorParent->right));
}

// updates heights from current node and downward
// keeps track of parent node and direction the current node is from the parent
bool AVLTree::removeHelper(Node* parent, Node* current, int dir, string& id)
{
    if(current == nullptr)
    {
        return false;
    }
    // update is true at the end if a removal occurred and the current node needs to be updated
    bool update = true;
    if(id < current->id)
    {
        update = removeHelper(current, current->left, -1, id);
    }
    else if(id > current->id)
    {
        update = removeHelper(current, current->right, 1, id);
    }
    // if current node has no children
    else if(current->left == nullptr && current->right == nullptr)
    {
        if(parent == nullptr)
        {
            delete current;
            head = nullptr;
        }
        else if(dir == 1)
        {
            parent->right = nullptr;
            delete current;
        }
        else if(dir == -1)
        {
            parent->left = nullptr;
            delete current;
        }
        // we return true so the parent node knows to update
        return true;
    }
    // if current node has 1 right child
    else if(current->left == nullptr && current->right != nullptr)
    {
        if(parent == nullptr)
        {
            head = current->right;
            delete current;
        }
        else if(dir == 1)
        {
            parent->right = current->right;
            delete current;
        }
        else if(dir == -1)
        {
            parent->left = current->right;
            delete current;
        }
        return true;
    }
    // if current node has 1 left child
    else if(current->right == nullptr && current->left != nullptr)
    {
        if(parent == nullptr)
        {
            head = current->left;
            delete current;
        }
        else if(dir == 1)
        {
            parent->right = current->left;
            delete current;
        }
        else if(dir == -1)
        {
            parent->left = current->left;
            delete current;
        }
        return true;
    }
    // if current node has 2 children
    else
    {
        Node* successor = current->right;
        // if the current node's right child has no left children
        if(successor->left == nullptr)
        {
            current->id = successor->id;
            current->name = successor->name;
            current->right = successor->right;
            delete successor;
        }
        else
        {
            // call the updateSuccessorChain function
            Node* successorParent = current->right;
            successor = successorParent->left;
            updateSuccessorChain(current, successor, successorParent);
        }
    }
    // this statement is executed either when backtracking or when no return has occurred yet and the current node needs updating
    if(update)
    {
        current->height = 1 + max(Node::getHeight(current->left), Node::getHeight(current->right));
    }
    // returns whether the current node was updated (which tells the parent node if it needs updating)
    return update;
}

// returns whether the id was successfully removed
bool AVLTree::remove(string& id)
{
    if(id.length() > 8)
        return false;
    for(char c : id)
    {
        if(!isdigit(c))
            return false;
    }
    // while id is less than 8 digits, add 0s to the beginning
    while(id.length() < 8)
    {
        id = "0" + id;
    }
    return removeHelper(nullptr, head, 0, id);
}

string AVLTree::searchIdHelper(Node* root, string& id)
{
    if(root == nullptr)
    {
        return "1";
    }
    if(root->id == id)
    {
        return root->name;
    }
    if(id < root->id)
    {
        return searchIdHelper(root->left, id);
    }
    return searchIdHelper(root->right, id);
}

// returns the name with the given id if it exists, otherwise returns 0 if id is not valid or 1 if id is not found
string AVLTree::searchId(string& id)
{
    if(id.length() > 8)
        return "0";
    for(char c : id)
    {
        if(!isdigit(c))
            return "0";
    }
    while(id.length() < 8)
    {
        id = "0" + id;
    }
    return searchIdHelper(head, id);
}

// populates the out vector with ids that match the name
void AVLTree::searchNameHelper(Node* root, string& name, vector<string>& out)
{
    if(root == nullptr)
        return;
    if(root->name == name)
    {
        out.push_back(root->id);
    }
    searchNameHelper(root->left, name, out);
    searchNameHelper(root->right, name, out);
}

// returns a list of ids that correspond to the name, otherwise 0 if name is invalid or 1 if name is not found
string AVLTree::searchName(string& name)
{
    if(name.empty())
    {
        return "0";
    }
    for(char c : name)
    {
        // return 0 to indicate the name isn't valid
        if(!isalpha(c) && c != ' ')
            return "0";
    }
    vector<string> out = {};
    searchNameHelper(this->head, name, out);
    if(out.empty())
    {
        // return 1 to indicate the name wasn't found
        return "1";
    }
    // use ostringstream to build a string
    ostringstream oss;
    for(int i = 0; i < out.size() - 1; ++i)
    {
        oss << out[i];
        oss << "\n";
    }
    oss << out[out.size() - 1];
    return oss.str();
}

// returns whether a node is inserted
bool AVLTree::insert(string name, string id)
{
    // checks if the name and id are valid and if the id doesn't exist yet
    if(validInsert(name, id) && searchId(id) == "1")
    {
        head = insertHelper(this->head, name, id);
        return true;
    }
    return false;
}

// returns a reference to the Inorder traversal vector
vector<string>& AVLTree::printInorderHelper(Node* root, vector<string>& list)
{
    if(root == nullptr)
    {
        return list;
    }
    printInorderHelper(root->left, list);
    list.push_back(root->name);
    printInorderHelper(root->right, list);
    return list;
}

// returns a reference to the Inorder traversal vector
vector<string>& AVLTree::printInorder(vector<string>& list)
{
    return printInorderHelper(head, list);
}

// returns a reference to the Preorder traversal vector
vector<string> &AVLTree::printPreorderHelper(Node* root, vector<string>& list)
{
    if(root == nullptr)
    {
        return list;
    }
    list.push_back(root->name);
    printPreorderHelper(root->left, list);
    printPreorderHelper(root->right, list);
    return list;
}

// returns a reference to the Preorder traversal vector
vector<string>& AVLTree::printPreorder(vector<string>& list)
{
    return printPreorderHelper(head, list);
}

// returns a reference to the Postorder traversal vector
vector<string> &AVLTree::printPostorderHelper(Node* root, vector<string>& list)
{
    if(root == nullptr)
    {
        return list;
    }
    printPostorderHelper(root->left, list);
    printPostorderHelper(root->right, list);
    list.push_back(root->name);
    return list;
}

// returns a reference to the Postorder traversal vector
vector<string>& AVLTree::printPostorder(vector<string>& list)
{
    return printPostorderHelper(head, list);
}

// return the level count
int AVLTree::printLevelCount()
{
    return Node::getHeight(head) + 1;
}

// populate list of ids with the Inorder traversal
void AVLTree::inorderIDs(Node* root, vector<string>& list)
{
    if(root == nullptr)
        return;
    inorderIDs(root->left, list);
    list.push_back(root->id);
    inorderIDs(root->right, list);
}

// returns whether the removal of the nth node is successful
bool AVLTree::removeInorder(int n)
{
    vector<string> inOrder = {};
    inorderIDs(head, inOrder);
    // if n is out of bounds
    if(n >= inOrder.size() || n < 0)
        return false;
    return removeHelper(nullptr, head, 0, inOrder[n]);
}
