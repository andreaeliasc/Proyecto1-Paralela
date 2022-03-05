/******************************************************************************
Authors:
Andrea Elias 17048
Sara Zavala 18893
Diego Estrada 18540

References:
-> Carnahan, B., Luther, H. A., &amp; Wilkes, J. O. (1969). Applied Numerical Methods. Wiley.

-> Trobec, R., Slivnik, B., Bulić, P., & Robič, B. (2018). Introduction to parallel computing: 
from algorithms to programming on state-of-the-art platforms. Springer.

*******************************************************************************/

#include<iomanip>
#include<iostream>
#include<cmath>
#include<stdlib.h>

int main(){


// Declaring constants
int  nx;
int  ntau;
double dx;  
double dtau; 
double TMAX; 
double L;  
double lambda;
int i, j;

// Defining constants
dx = 0.05;  
dtau = 0.001; 
TMAX = 0.95; 
L = 1.00;  
lambda = dtau/pow(dx,2);
nx = L/dx+1;
ntau = TMAX/dtau+1;



// Creating the matrix

double u[ntau][nx];  

// Initializing the matrix with zeros

for(i=0; i < nx; i++){
for(j=0; j < ntau; j++){
	 u[j][i] = 0.0;
}}

for(i=0; i < nx; i++){
	u[0][i] = 0.0; //sin(M_PI*i*dx/L);// 0.5;
}

for(j=1; j < ntau; j++){
u[j][0] = 1.0; //100
u[j][nx-1] = 1.0; //100
}

// In this part we use the equation proposed in the book
for(j=0; j < ntau-1; j++){
for(i=1; i < nx-1; i++){
		 u[j+1][i] = lambda*u[j][i-1] + (1-2*lambda)*u[j][i] + lambda*u[j][i+1]; // Equation
} } 

	
char const* m[ntau][nx];

// Print matrix
for(j=0; j < ntau; j++){
for(i=0; i < nx; i++){
	std::cout << u[j][i] << " ";
} } 
 
return 0;

}