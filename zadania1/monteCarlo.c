#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//abs nie dzialal, wiec zadeklarowalem funkcje, ktora zwraca wartosc bezwzgledna
#define ABS(X) (X)>=0 ? (X) : (-X)

//funkjca zwracajaca najwieksza (praktycznie najwieksza, w zaleznosci jak trafi sie a i b)
//wartosc funkcji sin w danym przedziale
double maxSin(double a, double b) {
	double maxSinus = 0.;
	for (double i=a; i<=b; i+=0.5) {
		double sinus = ABS(sin(i)); 
		if (sinus>maxSinus){
			maxSinus=sinus;
		}
	} return maxSinus;
}

//funkcja losujaca punkt (x,y) oraz
//sprawdzajaca czy nalezy on do wykresu funkcji sin(x)
double pointPicker(double a, double b, double h, int n) {
	int k=0;
	for (int i=0; i<n; i++){
		double x = (b-a)*drand48()+a;
		double y = h*drand48();

		double sinus = ABS(sin(x));

		if (y < sinus) k++;
	} return (double) k/n;
}

int main(void)
{
	srand48(time(NULL));

	double a,b=0.; //zakres przedzialu
	int n=0; // ile punktow bierzemy

	printf("Podaj a: ");
	scanf("%lf", &a);
	printf("\n");

	printf("Podaj b: ");
	scanf("%lf", &b);
	printf("\n");

	printf("Podaj n: ");
	scanf("%d", &n);
	printf("\n");

	double h=maxSin(a,b); //najwiekszy y nalezacy do funkcji

	double poleProstokata=h*(b-a); //pole prostokata

	//zmienna ponizej, to k/n z tego monteCarlo
	double k = pointPicker(a,b,h,n); 
	
	printf("Pole funkcji sin w przedziale [%lf : %lf] wynosi: %lf\n",a,b,poleProstokata*k);

	return 0;
}