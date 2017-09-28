#include <stdio.h>

double abso(double n){
  if(n<0.){return -n;}
  return n;
}

int main(){
  double e;
  double n;
  double sqrt_n;
  printf(">>> ");
  scanf("%lf %lf", &n, &e);

  double a = 1.;
  double b = n;
  double c;
  int i = 0;

  while(abso(n-c) > e){
    sqrt_n = (a+b)/2.;
    c = (sqrt_n*sqrt_n);
    printf("%lf|--------\t%lf\t--------|%lf\t%lf\n", a,sqrt_n,b,c);
    if(c > n){
      b = sqrt_n;
    }

    else if(c < n){
      a = sqrt_n;
    }

    else{
      printf("YAAAAAAAAAAAAAAAH\n");
      break;
    }
  }

  printf("%lf\n", sqrt_n);

}
