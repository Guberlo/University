#include <iostream>

using namespace std;

const int MaxDimTree=100;
class Nodo
{
public:
  int val;
  Nodo* left;
  Nodo* right;
  Nodo* padre;
};

class Tree
{
    private:
      void PreOrder(Nodo* p);
      void PostOrder(Nodo* p);
        Nodo* root;
    public:
        Tree() : root(NULL) {};
        void Insert(int valore);
        void InOrder(Nodo*p);
        void stampa();
};

void Tree::Insert(int valore)
{
  Nodo* nuovo = new Nodo; //creo nodo
  Nodo* x = root, *y = NULL; //tts setto x alla radice e y al padre (che inizialmente è null)

  nuovo->val = valore;
  nuovo->left = NULL; nuovo->right=NULL;
  while(x != NULL)
  {
    y = x; //assegno al padre il figlio
    if(x->val > valore) x = x->left;
    else x = x->right;
  }
  nuovo->padre = y;
  if (y == NULL) root = nuovo;
  else if (valore < y->val) y->left = nuovo;
  else y->right = nuovo;
}

void Tree::InOrder(Nodo* p)
{
  if(p != NULL)
  {
    InOrder(p->left);
    cout << p->val << "/t";
    InOrder(p->right);
  }
}

void Tree::PreOrder(Nodo* p)
{
  if(p != NULL)
  {
    cout << p->val << "/t";
    PreOrder(p->left);
    PreOrder(p->right);
  }
}

void Tree::PostOrder(Nodo* p)
{
  if(p != NULL)
  {
    PreOrder(p->left);
    PreOrder(p->right);
    cout << p->val << "/t";
  }
}

void Tree::stampa()
{
  cout << endl;
  InOrder(root);
}

int main()
{
  Tree tree;
  tree.Insert(6);
  tree.stampa();
  tree.Insert(5);
  tree.stampa();
  tree.Insert(7);
  tree.stampa();
  tree.Insert(2);
  tree.stampa();
  tree.Insert(8);
  tree.stampa();
  return 0;
}
