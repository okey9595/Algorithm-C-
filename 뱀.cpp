//���5[��] https://www.acmicpc.net/problem/3190
//2021.09.17 , 2:15�� �ɸ�
//�������� ������ ���� ���ذ� �������� 

#include <iostream>
#include <deque>
using namespace std;

int sec = 0; // �� �ð�
int BOARD[100][100] = { 0 }; //���� , ����� 1�� ǥ��, ���� 2�� ǥ��
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
deque<int>turndirec;  //1�̸� ������, 0�̸� ����
int play(int X,char C,int x, int y) {
	int newx,newy;
	newx = x; newy = y;
	for (int i = 1; i <=X; i++) {
		newx += dx[direc];
		newy += dy[direc];
		if (newx<0 || newx>N - 1 || newy<0 || newy>N - 1) { //���� ���� �ε�����
			quitprogrem = 1;
			return i;
		}
		if (BOARD[newx][newy] == 2) { //�쿡 �ε�����
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
		else { //����� ������ ��
			BOARD[newx][newy] = 2;
		}
		
	}
	if (C == 'L') {  //���� �ٲٱ�
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
	stX = 0; stY = 0; //ó�� ������
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

