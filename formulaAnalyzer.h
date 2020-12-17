#include <string>
#include <exception>
using namespace std;

#ifndef FORMULAANALYZER_H
#define FORMULAANALYZER_H

double evaluateFormula(string formula);
double handleRawFormula(string formula,double varValue);
double functionSolver(string formula,double est);
double derivative(string formula,double est);
void arithCtrl();
double segmentValue(string segment);

#endif //FORMULAANALYZER_H
