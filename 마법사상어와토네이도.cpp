//10.22 https://www.acmicpc.net/problem/20057 
//1시간 20분, 더 빨리 풀수 있었는데 dd를 선언하는 과정에서 문제 발생

#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>>MAP;
int N;
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
int ddx[8] = {0,1,1,1,0,-1,-1,-1};
int ddy[8] = {-1,-1,0,1,1,1,0,-1};
int SUM = 0;
bool check(int x, int y) {
	if (x<1 || x>N || y<1 || y>N)
		return false;
	else
		return true;
}
void moveSand(int x, int y, int d) {
	int startd = d * 2; //처음 시작 방향
	//int nx, ny;
	int sand = 0;
	for (int i = 0; i <8; i++) {
		int dd = startd + i;
		if (i == 4)
			continue;
		if (dd > 7)
			dd -= 8;
		int nx = x + ddx[dd];
		int ny = y + ddy[dd];
		
		if (i%2 == 0) {
			int a, b;
			if (i == 0) {
				a = 0; b = 5;
			}
			else  {
				a = 7; b = 2;
			}
			int n1 = MAP[x][y] * a / 100;
			int n2 = MAP[x][y] * b / 100;
			sand += n1;
			sand += n2;
			for (int j = 0; j < 2; j++) {
				if (check(nx, ny)) {
					if (j == 0)
						MAP[nx][ny] += n1;
					else
						MAP[nx][ny] += n2;
				}
				else {
					if (j == 0)
						SUM += n1;
					else
						SUM += n2;
				}
				nx += ddx[dd];
				ny += ddy[dd];
			}
		}
		else {//홀수 
			int a;
			if (i == 1)
				a = 10;
			else if (i == 7)
				a = 10;
			else
				a = 1;
			int n = MAP[x][y] * a / 100;
			sand += n;
			if (check(nx, ny)) {
				MAP[nx][ny] += n;
			}
			else
				SUM += n;
		}
		//dd++;
	}
	sand = MAP[x][y] - sand;
	//dd = d * 2;
	int nnx = x + ddx[startd];
	int nny = y + ddy[startd];
	if (check(nnx, nny)) {
		MAP[nnx][nny] += sand;
	}
	else
		SUM += sand;
	//cout << 'a';
}

void show() {
	cout << SUM<<'\n';
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cout << MAP[i][j] << '\t';
		}
		cout << '\n';
	}
	
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N;
	MAP.assign(N+1, vector<int>(N+1, 0));
	//vector<vector<int>>test;
	//test.assign(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int tmp;
			cin >> tmp;
			MAP[i][j] = tmp;
		}
	}
	int x = N / 2 +1;
	int y = N / 2 + 1;
	int cnt = 1;
	int tt = 1;
	while (x != 1 && y != 1) {
		int repeat;
		for (int i = 0; i < 5; i++) {
			if (i == 0)
				repeat = 1;
			else
				repeat = cnt;
			int d = i;
			if (i == 4)
				d = 0;
			for (int j = 0; j < repeat; j++) {
				//moveSand(i);
				x = x + dx[d];
				y = y + dy[d];
				
				moveSand(x, y, d);
				MAP[x][y] = 0;
				/*if (tt == 1)
					show();*/
				tt++;
			}
			if (i == 1)
				cnt++;
		}
		cnt++;
	}
	cout << SUM;
	
}