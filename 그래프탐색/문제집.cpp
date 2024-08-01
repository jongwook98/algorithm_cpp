// 위상 정렬, 우선순위 큐 이용
// 소요 시간 10m, 실행 시간 32ms

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;

vector<int> v[32001];
int in_[32001];
int N, M;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int A, B;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		v[A].push_back(B);
		in_[B] += 1;
	}

	for (int i = 1; i <= N; i++) {
		if (in_[i] == 0) pq.push(i);
	}

	while (!pq.empty()) {
		int cur = pq.top(); pq.pop();
		cout << cur << " ";

		for (int iter : v[cur]) {
			in_[iter] -= 1;
			if (in_[iter] == 0) pq.push(iter);
		}
	}


	return 0;
}