//마법사 상어와 블리자드 https://www.acmicpc.net/problem/21611
//20201.10.02 시간 초과 
//문제 1. MAP을 초기화 하는 부분 -> 이차원 벡터 초기화할 때 확인하기
//문제 2. 경우의 수 중에서 아무것도 넘어가지 않을 때 파악을 해줬어야함
//문제 3. 반드시 문제 잘 보기

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int N, M;
//vector<vector<int>> MAP(50,vector<int>(50,0));
int MAP[50][50] = { 0 };
int dirMoveX[4] = {1,0,-1,0}; //이동을 위한 방향
int dirMoveY[4] = {0,1,0,-1};
int dirX[5] = {0,-1,1,0,0};//파괴를 위한 방향
int dirY[5] = {0,0,0,-1,1};
pair<int, int>shark;  //상어 기준점 체크
int re[4] = { 0 };
int checkBomb = 0;

deque<int> moveBiz() { //비즈 이동하기
	int x = shark.first;
	int y = shark.second;
	int cnt = 1;
	deque<int>map;
	vector<int> checkSequenceZero;
	
	while (x != 1 && y != 1) {  //1,1 이 되면 종료
		y -= 1;
		if (MAP[x][y] != 0) {
			map.push_back(MAP[x][y]); //처음 시작 
		}
		else
			checkSequenceZero.push_back(1);		//최적화하기 위해 0이 연속으로 나오게 되면 끝내는 것을 추가 

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < cnt; j++) {
				x += dirMoveX[i];
				y += dirMoveY[i];
				if (MAP[x][y] != 0) {
					map.push_back(MAP[x][y]);
					checkSequenceZero.clear();
				}
				else {
					checkSequenceZero.push_back(1);
					if (checkSequenceZero.size() >= 2) {
						return map;
					}
				}
			}
			if (i == 0)
				cnt++;
		}
		cnt++;
	}
	
	return map;
}

deque<int>bomb(deque<int>map) {
	deque<int>newMap;
	vector<int>check;
	if (map.size() == 0)
		return map;
	check.push_back(map[0]);

	for (int i = 1; i < map.size(); i++) {
		if(check.back() != map[i]){
			if (check.size() < 4) {
				for (int j = 0; j < check.size(); j++)
					newMap.push_back(check.back());
			}
			else {
				re[check.back()] += check.size();
				checkBomb = 1;
			}
			check.clear();
		}
		check.push_back(map[i]);
	}
	if (check.size() < 4) {
		for (int j = 0; j < check.size(); j++)
			newMap.push_back(check.back());
	}
	else {
		checkBomb = 1;
		re[check.back()] += check.size();
	}
	
	return newMap;
}

void changeBiz(deque<int>map) {	//변환하기
	deque<int>newMap;
	vector<int>check;
	if (map.size() == 0) {
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < N + 1; j++) {
				MAP[i][j] = 0;
			}
		}
		return;
	}
		
	check.push_back(map[0]);

	for (int i = 1; i < map.size(); i++) {
		if (check.back() != map[i]) {
			newMap.push_back(check.size());
			newMap.push_back(check.back());
			check.clear();
		}
		check.push_back(map[i]);
	}
	newMap.push_back(check.size());
	newMap.push_back(check.back());
	
	//MAP에 추가
	int x = shark.first;
	int y = shark.second;
	int cnt = 1;
	int storenum = newMap.size();
	int n = 0;
	while (x != 1 && y != 1) {  //1,1 이 되면 종료
		y -= 1;
		if (n >=storenum) {
			MAP[x][y] = 0;
		}
		else {
			MAP[x][y] = newMap[n];
			n++;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < cnt; j++) {
				x += dirMoveX[i];
				y += dirMoveY[i];
				if (n >=storenum) {
					MAP[x][y] = 0;
				}
				else {
					MAP[x][y] = newMap[n];
					n++;
				}
			}
			if (i == 0)
				cnt++;
		}
		cnt++;
	}
	
}

void destroy(int d, int s) { //파괴 시작
	int startX = shark.first;
	int startY = shark.second;
	for (int i = 0; i < s; i++) { //파괴
		startX += dirX[d];
		startY += dirY[d];
		MAP[startX][startY] = 0;
	}
	//구슬 저장 완료
	deque<int> map = moveBiz();
;


	//폭발
	while (1) {	
		map = bomb(map);
		if (checkBomb == 0)
			break;
		checkBomb = 0;
	}
	//변환
	changeBiz(map);

}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	int tmp;
	
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cin >> tmp;
			MAP[i][j] = tmp;
		}
	}
	shark = { (N + 1) / 2,(N + 1) / 2 };


	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		destroy(d, s);
	}
	int sum = 0;

	for (int i = 1; i < 4; i++) {
		sum += re[i] * i;
	}
	cout << sum;

}