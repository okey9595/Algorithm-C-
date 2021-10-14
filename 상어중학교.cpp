#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
int N, M;
vector<vector<int>>MAP;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
//int visit[20][20] = { 0 }; 
vector<vector<int>>visit; //(N, vector<int>(N, 0));
int colorful = 0; // 무지개 블록의 합
vector<int> blockInfo(3,0); // 0: 모든 블록의 합, 1: 일반블록의 합, 2: 무지개 불록의 합
int blockNum = 0; //일반 블록 색의 합
int checkX =-1, checkY=-1; //기준 점의 시작
int SUM = 0;

void dfs(int x,int y,int color,int c) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx <0 || nx>N - 1 || ny<0 || ny>N - 1)
			continue;
		if (visit[nx][ny] == 0) {
			if (MAP[nx][ny] == color) {
				visit[nx][ny] = 1;
				if (c == 0) {
					blockNum++;
					//dfs(nx, ny, color, 0);
				}
				else {
					MAP[nx][ny] = -2;
					//dfs(nx, ny, color, 1);
				}
				dfs(nx, ny, color, c);
			}
			else if (MAP[nx][ny] == 0) {
				visit[nx][ny] = 1;
				if (c == 0) {
					colorful++;
					//dfs(nx, ny, color, 0);
				}
				else
					MAP[nx][ny] = -2;
				dfs(nx, ny, color, c);
			}
		}
	}
}

bool checkBlock() {
	int check = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(visit[i][j]==0)
				if (MAP[i][j] > 0) {
					blockNum++;
					visit[i][j] = 1;
					dfs(i, j,MAP[i][j],0);
					if (blockNum >= 1) {
						if (blockNum + colorful >= 2) {
							check = 1;
							if (blockInfo[0] < blockNum + colorful) {
								checkX = i;
								checkY = j;
								blockInfo[0] = blockNum + colorful;
								blockInfo[1] = blockNum;
								blockInfo[2] = colorful;
							}
							else if (blockInfo[0] == blockNum + colorful) {
								if (colorful >= blockInfo[2]) {
									checkX = i;
									checkY = j;
									blockInfo[0] = blockNum + colorful;
									blockInfo[1] = blockNum;
									blockInfo[2] = colorful;
								}
							}
							colorful = 0;
							blockNum = 0;
						}
					}
					for (int x = 0; x < N; x++) {
						for (int y = 0; y < N; y++) {
							if (visit[x][y] == 1 && MAP[x][y] == 0)
								visit[x][y] = 0;
						}
					}
					colorful = 0;
					blockNum = 0;
				}
		}
	}
	if (check == 1)
		return true;
	else
		return false;
}

void gravity() {
	for (int i = 0; i < N; i++) {
		vector<int>g;
		int index = N-1;
		int last = -1;
		//int c = 0;
		for (int j = 0; j < N; j++) {
			if(MAP[j][i] !=-2)
				g.push_back(MAP[j][i]);
			if (MAP[j][i] == -1) {
				//c = 1;
				index = j;
				if (g.size() != 0) {
					int loc = g.size() - 1;
					for (int t = index; t > last; t--) {
						if (loc == -1) {
							MAP[t][i] = -2;
						}
						else {
							MAP[t][i] = g[loc];
							loc--;
						}
					}
				}
				last = index;
				g.clear();
				index = N - 1;
			}
		}
		if (g.size() != 0) {
			int loc = g.size() - 1;
			for (int t = index; t > last; t--) {
				if (loc == -1) {
					MAP[t][i] = -2;
				}
				else {
					MAP[t][i] = g[loc];
					loc--;
				}
			}
		}
	}
}

void turnMap() {
	vector<vector<int>>tmp(N, vector<int>(N, 0));
	int x = 0, y = 0;
	for (int i = N - 1; i > -1; i--) {
		for (int j = 0; j < N; j++) {
			tmp[x][y] = MAP[j][i];
			y++;
		}
		y = 0;
		x++;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] = tmp[i][j];

		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	MAP.assign(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int tmp;
			cin >> tmp;
			MAP[i][j] = tmp;
			//cout << MAP[i][j]<<'\t';
		}
		//cout << '\n';
	}
	visit.assign(N, vector<int>(N, 0));
	while (checkBlock()) {
		visit.assign(N, vector<int>(N, 0));
		blockNum = 0;
		colorful = 0;
		int color = MAP[checkX][checkY];
		dfs(checkX, checkY, color,1);
		SUM += (blockInfo[0] * blockInfo[0]);
		gravity();
		turnMap();
		gravity();
		blockInfo.assign(3, 0);
		visit.assign(N, vector<int>(N, 0));
	}
	cout << SUM;
	/*if (checkBlock()) {
		visit.assign(N, vector<int>(N, 0));
		int color = MAP[checkX][checkY];
		dfs(checkX, checkY, color, 1);
		gravity();
		SUM += (blockInfo[0] * blockInfo[0]);
		blockInfo.assign(3, 0);
		turnMap();
		gravity();
		visit.assign(N, vector<int>(N, 0));
	}*/
	//cout << SUM;
	

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << MAP[i][j]<<'\t';
		}
		cout << '\n';
	}*/
}
