#include <stdio.h>
#include <stdlib.h>
int main(){
	int a, b, c, n;
	a = 1;
	b = -1;
	n = 1;
	double error = 1;
	double prevVal = 1.0*b/a;
	while (error > 1e-6){
		c = b;
		b = a + c;
		a = c;
		double newVal = 1.0*b/a;
		error = abs(newVal - prevVal);
		prevVal = newVal;
		n ++;
	}
	printf("phi=%f, n=%i",prevVal, n);
	return 0;
}
