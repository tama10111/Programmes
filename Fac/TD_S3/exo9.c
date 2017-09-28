#include <stdio.h>

int test(int n, int m){
  int sum = 0;
  int acc = 0;

  for(int i = 1; i<n; i++){
    if(n/i*i == n){
      sum+=i;
    }
  }

  if(sum == n){acc++;}
  sum = 0;

  for(int i = 1; i<m; i++){
    if(m/i*i == m){
      sum+=i;
    }
  }

  if(sum == m){acc++;}

  return acc;

}

int main(){
  int nmin, nmax;

  printf(">>> ");
  scanf("%i %i", &nmin, &nmax);

  for(int n = nmin; n<=nmax; n++){
    for(int m = nmin; m<=nmax; m++){
      if(test(n,m) == 2){
        printf("(%i,%i)\n", n,m);
      }
    }
  }
}
