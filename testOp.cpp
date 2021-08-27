//브론즈2 [시험감독] https://www.acmicpc.net/problem/13458
//2021.08.27

#include <iostream>
#include <vector>
using namespace std;
int N, B, C;

int main() {
	vector<int> v;
	long long sum = 0;
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		v.push_back(n);
	}
	cin >> B >> C;
	
	for (int i = 0; i < N; i++) {
		if ((v[i] - B) > 0) {
			int tmp = (v[i] - B)/C;
			
			sum += tmp;
			if ((v[i] - B) %C !=0)
				sum ++;
			
		}
	}
	sum += N;
	cout << sum;
}