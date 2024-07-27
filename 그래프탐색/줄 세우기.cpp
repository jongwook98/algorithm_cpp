// 위상 정렬(Topology Sort) 알고리즘이 생각나야 하는 문제,
// 반복 출력을 막기 위한 check를 생성했지만,
// 주석 처리해도 문제 없이 진행된다.
// =>
// 진입 차수가 0보다 작아지는 시점이 생성되지 않음
// 중복되는 입력이나 사이클만 없다면, 한 번만 출력된다.

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;

int in_[32001];
vector<int> v[32001];
queue<int> q;

//bool check[32001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int A, B;
	while (M--) {
		cin >> A >> B;
		in_[B]++;
		v[A].push_back(B);
	}

	for (int i = 1; i <= N; i++) {
		if (in_[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		//if (check[cur]) continue;
		//check[cur] = true;
		cout << cur << " ";

		for (int iter : v[cur]) {
			//if (check[iter]) continue;
			if ((--in_[iter]) <= 0) {
				q.push(iter);
			}
		}
	}

	return 0;
}