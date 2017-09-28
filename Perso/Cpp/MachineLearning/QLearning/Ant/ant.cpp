//##############################
//# 			TODO
//# 
//# Implémenter turn_Left/Right
//# Implémenter better_Q (inutile)
//#
//##############################
//# 			NOTE
//# Action : HAUT BAS GAUCHE DROITE


#include <iostream>

#define XMAX 200
#define YMAX 200

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
	void check(Mine mine, Base base);
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

void Ant::check(Mine mine, Base base){

	if (this->x == mine.x && this->y == mine.y && this->carry == 0){
		this->carry = 1;
		mine.quantity -= 1;
	}

	if (this->x == base.x && this->y == base.y && this->carry == 1){
		this->carry = 0;
		base.quantity += 1;
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

int main(){

	Mine mine;
	mine.set(5,5,1000);

	Base base;
	base.set(XMAX-5, YMAX-5, 0);

	Ant ant;

	cout << sizeof(ant.mem_Area) << endl;

	ant.set_mem_Area(mine.x, mine.y, base.x, base.y);
	ant.set(XMAX/2-10, YMAX/2-10, 0, 0.09, 0.9999999);

	int n = 0;

	int max_it = 10000000;


	while(n<max_it){

		ant.set_Q();
		ant.move(n);
		ant.check(mine, base);
		if(mine.quantity == 0){
			mine.x = rand()%XMAX;
			mine.y = rand()%YMAX;
			mine.quantity = 1000;
		}

		n++;
	}
	cout << "Fitness : " << ant.fitness << endl;
	return 0;
}
