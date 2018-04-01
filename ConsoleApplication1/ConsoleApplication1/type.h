#include <graphics.h>

struct point {
	int x;
	int y;
}; 

struct gathers{
	point points[10000];
	int length;
};

struct all{
	gathers gatherss[10000];
	int length;
};

#define LEFT 100
#define RIGHT 500
#define TOP 100
#define BUTTOM 500

int standard;

void drawMap(int n) {
	standard = 400 / (n - 1);
	for (int i = 0; i < n; i++) {
		line(LEFT + i * standard, TOP, LEFT + i * standard, BUTTOM);
		line(LEFT, TOP + i * standard, RIGHT, TOP + i * standard);
	}
}

void drawPath(gathers points) {
	for (int i = 0; i < points.length; i++) {
		//circle(location.x * 20, location.y * 20, 8);
		setfillcolor(0xFFFFFF);
		fillcircle(100 + points.points[i].x * standard, 100 + points.points[i].y * standard, standard / 2 - 2);
	}
}
