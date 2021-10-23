// 마법사상어와 파이어스톰, https://www.acmicpc.net/problem/20058
// 1시간 7분 걸림

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int N, Q,sizeOfMap =1;
vector<vector<int>>MAP;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
vector<pair<int, int>>eraseMapInfo;
int SUM = 0;
int MAXChunk = 0;

void changeMap(int r, int endR, int c, int endC,int sizeOfL) {
	//cout << r << "\t" << endR << '\t' << c << '\t' << endC << '\n';
	vector<vector<int>>tmp;
	tmp.assign(sizeOfL, vector<int>(sizeOfL, 0));
	for (int i = r; i < endR+1; i++) {
		//vector<int>v;
		for (int j = c; j < endC+1; j++) {
			//v.push_back(MAP[i][j]);
			tmp[j-c][sizeOfL-i+r-1] = MAP[i][j];
		}
	}
	for (int i = r; i < endR + 1; i++) {
		for (int j = c; j < endC + 1; j++) {
			MAP[i][j] = tmp[i - r][j - c];
		}
	}
}

void divideMap(int sizeOfL) {
	for (int i = 0; i < sizeOfMap; i++) {
		int endPointR = i + sizeOfL - 1;
		for (int j = 0; j < sizeOfMap; j++) {
			int endPointC = j + sizeOfL - 1;
			changeMap(i, endPointR, j, endPointC,sizeOfL);
			j = endPointC;
		}
		i = endPointR;
	}
}
void show() {
	for (int i = 0; i < sizeOfMap; i++) {
		for (int j = 0; j < sizeOfMap; j++) {
			cout << MAP[i][j] << '\t';
		}
		cout << '\n';
	}
}
void checkAndCal(int x,int y) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx<0 || nx > sizeOfMap - 1 || ny<0 || ny > sizeOfMap - 1)
			continue;
		if (MAP[nx][ny] != 0)
			cnt++;
	}
	if (cnt < 3) {
		eraseMapInfo.push_back({ x,y });
	}
}

void checkFreeze() {
	for (int i = 0; i < sizeOfMap; i++) {
		for (int j = 0; j < sizeOfMap; j++) {
			checkAndCal(i,j);
		}
	}
	for (int i = 0; i < eraseMapInfo.size(); i++) {
		if(MAP[eraseMapInfo[i].first][eraseMapInfo[i].second] != 0)
			MAP[eraseMapInfo[i].first][eraseMapInfo[i].second]--;
	}
	eraseMapInfo.clear();
}

void bfs() {
	vector<vector<int>>visit;
	visit.assign(sizeOfMap, vector<int>(sizeOfMap, 0));
	for (int i = 0; i < sizeOfMap; i++) {
		for (int j = 0; j < sizeOfMap; j++) {
			if (visit[i][j] == 0 && MAP[i][j]!=0) {
				/*if (i == 0 && j == 2)
					cout << 'a';*/
				queue <pair<int, int>> q;
				q.push({ i,j });
				visit[i][j] = 1;
				int cnt = 0;
				while (!q.empty()) {
					pair<int, int> p = q.front();
					SUM += MAP[p.first][p.second];
					cnt++;
					q.pop();
					for (int d = 0; d < 4; d++) {
						int nx = p.first + dx[d];
						int ny = p.second + dy[d];
						if (nx<0 || nx > sizeOfMap - 1 || ny<0 || ny > sizeOfMap - 1)
							continue;
						if (MAP[nx][ny] != 0 && visit[nx][ny] ==0) {
							visit[nx][ny] = 1;
							//cnt++;
							q.push({ nx,ny });
						}
					}
				}
				MAXChunk = max(MAXChunk, cnt);
			}
		}
	}

}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		sizeOfMap *= 2;
	}
	
	MAP.assign(sizeOfMap, vector<int>(sizeOfMap, 0));

	for (int i = 0; i < sizeOfMap; i++) {
		for (int j = 0; j < sizeOfMap; j++) {
			int tmp;
			cin >> tmp;
			MAP[i][j] = tmp;
		}
	}
	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;
		int sizeOfL =1;
		for (int j = 0; j < L; j++) {
			sizeOfL *= 2;
		}
		//cout << sizeOfL;
		divideMap(sizeOfL);
		checkFreeze();	
	}
	//show();
	bfs();
	cout << SUM<<'\n'<<MAXChunk;

}