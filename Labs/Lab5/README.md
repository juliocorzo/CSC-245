In order to compile both `myheap.cpp` and `STLpq.cpp` please do

`c++ -std=c++0x myheap.cpp -o myheap` and `c++ -std=c++0x STLpq.cpp -o STLpq` respectively.

The compiler was throwing errors because it doesn't support extended initialized lists by default, and my IDE, CLion, uses them.
