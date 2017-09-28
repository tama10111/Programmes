#include <stdio.h>
#include <stdlib.h>

double abso(double n){
  if(n<0.){return -n;}
  return n;
}

double racine(int m, int lim){

  int n;

  if(m <= lim){
    n=m+racine(m+1, lim);
  } else{
    n = m;
  }

  double e = 0.1;
  double sqrt_n;

  double a = 1.;
  double b = n;
  double c;

  while(abso(n-c) > e){
    sqrt_n = (a+b)/2.;
    c = (sqrt_n*sqrt_n);
    if(c > n){
      b = sqrt_n;
    }

    else if(c < n){
      a = sqrt_n;
    }

    else{
      return c;
    }
  }

  return c;
}

double suite(int n){

  return racine(1, n);

}

int main(){

  printf("Valeur : %lf\n", suite(10));

}
