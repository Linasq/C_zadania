#include <stdio.h>
#include <math.h>

//	function 'taylor' calculates the value of cos(x) using Taylor expansion
//	cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ... + (-1)^(k) x^(2k) / (2k)! + ...
double taylor(double x) {
	long k = 1;
//	eps is the requested precision; experiment with different values and see the results
	double f = 1, s = 0, eps = 1e-10;
	while(fabs(f) > eps) {	//	add until terms become sufficiently small
		s += f;
		f *= x*x/(k*(k+1));	//	next term (the previous one multiplied by x^2 / (k*(k+1))
		f = -f;	//	every term has opposite sign to the previous one
		k += 2;
	}
	return s;
}

int main(void) {
	double a, b, step;
	printf("\n");
	printf("a = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	if(a > b) {
		double temp = a;
		a = b;
		b = temp;
	}
	do {
		printf("step = ");
		scanf("%lf", &step);
	} while(step <= 0);
	printf("\n");
	printf("       x       ");
	printf("     cos(x)    ");
	printf("     taylor(x) ");
	printf("\n");
	for(int i = 0; i < 45; ++i) printf("-");
	printf("\n");
	for(double x = a; x < b; x += step) {
		printf("%15.8f%15.8f%15.8f\n", x, cos(x), taylor(x));
	}
//	print the value at 'b';
	printf("%15.8f%15.8f%15.8f\n", b, cos(b), taylor(b));
	for(int i = 0; i < 45; ++i) printf("-");
	printf("\n");
	printf("\n");
	return 0;
}

