#include <stdio.h>

int fibonacci(int a, int b, int limit){
	
	if(a+b >= limit){
		return b;
	}

	int d = a+b;
	
	fibonacci(b,d, limit);
}
	

	
int main(){
	
	fibonacci(1,2,4000000);
	
}
