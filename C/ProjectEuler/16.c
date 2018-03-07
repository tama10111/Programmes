#include <stdio.h>
#define LEN 1000

/*
2¹⁵ = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2¹⁰⁰⁰?
*/

void format(int tab[LEN]){

  int ret = 0;
  int i = 0;

  for(i = LEN-1; i != 0; i--){
    tab[i] += ret;
    ret = (tab[i]-tab[i]%10)/10;
    tab[i] %= 10;
  }
}

int main(){

  int tab[LEN];
  int i = 0;
  int n = 0;
  int sum = 0;

  for(i = 0; i<LEN; i++){
    tab[i] = 0;
  }

  tab[LEN-1] = 1;

  for(i = 0; i<1000; i++){
    for(int j = LEN-1; j != 0; j--){
      tab[j] *=2;
    }
    format(tab);
  }

  i = 0;

  while(tab[i] == 0){
    i++; n++;
  }

  for(i = n; i<LEN; i++){
    printf("%i", tab[i]);
    sum+=tab[i];
  }

  printf("\n%i\n", sum);

}
