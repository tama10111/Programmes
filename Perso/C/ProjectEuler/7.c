#include <stdio.h>

int main(){

  long int n_prime = 0;
  long int n = 3;
  long int i;
  long int acc = 0;

  while(n_prime != 10000){
    for(i=2; i<n; i++){
      if(!(n%i)){
        acc++;
      }
    }
    if(!acc){
      n_prime++;
    }
    n+=2;
    acc = 0;
  }
  printf("%li\n", n);
}
