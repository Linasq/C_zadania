#include <stdio.h>
#include <string.h>

int main(void)
{	
	char k[256]; //string
	int n; //o ile przesunac

	printf("Podaj ciag znakow: ");
	scanf("%s", k);

	printf("Podaj o ile mamy przesunac litery (max=25)\n");
	scanf("%d", &n);

	for(int i=0; i<strlen(k); i++){
		int asc = k[i];
		if (64<asc && asc<91) {
			asc = ((asc-65+n)%26)+65;
		}
		else if (96<asc && asc<123) {
			asc = ((asc-97+n)%26)+97;
		}
		char charAscii = asc;
		printf("%c", charAscii);
	} printf("\n");

	return 0;
}