#include <iostream>
using namespace std;

// Comparison functions required by the lab.
bool compareValues(double *x, double *y);
bool compareAddress(double *x, double *y);

// Report on the results of the comparison in a readable way.
void postValueResults(bool result, double *x, double *y);
void postAddressResults(bool result, double *x, double *y);

int main() {

  // Data and pointer declaration and assignment.
  double num1 = 10.0;
  double num2 = 11.0;
  double *ptr1 = &num1;
  double *ptr2 = &num2;

  // Comparisons are made here, to test that the functions are working.
  cout << endl;
  cout << "\tNumber\t\tAddress\n";
  cout << "\t" << num1 << "\t\t" << ptr1 << "\n";
  cout << "\t" << num2 << "\t\t" << ptr2 << endl;
  cout << "\n\tComparing 10 to itself: " << endl;
  postValueResults(compareValues(ptr1, ptr1), ptr1, ptr1);
  postAddressResults(compareAddress(ptr1, ptr1), ptr1, ptr1);
  cout << "\n\tComparing 10 and 11: " << endl;
  postValueResults(compareValues(ptr1, ptr2), ptr1, ptr2);
  postAddressResults(compareAddress(ptr1, ptr2), ptr1, ptr2);
  cout << endl;

  return 0;
}

bool compareValues(double *x, double *y) {
  return *x == *y;
}

bool compareAddress(double *x, double *y) {
  return x == y;
}

void postValueResults(bool result, double *x, double *y) {
  if(result) {
    cout << "\tTrue, " << *x << " and " << *y;
    cout << " are equal in value." << endl;
  } else {
    cout << "\tFalse, " << *x << " and " << *y;
    cout << " are not equal in value." << endl;
  }
}

void postAddressResults(bool result, double *x, double *y) {
  if(result) {
    cout << "\tTrue, the address " << x;
    cout << " is shared." << endl;
  } else {
    cout << "\tFalse, addresses " << x << " and " << y;
    cout << " are not equal." << endl;
  }
}
