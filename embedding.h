// Header file of Embedding class

#ifndef EMBEDDING_H
#define EMBEDDING_H

#include <vector>

using namespace std;

class Embedding {
  private:
    vector<int> data;
  public:
    // Constructor
    Embedding();

    // Getter
    vector<int> getData() {return data;}
    
    // Setter
    void setData(vector<int> l) {data = l;}
    void removeLast();
    void addLast(int n);

    int getLast() const;
    void displayEmbedding() const;
    bool hasNode(int node_idx) const;

    // Overload operator > to compare two embeddings
    bool operator>(const Embedding& e) const;
    bool operator<(const Embedding& e) const;
    bool operator==(const Embedding& e) const;
};


#endif

