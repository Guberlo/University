#include <iostream>
#include <fstream>
#include <list>

using namespace std;

/**
 *  Solve the knapsack unitary problem by creating a list of elements (each having 1 as weight)
 *  Ordering the list (ASC) and taking always the biggest element untill the sack weight is reached. 
 */
void knapsack(ifstream &in, ofstream &out, int size, int weight)
{
    list<int> *l = new list<int>();
    int sum = 0;
    int tmp;

    for (int i = 0; i < size; i++)
    {
        in >> tmp;
        l->push_back(tmp);
    }

    l->sort();

    for (int i=0; i<weight; i++) {
        sum += l->back();
        l->pop_back();
    }

    out << sum << endl;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int size, weight;

    for (int i = 0; i < 100; i++)
    {
        in >> size >> weight;
        knapsack(in, out, size, weight);
    }
}
