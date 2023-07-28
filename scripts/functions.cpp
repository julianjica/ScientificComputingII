// functions.cpp
// Including Math Functions
#include <math.h>
#include <stdio.h>
// declaration
double exponentiation(double a, double b);

// main function, called when the program starts
int main(void){
	double x = 4;
	double y = 0.5;
	double result = exponentiation(x, y);
	printf("%f", result);
	return 0;
}

// function definition
double exponentiation(double a, double b){
	return pow(a,b);
}
