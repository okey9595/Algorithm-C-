//나무 자르기 https://www.acmicpc.net/problem/2805
//이진탐색

//나무의 길이가 길기 때문에 long long 사용 해야한다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M;
vector<int> tree;
bool func(int mid) {
	long long sum = 0;

	for (int i = 0; i < N; i++) {
		if (tree[i] - mid > 0) {
			int tmp = tree[i] - mid;
			sum += (long long)tmp;
		}
	}
	return M > sum;
}

int main() {
	//결국에는 벌목 높이가 관건. 벌목 높이 최저 : 0, 벌목 높이 최고 : 제일 높은 나무
	//즉, 정렬한 뒤 벌목 높이 최고와 최저 사이 고르기
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	int tmp, st, end;
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		tree.push_back(tmp);
		sum += (long long)tmp;
	}
	sort(tree.begin(), tree.end());
	st = 0;
	end = tree.back();
	int mid;
	int answer;
	while (st <= end) {
		mid = (st + end) / 2;
		if (func(mid)) {  //M > sum 일때
			end = mid - 1;
		}
		else {
			answer = mid;
			st = mid + 1;
		}
	}
	
	cout << answer;

}