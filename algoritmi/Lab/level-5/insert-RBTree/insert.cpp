#include <iostream>
#include <fstream>

using namespace std;

enum class Color { RED, BLACK, D_BLACK };

char convertColor(Color color)
{
    switch (color)
    {
    case Color::RED:
        return 'R';
        break;
    case Color::BLACK:
        return 'B';
        break;
    default:
        return 'z';
        break;
    }
}

template <class T> class Node {
    private:
        T key;
        Color color;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;

    public:
        Node(T key, Node<T>* parent = NULL, Node<T>* left = NULL, Node<T>* right = NULL) {
            this->key = key;
            this->parent = parent;
            this->left = left;
            this->right = right;
            this->color = Color::RED;
        }

        Node<T>* getParent() { return this->parent; }

        void setParent(Node<T>* parent) { this->parent = parent; }

        Node<T>* getLeft() { return this->left; }

        void setLeft(Node<T>* left) { this->left = left; }

        Node<T>* getRight() { return this->right; }

        void setRight(Node<T>* right) { this->right = right; }

        T getKey() { return this->key; }

        void setKey(T key) { this->key = key; } 

        Color getColor() { return this->color; }

        void setColor(Color color) { this->color = color; }

        void swapColor(Node<T>* node) {
            Color tmp = this->getColor();
            this->setColor(node->getColor());
            node->setColor(tmp);
        }

        friend ostream& operator<<(ostream& os, const Node<T>& a) {
            return os << "(" << a.key << " " << convertColor(a.color) << ")";
        }
};

template <class T> class RBT {
    private:
        Node<T>* root;

        void _inorder(ofstream& out, Node<T>* node) {
            if (!node)  return;
            _inorder(out, node->getLeft());
            out << *node << " ";
            _inorder(out, node->getRight());
        }

        void _preorder(ofstream& out, Node<T>* node) {
            if (!node)  return;
            out << *node << " ";
            _preorder(out, node->getLeft());
            _preorder(out, node->getRight());
        }

        void _postorder(ofstream& out, Node<T>* node) {
            if (!node)  return;
            _postorder(out, node->getLeft());
            _postorder(out, node->getRight());
            out << *node << " ";
        }

        void rotateRight(Node<T>* node) {
            if (!node || !node->getLeft())  return;

            Node<T>* parent = node->getParent();
            Node<T>* left = node->getLeft();
            Node<T>* lRight = left->getRight();

            node->swapColor(left);

            if (parent) {
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

            if (lRight) lRight->setParent(node);
        }

        void rotateLeft(Node<T>* node) {
            if (!node || !node->getRight()) return; 

            Node<T>* parent = node->getParent();
            Node<T>* right = node->getRight();
            Node<T>* rLeft = right->getLeft();

            node->swapColor(right);

            if (parent) {
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

            if (rLeft)  rLeft->setParent(node);
        }

        void insertFixUp(Node<T>* node) {
            if (node->getParent() && node->getParent()->getColor() == Color::BLACK)
                return;

            if (node == root) {
                node->setColor(Color::BLACK);
                return;
            }

            Node<T>* parent = node->getParent();
            Node<T>* grandP = parent->getParent();
            Node<T>* uncle = grandP->getLeft();

            if (uncle == parent)
                uncle = grandP->getRight();

            if (uncle && uncle->getColor() == Color::RED) {
                grandP->setColor(Color::RED);
                uncle->setColor(Color::BLACK);
                parent->setColor(Color::BLACK);
                insertFixUp(grandP);
                return;
            }
            
            if (grandP->getLeft() == parent) {
                if (parent->getRight() == node) {
                    rotateLeft(parent); 
                    rotateRight(node->getParent());
                }
                else
                    rotateRight(grandP);
            }
            else {
                if (parent->getLeft() == node)  {
                    rotateRight(parent);
                    rotateLeft(node->getParent());
                }
                else
                    rotateLeft(grandP);
            }
        }

    public:
        RBT() { this->root = NULL; }

        void insert(T key) {
            Node<T>* tmp = root;
            Node<T>* parent = NULL;

            while (tmp) {
                parent = tmp;
                if (key <= tmp->getKey())
                    tmp = tmp->getLeft();
                else
                    tmp = tmp->getRight();
            }

            Node<T>* node = new Node<T>(key, parent);
            if (parent) {
                if (key <= parent->getKey())
                    parent->setLeft(node);
                else
                    parent->setRight(node);
            }
            else
                root = node;

            insertFixUp(node);
        }

        void inorder(ofstream& out) {
            _inorder(out, root);
        }

        void preorder(ofstream& out) {
            _preorder(out, root);
        }

        void postorder(ofstream& out) {
            _postorder(out, root);
        }

        void print(ofstream& out, string order) {
            if (order == "inorder")
                inorder(out);
            else if (order == "preorder")
                preorder(out);
            else
                postorder(out);

            out << endl;
        }
};

template <class T> void runInsert(ifstream& in, ofstream& out, int n, string order, T type) {
    RBT<T>* rbt = new RBT<T>();
    T tmp;

    for (int i=0; i<n; i++)  {
        in >> tmp;
        rbt->insert(tmp);
    }

    rbt->print(out, order);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type, order;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n >> order;

        if (type == "char")
            runInsert(in, out, n, order, char());
        else
            runInsert(in, out, n, order, double());
    }
}