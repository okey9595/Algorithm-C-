//골드5 [인구 이동] https://www.acmicpc.net/problem/16234
//1시간 20분 완성 -> 최적화는 어설프게 하지 말기, 2021.09.30

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

void dfs(vector<vector<int>>&visit,int cnt,int x,int y) { //cnt는 다시 체크를 통해 이동을 하기 위해 
	visit[x][y] = cnt;
	sum += MAP[x][y];
	countBlock++;

	for (int c = 0; c < 4; c++) {
		int nx = dx[c] + x;
		int ny = dy[c] + y;
		if (nx <0 || nx>=N || ny <0 || ny>=N)  //범위를 나갔을때,
			continue;
		int tmp = abs(MAP[x][y] - MAP[nx][ny]);
		if (tmp >= L && tmp <= R) {
			if (visit[nx][ny] == 0) {
				dfs(visit, cnt, nx, ny);	//visit를 표시하면서 연합 형성(&를 사용하여 visit 썼을 때, checkall,dfs 에서의 값이 동일한가 확인하기)
			}
		}
	}
}

void moveHuman(vector<vector<int>>visit,int x,int y,int cnt,int human) {  //다시 체크를 처음부터 하는게 아니고 visit한 것들을 queue로 설정하여 인구 이동했다면 더 빨랐을 것
	for (int i = x; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == x)
				if (j < y)
					continue;
			if (visit[i][j] == cnt)    //이부분 탐색 시간 줄일 수 있음 
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
					if (nx < 0 || nx >= N || ny < 0 || ny >= N)  //범위를 나갔을때,
						continue;
					int tmp = abs(MAP[i][j] - MAP[nx][ny]);
					if (tmp >= L && tmp <= R) {
						if (visit[nx][ny] == 0) {
							visit[i][j] = cnt;
							dfs(visit, cnt, nx, ny);	//visit를 표시하면서 연합 형성(&를 사용하여 visit 썼을 때, checkall,dfs 에서의 값이 동일한가 확인하기)
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
	for (int i = 0; i < N; i++) { //초기화
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