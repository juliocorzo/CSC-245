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

struct VertexType {
    string name;
    bool marked;
    int distance;
    string previous;
};

struct Flights {
    string origin;
    string destination;
    int distance;
};

void VerifyFile(int i);
void BuildGraph(Graph<string> &g, const string &f, vector<string> &c, int &v, int &e, VertexType ver[]);
void PrintCities(vector<string> c, int v);
void Dijkstra(Graph<string> &g, int v, VertexType ver[]);
string Start(int v, VertexType ver[]);
bool Marked(int v, VertexType ver[]);
void AssignWeights(Graph<string> &g, int v, VertexType ver[], int s, Queue<string>& q);
int FindMin(VertexType ver[], int v);
void PrintRow(int i, VertexType ver[]);

int main(int argc, char* argv[]) {
    VerifyFile(argc);
    string filename = argv[1];
    Graph<string> dGraph;
    int numVertices;
    int numEdges;
    VertexType myVertices [50];
    vector<string> cities;
    BuildGraph(dGraph, filename, cities, numVertices, numEdges, myVertices);
    PrintCities(cities, numVertices);
    Dijkstra(dGraph, numVertices, myVertices);
}

// Checks to see if a file name was passed.
void VerifyFile(int i) {
    if(i == 2) return;
    cout << "The command line inputs were not correct.\n"
            "Please try again." << endl;
    exit(EXIT_FAILURE);
}

// Builds the graph and populates several variables in main.
void BuildGraph(Graph<string> &g, const string &f, vector<string> &c, int &v, int &e, VertexType ver[]) {
    v = 0; e = 0;

    // Edges are temporarily pushed to a struct for easier handling.
    ifstream i(f.c_str()); string l; vector<Flights> Edges;
    if(!i.good()) {
        cout << "The command line inputs were not correct.\n"
                "Please try again." << endl;
        exit(EXIT_FAILURE);
    }
    while(getline(i, l)) {
        Flights edge; vector<string> temp; stringstream stream(l); string token;
        while(getline(stream, token, ';')) temp.push_back(token);
        edge.origin = temp[0]; edge.destination = temp[1]; edge.distance = atoi(temp[2].c_str());
        Edges.push_back(edge);
        e++;
    }

    // Unique origin vertices are pushed to edges.
    c.push_back(Edges[0].origin);
    for(int x = 0; x < Edges.size(); x++) {
        bool found = false;
        for(int y = 0; y < c.size() && !found; y++) if(Edges[x].origin == c[y]) found = true;
        if(!found) c.push_back(Edges[x].origin);
    }

    // Unique destination vertices are pushed to edges.
    for(int x = 0; x < Edges.size(); x++) {
        bool found = false;
        for(int y = 0; y < c.size() && !found; y++) if(Edges[x].destination == c[y]) found = true;
        if(!found) c.push_back(Edges[x].destination);
    }

    v = (int) c.size();

    // Vertices are sorted alphabetically and then pushed to the graph.
    sort(c.begin(), c.end());
    for(int x = 0; x < v; x++) {
        g.AddVertex(c[x]);
        ver[x].name = c[x];
        ver[x].marked = false;
        ver[x].distance = INT_MAX;
        ver[x].previous = "";
    }

    // Edges are added to the graph.
    for(int x = 0; x < e; x++) {
        g.AddEdge(Edges[x].origin, Edges[x].destination, Edges[x].distance);
    }
}

void PrintCities( vector<string> c, int v) {
    cout << "\n        ^^^^^^^^^^^^^^^^    DIJKSTRA'S ALGORITHM    ^^^^^^^^^^^^^^^^" << endl;
    cout << "\n        A weighted graph has been built for these " << v << " cities: \n" << endl;
    for(int x = 0; x < v; x++) {
        if(x % 3 == 0) cout << "        ";
        cout << setw(18) << c[x];
        if((x + 1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

void Dijkstra(Graph<string> &g, int v, VertexType ver[]) {

    // Starting vertex is obtained from user
    string start = Start(v, ver);
    int i = -1;
    for(int x = 0; x < v && i == -1; x++) {
        if(ver[x].name == start) i = x;
    }

    // Starting vertex is marked, in the graph and in our VertexType array.
    ver[i].marked = true;
    ver[i].distance = 0;
    ver[i].previous = "N/A";
    g.MarkVertex(ver[i].name);

    // Table header and starting index row is printed.
    cout << "\n        " << setw(18) << "Vertex" << setw(18) << "Distance" << setw(18) << "Previous\n" << endl;
    PrintRow(i, ver);

    // this boolean values will only be marked true if we arrive at a dead end (when the next minIndex is -1.
    // When that happens, the algorithm stops and the remaining unmarked values are marked appropriately.
    bool dead = false;
    while(!Marked(v, ver) && !dead) {
        Queue<string> adjacent;
        g.GetToVertices(ver[i].name, adjacent);
        AssignWeights(g, v, ver, i, adjacent);
        int minIndex = FindMin(ver, v);
        if(minIndex != -1) {
            ver[minIndex].marked = true;
            g.MarkVertex(ver[minIndex].name);
            i = minIndex;
            PrintRow(i, ver);
        }
        else dead = true;
    }

    if(dead) while(!Marked(v, ver)) for(int x = 0; x < v; x++)
        if(!ver[x].marked) {
            g.MarkVertex(ver[x].name);
            ver[x].marked = true;
            ver[x].distance = -1;
            ver[x].previous = "N/A";
            PrintRow(x, ver);
        }
    cout << endl;
}

string Start(int v, VertexType ver[]) {
    string start;
    cout << "\n        Please input your starting vertex: ";
    getline(cin, start);
    bool valid = false;
    for(int x = 0; x < v && !valid; x++) {
        if(start == ver[x].name) valid = true;
    }
    while(!valid){
        cout << "        Input was invalid, please enter starting vertex: ";
        getline(cin, start);
        for(int x = 0; x < v && !valid; x++) {
            if(start == ver[x].name) valid = true;
        }
    }
    cout << "\n        ------------------------------------------------------------" << endl;
    return start;
}

bool Marked(int v, VertexType ver[]) {
    for(int x = 0; x < v; x++) if(!ver[x].marked) return false;
    return true;
}

void AssignWeights(Graph<string> &g, int v, VertexType ver[], int s, Queue<string>& q) {
    while(!q.isEmpty()) {
        string temp = q.dequeue();
        int tempIndex = -1;
        for(int x = 0; x < v && tempIndex == -1; x++) {
            if(ver[x].name == temp) tempIndex = x;
        }
        int weight = g.WeightIs(ver[s].name, ver[tempIndex].name);
        if(ver[tempIndex].distance > weight + ver[s].distance && !ver[tempIndex].marked) {
            ver[tempIndex].distance = weight + ver[s].distance;
            ver[tempIndex].previous = ver[s].name;
        }
    }
}

int FindMin(VertexType ver[], int v) {
    int min = INT_MAX - 1;
    int index = -1;
    for(int x = 0; x < v; x++) {
        if(ver[x].distance < min && !ver[x].marked) {
            min = ver[x].distance;
            index = x;
        }
    }
    return index;
}

void PrintRow(int i, VertexType ver[]) {
    if(ver[i].distance != -1) {
        cout << "        " << setw(18) << ver[i].name << setw(18) << ver[i].distance << setw(18) << ver[i].previous << endl;
    }
    else {
        cout << "        " << setw(18) << ver[i].name << setw(18) << "Not on path" << setw(18) << ver[i].previous << endl;
    }
}