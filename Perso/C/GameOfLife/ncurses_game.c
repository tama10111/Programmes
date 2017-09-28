#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

int XMAX, YMAX;

void fill_map(int * T){

	for(int a = 0; a<XMAX*YMAX; a++){
		T[a] = 0;
	}
}

void refresh_map(WINDOW * w, int * T){

	for(int x = 0; x<XMAX; x++){
		for(int y = 0; y<YMAX; y++){
			attron(COLOR_PAIR(T[XMAX*y+x]));
			mvwaddch(w, y, x, ' ');
			attroff(COLOR_PAIR(T[XMAX*y+x]));
		}
	}

	refresh();
}

void one(int * T, int x, int y){
	T[XMAX*y+x] = 1;
}

void vessel_tr(int * T, int x, int y){
	one(T,x+1,y);
	one(T,x+2,y+1);
	one(T,x+1,y+1);
	one(T,x,y+2);
	one(T,x+2,y+2);
}

void generate_map(int * T){
;
}

void random_map(int * T){

	FILE * f = fopen("/dev/urandom", "r");
	char * ptr;

	for(int i = 0; i<(XMAX*YMAX)/20; i++){
		fread(ptr, 1, 2, f);
		vessel_tr(T, (*ptr)%(XMAX-10), (*(ptr+1))%(YMAX-10));
	}
}

int set_state(int x, int y, int * T){

	int accu = 0;
	int a,b;

	for(a = -1; a<=1; a++){
		for(b = -1; b<=1; b++){
			if(T[XMAX*(y+b)+(x+a)] == 1){
				if(!(a==0 && b==0) && ((y+b)<YMAX) && ((y+b)>=0) && ((x+a)<XMAX) && ((x+a)>=0)){
					accu++;
				}
			}
		}
	}

	if((accu == 2 && T[XMAX*y+x]) || accu == 3){
		return 1;
	}

	else{
		return 0;
	}
}

void copy(int * A, int * B){

	for(int i = 0; i<XMAX*YMAX; i++){
		B[i] = A[i];
	}
}

void caution(int * T){
	int y = YMAX-1;
	attron(COLOR_PAIR(32));
	for(int x = XMAX/4; x<(3*XMAX)/4; x++){
		T[XMAX*(YMAX-1)+x] = 1;
		T[XMAX*y+x] = 1;
		if(x < XMAX/2){y--;}
		if(x > XMAX/2){y++;}
	}
	attroff(COLOR_PAIR(0));
}
int main(){

	WINDOW * win = initscr();
	start_color();

	getmaxyx(win, YMAX, XMAX);

	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_WHITE);

	int * T = malloc(sizeof(int)*XMAX*YMAX);
	int * Tmem = malloc(sizeof(int)*XMAX*YMAX);
	int n,m;
	int comut = 1;

	struct timespec * time = malloc(sizeof(struct timespec));
	struct timespec * t = malloc(sizeof(struct timespec));

	time->tv_sec = 0;
	time->tv_nsec = 100000000L;


	fill_map(T);

	random_map(T);

	refresh_map(win,T);

	sleep(1);

	while(comut){

		comut = 0;

		vessel_tr(T,50,50);

		for(n = 0; n<XMAX; n++){

			for(m = 0; m<YMAX; m++){

				Tmem[XMAX*m+n] = set_state(n, m, T);

				if(Tmem[XMAX*m+n] == 1){
					comut = 1;
				}
			}
		}

		copy(Tmem, T);
		refresh_map(win,T);
		nanosleep(time, t);
	}

	endwin();
	exit(0);
}
