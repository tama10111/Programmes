#include <stdio.h>
#include <stdlib.h>

/*

  (a x 10² + b x 10¹ + c)
x (d x 10² + e x 10¹ + f)

= ad x 10⁴ + (ae + bd) x 10³ + (af + be + cd) x 10² + (bf + ce) x 10¹ + cf

Condition : ad == cf && (ae+bd) == (af+be+cd)

*/

int main(){

  int n;
  int len6[6];
  int i = 0;

  for(int a = 100; a<1000; a++){
    for(int b = 100; b<1000; b++){
      n = a*b;

      if(n > 100000){

        i = 0;

        for(int c = 100000; c>0; c/=10){
          len6[i] = n/c;
          n -= len6[i]*c;
          i++;
        }

        if(len6[0] == len6[5] && len6[1] == len6[4] && len6[2] == len6[3]){
          for(i = 0; i<6; i++){
            printf("%i", len6[i]);
          }
          printf("\n");
        }
      }
    }
  }


  return 0;
}
