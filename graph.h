// graph class header file
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_map>
// #include "p1_helper.h"

using namespace std;

struct GraphNode {
  string label;
  unordered_map<int, int> adj_list;   // First int for adjacent GraphNode index, second int for edge weight
  // GraphNode(string l) : label(l), adj_list() {} 
};

class Graph {
  private:
    string name;
    vector<GraphNode> nodes;
    int node_count;
    int edge_count;
    string canonical_label;
  public:
    // Constructor
    Graph();

    // Desctructor
    ~Graph();
    
    // Setter and Mutator
    void setName(string n);
    bool addNode(int idx, string l);
    bool addEdge(int n1, int n2, int edge_weight);
    void setMatrix(vector<vector<string>>& m);

    // Getter
    string getName();
    GraphNode getNode(int);
    string getNodeLabel(int node_idx) {return nodes[node_idx].label;}
    string getEdgeLabel(int row, int col);
    int getNodeCount() {return node_count;}
    int getEdgeCount() {return edge_count;}

    // Display functions (for Debugging purpose)
    void displayGraph();

    // Debug purpose
    string genGraphCode();

    // string canonicalLabel();
    // string backTrackCanonicalLabel(vector<vector<string>>& m, vector<vector<int>>& partition, vector<int>& mapping, vector<vector<string>>& m_mapped, int p_cur);

    friend bool isIsomorphism(Graph& g, Graph& s);
    friend bool isSameGraph(Graph& g, Graph& s);
    // Decide if current graph is subgraph of another graph
    friend bool isSubgraph(Graph& g, Graph& s);
    friend bool backTrackSearch(Graph& g, Graph& s, int idx, vector<int> mapped);

};

#endif

