// 위상정렬 문제
// 25m, 0ms

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> v[1001];
int in_[1001];
int N, M;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int arr, num, prev = 0;
		cin >> arr;
		while (arr--) {
			cin >> num;
			if (prev != 0) {
				v[prev].push_back(num);
				in_[num]++;
			}
			prev = num;
		}
	}

	queue<int> q;
	queue<int> ans_q;

	for (int i = 1; i <= N; i++) {
		if (in_[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		ans_q.push(cur);
		for (int iter : v[cur]) {
			if (--in_[iter] == 0) {
				q.push(iter);
			}
		}
	}

	if (ans_q.size() == N) {
		while (!ans_q.empty()) {
			cout << ans_q.front() << '\n';
			ans_q.pop();
		}
	}
	else cout << 0;

	return 0;
}