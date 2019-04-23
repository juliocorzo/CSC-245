
#include <string>
#include <iostream>
using namespace std;

void BreakDown(string name, string& first, string& last, string& mi);

int main() {
	string name, first, last, mi;

	cout << "Name? <Last, First MI.> ";
	getline(cin, name);

	BreakDown (name, first, mi, last);

	cout << "First Name Entered :  " << first << endl;
	cout << "Last Name Entered :  " << last << endl;
	cout << "Middle Initial Entered :  " << mi << endl;
	return 0;
}

// pre  : name is initialized with a full name
// post : first, mi, and last contain the individual components of that name
void BreakDown (string name, string& first, string& mi, string& last) {
	int commaPos = name.find(",");
	int dotPos = name.find(".");
	last = name.substr(0, commaPos);
	mi = name.substr(dotPos - 1, 1);
	first = name.substr(last.length() + 2, name.length() - last.length() - 4);
}
