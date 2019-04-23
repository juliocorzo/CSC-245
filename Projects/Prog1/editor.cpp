#include <iostream>
#include <string>
#include <fstream>
#include "linelist.h"

using namespace std;

char getResponse(LineList L);
string getNewLine(LineList L);

int main(int argc, char *argv[]) {

    if (argc == 1) {
        return 0;
    }

    LineList L;

    std::ifstream file(argv[1]);
    std::string str;
    while (std::getline(file, str)) {
        L.insertLine(str);
    }
    file.close();

    L.printList();

    char input;
    string tempLine;
    input = getResponse(L);

    bool quit = 0;

    while (!quit) {
        switch (input) {
            case 'I':
                tempLine = getNewLine(L);
                L.insertLine(tempLine);
                input = getResponse(L);
                break;
            case 'D':
                L.deleteLine();
                input = getResponse(L);
                break;
            case 'L':
                L.printList();
                input = getResponse(L);
                break;
            case 'P':
                L.movePrevLine();
                input = getResponse(L);
                break;
            case 'N':
                L.moveNextLine();
                input = getResponse(L);
                break;
            case 'E':
                quit = 1;
                break;
            default:
                cout << "Please enter a valid option in upper-case." << endl;
                input = getResponse(L);
                break;

        }
    }

    std::ofstream outfile(argv[1]);
    int size = L.getLength();
    L.goToTop();
    for (int i = 0; i < size; i++) {
        outfile << L.getCurrLine();
        L.moveNextLine();
    }
    outfile.close();

    return 0;

}

char getResponse(LineList L) {
    char input;
    cout << L.getCurrLineNum() << "> ";
    cin >> input;
    return input;
}

string getNewLine(LineList L) {
    string input;
    L.moveNextLine();
    cout << L.getCurrLineNum() << "> ";
    cin >> input;
    return input;
}
