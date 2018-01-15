// header file for AdjMatrix class 
#ifndef ADJ_MATRIX
#define ADJ_MATRIX

#include <string>
#include <vector>
#include <set>

#include "embedding.h"
#include "graph.h"

using namespace std;

class AdjMatrix {
  private:
    vector<vector<string>> m; 
    int graph_count;
    vector<set<Embedding>> emb_list;
  public:
    // Constructor
    AdjMatrix();
    AdjMatrix(int size);
    AdjMatrix(int size, int graph_num);

    int size() { return m.size(); }

    void displayMatrix() const;
    /* Function genCode: produces code by listing all elements on the lower left triangle of a given matrix
     * Output: a string
     */
    string genCode() const;

    // Overload operator ==
    bool operator==(const AdjMatrix& other) const;

    // Set edge of row number and col number with given value, if row != col, two cells are set
    void setElement(int row, int col, string val);

    // setGraphCount sets the size of emb_list
    void setGraphCount(int graph_num);
    int getGraphCount() { return graph_count; };

    // Insert a new embedding to specified graph
    void insertEmb(int graph_idx, Embedding new_emb);
    
    // Function swapRow: swap all elements on given two rows
    void swapRow(int r1, int r2);

    // Function swapCol: swap inplace all elements on given two columns
    void swapCol(int c1, int c2);

    // Decide if a matrix is a Canonical Adjcency Matrix (CAM)
    bool isCam();

    // Decide if a matrix is a Suboptimal Canonical Adjcency Matrix (Suboptimal CAM)
    bool isSubCam();

    // Check if a given matrix is inner matrix or outer matrix
    bool isInner();
    bool isOuter();

    // Create a maximal proper submatrix of given matrix
    AdjMatrix genMaxSubMatrix();

    // Join two given matrices
    static bool join(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);
    static bool joinCase1(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);
    static bool joinCase2(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);
    static bool joinCase3(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);
    static bool joinCase3a(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);
    static bool joinCase3b(AdjMatrix& m1, AdjMatrix& m2, vector<AdjMatrix>& joined_list);

    // Extend a given matrix
    bool extension(vector<Graph*>& graph_database, vector<AdjMatrix>& extension_list);

    // Get frequency of matrix by counting embeddings
    int getFrequency() const;
    int getUniqFrequency() const;
    int getGraphFrequency() const;
};

#endif


