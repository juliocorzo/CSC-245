#include <queue>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int maxElemLength(const vector<string>& v);
vector<string> PadStrings(const vector<string>& v, int k);
vector<string> UnpadStrings(const vector<string>& v);
void PrintVector(const vector<string>& L);
char GetChar(string word, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int passes);

int main() {
  vector<string> L;
  string a[10] = {"zebra", "apple", "orange", "can", "candy", "a",
                  "top", "pumpkin", "today", "parade"};

  for(int i = 0; i < 10; i++) L.push_back(a[i]);
  int passes = maxElemLength(L);

  cout << "\nRadix Sort String Implementation\n" << endl;
  cout << "Pre Sorting: \t";
  PrintVector(L);
  RadixSort(L, passes);
  cout << "Post Sorting: \t";
  PrintVector(L);
  cout << endl;
  
  return 0;
}

int maxElemLength(const vector<string>& v) {
  vector<string> tv = v;
  string largest = "";
  while(!tv.empty()) {
    string test = tv.back();
    tv.pop_back();
    if(largest.length() < test.length()) {
      largest = test;
    }
  }
  return largest.length();
}

vector<string> PadStrings(const vector<string>& v, int k) {
  vector<string> tv;
  for(int i = 0; i < v.size(); i++) {
    string temp = v[i];
    if(v[i].length() < k) temp.append(k - temp.length(), ' ');
    tv.push_back(temp);
  }
  return tv;
}

vector<string> UnpadStrings(const vector<string>& v) {
  vector<string> tv;
  for(int i = 0; i < v.size(); i++) {
    string temp = v[i];
    temp.erase(temp.find_last_not_of(" ") + 1);
    tv.push_back(temp);
  }
  return tv;
}

void PrintVector(const vector<string>& L) {
  for(int i = 0; i < L.size(); i++) {
    cout << L[i] << " ";
  }
  cout << endl;
}

char GetChar(string word, int k) {
  return word[k];
}

vector<queue<string> > ItemsToQueues(const vector<string>& L, int k) {
  vector<string> tv = L;
  vector<queue<string> > QA(128);
  while(!tv.empty()) {
    string temp = tv.front(); tv.erase(tv.begin());
    int loc = (int) GetChar(temp, k);
    QA[loc].push(temp);
  }
  return QA;
}

vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals) {
  vector<string> tv;
  for(int i = 0; i < 128; i++) {
    if(!QA[i].empty()) {
      while(!QA[i].empty()) {
        string front = QA[i].front();
        QA[i].pop();
        tv.push_back(front);
      }
    }
  }
  return tv;
}

void RadixSort(vector<string>& L, int passes) {
  L = PadStrings(L, passes);
  vector<queue<string> > QA(128);
  for(int k = passes; k != -1; k--) {
    QA = ItemsToQueues(L, k);
    L = QueuesToArray(QA, L.size());
  }
  L = UnpadStrings(L);
}
