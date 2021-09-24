//골드4 [사다리조작] https://www.acmicpc.net/problem/15684
//2021.09.24 , 1시간 30분 

#include <iostream>
#include <vector>
using namespace std;
int N, M, H;
int MIN = 3;
vector < vector<int>>map(H, vector<int>(N, 0));
int MAP[31][11] = { 0 };

int check() {

	for (int i = 1; i < N + 1; i++) {
		int x = 1, y = i;
		int visit[31][11] = { 0 };
		while (x != H+1) {
			if (visit[x][y] == 0) {
				if (MAP[x][y] == 1) {
					y++;
					visit[x][y] = 1;
				}
				else if (MAP[x][y] == 2) {
					y--;
					visit[x][y] = 1;
				}
				else {
					x++;
				}
			}
			else {
				x++;
			}
		}
		if (y != i)
			return 1;
	}
	return 0;
}

void recrusive(int ladderNUM) { //이거는 처음만 해결
	for (int i = 1; i < H+1; i++) {
		for (int j = 1; j < N; j++) {
			if (MAP[i][j] == 0 && MAP[i][j+1]==0 ) {   
				MAP[i][j] = 1; MAP[i][j + 1] = 2;
				//체크하기 
				if (check() == 0) {
					MIN = 1;
					break;
				}
				MAP[i][j] = 0; MAP[i][j + 1] = 0;
			}
		}
	}
}

int recrusive2(int ladderNum, int x, int y, int cnt) {   // return 값이 0이면 해결됐다는 의미로 종료 
	if (cnt == 0) {
		if (check() == 0) {
			MIN = ladderNum;
			return 0;
		}
		return 1;
	}
	int j = y;
	for (int i = x; i < H+1; i++) {
		while (j < N) {                  //뒤에 원하는 x,y 값부터 시작하기 위해서 for문 대신 while문으로 하게 되면 조금 더 깔끔하게 가능 
			if (MAP[i][j] == 0 && MAP[i][j + 1] == 0) {
				MAP[i][j] = 1; MAP[i][j + 1] = 2;
				//체크하기 
				int test = recrusive2(ladderNum, i, j, cnt - 1);
				if (test == 0)
					return 0;
				MAP[i][j] = 0; MAP[i][j + 1] = 0;
			}
			j++;
		}
		j = 1;
	}

	return 1;

}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		MAP[a][b] = 1; MAP[a][b + 1] = 2;
	}

	if (check() == 0) {
		cout << 0 << endl;
		return 0;
	}
	int tt = 1;
	recrusive(1);
	if (MIN == 1) {
		cout << 1 << endl;
		return 0;
	}
	if (recrusive2(2, 1, 1, 2) == 0) {
		cout << 2 << endl;
		return 0;
	}
	if (recrusive2(3, 1, 1, 3) == 0) {
		cout << 3 << endl;
		return 0;
	}
	cout << -1 << endl;
}
