//골드5[뱀] https://www.acmicpc.net/problem/3190
//2021.09.17 , 2:15분 걸림
//전반적인 문제에 대한 이해가 부족했음 

#include <iostream>
#include <deque>
using namespace std;

int sec = 0; // 총 시간
int BOARD[100][100] = { 0 }; //보드 , 사과는 1로 표현, 뱀은 2로 표현
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int N, K, L;
int direc = 0;
int tailx = 0;
int taily = 0;
int taildirec = 0;
int endX, endY;
int stX, stY;
int quitprogrem = 0;
deque <int>turnX;
deque<int>turnY;
deque<int>turndirec;  //1이면 오른쪽, 0이면 왼쪽
int play(int X,char C,int x, int y) {
	int newx,newy;
	newx = x; newy = y;
	for (int i = 1; i <=X; i++) {
		newx += dx[direc];
		newy += dy[direc];
		if (newx<0 || newx>N - 1 || newy<0 || newy>N - 1) { //뱀이 벽에 부딪히기
			quitprogrem = 1;
			return i;
		}
		if (BOARD[newx][newy] == 2) { //뱀에 부딪히기
			quitprogrem = 1;
			return i;
		}
		else if (BOARD[newx][newy] == 0) {
			BOARD[newx][newy] = 2;
			BOARD[tailx][taily] = 0;
			if (!turnX.empty()) {
				if (tailx == turnX.front() && taily == turnY.front()) {
					if (turndirec.front() == 1)
						taildirec++;
					else {
						taildirec--;
					}
					if (taildirec < 0)
						taildirec += 4;
					if (taildirec > 3)
						taildirec -= 4;
					turndirec.pop_front();
					turnX.pop_front();
					turnY.pop_front();
				}
			}
			tailx += dx[taildirec];
			taily += dy[taildirec];
			
		}
		else { //사과를 만났을 떄
			BOARD[newx][newy] = 2;
		}
		
	}
	if (C == 'L') {  //방향 바꾸기
		direc--;
		turndirec.push_back(0);
	}
	else {
		direc++;
		turndirec.push_back(1);
	}
	turnX.push_back(newx);
	turnY.push_back(newy);

	if (direc < 0)
		direc += 4;
	if (direc > 3)
		direc -= 4;
	endX = newx;
	endY = newy;
	stX = newx;
	stY = newy;
	return X;
}
int main() {
	int x, y;
	freopen("input.txt", "r", stdin);
	cin >> N >> K;
	
	for (int i = 0; i < K; i++) {
		cin >> x>>y;
		BOARD[x-1][y-1] = 1;
	}
	BOARD[0][0] = 2;
	cin >> L;
	int X;
	char C;
	stX = 0; stY = 0; //처음 시작점
	int check = 0;
	for (int i = 0; i <L; i++) {
		cin >> X >> C;
		X -= sec;
		
		int r = play(X, C,stX,stY);
		if (i == 3)
			int a = 1;
		if (quitprogrem ==1) {
			check = 1;
			sec += r;
			break;
		}
		else
			sec += r;	
	}
	/*if (check == 0) {
		if (direc == 0) {
			sec += (N - endY);
		}
		else if (direc == 1) {
			sec += (N - endX);
		}
		else if (direc == 2) {
			sec += (endY + 1);
		}
		else {
			sec += (endX + 1);
		}
	}*/
	if (check == 0) {
		int r = play(100, 'L', stX, stY);
		sec += r;
	}
	cout << sec;

}

