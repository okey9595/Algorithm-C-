//상어초등학교 https://www.acmicpc.net/status?user_id=andy618&problem_id=21608&from_mine=1
//약 2시간 , 완벽한 구현

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int MAP[21][21] = { 0 };
int N;
//map<int, vector<int>> like; //선호하는 학생 저장, <번호, 선호하는 학생>
map<int,vector<int>> like;
map<int, pair<int, int>>loc; //저장된 학생의 위치를 x 부터  
int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};
int Blank_for_like = 0; //빈칸의 개수 저장 
int likeBlank = 0; // 좋아하는 사람의 개수
int zeroBlank = 0;
pair<int, int>like_place;    //저장해야할 좋아하는 사람 옆 위치
pair<int, int>pick_place;   // 빈칸 위치 
int CC = 0;

void check(int stu,vector<int> v) { //stu : 좋아하는 학생 ,v: 좋아하는 학생들       학생 주위의 index 세기 위해 
	map<int, pair<int, int>>::iterator it;

	it = loc.find(stu);
	int x = it->second.first;
	int y = it->second.second;
	
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx <1 || nx>N || ny <1 || ny>N)
			continue;
		if (MAP[nx][ny] == 0) { // 빈칸인 걸 찾아야함
			int zerocnt = 0;
			int cnt = 0;  // 좋아하는 사람 몇명인지 카운트 
			CC = 1;

			for (int j = 0; j < 4; j++) {  // 또 다시 주위의 빈칸의 개수 세어야함, 주위에 또 다시 좋아하는 사람 있는지도 파악
				int nnx = nx + dx[j];
				int nny = ny + dy[j];
				if (nnx <1 || nnx>N || nny <1 || nny>N)
					continue;
				if (MAP[nnx][nny] == 0)  //빈칸 개수 채워 놓아야함
					zerocnt++;
				if (MAP[nnx][nny] == v[0] || MAP[nnx][nny] == v[1] || MAP[nnx][nny] == v[2] || MAP[nnx][nny] == v[3])
					cnt++;
			}

			if (likeBlank < cnt) {
				like_place = { nx,ny };
				likeBlank = cnt;
				Blank_for_like = zerocnt;
			}
			else if (likeBlank == cnt) {
				if (zerocnt > Blank_for_like) {
					like_place = { nx,ny };
					Blank_for_like = zerocnt;
				}
				else if(zerocnt == Blank_for_like){
					if (like_place.first > nx)
						like_place = { nx,ny };
					else if (like_place.first == nx) {
						if (like_place.second > ny)
							like_place = { nx,ny };
					}
				}
			}
		}
	}
	
}

void searchBlank() {
	int c = 0;
	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < N+1; j++) {
			if (MAP[i][j] == 0) {
				int cnt = 0;
				if (c == 0) {
					pick_place = { i,j };
					c++;
					for (int d = 0; d < 4; d++) {
						int nx = i + dx[d];
						int ny = j + dy[d];
						if (nx <1 || nx>N || ny <1 || ny>N)
							continue;
						if (MAP[nx][ny] == 0)  //빈칸 개수 채워 놓아야함
							cnt++;
						zeroBlank = cnt;
					}
					continue;					
				}
				//int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int nx = i + dx[d];
					int ny = j + dy[d];
					if (nx <1 || nx>N || ny <1 || ny>N)
						continue;
					if (MAP[nx][ny] == 0)  //빈칸 개수 채워 놓아야함
						cnt++;
				}
				if (cnt > zeroBlank) {
					zeroBlank = cnt;
					pick_place = { i,j };
				}
			}
		}
	}
}
int check_result() {
	int sum = 0;
	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < N + 1; j++) {
			int cnt = 0;
			map<int, vector<int>>::iterator it;
			it = like.find(MAP[i][j]);
			for (int d = 0; d < 4; d++) {
				int nx = i + dx[d];
				int ny = j + dy[d];
				if (nx <1 || nx>N || ny <1 || ny>N)
					continue;
				vector<int> v;
				vector<int>::iterator ii;
				v = it->second;
				ii = find(v.begin(), v.end(), MAP[nx][ny]);
				if (ii != v.end())
					cnt++;
			}
			if (cnt == 4)
				sum += 1000;
			else if (cnt == 3)
				sum += 100;
			else if (cnt == 2)
				sum += 10;
			else if (cnt == 1)
				sum += 1;
		}
	}
	return sum;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> N;
	
	for (int i = 0; i < N*N; i++) {
		int tmp,a,b,c,d;
		cin >> tmp >>a>>b>>c>>d;
		vector<int> v;
		v.push_back(a);
		v.push_back(b);
		v.push_back(c);
		v.push_back(d);
		like.insert({ tmp ,v});
		
		if (i == 0) {	//픽하는 위치 저장 
			MAP[2][2] = tmp;
			loc.insert({ tmp, { 2,2 } });
			continue;
		}
	
		map<int,vector<int>>::iterator it;
		int tt =0;
		for (int j = 0; j < 4; j++) {
			it = like.find(v[j]); 
			if (it != like.end()) {// 현재까지 좋아하는 학생이 있을 때
				check(it->first, v); // 여기에 와도 되는지 파악 (*it : 좋아하는 학생 )
				tt = 1;
			}
		}
		
		if (tt == 1 && CC==1) {
			MAP[like_place.first][like_place.second] = tmp;
			loc.insert({ tmp,{like_place.first,like_place.second} });
			like_place = { 0,0 };
			likeBlank = 0;
			Blank_for_like = 0;
			CC = 0;
		}
		else { //빈칸 중에서 들어갈 공간 찾아야함 
			CC = 0;
			searchBlank();
			MAP[pick_place.first][pick_place.second] = tmp;
			loc.insert({ tmp,{pick_place.first,pick_place.second} });
			zeroBlank = 0;
			pick_place = { 0,0 };
		}
	}

	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cout << MAP[i][j] << '\t';
		}
		cout << '\n';
	}
	int re = check_result();
	cout << re;
	
}