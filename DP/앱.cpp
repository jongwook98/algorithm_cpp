// DP, 배낭문제
// 문제 조건에서 주어진 전체 cost 비용의
// 시간 복잡도 안에 해결 가능한지 생각해보기

#include<iostream>
#include<algorithm>

using namespace std;

int byte[101], cost[101];
int DP[101][10001];

int N, M;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int value;
	for (int num = 1; num <= N; num++) {
		cin >> value;
		byte[num] = value;
	}

	int sum = 0;
	for (int num = 1; num <= N; num++) {
		cin >> value;
		cost[num] = value;
		sum += value;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= sum; j++) {

			if (j - cost[i] >= 0) DP[i][j] = max(DP[i][j], DP[i - 1][j - cost[i]] + byte[i]);

			DP[i][j] = max(DP[i][j], DP[i - 1][j]);
		}
	}

	for (int i = 0; i <= sum; i++) {
		if (DP[N][i] >= M) {
			cout << i << '\n';
			break;
		}
	}

	return 0;
}