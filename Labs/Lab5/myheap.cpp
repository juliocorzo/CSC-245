// Julio R. Corzo
// CSC245 - Lab 5

#include <iostream>
#include <string>
#include "BinaryHeap.cpp"

using namespace std;

int main() {
    cout << "\nLab 5, Part 1: Binary Heaps" << endl;

    // Requirement 1
    BinaryHeap<char> PQ(50);

    // Requirement 2
    char Letters[10] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    for(int i = 0; i < 10; i++) PQ.insert(Letters[i]);

    // Requirement 3
    PQ.deleteMin();

    // Requirement 6
    cout << "\nPrinting Left Subtree of the Root of Heap: ";
    PQ.printLtSubtree(); cout << endl;
    cout << "The Height of Heap is: " << PQ.Height() << endl;
    cout << "The Maximum Value of Heap is: " << PQ.findMax() << "\n" << endl;

    return 0;
}