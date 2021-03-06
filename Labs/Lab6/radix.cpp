#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int maxElemLength(const vector<int>& v);
int GetDigit(int number, int k);
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k);
vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals);
void RadixSort(vector<int>& L, int numDigits);
void PrintVector(const vector<int>& L);

int main() {
  vector<int> L;
  int ints[7] = {380, 95, 345, 382, 260, 100, 492};
  for(int i = 0; i < 7; i++) L.push_back(ints[i]);
  int passes = maxElemLength(L);

  cout << "\nRadix Sort Integer Implementation\n" << endl;
  cout << "Pre Sorting: \t";
  PrintVector(L);
  RadixSort(L, passes);
  cout << "Post Sorting: \t";
  PrintVector(L);
  cout << endl;

  return 0;
}

int maxElemLength(const vector<int>& v) {
  vector<int> tv = v; int largest = 0; int maxDecimals = 0;
  while(!tv.empty()) {
    int decimals = 0; int test = tv.back(); tv.pop_back();
    if(largest < test) {
      largest = test;
      while(test != 0) {
        test /= 10;
        decimals++;
      }
      maxDecimals = decimals;
    }
  }
  return maxDecimals;
}

int GetDigit(int number, int k) {
  int num = number; int testNum = number;
  int decimals = 0; int tempK = k;
  while(testNum != 0) {
    testNum /= 10;
    decimals++;
  }
  while(k > 0) {
    num /= 10;
    k--;
  }
  if(tempK > decimals) return 0;
  return num % 10;
}

vector<queue<int> > ItemsToQueues(const vector<int>& L, int k) {
  vector<int> tv = L;
  vector<queue<int> > QA(10);
  while(!tv.empty()) {
    int temp = tv.front(); tv.erase(tv.begin());
    int loc = GetDigit(temp, k);
    QA[loc].push(temp);
  }
  return QA;
}

vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals) {
  vector<int> tv;
  for(int i = 0; i < 10; i++) {
    if(!QA[i].empty()) {
      while(!QA[i].empty()) {
        int front = QA[i].front();
        QA[i].pop();
        tv.push_back(front);
      }
    }
  }
  return tv;
}

void RadixSort(vector<int>& L, int numDigits) {
  vector<queue<int> > QA(10);
  for(int k = 0; k < numDigits; k++) {
    QA = ItemsToQueues(L, k);
    L = QueuesToArray(QA, L.size());
  }
}

void PrintVector(const vector<int>& L) {
  for(int i = 0; i < L.size(); i++) {
    cout << L[i] << " ";
  }
  cout << endl;
}
