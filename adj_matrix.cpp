// Implementation file for AdjMatrix class
#include "adj_matrix.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "graph.h"
#include "p1_helper.h"

using namespace std;

// Default constructor
AdjMatrix::AdjMatrix() {
  graph_count = 0;
}

// Constructor given the matrix size
AdjMatrix::AdjMatrix(int size) {
  m.resize(size);
  vector<string> tmp(size, "0");
  for (int i = 0; i < size; i++) {
    m[i] = tmp;
  }
}

// Constructor with given matrix size and graph_count
AdjMatrix::AdjMatrix(int size, int graph_num) {
  m.resize(size);
  vector<string> tmp(size, "0");
  for (int i = 0; i < size; i++) {
    m[i] = tmp;
  }
  graph_count = graph_num;
  emb_list.resize(graph_num);
}

void AdjMatrix::displayMatrix() const {
  int n = m.size();
  cout << "matrix: " << endl;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Code: "<< genCode() << endl;
  /*
  cout << "Embedding list: " << endl;
  for (int i = 0; i < graph_count; i++) {
    cout << "Graph " << i << ": " << endl;
    for (const auto& emb_item : emb_list[i]) {
      emb_item.displayEmbedding();
    }
  }
  */
  // cout << endl;
}

/* Function genCode: produces code by listing all elements on the lower left triangle of a given matrix
 * Input: given matrix of strings, the matrix has to be a square
 * Output: a string
 */
string AdjMatrix::genCode() const {
  int n = m.size();
  string ans;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      ans += m[i][j];
    }
  }
  return ans;
}

// Overload operator ==
bool AdjMatrix::operator==(const AdjMatrix& other) const {
  return genCode() == other.genCode();
}

// Set edge of row number and col number with given value, if row != col, two cells are set
void AdjMatrix::setElement(int row, int col, string val) {
  m[row][col] = val;
  if (row != col) {
    m[col][row] = val;
  }
}

// setGraphCount sets the size of emb_list
void AdjMatrix::setGraphCount(int graph_num) {
  graph_count = graph_num;
  emb_list.resize(graph_num);
}

// Insert a new embedding to specified graph
void AdjMatrix::insertEmb(int graph_idx, Embedding new_emb) {
  if (graph_idx >= graph_count) {
    graph_count = graph_idx + 1;
    emb_list.resize(graph_count);
  }
  emb_list[graph_idx].insert(new_emb);
}

// Function swapRow: swap in place all elements on given two rows
void AdjMatrix::swapRow(int r1, int r2) {
  vector<string> tmp_row = m[r1];
  m[r1] = m[r2];
  m[r2] = tmp_row;
}

// Function swapCol: swap in place all elements on given two columns
void AdjMatrix::swapCol(int c1, int c2) {
  int n = m.size();
  string tmp;
  for (int i = 0; i < n; i++) {
    tmp = m[i][c1];
    m[i][c1] = m[i][c2];
    m[i][c2] = tmp;
  }
}

/* Function isCam: decides if a graph with given nodes order, is a Canonical Adjacency Matrix(CAM)
 * It does so by swapping each pairs of nodes on the graph to see if result code is larger than current code.
 * If a larger code could be produced after swapping any pair, return false
 */
bool AdjMatrix::isCam() {
  AdjMatrix test_m = *this;
  int n = m.size();
  string cur_code = genCode();
  string produced_code;
  string max_code = "";
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      test_m.swapRow(i, j);
      test_m.swapCol(i, j);
      if (test_m.genCode() > cur_code) {
        return false;
      }
      test_m.m = m;
    }
  }
  return true;
}

/* Decide if a matrix is a Suboptimal Canonical Adjcency Matrix (Suboptimal CAM)
 * Suboptimal Canonical Adjacency Matrix (simply, suboptimal CAM) of G 
 * is an adjacency matrix M of G such that its maximal proper submatrix N 
 * is the CAM of the graph N represents.
 */
bool AdjMatrix::isSubCam() {
  AdjMatrix test_m = genMaxSubMatrix();
  return test_m.isCam();
}

/* Check if a given matrix is inner matrix or outer matrix
 * A matrix is an “inner” matrix iff it has at least two edge entries in the last row. Otherwise, it is an outer matrix.
 * Input: a square matrix indicating a connected graph
 * Output: true, if the given matrix is an inner matrix. False if it is an outer matrix
 */
bool AdjMatrix::isInner() {
  int n = m.size();
  int count = 0;
  for (int i = 0; i < n - 1; i++) {
    if (m[n - 1][i] != "0") {
      count++;
    }
  }
  return count >= 2;
}

bool AdjMatrix::isOuter() {
  return !isInner();
}

/* Create a maximal proper submatrix of given matrix
 * Input: a square matrix indicating a connected graph
 * Output: the maximal proper submatrix
 */
AdjMatrix AdjMatrix::genMaxSubMatrix() {
  int n = m.size();
  AdjMatrix sub_adj_matrix;
  // If m is an inner matrix (has at least two edge entries on the last row)
  if (isInner()) {
    vector<vector<string>> sub_m = m;
    for (int i = n - 2; i >= 0; i--) {
      if (sub_m[n - 1][i] != "0") {
        sub_m[n - 1][i] = "0";
        sub_m[i][n - 1] = "0";
        sub_adj_matrix.m = sub_m;
        return sub_adj_matrix;
      }
    }
  }
  else {
    vector<vector<string>> sub_m(n - 1);
    vector<string> tmp(n - 1);
    for (int i = 0; i < n - 1; i++) {
      sub_m[i] = tmp;
      for (int j = 0; j < n - 1; j++) {
        sub_m[i][j] = m[i][j];
      }
    }
    sub_adj_matrix.m = sub_m;
    return sub_adj_matrix;
  }
}

/* Function join: joins two given matrices
 * First it need to be confirmed that: m1 and m2 share the same maximal proper submatrix
 * If not, return empty set
 * Then, if they are both inner matrices and genCode(m1) >= genCode(m2), call joinCase1
 * else if m1 is inner and m2 is outer and genCode(m1) >= genCode(m2) call joinCase2
 * else if both matrices are outer, call joinCase3a and joinCase3b
 * Output: True if joined matrices are appended to joined_list. False otherwise.  
 */
bool AdjMatrix::join(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  if (m1.genMaxSubMatrix().m != m2.genMaxSubMatrix().m) {
    return false;
  }
  bool inner1 = m1.isInner(), inner2 = m2.isInner();
  string code1 = m1.genCode(), code2 = m2.genCode();
  if (inner1 && inner2) {
    if (code1 >= code2) {
      return joinCase1(m1, m2, joined_list);
    }
    return false;
  }
  if (inner1 && !inner2 ) {
    if (code1 >= code2) {
      return joinCase2(m1, m2, joined_list);
    }
    return false;
  }
  if (!inner1 && !inner2) {
    return joinCase3(m1, m2, joined_list);
  }
  return false;
}

/* Function joinCase1: joins 2 inner matrices when conditions are met
 * Input: two matrices with shared Maximal Propor Submatrix
 * Output: True if joined matrix is generated. False otherwise.
 */
bool AdjMatrix::joinCase1(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  // Find the last entry on the last row that is not "0"
  int n1 = m1.m.size(), n2 = m2.m.size();
  int last_col_m1, last_col_m2;
  for (int i = n1 - 2; i >= 0; i--) {
    if (m1.m[n1 - 1][i] != "0") {
      last_col_m1 = i;
      break;
    }
  }
  for (int i = n2 - 2; i >= 0; i--) {
    if (m2.m[n2 - 1][i] != "0") {
      last_col_m2 = i;
      break;
    }
  }
  // if last_col_m1 == last_col_m2, the two matrices cannot be joined, return false
  // else, join the two matrices return join result
  if (last_col_m1 == last_col_m2) {
    return false;
  }
  AdjMatrix joined_adj_matrix;
  joined_adj_matrix.m = m1.m;
  joined_adj_matrix.m[n1 - 1][last_col_m2] = m2.m[n2 - 1][last_col_m2];
  joined_adj_matrix.m[last_col_m2][n1 - 1] = joined_adj_matrix.m[n1 - 1][last_col_m2];
  int num_graph = m1.emb_list.size();
 
  // Join embedding lists of m1 and m2. 
  // Intersection of the two embedding list will be inserted to embeddinglist of the new AdjMatrix. 
  for (int i = 0; i < num_graph; i++) {
    joined_adj_matrix.emb_list.emplace_back();
    set_intersection(m1.emb_list[i].begin(), m1.emb_list[i].end(), 
        m2.emb_list[i].begin(), m2.emb_list[i].end(), 
        inserter(joined_adj_matrix.emb_list[i], joined_adj_matrix.emb_list[i].begin()));
  }
  
  joined_list.push_back(joined_adj_matrix);
  return true;
}

/* Function joinCase2: joins 1 inner matrix and 1 outer matrix when conditions are met
 * Input: 1 inner matrix and 1 outer matrix with shared Maximal Propor Submatrix
 * Output: True if joined matrix is generated. 
 */
bool AdjMatrix::joinCase2(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  int n1 = m1.size(), n2 = m2.size();
  // Copy the joined matrix from m2 (since m2 is the same size as joined matrix) and update the last two rows
  // Next to the last row should be copied from m1, last row should remain the same as from m2
  AdjMatrix joined_adj_matrix;
  joined_adj_matrix.m = m2.m;
  for (int i = 0; i <= n2 - 3; i++) {
    joined_adj_matrix.setElement(n2 - 2, i, m1.m[n1 - 1][i]);
    joined_adj_matrix.m[i][n2 - 2] = joined_adj_matrix.m[n2 - 2][i];
  }

  // Join embedding list
  int graph_num = m1.emb_list.size();
  for (int i = 0; i < graph_num; i++) {
    for (auto iter = m2.emb_list[i].begin(); iter != m2.emb_list[i].end(); iter++) {
      Embedding emb = *iter;
      Embedding target_emb = emb;
      target_emb.removeLast();
      if (m1.emb_list[i].find(target_emb) != m1.emb_list[i].end()) {
        joined_adj_matrix.insertEmb(i, emb);
      }
    }
  }
  joined_list.push_back(joined_adj_matrix);
  return true;
}
 
/* Function joinCase3: joins 2 outer matrices when conditions are met
 * Input: 2 outer matrices with shared Maximal Propor Submatrix
 * Output: True if joined matrix is generated. False otherwise.
 */
bool AdjMatrix::joinCase3(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  joinCase3a(m1, m2, joined_list);
  joinCase3b(m1, m2, joined_list);

  return true;
}
 
/* Function joinCase3a: joins 2 outer matrices when conditions are met
 * Input: 2 outer matrices with shared Maximal Proper Submatrix
 * Output: True if joined matrix is generated. False otherwise.
 */
bool AdjMatrix::joinCase3a(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  // m1 and m2 should be the same size, 
  // since they are both outer matrices and their max proper submatrix is the same
  int n = m1.size();   

  // Last node of m1 and m2 must have same label
  if (m1.m[n - 1][n - 1] != m2.m[n - 1][n - 1]) {
    return false;
  }

  // Find the last edge column number of m1 and m2
  int last_col_m1, last_col_m2;
  for (last_col_m1 = n - 2; last_col_m1 >= 0; last_col_m1--) {
    if (m1.m[n - 1][last_col_m1] != "0") {
      break;
    }
  }
  for (last_col_m2 = n - 2; last_col_m2 >= 0; last_col_m2--) {
    if (m2.m[n - 1][last_col_m2] != "0") {
      break;
    }
  }
  // If the last edge entry is on the same column return empty set, otherwise, generate joined matrix
  if (last_col_m1 == last_col_m2) {
    return false;
  }
  
  // Copy whole m1 to the generated joined_adj_matrix, and the last entry of m2 to it
  AdjMatrix joined_adj_matrix;
  joined_adj_matrix.m = m1.m;
  joined_adj_matrix.setElement(n - 1, last_col_m2, m2.m[n - 1][last_col_m2]);
  
  // Join embedding lists of m1 and m2. 
  // Intersection of the two embedding list will be inserted to embeddinglist of the new AdjMatrix. 
  for (int i = 0; i < m1.getGraphCount(); i++) {
    joined_adj_matrix.emb_list.emplace_back();
    set_intersection(m1.emb_list[i].begin(), m1.emb_list[i].end(), 
        m2.emb_list[i].begin(), m2.emb_list[i].end(), 
        inserter(joined_adj_matrix.emb_list[i], joined_adj_matrix.emb_list[i].begin()));
  }
  joined_list.push_back(joined_adj_matrix);
  return true;
}

/* Function joinCase3b: joins 2 outer matrices when conditions are met
 * Input: 2 outer matrices with shared Maximal Proper Submatrix
 * Output: True if joined matrix is appended to joined list when conditions are met, false otherwise
 */
bool AdjMatrix::joinCase3b(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list) {
  int n = m1.m.size(); 
  AdjMatrix joined_adj_matrix;
  // Generate with join case 3b
  vector<vector<string>> joined_matrix(n + 1);
  vector<string> tmp(n + 1);
  // Copy row 0 to n - 1 and col 0 to n - 1 from m1
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmp[j] = m1.m[i][j];
    }
    joined_matrix[i] = tmp;
  }
  // Copy row n - 1 and col (0, n - 2) from m2 to row n of joined_matrix
  for (int i = 0; i < n - 1; i++) {
    tmp[i] = m2.m[n - 1][i];
  }
  joined_matrix[n] = tmp;
  joined_matrix[n][n - 1] = "0";
  for (int i = 0; i <= n - 1; i++) {
    joined_matrix[i][n] = joined_matrix[n][i];
  }
  joined_matrix[n][n] = m2.m[n - 1][n - 1]; // Copy last node label from m2
  joined_adj_matrix.m = joined_matrix;
  
  int graph_num = m1.getGraphCount();
  joined_adj_matrix.setGraphCount(graph_num);
  for (int i = 0; i < graph_num; i++) {
    for (auto it = m1.emb_list[i].begin(); it != m1.emb_list[i].end(); it++) {
      Embedding emb = *it;
      Embedding target_bound = emb;
      target_bound.removeLast();
      auto it_lower = m2.emb_list[i].lower_bound(target_bound);
      int last_ele = target_bound.getLast();
      target_bound.removeLast();
      target_bound.addLast(last_ele + 1);
      auto it_upper = m2.emb_list[i].upper_bound(target_bound);

      while (it_lower != it_upper) {
        if (emb.getLast() != it_lower->getLast()) {
          Embedding new_emb = emb;
          new_emb.addLast(it_lower->getLast());
          joined_adj_matrix.insertEmb(i, new_emb);
        }
        it_lower++;
      }
    }
  }
  joined_list.push_back(joined_adj_matrix);
  return true;
}

bool AdjMatrix::extension(vector<Graph*>& graph_db, vector<AdjMatrix>& extension_list) {
  int graph_num = graph_db.size();
  // List of new extended matrices, keyed by (new edge label, new node label)
  unordered_map<string, AdjMatrix> new_matrices_map;
  for (int i = 0; i < graph_num; i++) {
    // Iterate emb_list of the ith graph
    // For each embedding, look for all the nodes that are connected 
    // to the last node on the the embedding on the ith graph 
    int graph_size = graph_db[i]->getNodeCount();
    int matrix_size = m.size();
    for (auto it = emb_list[i].begin(); it != emb_list[i].end(); it++) {
      Embedding emb_list_item = *it;
      int last_emb_node_idx = emb_list_item.getLast();
      GraphNode node_last = graph_db[i]->getNode(last_emb_node_idx);
      for (auto it = node_last.adj_list.begin(); it != node_last.adj_list.end(); it++) {
        pair<int, int> edge = *it;
        int new_node_idx = edge.first;
        if ( !emb_list_item.hasNode(new_node_idx)) {
          string new_edge_label = intToStr(edge.second); 
          string new_node_label = graph_db[i]->getNodeLabel(new_node_idx);
          string key = new_edge_label + "$" + new_node_label;
          // If result matrix already exists, do not generate a new matrix, just update it's embedding list in the map
          if (new_matrices_map.find(key) == new_matrices_map.end()) {
            AdjMatrix new_adj_matrix(matrix_size + 1, graph_num);
            for (int k = 0; k < matrix_size; k++) {
              for (int p = k; p < matrix_size; p++) {
                new_adj_matrix.setElement(k, p, m[k][p]);
              }
            }
            for (int p = 0; p < matrix_size - 1; p++) {
              new_adj_matrix.setElement(matrix_size, p, "0");
            }
            new_adj_matrix.setElement(matrix_size, matrix_size - 1, new_edge_label);
            new_adj_matrix.setElement(matrix_size, matrix_size, new_node_label);
            new_matrices_map[key] = new_adj_matrix;
          }
          // new embedding is current embedding + matrix[j][j]
          Embedding new_emb = emb_list_item;
          new_emb.addLast(new_node_idx);
          new_matrices_map[key].emb_list[i].insert(new_emb);
        }
      }
    }
  }
  for (auto it = new_matrices_map.begin(); it != new_matrices_map.end(); it++) {
    pair<string, AdjMatrix> map_item = *it;
    extension_list.push_back(map_item.second);
  }
  return !new_matrices_map.empty();
}

// Get frequency of matrix by counting embeddings
int AdjMatrix::getFrequency() const {
  int count_embedding = 0;

  // When a subgraph can be counted in a graph multiple times
  for (int i = 0; i < graph_count; i++) {
    count_embedding += emb_list[i].size();
  }

  /* Case when only number of graphs that contain subgraph is count
  for (int i = 0; i < graph_count; i++) {
    if (!emb_list[i].empty()) {
      count_embedding++;
    }
  }
  */
  return count_embedding;
}

/* Function getUniqFrequency: counts the number of embeddings of AdjMatrix
 * It excludes embeddings that contains exactly same nodes
 */
int AdjMatrix::getUniqFrequency() const {
  vector<set<Embedding>> uniq_emb_list(graph_count);
  for (int i = 0; i < graph_count; i++) {
    for (auto iter = emb_list[i].begin(); iter != emb_list[i].end(); iter++) {
      Embedding uniq_emb = *iter;
      vector<int> emb_v = uniq_emb.getData();
      sort(emb_v.begin(), emb_v.end());
      uniq_emb.setData(emb_v);
      uniq_emb_list[i].insert(uniq_emb);
    }
  }
  int count_embedding = 0;
  for (int i = 0; i < graph_count; i++) {
    count_embedding += uniq_emb_list[i].size();
  }
  return count_embedding;
}

// Get frequency by counting how many graphs in the graph database contains the subgraph
int AdjMatrix::getGraphFrequency() const {
  int count_embedding = 0;

  // Case when only number of graphs that contain subgraph is count
  for (int i = 0; i < graph_count; i++) {
    if (!emb_list[i].empty()) {
      count_embedding++;
    }
  }
  
  return count_embedding;
}














