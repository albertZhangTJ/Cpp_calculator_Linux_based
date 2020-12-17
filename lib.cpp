#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "lib.h"

using namespace std;

//this function takes in an double and convert it to string
//the maximum length of the answer is set to be 16
string doubleToString(double x){
    string ans=to_string(x);
    if (ans.size()<16){
        return ans;
    }
    return getSubstring(ans,0,15);
}
//this function takes in a string and returns its content as a double
double stringToDouble(string raw){
    double ans=stod(raw);
    return ans;
}
void insertString(string& str,string content,int startIndex){
    int totalLength=str.size()+content.size();
    string ans="";
    int acnt=0,bcnt=0;
    for (int i=0;i<totalLength;i++){
        if (i<startIndex || i>=startIndex+content.size()){
            ans+=str[acnt];
            acnt++;
        }
        else {
            ans+=content[bcnt];
            bcnt++;
        }
    }
    str=ans;
}
//this function removes the part of string from startIndex to endIndex
void removeSubstring(string& str,int startIndex,int endIndex){
    int oriLength=str.size();
    string ans="";
    for (int i=0;i<oriLength;i++){
        if (!(i>=startIndex && i<=endIndex)){
            ans+=str[i];
        }
    }
    str=ans;
}
//this function takes the substring from a startIndex to endIndex
//the original string is passed as parameter
//note that this is not a member function of the string class
string getSubstring(string& str, int startIndex,int endIndex){
    string ans="";
    for (int i=0;i<str.size();i++){
        if (i>=startIndex && i<=endIndex){
            ans+=str[i];
        }
    }
    return ans;
}
//assuming no invalid inputs
int findMatchBracket(string& formula, int leftIndex){
    int leftCnt=1,rightCnt=0;
    for (int i=leftIndex+1;i<formula.size();i++){
        if (formula[i]=='('){
            leftCnt++;
        }
        else if(formula[i]==')'){
            rightCnt++;
        }
        if (leftCnt==rightCnt){
            return i;
        }
    }
    return -1;
}
//this function removes an element of double from a vector
//the location of the element to remove is indicated by an index of int
void removeDouble(vector<double>& data, int index){
    vector<double> ans;
    for (int i=0;i<data.size();i++){
        if (i!=index){
            ans.push_back(data[i]);
        }
    }
    data=ans;
}
//this function inserts a double into a vector
void insertDouble(vector<double>& data,double value, int index){
    vector<double> ans;
    int cnt=0;
    for(int i=0;i<data.size()+1;i++){
        if (i==index){
            ans.push_back(value);
        }
        else {
            ans.push_back(data[cnt]);
            cnt++;
        }
    }
    data=ans;
}
//The introduction to the whole function
void printMainIntro(){
    cout<<"Packages available:\n   statistics\n   plot\n   arithmetics\n   quit\n"<<endl;
}
//scanning the command into a string
void getCommand(string& cmd){
    cout<<"home@calculator:~$ ";
    cin>>cmd;
    cin.get();
    cout<<flush;
}
