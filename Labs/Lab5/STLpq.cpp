// Julio R. Corzo
// CSC245 - Lab 5

#include <queue>
#include <string>
#include <iostream>
using namespace std;

void populateQueue(priority_queue<string>& pq);
void printQueue(priority_queue<string>& pq);

int main() {
    cout << "\nLab 5, Part 2: STL Priority Queue\n" << endl;
    priority_queue<string> pq;
    populateQueue(pq);
    printQueue(pq);
    cout << "\n" << endl;
    return 0;
}

void populateQueue(priority_queue<string>& pq) {
    string names[10] {"Julio", "Rylee", "Javier", "Andy", "Johanna", "Sofia", "Jimena", "Antonio", "Robert", "Sufjan"};
    for (int i = 0; i < 10; i++) pq.push(names[i]);
}

void printQueue(priority_queue<string>& pq) {
    priority_queue<string>& temp = pq;
    while(!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}