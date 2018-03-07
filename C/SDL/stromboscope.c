#include <SDL/SDL.h>
#include <math.h>
#include <time.h>

#define TAU 2*M_PI

struct Circle{
	double x;
	double y;
	double r;
}; typedef struct Circle Circle;

Uint16 * get_pixel(SDL_Surface * w, int x, int y){
	return w->pixels + y*w->pitch + x*2;
}

float rad(float a){return TAU*(a/360.0);}

void draw_c(SDL_Surface * w, Circle c, Uint32 color){

	double root, proot;

	for(double dx = 0; dx<=c.r; dx++){

		root = sqrt(c.r*c.r-dx*dx);

		for(int i = -root; i<=root; i++){
			*(get_pixel(w, c.x+dx, c.y+i)) = color;
			*(get_pixel(w, c.x-dx, c.y+i)) = color;
		}
	}
}

int main(){
	SDL_Surface * win;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_SetVideoMode(800,800,16,SDL_HWSURFACE);

	int RAYON = 50;

    Circle c1, c2, c3, c4;
    c1.r = RAYON; c2.r = RAYON; c3.r = RAYON; c4.r = RAYON;

    float a1, a2, a3, a4;
    a1 = TAU/4.0;
    a2 = TAU/2.0;
    a3 = TAU*3.0/4.0;
    a4 = TAU;

    int i = 0; int ii = 160;

    float sin[360];
    float cos[360];

    Uint32 rouge = SDL_MapRGBA(win->format, 255,0,0,0);
    Uint32 noir = SDL_MapRGBA(win->format, 0,0,0,0);

    for(int i = 0; i<360; i++){
    	sin[i] = sinf(rad(i));
    	cos[i] = cosf(rad(i));
    }

    while(1){

    	i++; ii++;

    	if(i == 360){i=0;}
    	if(ii == 360){ii=0;}

    	//c1.x = 400+100*cosf(a1+rad(i)); c1.y = 400+100*sinf(a1+rad(i)); draw_c(win, c1, SDL_MapRGBA(win->format, 0,0,255,0));
    	c2.x = 400+100*cos[i]; c2.y = 400+100*sin[i]; draw_c(win, c2, rouge);
    	//c3.x = 400+100*cosf(a3+rad(i)); c3.y = 400+100*sinf(a3+rad(i)); draw_c(win, c3, SDL_MapRGBA(win->format, 0,0,255,0));
    	c4.x = 400+100*cos[ii]; c4.y = 400+100*sin[ii]; draw_c(win, c4, rouge);

    	SDL_Flip(win);

    //draw_c(win, c1, SDL_MapRGBA(win->format, 0,0,0,0));
		draw_c(win, c2, noir);
		//draw_c(win, c3, SDL_MapRGBA(win->format, 0,0,0,0));
		draw_c(win, c4, noir);
    }
}
