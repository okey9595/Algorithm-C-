//골드3[경사로] https://www.acmicpc.net/problem/14890
//2021.09.03 -> 41분 

#include <iostream>
#include <vector>
using namespace std;
int N, L;
vector <vector <int>>MAP(100, vector<int>(100, 0));
int SUM = 0;
vector<int> store;

int check(vector <int> v) {
	vector<int> store;
	store.push_back(v[0]);
	int cur = v[0];

	for (int i = 1; i < N; i++) {  
		if (cur - v[i] == 0) {
			store.push_back(v[i]);
		}
		else if (cur - v[i] == 1) {
			for (int j = i; j < i + L; j++) {
				if (j == N)   //범위를 넘었을 때
					return 0;
				if (v[i] != v[j])
					return 0;
			}
			cur = cur - 1;
			store.clear();
			i += L;
			i--;
		}
		else if (cur - v[i] == -1) {
			if (store.size() < L) {
				return 0;
			}
			cur = cur + 1;   
			store.clear();
			store.push_back(v[i]);
		}
		else {
			return 0;
		}
	}

	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		vector<int> tmp;
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			tmp.push_back(MAP[i][j]);
		}
		SUM += check(tmp);
	}
	
	for (int i = 0; i < N; i++) {
		vector <int> tmp;
		for (int j = 0; j < N; j++) {
			tmp.push_back(MAP[j][i]);
		}
		SUM += check(tmp);
	}
	cout << SUM;
}