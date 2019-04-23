
#include <string>
#include <iostream>
#include "time.h"
using namespace std;

int main() {
  Time myTime(9,30,0);
  myTime.Write();
  myTime.WriteAmPm();
  myTime.Set(8,0,0);
  myTime.WriteAmPm();
  myTime.Mealtime();

  Time Schedules[10];
  for(int i = 0; i < 10; i++) {
    Schedules[i].Set(11,0,0);
    Schedules[i].WriteAmPm();
  }

  return 0;
}

void Time::WriteAmPm() const {
  bool am;
  int tempHrs;
  am = (hrs <= 11);

  if (hrs == 0) tempHrs = 12;
  else if (hrs >= 13) tempHrs = hrs - 12;
  else tempHrs = hrs;

  if (tempHrs < 10) cout << '0';
  cout << tempHrs << ':';

  if (mins < 10) cout << "0";
  cout << mins << ":";

  if (secs < 10) cout << "0";
  cout << secs;

  if(am) cout << " AM" << endl;
  else cout << " PM" << endl;
}

Time::~Time() {
  cout << "Destructor Called." << endl;
}

void Time::Mealtime() const {
  if(hrs == 8 && mins == 0 && secs == 0) {
    cout << "Breakfast" << endl;
  } else if (hrs == 12 && mins == 0 && secs == 0) {
    cout << "Lunch" << endl;
  } else if (hrs == 19 && mins == 0 && secs == 0) {
    cout << "Dinner" << endl;
  }
}
