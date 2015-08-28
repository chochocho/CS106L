#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "SimpleGraph.h"

using namespace std;

void Welcome();
int edgecheck(int, int, SimpleGraph, int);
double repel(Node, Node);
double attract(Node, Node);
double theta(Node, Node);

// Main method
int main() {
    Welcome();

    const double kPi = 3.14159265358979323;

    char filename[255];
    double runtime;
    cout << "Please enter a graph file: ";
    cin >> filename;
    cout << "Please enter a running time: ";
    cin >> runtime;

    int nodecount;
    int edgecount = 0;
    SimpleGraph graph;
    ifstream inFile;
    inFile.open(filename);
    inFile >> nodecount;

    // change k = 1 if needed, and k <= nodecount
    for (int k = 0; k < nodecount; k++) {
        Node n;
        n.x = cos((2 * kPi * k)/nodecount);
        n.y = sin((2 * kPi * k)/nodecount);
        graph.nodes.push_back(n);
    }
    while(!inFile.eof()) {
        Edge e;
        inFile >> e.start >> e.end;
        graph.edges.push_back(e);
        edgecount++;
    }
    inFile.close();
    InitGraphVisualizer(graph);
    DrawGraph(graph);

    time_t startTime = time(NULL);
    while (difftime(time(NULL), startTime) < runtime) {
        for (int m = 0; m < nodecount; m++) {
            for (int n = 0; n < nodecount; n++) {
                if (edgecheck(m, n, graph, edgecount) == 0) {
                    double f = repel(graph.nodes[m], graph.nodes[n]);
                    double t = theta(graph.nodes[m], graph.nodes[n]);
                    graph.nodes[m].x -= f * cos(t);
                    graph.nodes[m].y -= f * sin(t);
                    graph.nodes[n].x += f * cos(t);
                    graph.nodes[n].y += f * sin(t);
                } else {
                    double f = attract(graph.nodes[m], graph.nodes[n]);
                    double t = theta(graph.nodes[m], graph.nodes[n]);
                    graph.nodes[m].x += f * cos(t);
                    graph.nodes[m].y += f * sin(t);
                    graph.nodes[n].x -= f * cos(t) ;
                    graph.nodes[n].y -= f * sin(t);
                }
            }
        }
        // redraw
        DrawGraph(graph);
    }
    return 0;
}

int edgecheck(int a, int b, SimpleGraph graph, int count) {
    for (int i = 0; i < count; i++) {
        if (graph.edges[i].start == a && graph.edges[i].end == b) {
            return 1;
        }
    }
    return 0;
}

double repel(Node a, Node b) {
    double k = 0.1;
    if (a.y == b.y && a.x == b.x) {
        return 0;
    }
    cout << k / sqrt(pow((b.y - a.y), 2) + pow((b.x - a.x), 2)) << endl;
    return k / sqrt(pow((b.y - a.y), 2) + pow((b.x - a.x), 2));
}

double attract(Node a, Node b) {
    double k = 0.1;
    // cout << k * sqrt(pow((b.y - a.y), 2) + pow((b.x - a.x), 2)) << endl;
    return  k * (pow((b.y - a.y), 2) + pow((b.x - a.x), 2));
}

double theta(Node a, Node b) {
    return atan2(b.y - a.y, b.x - a.x);
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}
