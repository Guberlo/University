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

        int getStart() { return start; }
        
        int getEnd() { return end; }

        friend bool operator<(const Activity& a, const Activity& b) {
            return a.end < b.end;
        }
        
        friend bool operator>(const Activity& a, const Activity& b) {
            return a.end > b.end;
        }

        friend ostream& operator<<(ostream& os, const Activity& a) {
            return os << "(" << a.start << " " << a.end << ")";
        }
};

void sortActivities(Activity** activities, int n) {
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            if (*activities[j] < *activities[i]) {
                Activity* tmp = activities[i];
                activities[i] = activities[j];
                activities[j]  = tmp;
            }
        }
    }
}

int activitySelection(ifstream& in, int n) {
    Activity** activities = new Activity*[n];
    int x, y;
    char c;

    for (int i=0; i<n; i++) {
        in >> c >> x >> y >> c;
        activities[i] = new Activity(x, y);
    }

    sortActivities(activities, n);
    
    int counter = 1;
    int end = activities[0]->getEnd();
    for (int i=1; i<n; i++) {
        if (activities[i]->getStart() >= end) {
            end = activities[i]->getEnd();
            counter++; 
        }
    }

    return counter;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;

    for (int i=0; i<100; i++) {
        in >> n;

        out << activitySelection(in, n) << endl;
    }
}