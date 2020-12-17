#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include "formulaAnalyzer.h"
#include "lib.h"
#include "IOhandler.h"
using namespace std;

//This function calculates the value of a segment of function that contains only *, /, and ^
//returns the answer for the segment as a double
double segmentValue(string segment){
    vector<double> values;
    //3 for *, 4 for /, 5 for ^
    vector<double> relations={3};
    int valueStartIndex=0;
    for (int i=0;i<segment.size();i++){
        //cut the original string from the characters
        if (segment[i]=='*' || segment[i]=='/' || segment[i]=='^'){
            //get the content of the part
            string context="";
            for (int j=valueStartIndex;j<i;j++){
                context+=segment[j];
            }
            double value=stringToDouble(context);
            values.push_back(value);
            //get the relationship
            if (segment[i]=='*'){
                relations.push_back(3);
            }
            else if (segment[i]=='/'){
                relations.push_back(4);
            }
            else if (segment[i]=='^'){
                relations.push_back(5);
            }
            //record the starting position for the next part
            valueStartIndex=i+1;
        }
        //deal with the last part
        else if (i==segment.size()-1){
            string context="";
            for (int j=valueStartIndex;j<=i;j++){
                context+=segment[j];
            }
            double value=stringToDouble(context);
            values.push_back(value);
        }
    }
    //handle the powers first
    for (int i=0;i<relations.size();i++){
        if (relations[i]-5<0.01 && relations[i]-5>-0.01){
            removeDouble(relations,i);
            double val=pow(values[i-1],values[i]);
            removeDouble(values,i-1);
            removeDouble(values,i-1);
            insertDouble(values,val,i-1);
            i--;
        }
    }
    //in case the sgement is empty
    if (values.size()==0){
        return 0;
    }
    //otherwise, calculate from left to right
    double ans=1;
    for (int i=0;i<relations.size();i++){
        if (relations[i]-3<=0.01 && relations[i]-3>=-0.01){
            ans*=values[i];
        }
        else {
            ans/=values[i];
        }
    }
    return ans;
}
/* The function to handle a formula without brackets and letter-represented variables
 * it cuts things from + and - and evaluate each part using segmentValue function
 */
double evaluateFormula(string formula){
    if (formula.size()==0){
        return 0;
    }
    vector<string> components;
    // 1 for +, 2 for -
    vector<int> relation={1};
    vector<double> values;
    int lastSectionIndex=0;
    //cut the formula from "+"s and "-"s, store the segments into components
    //the relationship between each component is stored using relations
    for (int i=0;i<formula.size();i++){
        //if a operand is found, add what is between it and the lst operand found to the vector
        //this part only deals with + and -
        if ((formula[i]=='+' || formula[i]=='-') && i!=0){
            string context="";
            for (int j=lastSectionIndex;j<i;j++){
                context+=formula[j];
            }
            components.push_back(context);
            if (formula[i]=='+'){
                relation.push_back(1);
            }
            else {
                relation.push_back(2);
            }
            lastSectionIndex=i+1;
            //in case the segment starts with a negative value (e.g.  (-5)^2)
            i++;
        }
        //this part deals with the last component in the formula
        else if (i==formula.size()-1){
            string context="";
            for (int j=lastSectionIndex;j<=i;j++){
                context+=formula[j];
            }
            components.push_back(context);
        }
    }
    //each of these components should contain no +, -, or brackets
    //they are evaluated by segmentValue function
    for (int i=0;i<components.size();i++){
        values.push_back(segmentValue(components[i]));
    }
    //sum up the components and return the answer
    double ans=0;
    for (int i=0;i<values.size();i++){
        if (relation[i]==1){
            ans+=values[i];
        }
        else {
            ans-=values[i];
        }
    }
    return ans;
}
/* The input formula is passed to this function
 * this function gets rid of the brackets and replaces the letter variables with real value
 * Recursively calls itself to handle multiple layers of brackets
 * calls evaluateFormula function for further analysis
 */
double handleRawFormula(string formula,double varValue){
    string stringifiedValue=doubleToString(varValue);
    for (int i=0;i<formula.size();i++){
        //get rid of brackets
        //uses recursion to handle multiple layers of brackets
        if (formula[i]=='('){
            int rightIndex=findMatchBracket(formula,i);
            string subFormula=getSubstring(formula,i+1,rightIndex-1);
            removeSubstring(formula,i,rightIndex);
            insertString(formula,doubleToString(handleRawFormula(subFormula,varValue)),i);
        }
        //replace letter variables with actual values
        if (formula[i]=='x'){
            removeSubstring(formula,i,i);
            insertString(formula,stringifiedValue,i);
        }
    }
    //calculates the actual value of the function
    return evaluateFormula(formula);
}


//this function solves a single-variable arithmetic function
double functionSolver(string formula,double est){
    for (double shift=0;shift<1000;shift+=0.00001){
        double ans=handleRawFormula(formula,est+shift);
        if (ans<0.001 && ans>-0.001){
            return est+shift;
        }
        ans=handleRawFormula(formula,est-shift);
        if (ans<0.001 && ans>-0.001){
            return est-shift;
        }
    }
    throw 1;
}

//This function calculates the derivative of a function at a certain point
double derivative(string formula,double est){
    double yLeft=handleRawFormula(formula,est-0.0001);
    double yRight=handleRawFormula(formula,est+0.0001);
    return (yRight-yLeft)/0.0002;
}

//This function calculates the definite integration of a formula
double integral(string formula,double left,double right){
    double ans=0;
    for (double x=left;x<right;x+=0.0001){
        ans+=0.0001*handleRawFormula(formula,x);
    }
    return ans;
}

//this function plots the derivative of a function
void plotDerivativeFunction(string formula,double leftBound,double rightBound){
    system("touch data.txt");
    ofstream data("data.txt");
    if (data.is_open()){
        double step=(rightBound-leftBound)/10000;
        for (double i=leftBound;i<=rightBound;i+=step){
            data<<i<<"  "<<derivative(formula,i)<<endl;
        }
        gnuPlotData2DCtrl("data.txt");
        system("rm data.txt");
    }
    else {
        throw 1;
    }
}
void plotIntegral(string formula,double leftLimit, double left,double right){
    system("touch data.txt");
    ofstream data("data.txt");
    if (data.is_open()){
        double step=(right-left)/10000;
        double yIndex=integral(formula,leftLimit,left);
        for (double i=left;i<=right;i+=step){
            data<<i<<"  "<<yIndex<<endl;
            yIndex+=step*handleRawFormula(formula,i);
        }
        gnuPlotData2DCtrl("data.txt");
        system("rm data.txt");
    }
    else {
        throw 1;
    }
}

/* This is the controlling function for the arithmetic package
 * it acts as the entrance to this package
 */
void arithCtrl(){
    printf("Command in this package:\n   calculate\n   funcSolv\n   derivative\n   integral\n   plotDerivative\n   plotIntegral\n   quit\n");
    printf("tip: Use ^ to represent powers.\n\n");
    while(1){
        printf("arithmetics@Calculator:~$ ");
        string cmd="";
        cin>>cmd;
        cin.get();
        if (cmd=="calculate"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();
            double ans=handleRawFormula(formula,1);
            cout<<"= "<<ans<<endl;
        }
        else if (cmd=="funcSolv"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();
            cout<<"please give an estimated solution, default to be 0: ";
            double est=0;
            cin>>est;
            cin.get();
            try {
                double ans=functionSolver(formula,est);
                cout<<"Solution x="<<ans<<endl;
            }
            catch (int err){
                cout<<"No solution found in interval [est-1000,est+1000]."<<endl;
            }
        }
        else if (cmd=="derivative"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();
            cout<<"please input the x value, default to be 0: ";
            double est=0;
            cin>>est;
            cin.get();
            double ans=derivative(formula,est);
            cout<<"dy/dx= "<<ans<<" at x="<<est<<endl;
        }
        else if (cmd=="integral"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();
            cout<<"please input the left bound: ";
            double left=0;
            cin>>left;
            cin.get();
            cout<<"please input the right bound: ";
            double right=0;
            cin>>right;
            cin.get();
            double ans=integral(formula,left,right);
            cout<<"The integral of "<<formula<<" from "<<left<<" to "<<right<<" is: "<<ans<<endl;
        }
        else if (cmd=="plotDerivative"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();
            cout<<"please input the left bound: ";
            double left=0;
            cin>>left;
            cin.get();
            cout<<"please input the right bound: ";
            double right=0;
            cin>>right;
            cin.get();
            cout<<"press ctrl+C for exiting the plot window"<<endl;
            try {
                plotDerivativeFunction(formula,left,right);
            }
            catch (int e){
                cout<<"!ERROR: Unable to generate coordinates file, please check system setting to make sure the current folder is not read-only!"<<endl;
            }
        }
        else if (cmd=="plotIntegral"){
            cout<<"please type the formula: ";
            string formula="";
            cin>>formula;
            cin.get();cout<<"please input the left limit of the integral: ";
            double leftL=0;
            cin>>leftL;
            cin.get();
            cout<<"please input the left bound: ";
            double left=0;
            cin>>left;
            cin.get();
            cout<<"please input the right bound: ";
            double right=0;
            cin>>right;
            cin.get();
            cout<<"press ctrl+C for exiting the plot window"<<endl;
            try {
                plotIntegral(formula,leftL,left,right);
            }
            catch (int e){
                cout<<"!ERROR: Unable to generate coordinates file, please check system setting to make sure the current folder is not read-only!"<<endl;
            }
        }
        else if (cmd=="quit"){
            printf("Leaving package: arithmetics ...\n");
            break;
        }
    }
}
