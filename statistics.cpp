#include "statistics.h"
#include "basic.h"
#include <string>
#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
double getProbabilityNorm(double z){
    return exp(-(z*z)/2)/sqrt(2*3.1415926);
}
void normalpdf(){
    cout<<"Input expected value: ";
    double expv=0;
    cin>>expv;
    cin.get();
    cout<<"Input standard deviation: ";
    double sigma=1;
    cin>>sigma;
    cin.get();
    cout<<"Set x value: ";
    double x=0;
    cin>>x;
    cin.get();
    cout<<"Probability: "<<getProbabilityNorm((x-expv)/sigma)<<endl;
}
void normalcdf(){
    cout<<"Input expected value: ";
    double expv=0;
    cin>>expv;
    cin.get();
    cout<<"Input standard deviation: ";
    double sigma=1;
    cin>>sigma;
    cin.get();
    cout<<"Set lower bound: ";
    double lo=-1000;
    cin>>lo;
    cin.get();
    cout<<"Set upper bound: ";
    double up=1000;
    cin>>up;
    cin.get();
    double zlo=(lo-expv)/sigma;
    double zup=(up-expv)/sigma;
    double ans=0;
    double step=0.00001;
    for (double i=zlo;i<zup;i+=step){
        ans+=getProbabilityNorm(i)*step;
    }
    cout<<"Probability: "<<ans<<endl;
}
void binomcdf(){
    cout<<"Set n value: ";
    int n;
    cin>>n;
    cin.get();
    cout<<"Set p value: ";
    double p;
    cin>>p;
    cin.get();
    cout<<"Set x value: ";
    int x;
    cin>>x;
    cin.get();
    double ans=0;
    for (int i=0;i<=x;i++){
        ans+=combination(n,i)*pow(p,i)*pow(1-p,n-i);
    }
    cout<<"Probability: "<<ans<<endl;
}
void binompdf(){
    cout<<"Set n value: ";
    int n;
    cin>>n;
    cin.get();
    cout<<"Set p value: ";
    double p;
    cin>>p;
    cin.get();
    cout<<"Set x value: ";
    int x;
    cin>>x;
    cin.get();
    cout<<"Probability: "<<combination(n,x)*pow(p,x)*pow(1-x,n-x)<<endl;;
}
void statControl(){
    cout<<"Command in this package:\n   binompdf\n   binomcdf\n   normalpdf\n   normalcdf\n   quit\n"<<endl;
    while(1){
        cout<<"stat@calculator:~$ ";
        string cmd="";
        cin>>cmd;
        cin.get();
        if (cmd=="binomcdf"){
            binomcdf();
        }
        else if (cmd=="binompdf"){
            binompdf();
        }
        else if (cmd=="normalcdf"){
            normalcdf();
        }
        else if (cmd=="normalpdf"){
            normalpdf();
        }
        else if (cmd=="quit"){
            printf("Leaving package: statistics ...\n");
            break;
        }
    }
}