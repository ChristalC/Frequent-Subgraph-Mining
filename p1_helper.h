#ifndef P1_HELPER_H
#define P1_HELPER_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"

using namespace std;

/* Function splitString: splits input string with white space
 * Input: string ip
 * Output: vector of strings, get rid of characters after '#'
 */
vector<string> splitString(string ip);

/* Function isMinsup: check if input string vector is a valid integer
 * Input: vector<string> with size 1
 * Output: true if the string can be converted into an integer; false otherwise
 */
bool isMinsup(vector<string>& ip);

/* Function isNode: check if given string vector provides a valid node data
 * Input: vector<string> with size of 2
 * Output: true if the first string is an integer and the second string is a string
 */
bool isNode(vector<string>& ip);

/* Function isEdge: check if given string vector provides a valid edge data
 * Input: vector<string> with size of 3
 * Output: true if the 3 strings are integers
 */
bool isEdge(vector<string>& ip);

/* Function isNum: check if given string is a number
 * Input: a string
 * Output: true if the string consists of digit only; false if otherwise
 */
bool isNum(string);

string intToStr(int num);


#endif











