#include <iwlib.h>
#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*
TODO : Interface graphique, association
*/

typedef struct ListESSID ListESSID;

struct ListESSID{
  char * name;
  int id;
  ListESSID * prev;
  ListESSID * next;
};

int gen_id(char * str){

  int acc = 0;

  for(int i = 0; i<strlen(str); i++){
    acc ^= str[i];
  }

  return acc;
}

ListESSID * add_to_list(ListESSID * list, char * name){
  ListESSID * nw = malloc(sizeof(ListESSID));

  nw->name = malloc(sizeof(char)*strlen(name));
  strcpy(nw->name, name);

  nw->id = gen_id(name);
  nw->prev = list;

  if(list != NULL){
    list->next = nw;
  }

  return nw;

}

void remove_from_list(ListESSID * ptr){
  ptr->prev->next = ptr->next;
  ptr->next->prev = ptr->prev;
  free(ptr);

}

int is_in_list(ListESSID * ptr, int id){
  while(ptr->prev != NULL){
    if(id == ptr->id){
      return 1;
    }
  }
  return 0;
}

void scan(int sock, char * IFACE, int WE_V, wireless_scan_head * header){
	if(iw_scan(sock, IFACE, WE_V, header) == -1){
		endwin();
		perror("Erreur scan ");
	}
}

int count_essid(wireless_scan * addr, ListESSID * list){

	int i = 0;

	while(addr != NULL){

		addr = addr->next;
		i++;
	}

	return i;

}

void refresh_screen(WINDOW * win, int n_essid, char ** T_NAME, int XMAX, int YMAX, int CURRENT_SELECTED){

	for(int i = YMAX/2; i<YMAX/2+n_essid; i++){

		if((i-YMAX/2) == CURRENT_SELECTED){
			attron(COLOR_PAIR(1));
			mvwaddstr(win, i, XMAX/3, *(T_NAME+(i-YMAX/2)));
			attron(COLOR_PAIR(1));
		}

		else{
			attron(COLOR_PAIR(0));
			mvwaddstr(win, i, XMAX/3, *(T_NAME+(i-YMAX/2)));
			attroff(COLOR_PAIR(0));
		}

	}

	refresh();

}

int main(){

	int ig = 0;

	/* Variables pour l'inteface graphique */

	if(ig){
	WINDOW * win;

	win = initscr();
	noecho();

	int XMAX, YMAX;
	int CURRENT_X = 0;
	int CURRENT_Y = 0;
	int CURRENT_SELECTED = 0;
	init_pair(0, COLOR_WHITE, COLOR_GREEN);
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);

	getmaxyx(win,YMAX,XMAX);
	}

	/* Variables pour la gestion du Wifi */

	int sock = iw_sockets_open(); if(sock == -1){perror("Erreur socket");}
	int n_essid;
	int get_key;

	struct wireless_scan_head * header = malloc(sizeof(struct wireless_scan_head));

	char * IFACE = "wlo1";
	ListESSID * list = NULL;

	/* Premier scan */

	scan(sock, IFACE, WE_VERSION, header);
	printf("%i point d'accès scannés\n", n_essid = count_essid(header->result,list));


/* NOTE Refaire cette merde aussi
	while(1){
		refresh_screen(win, n_essid, T_NAME, XMAX, YMAX, CURRENT_SELECTED);
		get_key = wgetch(win);
		if(get_key == KEY_UP && CURRENT_SELECTED > 0){CURRENT_SELECTED-=1;}
		if(get_key == KEdY_DOWN && CURRENT_SELECTED < n_essid){CURRENT_SELECTED+=1;}
	}
*/
}
