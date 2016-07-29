#include <cmath>
#include <iostream>
#include <string>  
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "energyfinder.h"
int main(){
  /* 
  double I=500.;
  double p=1;
  double xin=0.;
  double thetain=0.;
  double dx=0.001;
  double xout;
  double thetaout;
  double deltaz;
  double zend=2330.;
  
  //fieldmap ends @2320, center of the magnet @ 1160 

    for(int i=0; i<200; i++){
  //  zend=2320.+i*10;
      I=0.5+i*0.5;
  zend=1300+1160.;
 deflection(p,I,zend,thetaout, xout, thetain, xin, dx);
 deltaz=zend-1160;
 std::cout<< "zend= " <<zend <<" deltaz= " <<deltaz<< " xout= "<< xout << " I= "<< I<< " thetaout " << thetaout<< std::endl;
 }*/
  
    energyfinder test(0.1,-0.35,1400);
    std::cout << "test" << std::endl;
    std::cout << "test energyfinder E=" << test.getenergy() << std::endl;

  energyfinder test2(0,-0.45,1400);
    std::cout << "test" << std::endl;
    std::cout << "test energyfinder E=" << test2.getenergy() << "+" << test2.geterrplus(0.01,0.1)<< "-" << test2.geterrminus(0.01,0.1)<<  std::endl;


 return(0);



}
