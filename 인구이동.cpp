//���5 [�α� �̵�] https://www.acmicpc.net/problem/16234
//1�ð� 20�� �ϼ� -> ����ȭ�� ����� ���� ����, 2021.09.30

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int N, L, R;
int MAP[50][50];
int visit[50][50];
int date = 0;
int dx[4] = { 0,1,0,-1};
int dy[4] = { 1,0 ,-1,0};
int sum = 0;
int countBlock = 1;

void dfs(vector<vector<int>>&visit,int cnt,int x,int y) { //cnt�� �ٽ� üũ�� ���� �̵��� �ϱ� ���� 
	visit[x][y] = cnt;
	sum += MAP[x][y];
	countBlock++;

	for (int c = 0; c < 4; c++) {
		int nx = dx[c] + x;
		int ny = dy[c] + y;
		if (nx <0 || nx>=N || ny <0 || ny>=N)  //������ ��������,
			continue;
		int tmp = abs(MAP[x][y] - MAP[nx][ny]);
		if (tmp >= L && tmp <= R) {
			if (visit[nx][ny] == 0) {
				dfs(visit, cnt, nx, ny);	//visit�� ǥ���ϸ鼭 ���� ����(&�� ����Ͽ� visit ���� ��, checkall,dfs ������ ���� �����Ѱ� Ȯ���ϱ�)
			}
		}
	}
}

void moveHuman(vector<vector<int>>visit,int x,int y,int cnt,int human) {  //�ٽ� üũ�� ó������ �ϴ°� �ƴϰ� visit�� �͵��� queue�� �����Ͽ� �α� �̵��ߴٸ� �� ������ ��
	for (int i = x; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == x)
				if (j < y)
					continue;
			if (visit[i][j] == cnt)    //�̺κ� Ž�� �ð� ���� �� ���� 
				MAP[i][j] = human;
		}
	}
}



int checkAll(vector<vector<int>>visit) {
	int check = 0;
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int checkDfs = 0;
			if (visit[i][j] == 0) {
				for (int c = 0; c < 2; c++) {
					int nx = dx[c] + i;
					int ny = dy[c] + j;
					if (nx < 0 || nx >= N || ny < 0 || ny >= N)  //������ ��������,
						continue;
					int tmp = abs(MAP[i][j] - MAP[nx][ny]);
					if (tmp >= L && tmp <= R) {
						if (visit[nx][ny] == 0) {
							visit[i][j] = cnt;
							dfs(visit, cnt, nx, ny);	//visit�� ǥ���ϸ鼭 ���� ����(&�� ����Ͽ� visit ���� ��, checkall,dfs ������ ���� �����Ѱ� Ȯ���ϱ�)
							check = 1;
							checkDfs = 1;
						}
					}
				}
				if (checkDfs == 1) {
					sum += MAP[i][j];
					int human = sum / countBlock;
					moveHuman(visit, i, j, cnt, human);
					sum = 0;
					countBlock = 1;
					cnt++;
				}
			}
		}
	}
	return check;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> L >> R;
	int tmp;
	for (int i = 0; i < N; i++) { //�ʱ�ȭ
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			MAP[i][j] = tmp;
		}
	}

	while (1) {
		vector<vector<int>>visit(N, vector<int>(N, 0));
		int t = checkAll(visit);
		if (t == 0)
			break;
		date++;
	}
	cout << date << endl;

}