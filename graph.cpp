// Implementation for Graph class
#include "graph.h"
#include <iostream>
#include <cstdlib>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <cassert>
#include "p1_helper.h"

using namespace std;

// Constructor
Graph::Graph() {
  // nodes = new vector<GraphNode*>;
  name = "";
  node_count = 0;
  edge_count = 0;
  canonical_label = "";
}

// Destructor
Graph::~Graph() {
  // delete nodes;
}

// setName function
void Graph::setName(string n) { name = n; }

/* Function addNode
 * Input: Node index(int) and node label(char)
 * Output: true if node is added successfully, false if otherwise
 */
bool Graph::addNode(int idx, string l) {
  GraphNode new_node;
  new_node.label = l;
  if (idx == node_count) {
    nodes.push_back(new_node);
    node_count++;
  }
  else if (idx < node_count) {
    nodes[idx] = new_node;
  }
  else if (idx > node_count) {
    nodes.resize(idx + 1); 
    nodes[idx] = new_node;
    node_count = idx + 1;
  }
  return true;
}

/* Function addEdge
 * Input: Two node indices (ints) and number of edges between the two nodes
 * Output: true if new edge is added successfully, false otherwise.
 * Cases when addEdge will fail: node index does not exist, or two node indices are the same
 */
bool Graph::addEdge(int idx1, int idx2, int edge_weight) {
  if (idx1 >= node_count) {
    cout << "Node index " << idx1 << " out of range." << endl;
    return false;
  }
  if (idx2 >= node_count) {
    cout << "Node index " << idx2 << " out of range." << endl;
    return false;
  }
  if (nodes[idx1].label == "") {
    cout << "Node index " << idx1 << " was not initialized." << endl;
    return false;
  }
  if (nodes[idx2].label == "") {
    cout << "Node index " << idx2 << " was not initialized." << endl;
    return false;
  }
  nodes[idx1].adj_list[idx2] = edge_weight;
  nodes[idx2].adj_list[idx1] = edge_weight;

  return true;
}

/* displayGraph function prints the graph on screen with same format as the input
 */
void Graph::displayGraph() {
  cout << "# graph name\n";
  cout << name << endl;
  
  cout << "# node ID, label\n";
  for (int i = 0; i < node_count; i++) {
    cout << i << " " << nodes[i].label << endl;
  }

  cout << "# node ID1, node ID2, number of bounds\n";
  for (int i = 0; i < node_count; i++) {
    if (!nodes[i].adj_list.empty()) {
      for (auto iter = nodes[i].adj_list.begin(); iter != nodes[i].adj_list.end(); iter++) {
        pair<int, int> it = *iter;
        cout << i << " " << it.first << " " << it.second << endl;
      }
    }
  }
  // Debug
  cout << "display done" << endl;
}

// GetName function
string Graph::getName() {
  return name;
}

// getNode function
GraphNode Graph::getNode(int n) {
  assert(n < node_count);
  return nodes[n];
}

// getEdgeLabel with given row number and column number
// If the edge does not exist, return "0"
string Graph::getEdgeLabel(int row, int col) {
  assert(row < node_count && col < node_count);
  auto it = nodes[row].adj_list.find(col);
  if (it != nodes[row].adj_list.end()) {
    return intToStr(it->second);
  }
  return "0";
}
















