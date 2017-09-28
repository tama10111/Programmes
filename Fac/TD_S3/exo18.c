#include <stdio.h>
#include <stdlib.h>


int alea(int n){
  return rand()%n;
}

typedef struct Tab{
  int tab[200];
  int taille;
} Tab;

Tab * init_tab(){
  Tab * ret = malloc(sizeof(Tab));
  ret->taille = 100;
  for(int i = 0; i<ret->taille; i++){
    ret->tab[i] = alea(20);
  }

  return ret;
}

void print_tab(Tab * tab){


  for(int i = 1; i<tab->taille+1; i++){
    printf("%i ", tab->tab[i-1]);
  }

  printf("\n\n");
}

int get_tab_product(Tab * tab){
  int acc = 1;

  for(int i = 0; i<tab->taille; i++){
    acc*=tab->tab[i];
  }

  return acc;

}

int get_tab_min(Tab * tab){
  int min = tab->tab[0];

  for(int i = 1; i<tab->taille; i++){
    if(tab->tab[i] < min){
      min = tab->tab[i];
    }
  }
  return min;
}

void decalage_droite(Tab * tab, int deb){
  tab->taille++;

  for(int i = tab->taille; i > deb; i--){
    tab->tab[i] = tab->tab[i-1];
  }

  tab->tab[deb] = 0;

}

void decalage_gauche(Tab * tab, int del_index){

  for(int i = del_index; i < tab->taille-1; i++){
    tab->tab[i] = tab->tab[i+1];
  }
  tab->taille--;
}

void permut(Tab * tab, int a, int b){

  int mem = tab->tab[a];
  tab->tab[a] = tab->tab[b];
  tab->tab[b] = mem;
}

void sort_tab(Tab * tab){

  int max;
  int indice;
  int borne = tab->taille;

  for(int i = 0; i<tab->taille; i++){
    max = -1;
    for(int j = 0; j<borne; j++){
      if(tab->tab[j] >= max){
        max = tab->tab[j];
        indice = j;
      }
    }
    permut(tab, indice, borne);
    borne--;
  }
}

void insert(Tab * tab, int val){
  for(int i = 0; i<tab->taille; i++){
    if(tab->tab[i] > val){
      decalage_droite(tab, i-1);
      tab->tab[i-1] = val;
      break;
    }
  }
}

void random_delete(Tab * tab){
  int index = alea(tab->taille);
  decalage_gauche(tab, index);
}

int invert(Tab * tab){

  int acc = 0;

  for(int i = 0; i<tab->taille/2; i++){
    permut(tab, i, tab->taille-i-1);
    acc++;
  }
  return acc;
}

int tri_selection(Tab * tab){

  int min;
  int indice;
  int acc = 0;

  for(int i = 0; i<tab->taille; i++){
    min = tab->tab[i];
    for(int j = i; j<tab->taille; j++){
      if(tab->tab[j] <= min){
        min = tab->tab[j];
        indice = j;
      }
    }
    permut(tab, i, indice);
    acc++;
  }
  return acc;
}

int tri_insertion(Tab * tab){

  int ptr_tab;
  int acc = 0;

  for(int i = 1; i<tab->taille; i++){
    ptr_tab = i;
    while( (tab->tab[ptr_tab] < tab->tab[ptr_tab-1]) && (ptr_tab > 0)){
      permut(tab, ptr_tab, ptr_tab-1);
      acc++;
      ptr_tab--;
    }
  }
}

int tri_bulle(Tab * tab){

  int ptr_tab;
  int acc = 0;

  for(int i = 0; i<tab->taille; i++){
    ptr_tab = i;
    for(int j = i; j<tab->taille; j++){
      if(tab->tab[j] < tab->tab[i]){
        permut(tab, i, j);
        acc++;
      }
    }
  }
}

void delete_doublon_after_sorting(Tab * tab){

  int ptr_tab = 0;
  int acc = 0;
  int mem = tab->taille-1;

  while(ptr_tab < tab->taille && acc+ptr_tab < mem){
    while(tab->tab[ptr_tab] == tab->tab[ptr_tab+1] && acc+ptr_tab < mem){
      decalage_gauche(tab, ptr_tab);
      acc++;
    }
    ptr_tab++;
  }
}

int main(){
  Tab * tableau = init_tab();

  printf("%i\n", tri_selection(tableau));
  print_tab(tableau);
  delete_doublon_after_sorting(tableau);
  print_tab(tableau);
}
