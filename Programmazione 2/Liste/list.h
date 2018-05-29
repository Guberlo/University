#ifndef  LIST.H
#define LIST.H


using namespace std;



class ListaSemplice
{
  public:
    int num;
    ListaSemplice* ptr;

    ListaSemplice(){} //default constructor
    ListaSemplice(int _num); //set ptr to null and num to parameter
    ListaSemplice(int _num, ListaSemplice* _ptr); //set num and ptr to parameter
    ~ListaSemplice(); // default destructor
    void print(ListaSemplice* _ptr);

    /*            GETTERS/SETTERS
    void setElemento(int _num); //set element to parameter
    void setPtr(ListaSemplice* _ptr); //set next node
    int getElemento(); //get element in current position
    Nodo* getPtr(); //get the next node address
    */

};

ListaSemplice::ListaSemplice(int _num)
{
  num = _num;
  ptr = NULL;
}

ListaSemplice::ListaSemplice(int _num, ListaSemplice* _ptr)
{
  num= _num;
  ptr = _ptr;
}

/*void ListaSemplice::setElemento(int _num)
{
  num = _num;
}

void ListaSemplice::setPtr(ListaSemplice* _ptr)
{
  ptr = _ptr;
}

int ListaSemplice::getElemento()
{
  return num;
}

ListaSemplice* ListaSemplice::getPtr()
{
  return ptr;
}
*/

void ListaSemplice::print(ListaSemplice* _ptr)
{
  ListaSemplice* testa = _ptr;

  while(testa!=NULL)
  {
    cout << " " << testa->num << endl;
    testa = testa->ptr;
  }
}
#endif
