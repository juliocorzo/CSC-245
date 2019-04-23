#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;

void Initialize(vector<int> &v);
void Print(vector<int> &v);
void Reverse(vector<int> &v);

int main() {
  std::stack<string> s1, s2;
  s1.push("Hi there");
  s1.push("Hello there");
  s2.push("Hey there");
  s2.push("What's up?");

  bool equal = 0;

  cout << "\nBoolean values: " << endl;

  if(s1 == s2) {
    cout << "s1 and s2 are equal." << endl;
    equal = 1;
  } else {
    cout << "s1 and s2 are not equal." << endl;
  }

  if(s1 < s2 && !equal) {
    cout << "s2 is greater than s1." << endl;
  } else if (s2 < s1 && !equal) {
    cout << "s1 is greater than s2." << endl;
  }

  vector<int> v;
  Initialize(v);
  Print(v);
  Reverse(v);
  Print(v);
  cout << "Sorting integer vector...\n" << endl;
  sort(v.begin(),v.end());
  Print(v);
}

void Initialize(vector<int> &v) {
  int loop = 1;
  int input;
  cout << "\nPlease enter integers. For each integer, press  \n";
  cout << "ENTER after you have finished entering it. Input \n";
  cout << "will end after 5 integers are entered correctly." << endl;
  while(loop < 6) {
    cout << "int " << loop << ": ";
    cin >> input;
    v.push_back(input);
    loop++;
  }
  cout << endl;
}

void Print(vector<int> &v) {
  cout << "The integers contained in the vector are: " << endl;
  for(int i = 0; i < 5; i++) {
    cout << v.at(i);
    if(i < 4) {
      cout << ", ";
    }
  }
  cout << "\n" << endl;
}

void Reverse(vector<int> &v) {
  cout << "Reversing values...\n" << endl;
  for(int i = 0; i < 2; i++) {
    int temp = v.at(i);
    int temp2 = v.at(4 - i);
    v.at(i) = temp2;
    v.at(4 - i) = temp;
  }
}
