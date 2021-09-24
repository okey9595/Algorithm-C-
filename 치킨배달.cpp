//���5 [ġŲ���] https://www.acmicpc.net/problem/15686
//2021.09.24 , 42�� 

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int N, M;
int MIN = 999999999;
vector<pair<int, int>> chicken;
vector<pair<int, int>> home;

void countDistance(vector<int> ch) {
	int total = 0;
	for (int i = 0; i < home.size(); i++) {
		int m = 2 * N;
		for (int j = 0; j < chicken.size(); j++) {
			if (ch[j] == 1) {
				int t = abs(home[i].first - chicken[j].first) + abs(home[i].second - chicken[j].second);
				m = min(m, t);
			}
		}
		total += m;
	}
	MIN = min(MIN, total);
}

void pickCh(int num,vector<int> n, int index) {  // num : ���� Ƚ�� , index : �ε��� �� , n : ����Ǿ��ִ� ����
	if (num == M) {
		countDistance(n);
		return;
	}
	for (int i = index; i < chicken.size()-M+num+1; i++) {
		n[i] = 1;
		pickCh(num + 1, n, i + 1);
		n[i] = 0;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			if (tmp == 1)
				home.push_back({ i,j });
			else if (tmp == 2)
				chicken.push_back({ i,j });
		}
	}
	if (chicken.size() == M) { 
		vector<int> v(chicken.size(), 1);   // �̰� 1�� �ʱ�ȭ �Ǵ��� Ȯ�� ( �ʱ�ȭ ��)
		countDistance(v);
		cout << MIN << endl;
		return 0;
	}
	vector<int> n(chicken.size(), 0);
	pickCh(0,n,0);

	cout << MIN << endl;
}