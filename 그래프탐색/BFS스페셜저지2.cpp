#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int N, A, B, pos;
vector<int> v[100001];
queue<int> q;
int bfs_order[100001];

bool comp(const int& a, const int& b) {
	return bfs_order[a] < bfs_order[b];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> A >> B;
		v[A].push_back(B);
		v[B].push_back(A);
	}
	for (int i = 1; i <= N; i++) {
		cin >> A;
		q.push(A);
		bfs_order[A] = i;
	}
	
	// 이 정렬이 핵심이다..
	// bfs_order를 통해 방문 순서에 따라 우선순위를 다르게 하여
	// 정점에서의 방문을 정렬한다.
	for (int i = 1; i <= N; i++) {
		sort(v[i].begin(), v[i].end(), comp);
	}
	if (q.front() != 1) {
		cout << "0" << '\n';
		exit(0);
	}
	else {
		queue<int> temp;
		temp.push(1);
		q.pop();
		while (!temp.empty()) {
			pos = temp.front();
			temp.pop();
			for (auto i : v[pos]) {
				if (i == q.front()) {
					temp.push(q.front());
					q.pop();
				}
				else;
			}
		}
	}
	if (q.empty()) cout << "1" << '\n';
	else cout << "0" << '\n';
	return 0;
}