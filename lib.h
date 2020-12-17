#include <string>
#include <vector>
#include <exception>

#ifndef LIB_H
#define LIB_H
using namespace std;

string doubleToString(double x);
double stringToDouble(string raw);
void insertString(string& str,string content,int startIndex);
void removeSubstring(string& str,int startIndex,int endIndex);
int findMatchBracket(string& formula, int leftIndex);
string getSubstring(string& str, int startIndex,int endIndex);
void removeDouble(vector<double>& data, int index);
void insertDouble(vector<double>& data,double value, int index);
void printMainIntro();
void getCommand(string& cmd);

#endif