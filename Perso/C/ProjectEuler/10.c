#include <stdio.h>
#include <string.h>

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

int powi(int a, int b){

  int acc = 1;

  for(int i = 0; i<b; i++){
    acc*=a;
  }

  return acc;
}

int main(int argc, char * argv[]){

  int n = 0;
  int m = 0;
  int i;

  for(i = 0; i<strlen(argv[1]); i++){
    n += ((argv[1][i]-48)*powi(10,strlen(argv[1])-1-i));
  }

  for(i = 0; i<strlen(argv[2]); i++){
    m += ((argv[2][i]-48)*powi(10,strlen(argv[2])-1-i));
  }

  int acc = 0;
  double sum = 0.;


  while(n < m){
    for(i=2; i<n; i++){
      if(!(n%i)){
        acc++;
        break;
      }
    }
    if(!acc){
      sum+= (double) n;
    }
    n+=2;
    acc = 0;
  }
  printf("%lf\n", sum);
}
