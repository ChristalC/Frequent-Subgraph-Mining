// Implementation of embedding class
#include "embedding.h"

#include <cstdlib>
#include <vector>
#include <iostream>


using namespace std;
// Default Constructor
Embedding::Embedding() {}

void Embedding::displayEmbedding() const {
  int size = data.size();
  for (int i = 0; i < size; i++) {
    cout << data[i] << " ";
  }
  cout << endl;
}

// Remove the last element of embedding
void Embedding::removeLast() {
  data.erase(data.end() - 1);
}
// Return the last element of data
int Embedding::getLast() const {
  return data[data.size() - 1];
}

// Add given integer to the end of the data
void Embedding::addLast(int n) {
  data.push_back(n);
}
// hasNode checks if a node is in embedding list
bool Embedding::hasNode(int node_idx) const {
  int size = data.size();
  for (int i = 0; i < size; i++) {
    if (data[i] == node_idx) {
      return true;
    }
  }
  return false;
}

bool Embedding::operator<(const Embedding& e) const {
  // Assume the size of two embeddings are the same
  int size1 = data.size(), size2 = e.data.size();
  int n = std::min(size1, size2);
  for (int i = 0; i < n; i++) {
    if (data[i] < e.data[i]) {
      return true;
    }
    else if (data[i] > e.data[i]) {
      return false;
    }
  }
  return size1 < size2;
}

bool Embedding::operator==(const Embedding& e) const {
  // Assume the size of two embeddings are the same
  if (data.size() != e.data.size()) {
    return false;
  }
  int n = data.size();
  for (int i = 0; i < n; i++) {
    if (data[i] != e.data[i]) {
      return false;
    }
  }
  return true;
}
