
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 100;

struct DateType {
	string month;
	int day;
	int year;
};

struct EventType {
	string place;
	DateType date;
};

void PrintStruct(DateType Holiday);
void AssignMonth(EventType Dates[]);
void PrintStructArray(EventType Dates[]);

int main() {
	DateType Holiday;
	Holiday.month = "January";
	Holiday.day = 5;
	Holiday.year = 2019;
	EventType Dates[SIZE];
	PrintStruct(Holiday);
	AssignMonth(Dates);
	PrintStructArray(Dates);
	return 0;
}

// pre  : Holiday is intialized with three field values
// post : Function prints date of Holiday in form mm dd, yy
void PrintStruct(DateType Holiday) {
	cout << Holiday.month << " " << Holiday.day << ", " << Holiday.year << "\n";
}

// pre  : none
// post : The month field of every date record in array is assigned a month
void AssignMonth(EventType Dates[]) {
	for(int i = 0; i < SIZE; i++) {
		Dates[i].date.month = "January";
	}
}

// pre  : Date filed of every date record is assigned a month.
// post : Function prints month of every date in the array.
void PrintStructArray(EventType Dates[]) {
	for(int i = 0; i < SIZE; i++) {
		cout << Dates[i].date.month << "\n";
	}
}
