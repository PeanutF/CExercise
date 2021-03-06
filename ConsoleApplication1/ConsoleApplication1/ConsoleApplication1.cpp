// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include "type.h"
#include <conio.h>

void run(int x ,int y,double &successN, double &successL, double &failN, double &failL, int &count, int &l, bool &flag);

/*typedef struct METHOD
{
	int success;
	int length;
}Method;

//int map[][];
*/
int map[501][501];
int n;
int direction;
int runCount;
all gather;



int main()
{
	scanf_s("%d", &n);
	printf("input run count:\n");
	scanf_s("%d", &runCount);
	printf("\n");
	srand((unsigned)time(NULL));
	int l = 0,count = 0;
	int showCount = 0;
	double successN = 0, successL = 0, failN = 0, failL = 0;
	bool flag = 0;
	while (runCount > 0) {
		run(n / 2, n / 2, successN, successL, failN, failL, count, l, flag);
		runCount--;
		flag = false;
		l = 0;
		//reset the map
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				map[i][j] = 0;
	}
	gather.length = count;
	/*initgraph(800, 600);
	while (getchar()) {		
		cleardevice();
		drawMap(n);
		drawPath(gather.gatherss[showCount]);
		if (showCount == gather.length)
			break;
		showCount++;
		
	}
	closegraph();*/

	printf("逃出概率为%f,成功平均长度为%f，失败平均长度为%f，总平均长度为%f", successN / count, successL / successN, failL / failN, (successL + failL) / count);
	//return 0;
}

void run(int x, int y, double &successN, double &successL, double &failN, double &failL, int &count, int &l, bool &flag) {
	if (flag) return;
	if (map[x][y] == 1) return;
	//printf("%d,%d\n",x, y);
	point newPoint;
	newPoint.x = x;
	newPoint.y = y;
	gather.gatherss[count].points[l] = newPoint;
	l++;
	map[x][y] = 1;

	//if run to the exit
	if (x == n - 1 || x == 0 || y == n - 1 || y == 0) {
		successN++;
		successL += l;
		gather.gatherss[count].length = l;
		count++;
		flag = true;
		//printf("success\n");
	}
	else if (map[x + 1][y] == 1 && map[x][y + 1] == 1 && map[x - 1][y] == 1 && map[x][y - 1] == 1) {
		//fail to run out
		failL += l;
		failN++;
		gather.gatherss[count].length = l;
		count++;
		flag = true;
		//printf("fail\n");
	}
	else {
		//continue to run
		//printf("continue\n");
		while (true) {
			if (flag) break;
			direction = rand() % 4;
			switch (direction)
			{
			case 0:run(x + 1, y, successN, successL, failN, failL, count, l, flag); break;
			case 1:run(x, y + 1, successN, successL, failN, failL, count, l, flag); break;
			case 2:run(x - 1, y, successN, successL, failN, failL, count, l, flag); break;
			default:run(x, y - 1, successN, successL, failN, failL, count, l, flag);
				break;
			}
		}
	}
}



