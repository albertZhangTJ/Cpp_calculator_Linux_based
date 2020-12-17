#include <iostream>
#include <fstream>
#include <string>
#include "IOhandler.h"
//these plot functions would only work under GUI
//would not work otherwise due to fail in initializing graphing windows of GNUplot
using namespace std;

//The control function to plot 3D data file
bool gnuPlotData3DCtrl(string dataFileName){
    ofstream out("ctrl.txt");
    if (out.is_open()){
        out<<"set hidden3d;"<<endl;
        out<<"set contour;"<<endl;
        out<<"splot \""<<dataFileName<<"\";"<<endl;
        out<<"pause(100)"<<endl;
        system("gnuplot ctrl.txt");
        system("rm ctrl.txt");
        return true;
    }
    return false;
}
//The control function for plotting 3D function
bool gnuPlotFunction3DCtrl(string function){
    ofstream out("ctrl.txt");
    if(out.is_open()){
        out<<"set hidden3d;"<<endl;
        out<<"set contour;"<<endl;
        out<<"splot "<<function<<";"<<endl;
        out<<"pause(100)"<<endl;
        system("gnuplot ctrl.txt");
        return true;
    }
    return false;
}
//The control for plotting 2D datafiles
bool gnuPlotData2DCtrl(string dataFileName){
    ofstream out("ctrl.txt");
    if (out.is_open()){
        out<<"plot \""<<dataFileName<<"\";"<<endl;
        out<<"pause(100)"<<endl;
        system("gnuplot ctrl.txt");
        return true;
    }
    return false;
}
//The control function for plotting 2D function
bool gnuPlotFunction2DCtrl(string function){
    ofstream out("ctrl.txt");
    if(out.is_open()){
        out<<"plot "<<function<<";"<<endl;
        out<<"pause(100)"<<endl;
        system("gnuplot ctrl.txt");
        return true;
    }
    return false;
}
void plotCtrl(){
    printf("Be advised: this package only works on a computer with GNUplot installed and supports GUI!\n");
    printf("Command in this package:\n   2Ddata\n   3Ddata\n   2Dfunction\n   3Dfunction\n");
    printf("tip: Use ** to represent powers.\n\n");
    while(1){
        printf("plot@Calculator:~$ ");
        string cmd="";
        cin>>cmd;
        cin.get();
        if (cmd=="2Ddata"){
            string file="";
            cout<<"Please input data file name: ";
            cin>>file;
            cin.get();
            printf("Press ctrl+C to continue.\n");
            gnuPlotData2DCtrl(file);
        }
        else if (cmd=="3Ddata"){
            string file="";
            cout<<"Please input data file name: ";
            cin>>file;
            cin.get();
            printf("Press ctrl+C to continue.\n");
            gnuPlotData3DCtrl(file);
        }
        else if (cmd=="2Dfunction"){
            string function="";
            cout<<"Please input function: ";
            cin>>function;
            cin.get();
            printf("Press ctrl+C to continue.\n");
            gnuPlotFunction2DCtrl(function);
        }
        else if (cmd=="3Dfunction"){
            string function="";
            cout<<"Please input function: ";
            cin>>function;
            cin.get();
            printf("Press ctrl+C to continue.\n");
            gnuPlotFunction3DCtrl(function);
        }
        else if (cmd=="quit"){
            printf("Leaving package: plot ...\n");
            system("rm ctrl.txt");
            break;
        }
    }
}
