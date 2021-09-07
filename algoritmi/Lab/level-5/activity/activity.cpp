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

        int getProfit() { return end - start; }

        friend bool operator<(const Activity& a, const Activity& b) {
            return a.end < b.end;
        }

        friend ostream& operator<<(ostream& os, const Activity& a) {
            return os << "(" << a.start << " " << a.end << ")";
        }
};

void printVector(Activity** activities, int n) {
    for (int i=0; i<n; i++)
        cout << *activities[i] << " ";
    cout << endl;
}

void printMatrix(int** matrix, int n, int m) {
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=m; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void sortActivities(Activity** activities, int n) {
    Activity* tmp;

    for (int i=0; i<n; i++) {
        for (int j = i; j<n; j++) {
            if (*activities[j] < *activities[i]) {
                tmp = activities[i];
                activities[i] = activities[j];
                activities[j] = tmp;
            }
        }
    }
}

int getLastActivity(Activity** activities, int i) {
    for (int j=i-1; j>=0; j--)
        if (activities[j]->getEnd() <= activities[i]->getStart())   return j;
    return -1;
}

int profitActivity(ifstream& in, int n) {
    Activity** activities = new Activity*[n];
    int start, end;
    char c;

    for (int i=0; i<n; i++) {
        in >> c >> start >> end >> c;
        activities[i] = new Activity(start, end);
    }

    sortActivities(activities, n);

    int tmp;
    int B[n];
    B[0] = activities[0]->getProfit();

    for (int i=1; i<n; i++) {
        tmp = activities[i]->getProfit();
        int last = getLastActivity(activities, i);

        if (last != -1)
            tmp += B[last];
        
        B[i] = max(tmp, B[i-1]);
    }

    printVector(activities, n);

    return B[n-1];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;

    for (int i=0; i<100; i++) {
        in >> n;
        out << profitActivity(in, n) << endl;
    }
}