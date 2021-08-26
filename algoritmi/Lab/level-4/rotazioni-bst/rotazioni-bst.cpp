#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Node
{
private:
    T key;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

public:
    Node(T key, Node<T> *parent = NULL, Node<T> *right = NULL, Node<T> *left = NULL)
    {
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }

    T getKey() { return this->key; }

    void setKey(T key) { this->key = key; }

    Node<T> *getLeft() { return this->left; }

    void setLeft(Node<T> *left) { this->left = left; }

    Node<T> *getRight() { return this->right; }

    void setRight(Node<T> *right) { this->right = right; }

    Node<T> *getParent() { return this->parent; }

    void setParent(Node<T> *parent) { this->parent = parent; }
};

template <class T>
class BST
{
private:
    Node<T> *root;

    Node<T> *_search(T key, Node<T> *node)
    {
        if (!node || node->getKey() == key)
            return node;

        if (key < node->getKey())
            return _search(key, node->getLeft());
        return _search(key, node->getRight());
    }

    Node<T> *_min(Node<T> *node)
    {
        if (!node || !node->getLeft())
            return node;
        return _min(node->getLeft());
    }

    void _delete(T key, Node<T> *node)
    {
        cout << "DEBUG: enter in delete\n";
        Node<T> *tmp = _search(key, node);
        if (!tmp)
            return;

        if (tmp->getLeft() && tmp->getRight())
        {
            cout << "DEBUG: delete 2 children\n";
            Node<T> *succ = _min(tmp->getRight());
            tmp->setKey(succ->getKey());
            _delete(succ->getKey(), succ);
        }
        else
        {
            cout << "DEBUG: delete 1 child\n";
            Node<T> *child = tmp->getLeft();
            if (!child)
                child = tmp->getRight();
            Node<T> *parent = tmp->getParent();

            if (parent)
            {
                if (key < parent->getKey())
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            }
            else
                root = child;

            if (child)
                child->setParent(parent);
        }
    }

    void _inorder(Node<T> *node, ofstream &out)
    {
        if (!node)
            return;
        _inorder(node->getLeft(), out);
        out << node->getKey() << " ";
        _inorder(node->getRight(), out);
    }

    void _preorder(Node<T> *node, ofstream &out)
    {
        if (!node)
            return;
        out << node->getKey() << " ";
        _preorder(node->getLeft(), out);
        _preorder(node->getRight(), out);
    }

    void _postorder(Node<T> *node, ofstream &out)
    {
        if (!node)
            return;
        _postorder(node->getLeft(), out);
        _postorder(node->getRight(), out);
        out << node->getKey() << " ";
    }

    void _rightRotate(Node<T> *node)
    {
        if (!node || !node->getLeft())
            return;
        Node<T> *parent = node->getParent();
        Node<T> *left = node->getLeft();
        Node<T> *lRight = left->getRight();

        if (parent)
        {
            if (parent->getLeft() == node)
                parent->setLeft(left);
            else
                parent->setRight(left);
        }
        else
            root = left;

        left->setParent(parent);
        node->setParent(left);
        left->setRight(node);
        node->setLeft(lRight);

        if (lRight)
            lRight->setParent(node);
    }

    void _leftRotate(Node<T> *node)
    {
        if (!node || !node->getRight())
            return;
        Node<T> *parent = node->getParent();
        Node<T> *right = node->getRight();
        Node<T> *rLeft = right->getLeft();

        if (parent)
        {
            if (parent->getLeft() == node)
                parent->setLeft(right);
            else
                parent->setRight(right);
        }
        else
            root = right;

        right->setParent(parent);
        node->setParent(right);
        right->setLeft(node);
        node->setRight(rLeft);

        if (rLeft)
            rLeft->setParent(node);
    }

public:
    BST() { this->root = NULL; }

    void insert(T key)
    {
        cout << "DEBUG: enter in insert" << endl;
        Node<T> *tmp = root;
        Node<T> *parent = NULL;

        while (tmp)
        {
            parent = tmp;
            if (key <= tmp->getKey())
                tmp = tmp->getLeft();
            else
                tmp = tmp->getRight();
        }

        cout << "DEBUG: exit while loop" << endl;

        Node<T> *node = new Node<T>(key, parent);
        if (parent)
            cout << "\033[32;1m NODE: value -> " << key << " parent -> " << parent->getKey() << endl;

        if (parent)
        {
            if (key <= parent->getKey())
                parent->setLeft(node);
            else
                parent->setRight(node);
        }
        else
            root = node;
    }

    void deleteKey(T key)
    {
        _delete(key, root);
    }

    void rightRotate(T key)
    {
        Node<T> *node = _search(key, root);
        _rightRotate(node);
    }

    void leftRotate(T key)
    {
        Node<T> *node = _search(key, root);
        _leftRotate(node);
    }

    void inorder(ofstream &out)
    {
        _inorder(root, out);
    }

    void preorder(ofstream &out)
    {
        _preorder(root, out);
    }

    void postorder(ofstream &out)
    {
        _postorder(root, out);
    }
};

template <class T>
T convert(string elem, T type)
{
    cout << "\033[33;1m Converting " << elem << " to double. . .\n";
    return stod(elem);
}

template <class T>
void rotazioni(ifstream &in, ofstream &out, int n, int m, string order, T type)
{
    BST<T> *bst = new BST<T>();
    string operation;

    cout << "\033[32;1m " << n << " I/D operations to do. . . \n";
    for (int i = 0; i < n; i++)
    {
        in >> operation;

        cout << "\033[33;1m operation -> " << operation << endl;

        if (operation[0] == 'i')
            bst->insert(convert(operation.substr(4), T()));
        else
            bst->deleteKey(convert(operation.substr(5), T()));
    }

    cout << "\033[32;1m " << m << " rotations to do. . . \n";
    for (int i = 0; i < m; i++)
    {
        in >> operation;

        if (operation[0] == 'r')
            bst->rightRotate(convert(operation.substr(6), T()));
        else
            bst->leftRotate(convert(operation.substr(5), T()));
    }

    if (order == "inorder")
        bst->inorder(out);
    else if (order == "preorder")
        bst->preorder(out);
    else
        bst->postorder(out);

    out << endl;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    string type, order;

    for (int i = 0; i < 100; i++)
    {
        in >> type >> n >> m >> order;

        rotazioni(in, out, n, m, order, double());
    }
}