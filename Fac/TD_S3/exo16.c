#include <stdio.h>

int is_in(int * t, int n){

  for(int i = 0; i<100; i++){ if(t[i] == n) return 1; }
  return 0;
}

int main(){

  int * t = malloc(100*sizeof(int));
  int ptr_val = 0;
  int * val = malloc(100*sizeof(int)):

  for(int i = 0; i<100; i++){t[i] = rand(100);}
    t[i] = rand(254)+1;
  }

  for(int i = 0; i<100; i++){
    if(is_in(val, t[i])){;}
    else{val[ptr_val] = t[i]; ptr_val++;}
  }
