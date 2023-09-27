/* Program losuje liczbę 0 ≤ X < 100. 
Napisz funkcję, która zgaduje wartość X.
W pętli losujemy n z przedziału [0, 100). 
Jeżeli X = n zgadliśmy X. 
Jeżeli nie, na podstawie wartości X i n ograniczamy przedział, 
z którego losujemy kolejne n.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gen(int a, int b) {
	return (b-a)*drand48()+a;
}

int main(void)
{
	srand48(time(NULL));
	int a = 0;
	int b =100.;
	int x = gen(a, b);
	printf("Liczba do zgadniecia: %d\n",x);

	int n=gen(a, b);
	int ileProb=1;
	while(1==1) {
		printf("Wylosowana: %d, a: %d, b: %d\n", n,a,b);
		if (n==x) {
			printf("Udalo sie zgadnac liczbe: n=%d\n", n);
			break;
		} else {
			ileProb++;
			if (n>x) {
				b=n;
				n=gen(a,b);
			} else {
				a=n;
				n=gen(a,b);
			}
		}
	}
	printf("Zgadlismy po %d prob.\n", ileProb); 
	return 0;
}
