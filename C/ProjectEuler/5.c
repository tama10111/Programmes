#include <stdio.h>
#include <stdlib.h>

/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

int main(){

  int n = 2;
  int acc = 0;
  int comut = 0;
  int i = 0;

  while(!comut){

    acc = 0;

    for(i = 1; i<21; i++){
      if((n/i)*i != n){
        acc++;
      }
    }

    if(!acc){
      comut = 1;
    }

    n++;
  }

  printf("%i\n",n-1);

}
