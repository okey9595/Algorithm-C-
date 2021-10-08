//���� �ڸ��� https://www.acmicpc.net/problem/2805
//����Ž��

//������ ���̰� ��� ������ long long ��� �ؾ��Ѵ�.
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
	//�ᱹ���� ���� ���̰� ����. ���� ���� ���� : 0, ���� ���� �ְ� : ���� ���� ����
	//��, ������ �� ���� ���� �ְ�� ���� ���� ����
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
		if (func(mid)) {  //M > sum �϶�
			end = mid - 1;
		}
		else {
			answer = mid;
			st = mid + 1;
		}
	}
	
	cout << answer;

}