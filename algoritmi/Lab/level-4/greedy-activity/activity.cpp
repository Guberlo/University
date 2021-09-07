#include <iostream>
#include <fstream>

using namespace std;

class Activity {
    private:
        int start;
        int end;

    public:
        Activity(int start, int end) {
            this->start = start;
            this->end = end;
        }

        friend bool operator<(const Activity& a, const Activity& b);
        friend ostream& operator<<(ostream& os, const Activity& a);
};

bool operator<(const Activity& a, const  Activity& b) {
    return a.end < b.end;
}

