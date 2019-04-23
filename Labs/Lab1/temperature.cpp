// Julio R. Corzo
// Lab 1 - CSC-245
// 2018-01-09

#include <iostream>
using namespace std;

double convert(double value);

int main(){
  double celsius;
  cout << "Please enter a Celsius value: ";
  cin >> celsius;
  double fahrenheit = convert(celsius);
  cout << celsius << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit.\n";
  return 0;
}

double convert(double tmp) {
  return tmp * 1.8 + 32.0;
}
