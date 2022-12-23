#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int DP[10001];

priority_queue<int, vector<int>, greater<int>> pq;

// 순서를 고려하지 않고 사용한 동전의 구성만을 생각하므로
// 작은 가치의 동전부터 점차 사용하는 것으로 생각

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k;
	cin >> n >> k;

	int val;
	while (n--) {
		cin >> val;
		pq.push(val);
	}
	
	DP[0] = 1;
	while (!pq.empty()) {
		int iter = pq.top(); pq.pop();

		for (int i = iter; i <= k; i++) {
			DP[i] += DP[i - iter];
		}
	}

	cout << DP[k] << '\n';

	return 0;
}