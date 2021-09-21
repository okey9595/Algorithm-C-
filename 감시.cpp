#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//int MAP[8][8];
vector <vector <int>>MAP(8, vector<int>(8,0));
int N, M;
vector<pair<int, int>>CCTV;
int MIN =99999;  //cctv의 개수 
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int check(vector <vector <int>>cctv_map) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (cctv_map[i][j] == 0)
				cnt++;
		}
	}
	return cnt;
}

vector <vector <int>> paint(vector <vector <int>>tmp, int x, int y, int num, int d) { // x,y cctv 위치, num : cctv 번호 , f : cctv방향 
	if (num == 1) {
		for (int i = 0; i <= num - 1; i++) {
			int tmpd = d + i;
			tmpd %= 4;
			int nx = x + dx[tmpd];
			int ny = y + dy[tmpd];
			while (1) {
				if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1)  // 범위 벗어났을때
					break;
				if (tmp[nx][ny] == 6)
					break;
				else if (tmp[nx][ny] >= 1 && tmp[nx][ny] <= 5) {
					nx += dx[tmpd];
					ny += dy[tmpd];
					continue;
				}
				else
					tmp[nx][ny] = 8;
				nx += dx[tmpd];
				ny += dy[tmpd];
			}
		}
	}
	else if(num == 3 || num ==4 || num == 5){
		for (int i = 0; i <num - 1; i++) {
			int tmpd = d + i;
			tmpd %= 4;
			int nx = x + dx[tmpd];
			int ny = y + dy[tmpd];
			while (1) {
				if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1)  // 범위 벗어났을때
					break;
				if (tmp[nx][ny] == 6)
					break;
				else if (tmp[nx][ny] >= 1 && tmp[nx][ny] <= 5) {
					nx += dx[tmpd];
					ny += dy[tmpd];
					continue;
				}
				else
					tmp[nx][ny] = 8;
				nx += dx[tmpd];
				ny += dy[tmpd];
			}
		}
	}
	else {  //cctv 2일때
		for (int i = 0; i <= num; ) {
			int tmpd = d + i;
			tmpd %= 4;
			int nx = x + dx[tmpd];
			int ny = y + dy[tmpd];
			while (1) {
				if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1)  // 범위 벗어났을때
					break;
				if (tmp[nx][ny] == 6)
					break;
				else if (tmp[nx][ny] >= 1 && tmp[nx][ny] <= 5) {
					nx += dx[tmpd];			//이 continue를 하는 과정에서 다음으로 넘어가는 과정 사이에 더해줘야하는 부분을 뺏었음 문제 발생
					ny += dy[tmpd];
					continue;
				}
				else
					tmp[nx][ny] = 8;
				nx += dx[tmpd];
				ny += dy[tmpd];
			}
			i += 2;
		}
	}
	return tmp;
}

void recrusive(vector <vector <int>>cctv_map,int cnt) {
	if (cnt == 0) {
		MIN = min(check(cctv_map), MIN);
		return;
	}
	int cctvX = CCTV[cnt - 1].first;
	int cctvY = CCTV[cnt - 1].second;
	if (cctv_map[cctvX][cctvY] == 1 || cctv_map[cctvX][cctvY] == 3 || cctv_map[cctvX][cctvY] == 4) {  //회전 방향이 4개기 때문
		for (int i = 0; i < 4; i++) {
			vector <vector <int>>tmp(cctv_map);
			tmp = paint(tmp,cctvX, cctvY, cctv_map[cctvX][cctvY], i);

			recrusive(tmp, cnt - 1);
		}
	}
	else if (cctv_map[cctvX][cctvY] == 2) {  //방법이 두가지
		for (int i = 0; i < 2; i++) {
			vector <vector <int>>tmp(cctv_map);
			tmp = paint(tmp, cctvX, cctvY, cctv_map[cctvX][cctvY], i);
			recrusive(tmp, cnt - 1);
		}
	}
	else {
		//그냥 동서남북 다 체크 
		vector <vector <int>>tmp(cctv_map);
		tmp = paint(tmp, cctvX, cctvY, cctv_map[cctvX][cctvY], 0);
		recrusive(tmp, cnt - 1);
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> N >> M;

	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> tmp;
			MAP[i][j] = tmp;
			if (tmp >= 1 && tmp <= 5) {
				CCTV.push_back({ i,j });
			}
		}
	}

	int cnt = CCTV.size();
	if (cnt == 0) {
		int tmp = check(MAP);
		cout << tmp;
		return;
	}
	recrusive(MAP,cnt);
	cout << MIN;

}