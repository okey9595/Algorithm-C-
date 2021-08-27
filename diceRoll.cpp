//골드5 [주사위굴리기] https://www.acmicpc.net/problem/14499
//2021.8.27, 1:20 분 걸림

#include <iostream>
#include <vector>
using namespace std;
int N, M, x, y, k;
int MAP[20][20] = { 0 };
int DICE[4][3] = { 0 };
int direcX[5] = {0,0,0,-1,1};  //동 : 1 , 서 : 2, 북 : 3, 남 : 4
int direcY[5] = {0,1,-1,0,0 }; //동 : 1 , 서 : 2, 북 : 3, 남 : 4

int roll(int index,int box,int x ,int y) {
	if (index == 1) {
		int tmp1 = DICE[1][0], tmp2 = DICE[1][1], tmp3 = DICE[1][2], tmp4 = DICE[3][1];
		DICE[1][0] = tmp2; DICE[1][1] = tmp3; DICE[1][2] = tmp4; DICE[3][1] = tmp1;
		
	}
	else if (index == 2) {
		int tmp1 = DICE[1][0], tmp2 = DICE[1][1], tmp3 = DICE[1][2], tmp4 = DICE[3][1];
		DICE[1][0] = tmp4; DICE[1][1] = tmp1; DICE[1][2] = tmp2; DICE[3][1] = tmp3;
	}

	else if (index == 3) {
		int tmp1 = DICE[0][1], tmp2 = DICE[1][1], tmp3 = DICE[2][1], tmp4 = DICE[3][1];
		DICE[0][1] = tmp4; DICE[1][1] = tmp1; DICE[2][1] = tmp2; DICE[3][1] = tmp3;
	}

	else {
		int tmp1 = DICE[0][1], tmp2 = DICE[1][1], tmp3 = DICE[2][1], tmp4 = DICE[3][1];
		DICE[0][1] = tmp2; DICE[1][1] = tmp3; DICE[2][1] = tmp4; DICE[3][1] = tmp1;
	}
	
	if (box == 0) {
		MAP[x][y] = DICE[1][1];
	}
	else
		DICE[1][1] = MAP[x][y];
	return DICE[3][1];
	
}

int main() {
	cin >> N >> M >> x >> y >> k;
	vector <int> order,re;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		int tmp;
		cin >> tmp;
		order.push_back(tmp);
	}
	int locX = x;
	int locY = y;
	for (int i = 0; i < k; i++) {
		locX += direcX[order[i]];
		locY += direcY[order[i]];
		if (locX >= N || locY >= M || locX < 0 || locY < 0) {
			locX -= direcX[order[i]];
			locY -= direcY[order[i]];
			continue;
		}
		int box = 0;  //칸이 0인지 아닌지 여부 
		if (MAP[locX][locY] != 0)
			box = 1;

		cout << roll(order[i],box,locX,locY)<<'\n';
		

	}


}
