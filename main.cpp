#include <stdio.h>
#include <iostream>
#include <string>
#include "basic.h"
#include "statistics.h"
#include "IOhandler.h"
#include "formulaAnalyzer.h"
#include "lib.h"
using namespace std;
int main(){
    printMainIntro();
    while(1){
        string cmd="";
        getCommand(cmd);
        if (cmd=="statistics"){
            statControl();
        }
        if (cmd=="arithmetics"){
            arithCtrl();
        }
        if (cmd=="plot"){
            plotCtrl();
        }
        else if (cmd=="quit"){
            printf("--------Program terminated--------\n");
            break;
        }
    }
    return 0;
}