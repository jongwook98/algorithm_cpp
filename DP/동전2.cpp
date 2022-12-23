#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pq;

int DP[10001];

// 동전의 최소 개수를 구해야하므로
// 기존의 DP 값과 동전의 가치를 뺀 DP 값 + 1 중에 작은 값으로 갱신

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i <= k; i++) DP[i] = int(1e6);

	int val;
	while (n--) {
		cin >> val;
		pq.push(val);
		if (val <= 10000) DP[val] = 1;
	}

	while (!pq.empty()) {
		int iter = pq.top(); pq.pop();
		for (int i = iter; i <= k; i++) {
			DP[i] = min(DP[i], DP[i - iter] + 1);
		}
	}

	//for (int i = 0; i <= k; i++) cout << DP[i] << " ";
	if (DP[k] != int(1e6)) cout << DP[k] << '\n';
	else cout << -1 << '\n';

	return 0;
}