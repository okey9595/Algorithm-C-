#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
//vector <string> dic;
set <string> dic;
//vector <string> check;
int N, M;
int SUM = 0;
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;
		//dic.push_back(tmp);
		dic.insert(tmp);
	}
	for (int i = 0; i < M; i++) {
		string tmp;
		cin >> tmp;
		if (dic.find(tmp) != dic.end())
			SUM++;
	}

	cout<< SUM;
	

}