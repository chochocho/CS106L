
/*-----------------------------------------------------------------------------
 *  This is a better way to handle the problem of reading in the graphviz Graph
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
  int numNodes;
  file >> numNodes;

  // Initialize our nodes
  g.nodes.resize(numNodes);
  for (int i = 0; i < numNodes; i++)
    g.nodes[i] = {cos( 2 * kPi * i / numNodes), sin( 2 * kPi * i / numNodes)};

  // Read in our edges
  Edge e;
  while (file >> e.start >> e.end)
    g.edges.push_back(e);
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
