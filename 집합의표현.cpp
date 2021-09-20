//집합의 표현 https://www.acmicpc.net/problem/1717
//cout 보다 printf 가 속도가 훨씬 빠름

#include <iostream>
#include <cstdio>
using namespace std;
int parent[1000001];
int do_find(int f) {
	if (parent[f] == f)
		return f;
	else
		return parent[f] = do_find(parent[f]);
}

void do_union(int a, int b) {
	int pa = do_find(a);
	int pb = do_find(b);
	
	parent[pb] = pa;
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < m; i++) {
		int query, a, b;

		cin >> query >> a >> b;
		if (query == 0) {
			do_union(a, b);
		}
		else {
			if (do_find(a) == do_find(b))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
}