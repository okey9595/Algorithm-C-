//������ ���� ���ڵ� https://www.acmicpc.net/problem/21611
//20201.10.02 �ð� �ʰ� 
//���� 1. MAP�� �ʱ�ȭ �ϴ� �κ� -> ������ ���� �ʱ�ȭ�� �� Ȯ���ϱ�
//���� 2. ����� �� �߿��� �ƹ��͵� �Ѿ�� ���� �� �ľ��� ��������
//���� 3. �ݵ�� ���� �� ����

#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int N, M;
//vector<vector<int>> MAP(50,vector<int>(50,0));
int MAP[50][50] = { 0 };
int dirMoveX[4] = {1,0,-1,0}; //�̵��� ���� ����
int dirMoveY[4] = {0,1,0,-1};
int dirX[5] = {0,-1,1,0,0};//�ı��� ���� ����
int dirY[5] = {0,0,0,-1,1};
pair<int, int>shark;  //��� ������ üũ
int re[4] = { 0 };
int checkBomb = 0;

deque<int> moveBiz() { //���� �̵��ϱ�
	int x = shark.first;
	int y = shark.second;
	int cnt = 1;
	deque<int>map;
	vector<int> checkSequenceZero;
	
	while (x != 1 && y != 1) {  //1,1 �� �Ǹ� ����
		y -= 1;
		if (MAP[x][y] != 0) {
			map.push_back(MAP[x][y]); //ó�� ���� 
		}
		else
			checkSequenceZero.push_back(1);		//����ȭ�ϱ� ���� 0�� �������� ������ �Ǹ� ������ ���� �߰� 

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

void changeBiz(deque<int>map) {	//��ȯ�ϱ�
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
	
	//MAP�� �߰�
	int x = shark.first;
	int y = shark.second;
	int cnt = 1;
	int storenum = newMap.size();
	int n = 0;
	while (x != 1 && y != 1) {  //1,1 �� �Ǹ� ����
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

void destroy(int d, int s) { //�ı� ����
	int startX = shark.first;
	int startY = shark.second;
	for (int i = 0; i < s; i++) { //�ı�
		startX += dirX[d];
		startY += dirY[d];
		MAP[startX][startY] = 0;
	}
	//���� ���� �Ϸ�
	deque<int> map = moveBiz();
;


	//����
	while (1) {	
		map = bomb(map);
		if (checkBomb == 0)
			break;
		checkBomb = 0;
	}
	//��ȯ
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