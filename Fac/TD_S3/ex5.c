#include <stdio.h>

int main(){

  int sec;
  printf("Combien de sec ?\n>>> ");
  scanf("%i", &sec);
  printf("%i:%i:%i\n", sec/60/60, (sec/60)%60, sec%60);
}
