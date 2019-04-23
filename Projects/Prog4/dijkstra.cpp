#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "cert-err34-c"
#include <climits>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "graph.h"
#include <cstdlib>

using namespace std;

/*
 *  Program 4 V2
 *  Changes:
 *      1.  Everything uses vectors now, avoiding the use of normal arrays and the risk
 *          of overflow (at least for the client program. Graph class still uses arrays.)
 *      2.  One single struct for both Vertex and Edges. Edges only ever structs when they
 *          are being added and checked for vertices, so I thought it was a waste to try
 *          to make a complete new struct for it.
 */

struct Vertex {

    string  n;      // Name
    bool    m;      // Marked
    int     w;      // Weight
    string  p;      // Previous

    bool operator<(const Vertex &a) const {
        return n.compare(a.n) < 0;
    }
};

void verifyFile(int argc);
void buildGraph(Graph<string> &g, const string &f, vector<Vertex> &v);
void printVertices(vector<Vertex> v);
void dijkstra(Graph<string> &g, vector<Vertex> v);
string getStartVertex(vector<Vertex> v);
bool allMarked(vector<Vertex> v);
void assignWeights(Graph<string> &g, vector<Vertex> &v, int s, Queue<string>& q);
int findMin(vector<Vertex> v);
void printRow(const Vertex& v);

int main(int argc, char* argv[]) {

    verifyFile(argc);

    Graph<string> g;
    vector<Vertex> v;

    buildGraph(g, argv[1], v);
    printVertices(v);
    dijkstra(g, v);

}

void verifyFile(int argc) {

    /*  TODO Done.
     *  Verifies that a file is passed, but it doesn't check if the file is correct. That
     *  is done at the start of the BuildGraph() method.
     */

    if(argc == 2) return;
    cout << "The command line inputs were not correct.\n"
            "Please try again." << endl;
    exit(EXIT_FAILURE);
}

void buildGraph(Graph<string> &g, const string &f, vector<Vertex> &v) {

    /*  TODO Done.
     *  Builds the graph based on the file that the user specified.
     *
     *  Steps:
     *      1. Verify that the file is actually good. If it isn't, the program quits.
     *      2. Build a temporary vector of edges for later use. Populates it with all
     *         the edges included in the file as start, destination, distance. This
     *         is stored in a struct of type Edge, with three parameters.
     *      3. Push the start parameter of the first edge into the vertices. This is to
     *         make sure that v.size() will always return 1 at the start, allowing the
     *         nested for loop to run at least once.
     *      3. Push the unique vertices from the start parameter of every edge into
     *         the Vertex vector.
     *      4. Push the unique vertices from the end of every edge into the Vertex vector.
     *         Steps 3 and 4 were performed in order to ensure that all vertices are
     *         found.
     *      5. Sort vertices alphabetically using vertex sort method, and add are then
     *         added to the graph.
     *      6. Edges are added to the graph.
     *
     *  Parameters:
     *      Graph<string> &g    -   The graph that we're building.
     *      const string &f     -   The file that was sent by the user (as a string)
     *      vector<string> &v   -   Holds all the vertices as strings.
     */

    // Step 1
    ifstream input(f.c_str());
    if(!input.good()) {
        cout << "The command line inputs were not correct.\n"
                "Please try again." << endl;
        exit(EXIT_FAILURE);
    }

    // Step 2
    vector<Vertex> e;
    string currentLine;

    while(getline(input, currentLine)) {
        string token;
        vector<string> lineTokens;
        stringstream ss(currentLine);

        while(getline(ss, token, ';'))
            lineTokens.push_back(token);

        Vertex tempEdge = {lineTokens[0], false, atoi(lineTokens[2].c_str()), lineTokens[1]};
        e.push_back(tempEdge);
    }

    // Step 3
    Vertex firstVertex = {e[0].n, false, INT_MAX, ""};
    v.push_back(firstVertex);

    for(int x = 0; x < e.size(); x++) {

        // Step 4
        bool originDupe = false;

        for(int y = 0; y < v.size() && !originDupe; y++)
            if(e[x].n == v[y].n)
                originDupe = true;

        if(!originDupe) {
            Vertex startVertex = {e[x].n, false, INT_MAX, ""};
            v.push_back(startVertex);
        }

        // Step 5
        bool destinationDupe = false;

        for(int y = 0; y < v.size() && !destinationDupe; y++)
            if(e[x].p == v[y].n)
                destinationDupe = true;

        if(!destinationDupe) {
            Vertex endVertex = {e[x].p, false, INT_MAX, ""};
            v.push_back(endVertex);
        }
    }

    // Step 6
    sort(v.begin(), v.end());
    for(int x = 0; x < v.size(); x++)
        g.AddVertex(v[x].n);

    // Step 7
    for(int x = 0; x < e.size(); x++)
        g.AddEdge(e[x].n, e[x].p, e[x].w);
}

void printVertices(vector<Vertex> v) {

    /*  TODO Done.
     *  Prints all the vertices in alphabetical order at the start of the program.
     *  Assumes that vertices have already been sorted, which they have, in the
     *  buildGraph() method.
     */

    cout << "\n        ^^^^^^^^^^^^^^^^    DIJKSTRA'S ALGORITHM    ^^^^^^^^^^^^^^^^" << endl;
    cout << "\n        A weighted graph has been built for these " << v.size() << " cities: \n" << endl;

    for(int x = 0; x < v.size(); x++) {
        if(x % 3 == 0) cout << "        ";
        cout << setw(18) << v[x].n;
        if((x + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

void dijkstra(Graph<string> &g, vector<Vertex> v) {

    // Starting vertex is obtained from user
    string startVertex = getStartVertex(v);
    int i = -1;
    for(int x = 0; x < v.size() && i == -1; x++) {
        if(v[x].n == startVertex) i = x;
    }

    // Starting vertex is marked, in the graph and in our Vertex vector.
    v[i].m = true;
    v[i].w = 0;
    v[i].p = "N/A";
    g.MarkVertex(v[i].n);

    // Table header and starting index row is printed.
    cout << "\n        " << setw(18) << "Vertex" << setw(18) << "Distance" << setw(18) << "Previous\n" << endl;
    printRow(v[i]);

    // this boolean values will only be marked true if we arrive at a dead end (when the next minIndex is -1.
    // When that happens, the algorithm stops and the remaining unmarked values are marked appropriately.
    bool deadEnd = false;
    while(!allMarked(v) && !deadEnd) {
        Queue<string> adjacent;
        g.GetToVertices(v[i].n, adjacent);
        assignWeights(g, v, i, adjacent);
        int minIndex = findMin(v);
        if(minIndex != -1) {
            v[minIndex].m = true;
            g.MarkVertex(v[minIndex].n);
            i = minIndex;
            printRow(v[i]);
        }
        else deadEnd = true;
    }

    // If a dead end is found, all unmarked vertices are marked in the graph and in our
    // vector and are given a weight of -1, and a previous value of N/A, since they are
    // not in the starting vertex's path.
    if(deadEnd) while(!allMarked(v)) for(int x = 0; x < v.size(); x++)
        if(!v[x].m) {
            g.MarkVertex(v[x].n);
            v[x].m = true;
            v[x].w = -1;
            v[x].p = "N/A";
            printRow(v[x]);
        }
    cout << endl;
}

string getStartVertex(vector<Vertex> v) {

    /*  TODO Done.
     *  Asks the user to input the starting vertex, checks that it's valid, and continues
     *  asking until a valid vertex is input.
     */

    string inputPrompt = "Please input your starting vertex: ";
    string invalidInputPrompt = "Input was invalid, please enter starting vertex: ";
    string startVertex;
    bool validInput = false;

    // Prompt to ask user for input, which is stored in inputVertex
    cout << "\n" << string(8, ' ') << inputPrompt;
    getline(cin, startVertex);

    // Initial test to see if the input is valid.
    for(int x = 0; x < v.size() && !validInput; x++) {
        if(startVertex == v[x].n) validInput = true;
    }

    // If the input was not valid, infinite while loop runs until user finally inputs
    // A valid response.
    while(!validInput) {
        cout << string(8, ' ') << invalidInputPrompt;
        getline(cin, startVertex);
        for(int x = 0; x < v.size() && !validInput; x++) {
            if(startVertex == v[x].n) validInput = true;
        }
    }

    // Separating border is printed.
    cout << "\n" << string(8, ' ') << string(60, '-')  << endl;

    return startVertex;
}

bool allMarked(vector<Vertex> v) {

    /*  TODO Done.
     *  Returns true if all Vertex objects inside the vector have been marked. Returns
     *  false otherwise.
     */

    for(int x = 0; x < v.size(); x++) if(!v[x].m) return false;
    return true;
}

void assignWeights(Graph<string> &g, vector<Vertex> &v, int s, Queue<string>& q) {

    /*  TODO Done.
     *  Parses through a queue of strings, finding the weight of them and adding the
     *  previous name of the vertex, if that vertex had not been marked.
     */

    while(!q.isEmpty()) {

        string t = q.dequeue();
        int i = -1;

        for(int x = 0; x < v.size() && i == -1; x++)
            if(v[x].n == t)
                i = x;

        int w = g.WeightIs(v[s].n, v[i].n);

        if(v[i].w > w + v[s].w && !v[i].m) {
            v[i].w = w + v[s].w;
            v[i].p = v[s].n;
        }
    }
}

int findMin(vector<Vertex> v) {

    /*  TODO Done.
     *  Finds the minimum non-marked vertex and returns its index.
     */

    int m = INT_MAX - 1;
    int i = -1;

    for(int x = 0; x < v.size(); x++) {
        if(v[x].w < m && !v[x].m) {
            m = v[x].w;
            i = x;
        }
    }
    return i;
}

void printRow(const Vertex& v) {

    /*  TODO Done.
     *  If the weight of the desired Vertex struct is not -1, it prints a standard line
     *  like it does in the example. If it is -1, a row is printed stating that the
     *  vertex was not on the path.
     */

    if(v.w != -1) {
        cout << "        " << setw(18) << v.n << setw(18) << v.w << setw(18) << v.p << endl;
    }
    else {
        cout << "        " << setw(18) << v.n << setw(18) << "Not on path" << setw(18) << v.p << endl;
    }
}