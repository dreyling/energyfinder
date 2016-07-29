#include <cmath>
#include <iostream>
#include <string>  
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"

class energyfinder{


 public:

  energyfinder(double theta1, double theta2, double IBRM);
  double getenergy();
  double geterrplus(double errin, double errout);
  double geterrminus(double errin, double errout);

 private:
 void  deflection();
 double  evalB(int n, double z);
 void bMap(double I, double *bcurr, double *zcoord); 
 double I;
 double pGeV;
 double xin;
 double thetain;
 double dx;
 double xout;
 double thetaout;
 double zend;
 double theta;
 double dp;
 double bfield[117];
 double zcoord[117];

};

  
