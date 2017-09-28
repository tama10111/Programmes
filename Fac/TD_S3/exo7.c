#include <stdio.h>
#include <math.h>

int main(){

  double sn = 0.;
  double sn1 = 0.;
  double e;
  double i = 1.;
  printf("Précision :\n>>> ");
  scanf("%lf", &e);

  do{
    sn = sn1;
    sn1+=1./(i*i);
    i++;
  }while(sn1-sn<e);

  printf("Limite : %lf\n", sn1);
}
