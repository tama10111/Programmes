#include <stdio.h>

/*

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a2 + b2 = c2
For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.

*/

int is_pythagorean(int a, int b, int c){
  if((a*a + b*b) == c*c){
    return 1;
  } else{
    return 0;
  }
}

int main(){
  int a;
  int b;
  int c;

  for(a = 0; a<1000; a++){
    for(b = 0; b<1000; b++){
      for(c = 0; c<1000; c++){
        if(is_pythagorean(a,b,c) && a+b+c == 1000){
          printf("%i² + %i² = %i²\na x b x c = %i\n",a,b,c,a*b*c);
        }
      }
    }
  }
}
