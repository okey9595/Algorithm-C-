//기타레슨 https://jaimemin.tistory.com/1130
//이진 탐색 
#include <iostream>
#include <vector>
using namespace std;
vector<int> video;
int N, M;

bool func(int mid) {  //mid : 최대 강의 길이
	
	int sum = 0;
	int cnt = 1;
	for (int i = 0; i < video.size(); i++) {
		sum += video[i];
		if (video[i] > mid)
			return false;
		if (sum > mid) {
			sum = video[i];
			cnt++;
		}
	}
	return M >= cnt;

}

int main() { // 최적의 강의 길이를 찾기 위해 이분 탐색 해야함으로 st와 end는 강의 길이로 설정 
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	int answer;
	int tmp;
	int sum = 0;
	int st = 1;
	int end;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		sum += tmp;
		video.push_back(tmp);
	}
	end = sum;
	int mid;

	while (st <= end) {
		mid = (st + end) / 2;
		if (func(mid)) {
			answer = mid;
			end = mid - 1;
		}
		else {
			st = mid + 1;
		}
	}
	cout << answer;
}