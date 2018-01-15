// Implementation for p1_helper
#include "p1_helper.h"
#include <sstream>
#include <tuple>

using namespace std;

/* Function splitString: splits input string with white space
 * Input: string ip
 * Output: vector of strings, get rid of characters after '#'
 */
vector<string> splitString(string ip) {
  // Find the '#' and get rid of anything after, including '#'
  size_t pos;
  pos = ip.find("#");
  if (pos != string::npos) {
    ip = ip.substr(0, pos);
  }

  // Split the string by white spaces
  string buf;
  stringstream ss(ip);

  vector<string> tokens;

  while (ss >> buf) {
    tokens.push_back(buf);
  }
  return tokens;
}

/* Function isMinsup: check if input string vector is a valid integer
 * Input: vector<string> with size 1
 * Output: true if the string can be converted into an integer; false otherwise
 */
bool isMinsup(vector<string>& ip) {
  return isNum(ip[0]);
}

/* Function isNode: check if given string vector provides a valid node data
 * Input: vector<string> with size of 2
 * Output: true if the first string is an integer and the second string is a string
 */
bool isNode(vector<string>& ip) {
  return isNum(ip[0]);
}

/* Function  isEdge: check if given string vector provides a valid edge data
 * Input: vector<string> with size of 3
 * Output: true if the 3 strings are integers
 */
bool isEdge(vector<string>& ip) {
  for (int i = 0; i < 3; i++) {
    if (!isNum(ip[i])) {
      return false;
    }
  } 
  return true;
}

/* Function isNum: check if given string is a number
 * Input: a string
 * Output: true if the string consists of digit only; false if otherwise
 */
bool isNum(string s) {
  return (s.find_first_not_of("0123456789") == string::npos);
}

// Function intToStr accepts an integer as input and output the number as a string
string intToStr(int num) {
  stringstream ss;
  ss << num;
  return ss.str();
}












