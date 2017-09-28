#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int acc = 0;
	
	for(int i = 0; i<1000; i++){
			if( !(i%5) || !(i%3) ){
				acc+=i;
			}
	}
	
	printf("%i\n", acc);
}
