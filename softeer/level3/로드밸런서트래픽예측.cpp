#include<iostream>
#include<vector>
#include<queue>

using namespace std;

// 위상 정렬

// dfs 구조로 작성하면 시간초과가 나는 이유는 중복되는 node에 값이 들어오면 따로 처리해주기 때문에 시간초과가 난다.
// 위상정렬을 이용하면 이미 값이 다 받아진 상태 (더 이상 해당 node로 값이 들어오지 않는 상태) 에서 다음 node로 한 번에 넘겨주기 때문에
// 중복 연산을 피할 수 있다.

vector<int> node[100000];
int indegree[100000];
long long ans[100000];

queue<int> q;

void func(int cur) {

	if (node[cur].empty()) return;
	long long div = ans[cur] / long(node[cur].size());
	int res = int(ans[cur] % long(node[cur].size()));

	for (int n_node : node[cur]) {
		if (res > 0) ans[n_node] += div + 1;
		else ans[n_node] += div;
		indegree[n_node] -= 1;

		if (indegree[n_node] == 0) q.push(n_node);
		res--;
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	long long K;

	cin >> N >> K;

	int ri, pi;
	for (int i = 0; i < N; i++) {
		cin >> ri;
		if (ri == 0) continue;

		for (int j = 0; j < ri; j++) {
			cin >> pi;
			node[i].push_back(pi - 1);
			indegree[pi - 1] += 1;
		}
	}

	q.push(0);
	ans[0] = K;

	int cur;
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		func(cur);
	}

	for (int i = 0; i < N; i++) cout << ans[i] << " ";

	return 0;
}