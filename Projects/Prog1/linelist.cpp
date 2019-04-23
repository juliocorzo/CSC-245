#include <iostream>
#include "linelist.h"

// Constructor
LineList::LineList() {
    LineNode *line = new LineNode;
    LineNode *line2 = new LineNode;

    line -> info = topMessage;
    currLine = line;
    currLineNum = 1;
    length = 0;
    line2 -> info = bottomMessage;
    currLine -> back = NULL;
    currLine -> next = line2;
    line2 -> back = line;
    line2 -> next = NULL;
}

// Post:    Moves currLine to line 1
void LineList::goToTop() {
    while(currLine -> back != NULL) {
        movePrevLine();
    }
}

// Post:    Advances currLine to last line
void LineList::goToBottom() {
    while(currLine -> next != NULL) {
        moveNextLine();
    }
}

// Post:    newLine has been inserted after the current line, then moves current line to the newly inserted line.
void LineList::insertLine(string newLine) {
    LineNode *newLineNode = new LineNode;
    newLineNode -> info = newLine;

    // If this is the first line to be inserted...
    if(currLine -> info == topMessage) {
        currLine = newLineNode;
        return;
    }

    currLine -> next = newLineNode;
    newLineNode -> back = currLine;
    currLine = newLineNode;
    currLineNum++;
}

// Post:    Deletes the current line leaving currentLine pointing to line following
void LineList::deleteLine() {
    currLine -> back -> next = currLine -> next;
    currLine -> next -> back = currLine -> back;
    currLine -> next = currLine;
}

void LineList::printList() {
    goToTop();
    cout << currLineNum << "> " << currLine -> info << endl;
    while(currLine -> next != NULL) {
        moveNextLine();
        cout << currLineNum << "> " << currLine -> info << endl;
    }

}

string LineList::getCurrLine() const {
    return currLine -> info;
}

// Post: Moves currLine one line forward (unless already at last line)
void LineList::moveNextLine() {
    if(currLine -> next != NULL) {
        currLine = currLine -> next;
        currLineNum++;
    }
}

// Post: Moves currLine one line back (unless already at last line)
void LineList::movePrevLine() {
    if(currLine -> back != NULL) {
        currLine = currLine -> back;
        currLineNum--;
    }
}

// Post:    Returns currLineNum.
int LineList::getCurrLineNum() const {
    return currLineNum;
}

// Post:    Returns the amount of strings in the text.
int LineList::getLength() const {
    return length;
}
