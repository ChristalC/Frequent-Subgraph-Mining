// Implementation of runner class
#include "runner.h" 

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

#include "p1_helper.h"

using namespace std;

// Default constructor
Runner::Runner() {
  minsup = 0;
}

// Constructor with given graph database and minsup
Runner::Runner(vector<Graph*>& db, int ms) {
  graph_db = db;
  graph_count = db.size();
  minsup = ms;
}

/* Function generateFrequentNodes: finds all nodes appear in graph database equal or larger than minsup times
 * The function will update the freq_nodes field of runner class
 * Output: a vector of AdjMatrix, with embedding list included in AdjMatrix
 */
vector<AdjMatrix> Runner::generateFrequentNodes() {
  unordered_map<string, AdjMatrix> string_adj_matrix_map;
  for (int i = 0; i < graph_count; i++) {
    int graph_size = graph_db[i]->getNodeCount();
    for (int j = 0; j < graph_size; j++) {
      string node_label = graph_db[i]->getNodeLabel(j);
      AdjMatrix new_adj_matrix(1, graph_count);
      new_adj_matrix.setElement(0, 0, node_label);
      Embedding new_emb;
      new_emb.setData({j});

      string matrix_code = new_adj_matrix.genCode();
      // If same AdjMatrix is not in string_adj_matrix_map, add the new_adj_matrix to it
      // If already in exists, insert the new embedding to existing AdjMatrix
      if (string_adj_matrix_map.find(matrix_code) == string_adj_matrix_map.end()) {
        string_adj_matrix_map[matrix_code] = new_adj_matrix;
      }
      string_adj_matrix_map[matrix_code].insertEmb(i, new_emb);
    }
  }
  vector<AdjMatrix> freq_node_list;
  for (auto it = string_adj_matrix_map.begin(); it != string_adj_matrix_map.end(); it++) {
    pair<string, AdjMatrix> item = *it;
    if (item.second.getFrequency() >= minsup) {
      freq_node_list.push_back(item.second);
    }
  }
  freq_nodes = freq_node_list;
  return freq_node_list;
}


/* Function generateFrequentEdges: finds all edges appear in graph database equal or larger than minsup times
 * Output: a vector of AdjMatrix, with embedding list included in AdjMatrix
 */
vector<AdjMatrix> Runner::generateFrequentEdges() {
  unordered_map<string, AdjMatrix> string_adj_matrix_map;
  for (int i = 0; i < graph_count; i++) {
    int graph_size = graph_db[i]->getNodeCount();
    for (int j = 0; j < graph_size; j++) {
      GraphNode node_j = graph_db[i]->getNode(j);
      for (auto it = node_j.adj_list.begin(); it != node_j.adj_list.end(); it++) {
        pair<int, int> edge = *it;
        int k = edge.first;
        string node1_label = graph_db[i]->getNodeLabel(j);
        string node2_label = graph_db[i]->getNodeLabel(k);
        string edge_label = intToStr(edge.second);
        assert(edge_label != "0");
        if (node1_label < node2_label) {
          continue;
        }
        string code = node1_label + edge_label + node2_label;
        Embedding new_emb;
        new_emb.setData({j, k});

        if (string_adj_matrix_map.find(code) == string_adj_matrix_map.end()) {
          AdjMatrix new_adj_matrix(2, graph_count);
          new_adj_matrix.setElement(0, 0, node1_label);
          new_adj_matrix.setElement(1, 1, node2_label);
          new_adj_matrix.setElement(0, 1, edge_label);
          string_adj_matrix_map[code] = new_adj_matrix;
        }
        string_adj_matrix_map[code].insertEmb(i, new_emb);
      }
    }
  }
  vector<AdjMatrix> freq_edge_list;
  for (auto it = string_adj_matrix_map.begin(); it != string_adj_matrix_map.end(); it++) {
    pair<string, AdjMatrix> item = *it;
    if (item.second.getFrequency() >= minsup) {
      freq_edge_list.push_back(item.second);
    }
  }
  freq_edges = freq_edge_list;
  return freq_edge_list;
}

/* Function ffsmExplore contains the main algorithm
 * Runs recursively until 
 * Input: First one is CAMs of frequent edges; second one is CAMs of frequent nodes and edges
 * Output: set W contains CAMs of all frequent subgraphs searched so far
 * W = cam_freq_subgraphs, should be empty at first call, get updated on each call
 * C = new_candidates, in the first call, P will be passed in as C
 * P = frequent edges
 * X = current_adj
 */
void Runner::ffsmExplore(vector<AdjMatrix>& candidates, vector<AdjMatrix>& cam_freq_subgraphs) {
  int num_candidates = candidates.size();
  
  for (int i = 0; i < num_candidates; i++) {
    AdjMatrix current_adj = candidates[i];
    if (current_adj.isCam()) {
      cam_freq_subgraphs.push_back(current_adj);
      vector<AdjMatrix> new_candidates;

      // Join current_adj with each AdjMatrix in candidates(P)
      for (int j = 0; j < num_candidates; j++) {
        AdjMatrix::join(current_adj, candidates[j], new_candidates);
      }
      current_adj.extension(graph_db, new_candidates);
      
      auto it = new_candidates.begin();
      while (it != new_candidates.end()) {
        if (it->getFrequency() < minsup || !it->isSubCam()) {
          it = new_candidates.erase(it);
        }
        else {
          it++;
        }
      }
      ffsmExplore(new_candidates, cam_freq_subgraphs);
    }
  }
}

void Runner::run() {
  generateFrequentNodes();
  output.insert(output.end(), freq_nodes.begin(), freq_nodes.end());
  generateFrequentEdges();
  // output.insert(output.end(), freq_edges.begin(), freq_edges.end());
  ffsmExplore(freq_edges, output);
}

void Runner::displayOutput() const {
  cout << "Frequent graphs output: " << endl; 
  
  /* Used for display number of graphs that contain certain subgraph
  for (auto it = output.begin(); it != output.end(); it++) {
    AdjMatrix adj_matrix = *it;
    adj_matrix.displayMatrix();
  }
  */

  // repeatedly count subgraphs in a single graph
  for (auto it = output.begin(); it != output.end(); it++) {
    int freq = it->getUniqFrequency();
    if (freq >= minsup) {
      it->displayMatrix();
    }
  }
}
























