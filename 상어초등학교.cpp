//����ʵ��б� https://www.acmicpc.net/status?user_id=andy618&problem_id=21608&from_mine=1
//�� 2�ð� , �Ϻ��� ����

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int MAP[21][21] = { 0 };
int N;
//map<int, vector<int>> like; //��ȣ�ϴ� �л� ����, <��ȣ, ��ȣ�ϴ� �л�>
map<int,vector<int>> like;
map<int, pair<int, int>>loc; //����� �л��� ��ġ�� x ����  
int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};
int Blank_for_like = 0; //��ĭ�� ���� ���� 
int likeBlank = 0; // �����ϴ� ����� ����
int zeroBlank = 0;
pair<int, int>like_place;    //�����ؾ��� �����ϴ� ��� �� ��ġ
pair<int, int>pick_place;   // ��ĭ ��ġ 
int CC = 0;

void check(int stu,vector<int> v) { //stu : �����ϴ� �л� ,v: �����ϴ� �л���       �л� ������ index ���� ���� 
	map<int, pair<int, int>>::iterator it;

	it = loc.find(stu);
	int x = it->second.first;
	int y = it->second.second;
	
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx <1 || nx>N || ny <1 || ny>N)
			continue;
		if (MAP[nx][ny] == 0) { // ��ĭ�� �� ã�ƾ���
			int zerocnt = 0;
			int cnt = 0;  // �����ϴ� ��� ������� ī��Ʈ 
			CC = 1;

			for (int j = 0; j < 4; j++) {  // �� �ٽ� ������ ��ĭ�� ���� �������, ������ �� �ٽ� �����ϴ� ��� �ִ����� �ľ�
				int nnx = nx + dx[j];
				int nny = ny + dy[j];
				if (nnx <1 || nnx>N || nny <1 || nny>N)
					continue;
				if (MAP[nnx][nny] == 0)  //��ĭ ���� ä�� ���ƾ���
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
						if (MAP[nx][ny] == 0)  //��ĭ ���� ä�� ���ƾ���
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
					if (MAP[nx][ny] == 0)  //��ĭ ���� ä�� ���ƾ���
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
		
		if (i == 0) {	//���ϴ� ��ġ ���� 
			MAP[2][2] = tmp;
			loc.insert({ tmp, { 2,2 } });
			continue;
		}
	
		map<int,vector<int>>::iterator it;
		int tt =0;
		for (int j = 0; j < 4; j++) {
			it = like.find(v[j]); 
			if (it != like.end()) {// ������� �����ϴ� �л��� ���� ��
				check(it->first, v); // ���⿡ �͵� �Ǵ��� �ľ� (*it : �����ϴ� �л� )
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
		else { //��ĭ �߿��� �� ���� ã�ƾ��� 
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