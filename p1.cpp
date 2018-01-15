#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "p1_helper.h"
#include "runner.h"

using namespace std;

bool processInput(vector<Graph*>& graph_list, int& ms);

int main() {
  vector<Graph*> graph_ptrs;
  int minsup;
  bool read_successful = processInput(graph_ptrs, minsup);
  int n = graph_ptrs.size();
  if (read_successful == false) {
    for (int i = 0; i < n; i++) {
      delete graph_ptrs[i];
    }
    return 0;
  }
  /*
  for (int i = 0; i < n; i++) {
    graph_ptrs[i]->displayGraph();
  }
  */
  Runner test_runner(graph_ptrs, minsup);
  test_runner.run();
  test_runner.displayOutput();

  for (int i = 0; i < n; i++) {
    delete graph_ptrs[i];
  }
  return 0;
}



/* processInput function reads minsup value and graphs data from stdin
 * Input: vector of graph pointer, where to store graphs from input
 * Output: minsup value
 */
bool processInput(vector<Graph*>& graph_list, int& ms) {
  int minsup;
  string holder;
  vector<string> read_input;
  Graph* new_graph;

  do {
    if (getline(cin, holder)) {
      read_input = splitString(holder);
    }
    else {
      return false;
    }   
  } while (read_input.size() == 0);

  if (read_input.size() == 1 && isMinsup(read_input)) {
    minsup = stoi(read_input[0], NULL, 10);
  }
  else {
    cout << "Minsup input is incorrect!\n";
    return false;
  }
  ms = minsup;

  /* The variable tracks the status of line input after previous line input, it is used to check if current line input is valid.
   * If previous line is graph name, data_mode = 1;
   * If previous line is node input, data_mode = 2; 
   * If previous line is edge input, data_mode = 3; When data_mode = 3, do not allow other inputs like graph name or node input.
   */
  int data_mode = 0;
  
  while (getline(cin, holder)) {
    read_input = splitString(holder);
    if (read_input.size() == 1) {
      new_graph = new Graph;
      new_graph->setName(read_input[0]);
      graph_list.push_back(new_graph);
      data_mode = 1;
    }
    else if (read_input.size() == 2) {
      // Check if data_mode is 1 or 2 so that new node can be added
      if (data_mode != 1 && data_mode != 2) {
        cout << "Data_mode is incorrect, cannot add new node!\n";
        return false;
      }
      if (!isNode(read_input)) {
        cout << "Node input is incorrect!\n";
        return false;
      }
      new_graph->addNode(stoi(read_input[0], NULL, 10), read_input[1]);
      data_mode = 2;
    }
    else if (read_input.size() == 3) {
      // Check if data_mode is 2 or 3 so that new edge can be added
      if (data_mode != 2 && data_mode != 3) {
        cout << "Data_mode is incorrect, cannot add new edge!\n";
        return false;
      }

      if (!isEdge(read_input)) {
        cout << "Edge input is incorrect!\n";
        return false;
      }
      new_graph->addEdge(stoi(read_input[0], NULL, 10), stoi(read_input[1], NULL, 10), stoi(read_input[2], NULL, 10));
      data_mode = 3;
    }
  }
  // Validate read graphs to see if any node is missing
  int graph_num = graph_list.size();
  for (int i = 0; i < graph_num; i++) {
    int node_num = graph_list[i]->getNodeCount();
    for (int j = 0; j < node_num; j++) {
      if (graph_list[i]->getNodeLabel(j) == "") {
        cout << "Some nodes are missing from input file. Cannot proceed!\n";
        return false;
      }
    }
  }
  return true;;
}

