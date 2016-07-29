#include <cmath>
#include <iostream>
#include <string>  
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "energyfinder.h"
#include <fstream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////written by Torben Lange/////////////////////////////
//////////////this class is supposed to determine the momentum/////////////////
////////////// of testbeam electrons (or positrons) deflected /////////////////
////////////// in the magnetic of the "Big Red Magnet" in     /////////////////
////////////// test beam area 21, using the inital and the    /////////////////
////////////// deflection angle of the particles.             /////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


energyfinder::energyfinder(double theta1, double theta2, double IBRM): xout(),thetaout(), theta(), bfield({0}), zcoord({0}){
using namespace std;
  I=IBRM;
  pGeV=1;
  xin=0.;
  thetain=theta1;
  dx=0.001;
  zend=2230.;
  theta=theta2;
  dp=0.00001;
}



double energyfinder::getenergy(){
using namespace std;
  double plow=0.5;
  double phigh=7.;
  double thetalow;
  double thetahigh;
  double deltap;
   do{
    pGeV=plow;
    energyfinder::deflection();
    thetalow=thetaout;
    pGeV=phigh;
    energyfinder::deflection();
    thetahigh=thetaout;
    pGeV=(plow+phigh)/2;
    energyfinder::deflection();
    if(theta>=thetalow&&theta<=thetaout){
      phigh=(plow+phigh)/2;
    }
    else{
      plow=(plow+phigh)/2;
    }
    deltap=phigh-plow;
     }while(deltap>=dp);
  return(pGeV);
}
double energyfinder::geterrplus(double errin, double errout){
using namespace std;
  double plow=0.5;
  double phigh=7.;
  double thetalow;
  double thetahigh;
  double deltap;
  double p1;
  double p2;
  double p3;
 do{
    pGeV=plow;
    energyfinder::deflection();
    thetalow=thetaout;
    pGeV=phigh;
    energyfinder::deflection();
    thetahigh=thetaout;
    pGeV=(plow+phigh)/2;
    energyfinder::deflection();
    if((theta+errout)>=thetalow&&(theta+errout)<=thetaout){
      phigh=(plow+phigh)/2;
    }
    else{
      plow=(plow+phigh)/2;
    }
    deltap=phigh-plow;
     }while(deltap>=dp);
 p1=pGeV;
 do{
    pGeV=plow;
    energyfinder::deflection();
    thetalow=thetaout;
    pGeV=phigh;
    energyfinder::deflection();
    thetahigh=thetaout;
    pGeV=(plow+phigh)/2;
    energyfinder::deflection();
    if((theta+errout)>=thetalow&&(theta+errout)<=thetaout){
      phigh=(plow+phigh)/2;
    }
    else{
      plow=(plow+phigh)/2;
    }
    deltap=phigh-plow;
     }while(deltap>=dp);
 p2=pGeV;
 p3=energyfinder::getenergy();
 if(p1>p2){
return(p1-p3);
 }
 else{
return(p2-p3);
 }
}


double energyfinder::geterrminus(double errin, double errout){
using namespace std;
  double plow=0.5;
  double phigh=7.;
  double thetalow;
  double thetahigh;
  double deltap;
  double p1;
  double p2;
  double p3;
 do{
    pGeV=plow;
    energyfinder::deflection();
    thetalow=thetaout;
    pGeV=phigh;
    energyfinder::deflection();
    thetahigh=thetaout;
    pGeV=(plow+phigh)/2;
    energyfinder::deflection();
    if((theta-errout)>=thetalow&&(theta-errout)<=thetaout){
      phigh=(plow+phigh)/2;
    }
    else{
      plow=(plow+phigh)/2;
    }
    deltap=phigh-plow;
     }while(deltap>=dp);
 p1=pGeV;
 do{
    pGeV=plow;
    energyfinder::deflection();
    thetalow=thetaout;
    pGeV=phigh;
    energyfinder::deflection();
    thetahigh=thetaout;
    pGeV=(plow+phigh)/2;
    energyfinder::deflection();
    if((theta-errout)>=thetalow&&(theta-errout)<=thetaout){
      phigh=(plow+phigh)/2;
    }
    else{
      plow=(plow+phigh)/2;
    }
    deltap=phigh-plow;
      }while(deltap>=dp);
 p2=pGeV;
 p3=energyfinder::getenergy();
 if(p1<p2){
return(p3-p1);
 }
 else{
return(p3-p2);
 }
}

void energyfinder::setI(double x){
  I=x;
  return;
}

void energyfinder::setthetain(double x){  
  thetain=x;
  return;
  }

void energyfinder::setthetaout(double x){
  theta=x;
  return;
}

void energyfinder::setdp(double x){
  dp=x;
  return;
}


void energyfinder::setdx(double x){
  dx=x;
  return;
  }


double energyfinder::getdeltax(double z, double E){
  zend=zend+z;
  pGeV=E;
  energyfinder::deflection();
  zend=zend-z;
  return(xout);
  }


//////////////////////////// the following methods are based on some code from Paul Schuetz////////
void  energyfinder::deflection(){
using namespace std;
    const double c=299792458.;
    const double pi=3.14159265359;
    const double q=1.6e-19;
    const double m=510999.;
    
    // get the FieldMap
     const int n=117;
    
     // double bfield[n]={0};
     // double zcoord[n]={0};
    
    
    bMap(I, bfield, zcoord);
    
    
    // Simulate the particles trajectory inside the magnetic field
    
    
    double x1,z1,vx1,vx2,vz1,vz2,vtot;
    
    double dt=dx/c; // equivalent stepsize in s
    double  p=pGeV*1.e9;
    //Get the total velocity
    vtot=p*c/sqrt(pow(m,2)+pow(p,2))*1000.; // Factor 1000: Talking in millimeters
    
    // Calculate vx and vz out of vtot and the incident angle (given in rad)
    vx1=vtot*sin(thetain);
    vz1=vtot*cos(thetain);
    
    double gamma=1./sqrt(1-pow(vtot/1000./c,2));
    
    x1=xin;
    //z1=-1360.+410.; // distance between collimator and magnet: 1360, then subtracting the z coordinate of the FieldMap at which the magnet is starting, approx. 0410
    z1=-10.; // Starting from right before the magnet
    
    
    double kon;
    // Here we go, using the Boris Method (according to http://www.particleincell.com/2011/vxb-rotation/)
    
    int i=0;
    
    // double zend=2330.;
    //while (z1<3928.-950.) {
     while (z1<zend) {
       //  std::cout << p <<" " << z1 << std::endl;
        //usually there would be a minus in front of the evalB, but i choose the field to be the other way round.
       kon=energyfinder::evalB(n,z1)*dt/(2.*gamma*m/pow(c,2));
	// kon=evalB(bfield, zcoord, z1, n)*dt/(2.*gamma*m/pow(c,2));
	//cout << "B field?" << kon << endl;
        vx2=vx1+2.*kon/(1+1.*pow(kon,2))*(-vz1-vx1*kon);
        vz2=vz1+2.*kon/(1+1.*pow(kon,2))*(vx1-vz1*kon);
        
        x1+=vx2*dt;
        z1+=vz2*dt;
	// cout<< z1<<" p= "<< p <<  endl;
        i++;
        
        vx1=vx2;
        vz1=vz2;
        
	// cout << i << endl;
        
        
    }
    
    thetaout=atan(vx1/vz1);
    // cout << thetaout << endl; 
    xout=x1;
    
  
    return;

}

double energyfinder::evalB(int n, double z){
using namespace std;

  int i=0;
    double b;
    double corrfact=1.005;
    
    // B is calculated in the region, where zcoord is defined. Elsewhere it is set to 0
    
    if (z>zcoord[0]){
        
        if (z<=zcoord[n-1]) {
            
            while (zcoord[i]<z && i<n) {
                i++;
            }
            
            // B is approximated assuming linearity between the given values
            b=bfield[i-1]+(z-zcoord[i-1])/(zcoord[i]-zcoord[i-1])*(bfield[i]-bfield[i-1]);
            b*=corrfact;
            
        }else{
            
            b=0;
            
        }
    }else{
        b=0;
    }
    
    // cout << "B=" << b << endl;
    
    return(b);
    
}

void energyfinder::bMap(double I, double *bcurr, double *zcoord){
using namespace std;

 ifstream inp;
    ofstream outp;
    double in1,in2,in3,in4;
    
    
    double bfield[15][117]={0};
    double Iarr[15]={0};
    
    
    // Readout all the FieldMaps
    
    char filename[200];
   
    for (int i=1; i<15; i++) {
      // sprintf(filename, "/Users/Paul/Studium/DESY/EnergyMeasurement/Simulation/md_corr_edit/md365.%02d1.4", i);
       sprintf(filename, "/home/tlange/Documents/Summer_student_Programme/EnergyMeasurement/Simulation/md_corr_edit/md365.%02d1.4", i);
       //  cout << filename << endl;
        inp.open(filename);
        
        char buff[100];
        
        for (int j=0; j<6; j++) {
            inp.getline(buff, 100);
        }
        
        // Read data:
        int icount=0;

        while (inp >> in1 >> in2 >> in3 >> in4) {
            if(i==1)zcoord[icount]=(in1);
            bfield[i][icount]=(in2/10000.);
            icount++;
        }
        
        inp.close();
        
        Iarr[i]=100.*i;
        
    }
    
    // Interpolate the field and write it into bcurr[]
    
    int icount=0;
    
    // B is calculated in the region, where zcoord is defined. Elsewhere it is set to 0
    
    
    bool hitcurr=0;
    
    // Did we hit a measured current?
    for (int i=0; i<15; i++) {
        if (I==Iarr[i]){
            for (int j=0; j<117; j++) {
                bcurr[j]=bfield[i][j];
            }
            hitcurr=1;
        }
        
    }
    
    if (hitcurr==0){
        if (I>Iarr[0]){
        
            if (I<=Iarr[14]) {
            
                while (Iarr[icount]<I && icount<15) {
                    icount++;
                }
            
                // B is approximated assuming linearity between the given currents
            
                for (int j=0; j<117; j++) {
                    bcurr[j]=bfield[icount-1][j]+(I-Iarr[icount-1])/(Iarr[icount]-Iarr[icount-1])*(bfield[icount][j]-bfield[icount-1][j]);
                }
            
            }else{
            
                cout << "Magnetic Field not known for your current current!" << endl;
            
            }
        }else{
            cout << "Magnetic Field not known for your current current!" << endl;
        }
    }
    
    //cout << "Current is between " << Iarr[icount-1] << " and " << Iarr[icount] << endl;
    //  cout << "BField at z=" << zcoord[56] << " is " << bcurr[56] << endl;
    
    return;
    
}

