//##############################
//# 			TODO
//# 
//# Implémenter turn_Left/Right
//# Implémenter better_Q (inutile)
//#
//##############################
//# 			NOTE
//# Action : HAUT BAS GAUCHE DROITE


#include <SDL/SDL.h>
#include <iostream>
#include <math.h>

#define XMAX 80
#define YMAX 80

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

	double fitness;
	double curiosity;

	double learning_rate;
	double gamma;

	double actions[8][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {1,1,0,0}, {1,0,0,1}, {0,1,1,0}, {0,0,1,1}};

	double better_action[4]; 

	Area mem_Area[XMAX][YMAX][2];

	void set_mem_Area(int bx, int by, int mx, int my);
	Area predict_Area(double action[4]);
	int impossible_action(double action[4]);
	void better_move();
	void move(int n);
	void check(Mine * mine, Base * base);
	void set_Q();
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

Area Ant::predict_Area(double action[4]){

	int x = this->x-action[1]+action[3];
	int y = this->y-action[0]+action[2];

	if(impossible_action(action)){
		return this->mem_Area[int(this->x)][int(this->y)][int(this->carry)];
	}

	else{
		return this->mem_Area[x][y][int(this->carry)];
	}
}

void Ant::better_move(){

	double maxi = -99999999;

	for(int n = 0; n<8; n++){

		if(this->predict_Area(this->actions[n]).Q + this->predict_Area(this->actions[n]).reward > maxi && !impossible_action(actions[n])){

			maxi = this->predict_Area(this->actions[n]).Q + this->predict_Area(this->actions[n]).reward;

			for(int m = 0; m<4; m++){

				this->better_action[m] = this->actions[n][m];

			}
		}
	}

}

void Ant::check(Mine * mine, Base * base){

	if (this->x == (*mine).x && this->y == (*mine).y && this->carry == 0){
		this->carry = 1;
		(*mine).quantity -= 1;
	}

	if (this->x == (*base).x && this->y == (*base).y && this->carry == 1){
		this->carry = 0;
		(*base).quantity += 1;
		this->fitness += 1;
	}

}

void Ant::move(int n){

	this->x += -this->better_action[1] + this->better_action[3];
	this->y += -this->better_action[0] + this->better_action[2];

	this->mem_Area[int(this->x)][int(this->y)][int(this->carry)].frequency +=1;

}

void Ant::set_Q(){

	this->better_move();

	Area better_area = this->predict_Area(this->better_action);

	this->mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q += this->learning_rate * (better_area.reward + this->gamma * better_area.Q - this->mem_Area[int(this->x)][int(this->y)][int(this->carry)].Q);
}

void Ant::set_mem_Area(int mx, int my, int bx, int by){

	for(int x = 0; x < XMAX; x++){
		for(int y = 0; y < YMAX; y++){
			for(int i = 0; i<2; i++){
				this->mem_Area[x][y][i].Q = 0;
				this->mem_Area[x][y][i].frequency = 0;
				this->mem_Area[x][y][i].reward = -0.01;
			}
		}
	}

	this->mem_Area[mx][my][0].reward = 10;
	this->mem_Area[mx][my][1].reward = -10;
	this->mem_Area[bx][by][0].reward = -10;
	this->mem_Area[bx][by][1].reward = 10;

	this->mem_Area[int(this->x)][int(this->y)][int(this->carry)].frequency = 1;
}

void Ant::set(double x, double y, double curiosity, double learning_rate, double gamma){

	this->x = x;
	this->y = y;
	this->curiosity = curiosity;
	this->learning_rate = learning_rate;
	this->gamma = gamma;
	this->fitness = 0;

}

class Window {

	public :

	SDL_Surface * win = SDL_SetVideoMode(XMAX*10,YMAX*10,32,SDL_HWSURFACE);

	Uint32 * get_pixel(double x, double y);
	void draw_point(double x, double y,Uint32 color);
	void refresh();
	Uint32 MapRGBA(int r, int g, int b, int a);
	void draw_circle(int r, double x, double y, Uint32 color);
	void draw_rect(int x1, int y1, int x2, int y2, Uint32 color);
	void quit();

};

void Window::draw_circle(int r, double x, double y, Uint32 color){

	double root, proot;
	x = int(x);
	y = int(y);

	for(double dx = 0; dx<=r; dx++){

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

int main(){

	Window window;
	Uint32 red   = window.MapRGBA(255,0,0,0);
	Uint32 green = window.MapRGBA(0,255,0,0);
	Uint32 blue  = window.MapRGBA(0,0,255,0);
	Uint32 black = window.MapRGBA(0,0,0,0);

	Mine mine;
	mine.set(5,5,10000);

	Base base;
	base.set(XMAX-5, YMAX-5, 0);

	Ant ant;

	ant.set_mem_Area(mine.x, mine.y, base.x, base.y);
	ant.set(rand()%XMAX, rand()%YMAX, 50, 0.09, 0.9999999);

	int n = 0;
	int max_it = 100000000;

	double coef = 0;

	if(n){SDL_Init(SDL_INIT_VIDEO);}

	while(n < max_it){


		if(n){
			window.draw_circle(4, 10*(ant.x)+5, 10*(ant.y)+5, black);
			window.draw_circle(4, 10*(mine.x)+5, 10*(mine.y)+5, black);
			window.draw_circle(4, 10*(base.x)+5, 10*(base.y)+5, black);

			for(int x = 0; x<XMAX; x++){
				for(int y = 0; y<YMAX; y++){
					coef = ant.mem_Area[int(x)][int(y)][int(ant.carry)].Q;

					if(coef <= 0){
						window.draw_rect(10*x, 10*y, 10*x+10, 10*y+10, window.MapRGBA(int(-coef) < 255 ? int(-coef) : 255,0,0,0));
					}

					else {
						window.draw_rect(10*x, 10*y, 10*x+10, 10*y+10, window.MapRGBA(0,int(coef) < 255 ? int(coef) : 255,0,0));
					}
				}
			}
		}

		ant.set_Q();
		ant.move(n);
		ant.check(&mine, &base);

		if(mine.quantity == 0){
			ant.mem_Area[int(mine.x)][int(mine.y)][0].reward = -0.01;
			ant.mem_Area[int(mine.x)][int(mine.y)][1].reward = -0.01;
			mine.set(rand()%XMAX,rand()%YMAX,10000);
		}


		if(n){
			window.draw_circle(4, 10*(ant.x)+5, 10*(ant.y)+5, red);
			window.draw_circle(4, 10*(mine.x)+5, 10*(mine.y)+5, blue);
			window.draw_circle(4, 10*(base.x)+5, 10*(base.y)+5, green);
			window.refresh();
		}

		n++;

	}

	cout << ant.fitness;

	getchar();
	SDL_Quit();

	return 0;
}