
/*-----------------------------------------------------------------------------
 * This file demonstrates some suboptimal code for reading in a graphviz graph
 * file.  See readNumbersBetter.cpp for a better way to solve this problem.
 *-----------------------------------------------------------------------------*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

const double kPi = 3.14159265358979323;

struct Node {
  double x;
  double y;
};
struct Edge {
  int start;
  int end;
};
struct SimpleGraph {
  vector<Node> nodes;
  vector<Edge> edges;
};

void readGraph(SimpleGraph& g, ifstream& file) {
  // Read in how many nodes we have
  string temp;
  getline(file, temp);
  stringstream countConverter;
  countConverter << temp;
  int numNodes;
  countConverter >> numNodes;

  // Initialize our nodes
  for (int i = 0; i < numNodes; i++) {
    Node n;
    n.x = cos( 2 * kPi * i / numNodes);
    n.y = sin( 2 * kPi * i / numNodes);
    g.nodes.push_back(n);
  }

  // Read in our edges
  while (true) {
    string temp;
    getline(file, temp);
    if (file.fail())
      break;

    stringstream converter;
    converter << temp;
    int node1, node2;
    converter >> node1;
    converter >> node2;
    if (converter.fail())
      break;
    Edge e;
    e.start = node1;
    e.end = node2;
    g.edges.push_back(e);
  }
}

int main() {
  SimpleGraph g;
  ifstream f("numbers.txt");
  readGraph(g, f);

  cout << "Graph has " << g.nodes.size() << " nodes" << endl;
  cout << "The edges of our graph are as follows:" << endl;
  for (int i = 0; i < g.edges.size(); i++) {
    cout << g.edges[i].start <<" " << g.edges[i].end << endl;;
  }
}
