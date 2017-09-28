#include <stdio.h>
#include <stdlib.h>

int main(){

	unsigned long int n = 9356773073709551616;

	unsigned long int d = 2;

	while(n > 1){
		while(n%d){
			d++;
		}
		n /= d;
		printf("%i ", d);
		d = 2;
	}
}
