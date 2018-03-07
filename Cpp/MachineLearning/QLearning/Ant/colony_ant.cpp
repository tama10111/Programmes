//##############################
//# 			TODO
//#
//# Optimiser
//#
//#
//##############################
//# 			NOTE
//# Action : HAUT BAS GAUCHE DROITE
//# learning_rate = -1 <=> fourmis morte


#include <SDL/SDL.h>
#include <iostream>
#include <math.h>

#define XMAX 	180
#define YMAX 	100
#define N_ANT	2000
#define N_BASE 	10
#define N_MINE 	20
#define SCALE	10

using namespace std;

class Mine {

	public : double x; double y; double quantity;

	void set(double x, double y, double quantity) {

		this->x = x;
		this->y = y;
		this->quantity = quantity;

	}

};

class Base {

	public : double x; double y; double quantity;

	void set(double x, double y, double quantity) {

		this->x = x;
		this->y = y;
		this->quantity = quantity;

	}

};



class Area {

	public :

	double Q = 0;
	double frequency = 0;
	double reward = -0.01;

};

class Ant {

	public :

	double x;
	double y;
	double carry;

	double energy;
	double resistance;

	double fitness;
	double curiosity;

	double learning_rate;
	double gamma;

	double actions[8][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {1,1,0,0}, {1,0,0,1}, {0,1,1,0}, {0,0,1,1}};

	double better_action[4];

	Area predict_Area(double action[4], Area mem_Area[XMAX][YMAX][2]);
	int impossible_action(double action[4]);
	void better_move(Area mem_Area[XMAX][YMAX][2]);
	void move();
	void check_mine(Mine * mine);
	void check_base(Base * base);
	void set_Q(Area mem_Area[XMAX][YMAX][2]);
	void set(double x, double y, double curiosity, double learning_rate, double gamma);

};

int Ant::impossible_action(double action[4]){

	double x = this->x-action[1]+action[3];
	double y = this->y-action[0]+action[2];

	if(x >= XMAX || x < 0 || y >= YMAX || y < 0){
		return 1;
	}

	else{
		return 0;
	}
}

Area Ant::predict_Area(double action[4], Area mem_Area[XMAX][YMAX][2]){

	int x = this->x-action[1]+action[3];
	int y = this->y-action[0]+action[2];

	if(impossible_action(action)){
		return mem_Area[int(this->x)][int(this->y)][int(this->carry)];
	}

	else{
		return mem_Area[x][y][int(this->carry)];
	}
}

void Ant::better_move(Area mem_Area[XMAX][YMAX][2]){

	double maxi = -99999999;
	double Q; double r;
	int com = 0;

	for(int n = 0; n<8; n++){

		Q = this->predict_Area(this->actions[n], mem_Area).Q;
		r = this->predict_Area(this->actions[n], mem_Area).reward;

		if(n && Q+r != predict_Area(this->actions[n-1], mem_Area).Q + predict_Area(this->actions[n-1], mem_Area).reward){
			com++;
		}

		if(Q + r > maxi && !impossible_action(actions[n])){

			maxi = Q + r;

			for(int m = 0; m<4; m++){

				this->better_action[m] = this->actions[n][m];

			}
		}

		if(com < 2){
			int a = rand()%8;
			while(this->impossible_action(this->actions[a])) a = rand()%8;
			for(int m = 0; m<4; m++){
				this->better_action[m] = this->actions[a][m];
			}
		}
	}
}

void Ant::check_mine(Mine * mine){

	if (this->x == (*mine).x && this->y == (*mine).y && this->carry == 0){
		this->carry = 1;
		(*mine).quantity -= 1;
	}
}

void Ant::check_base(Base * base){

	if (this->x == (*base).x && this->y == (*base).y && this->carry == 1){
		this->carry = 0;
		(*base).quantity += 1;
		this->fitness += 1;
	}

}

void Ant::move(){

	this->x += -this->better_action[1] + this->better_action[3];
	this->y += -this->better_action[0] + this->better_action[2];

}

void Ant::set_Q(Area mem_Area[XMAX][YMAX][2]){

	this->better_move(mem_Area);

	Area better_area = this->predict_Area(this->better_action, mem_Area);

	mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q += this->learning_rate * (better_area.reward + this->gamma * better_area.Q - mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q);
//	cout << mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q << endl;
//	cout << " " << this->x << " " << this->y << " " << this->carry << " " << mem_Area << endl;

	if(mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q < 0){
		mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q+=0.0001;
	}

	else if(mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q > 0){
		mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q-=0.0001;
	}
}

void Ant::set(double x, double y, double curiosity, double learning_rate, double gamma){

	this->x = x;
	this->y = y;
	this->curiosity = curiosity;
	this->learning_rate = learning_rate;
	this->gamma = gamma;
	this->fitness = 0;
	this->energy = 100;
	this->resistance = rand()%20+1;

}

class Window {

	public :

	SDL_Surface * win = SDL_SetVideoMode(XMAX*SCALE,YMAX*SCALE,32,SDL_HWSURFACE);

	Uint32 * get_pixel(double x, double y);
	void draw_point(double x, double y,Uint32 color);
	void refresh();
	Uint32 MapRGBA(int r, int g, int b, int a);
	void draw_circle(int r, double x, double y, Uint32 color);
	void draw_rect(int x1, int y1, int x2, int y2, Uint32 color);
	void quit();

};

void Window::draw_circle(int r, double x, double y, Uint32 color){

	double root;
	x = int(x);
	y = int(y);

	for(int dx = 0; dx<=r; dx++){

		root = sqrt(r*r-dx*dx);

		for(int i = -root; i<=root; i++){
			*(get_pixel(x+dx, y+i)) = color;
			*(get_pixel(x-dx, y+i)) = color;
		}
	}
}

void Window::draw_rect(int x1, int y1, int x2, int y2, Uint32 color){

	for(int x = x1; x < x2; x++){
		for(int y = y1; y < y2; y++){
			*(get_pixel(x,y)) = color;
		}
	}
}

Uint32 * Window::get_pixel(double x, double y){

	return (Uint32*)(this->win->pixels + ( int(y) * this->win->pitch + int(x)*sizeof(Uint32) ));
}

void Window::refresh(){
	SDL_Flip(this->win);
}

Uint32 Window::MapRGBA(int r, int g, int b, int a){
	return SDL_MapRGBA(this->win->format, r,g,b,a);
}

int is_on_base(Base base[N_BASE], Ant ant){
	for(int i = 0; i<N_BASE; i++){
		if(ant.x == base[i].x && ant.y == base[i].y){
			return i+1;
		}
	}

	return 0;
}

int main(){

	Window window;
	Uint32 red   = window.MapRGBA(255,0,0,0);
	Uint32 green = window.MapRGBA(0,255,0,0);
	Uint32 blue  = window.MapRGBA(0,0,255,0);
	Uint32 black = window.MapRGBA(0,0,0,0);

	Area mem_Area[XMAX][YMAX][2];

	Mine mine[N_MINE];
	for(int i = 0; i<N_MINE; i++){mine[i].set(rand()%XMAX,rand()%YMAX,5000);}

	Base base[N_BASE];
	for(int i = 0; i<N_BASE; i++){base[i].set(XMAX*(i+1)/(N_BASE+1), YMAX-5, 0);}

	Ant ant[N_ANT];
	for(int i = 0; i<N_ANT; i++){ant[i].set(rand()%XMAX, rand()%YMAX, 50, 0.09, 0.9999999);}


	for(int x = 0; x < XMAX; x++){
		for(int y = 0; y < YMAX; y++){
			for(int i = 0; i<2; i++){
				mem_Area[x][y][i].Q = 0;
				mem_Area[x][y][i].frequency = 0;
				mem_Area[x][y][i].reward = -0.01;
			}
		}
	}

	for(int i = 0; i<N_MINE; i++){mem_Area[int(mine[i].x)][int(mine[i].y)][1].reward = -1; mem_Area[int(mine[i].x)][int(mine[i].y)][0].reward =  1;}
	for(int i = 0; i<N_BASE; i++){mem_Area[int(base[i].x)][int(base[i].y)][1].reward = 1; mem_Area[int(base[i].x)][int(base[i].y)][0].reward =  -1;}

	int n = 0;
	int max_it = 100000000;
	int coef;
	int index;

	SDL_Init(SDL_INIT_VIDEO)

	while(n<max_it){

		if(n){
			for(int i = 0; i<N_ANT; i++){	if(ant[i].learning_rate != -1){window.draw_circle(2, SCALE*(ant[i].x)+SCALE/2, SCALE*(ant[i].y)+SCALE/2, black);}}
			for(int i = 0; i<N_MINE; i++){	window.draw_circle(4, SCALE*(mine[i].x)+SCALE/2, SCALE*(mine[i].y)+SCALE/2, black);}
			for(int i = 0; i<N_BASE; i++){	window.draw_circle(4, SCALE*(base[i].x)+SCALE/2, SCALE*(base[i].y)+SCALE/2, black);}
		}

		for(int i = 0; i<N_ANT; i++){

			if(ant[i].learning_rate != -1){

				ant[i].set_Q(mem_Area);
				ant[i].move();

				for(int ii = 0; ii<N_MINE; ii++){
					ant[i].check_mine(&mine[ii]);
				}

				for(int ii = 0; ii<N_BASE; ii++){
					ant[i].check_base(&base[ii]);
				}

				ant[i].energy -= 0.001;

				if(ant[i].energy <= 0){
					cout << "Adieu A" << i << " :'(" << endl;
					window.draw_circle(2, SCALE*(ant[i].x)+SCALE/2, SCALE*(ant[i].y)+SCALE/2, black);
					ant[i] = ant[N_ANT-1];
					ant[N_ANT-1].learning_rate = -1;

				}

				else if(ant[i].energy < ant[i].resistance){

					index = is_on_base(base, ant[i]);

					if(index){
						while(ant[i].energy <= 99 && base[i].quantity > 0){
							ant[i].energy += 1;
							base[i].quantity -= 1;
						}
					}

					else if(ant[i].carry){
						ant[i].carry = 0;
						ant[i].energy += 1;
					}
				}
			}
		}

		for(int i = 0; i<N_MINE; i++){
			if(mine[i].quantity <= 0){
				mem_Area[int(mine[i].x)][int(mine[i].y)][0].reward = -0.01;
				mem_Area[int(mine[i].x)][int(mine[i].y)][1].reward = -0.01;
				mine[i].set(rand()%XMAX,rand()%YMAX,1000);
			}
		}

		if(n){
			for(int i = 0; i<N_ANT; i++){	if(ant[i].learning_rate != -1){window.draw_circle(2, SCALE*(ant[i].x)+SCALE/2, SCALE*(ant[i].y)+SCALE/2, red);}}
			for(int i = 0; i<N_MINE; i++){	window.draw_circle(4, SCALE*(mine[i].x)+SCALE/2, SCALE*(mine[i].y)+SCALE/2, 0x000001*(int(mine[i].quantity)%256));}
			for(int i = 0; i<N_BASE; i++){	window.draw_circle(4, SCALE*(base[i].x)+SCALE/2, SCALE*(base[i].y)+SCALE/2, 0x000100*(int(base[i].quantity)%256));}
			window.refresh();
		}

		n++;
	}

	getchar();
	SDL_Quit();

	return 0;
}
