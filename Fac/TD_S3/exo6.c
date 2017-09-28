#include <stdio.h>

int main(){

  int x,y;

  printf(">>> ");
  scanf("%i %i", &x, &y);

  int ret = 0;

  printf("\n%i x %i\n", x, y);

  while(x!=1){
    if(x/2*2 != x){
      ret+=y;
      x-=1;
    } else{
      x/=2;
      y*=2;
    }
    printf("= %i x %i + %i\n", x, y, ret);
  }

  printf("= %i\n", x*y+ret);

}
