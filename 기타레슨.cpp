//��Ÿ���� https://jaimemin.tistory.com/1130
//���� Ž�� 
#include <iostream>
#include <vector>
using namespace std;
vector<int> video;
int N, M;

bool func(int mid) {  //mid : �ִ� ���� ����
	
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

int main() { // ������ ���� ���̸� ã�� ���� �̺� Ž�� �ؾ������� st�� end�� ���� ���̷� ���� 
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