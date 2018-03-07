#include <stdio.h>
#include <inttypes.h>

#define __STDC_FORMAT_MACROS

/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

int main(){

  uint64_t n = 0;
  uint64_t acc = 0;
  uint64_t max = 0;
  uint64_t max_acc = 0;

  uint64_t i;

  for(i = 1; i<1000000; i++){
    n = i;
    acc = 1;
    while(n != 1){
      if(n/2*2 != n){
        n=3*n+1;
      } else{
        n/=2;
      }
      acc++;
    }
    if(acc > max_acc){
      max = i;
      max_acc = acc;
    }
  } printf("%" PRIu64 "-> %" PRIu64 "\n", max, max_acc);
}
