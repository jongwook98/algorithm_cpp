#include<iostream>
#include<cmath>

// 백트래킹으로 해결

using namespace std;

int arr[2][3000];
bool check[3000][3000];

int ans;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, K, T, U;
	cin >> N >> M >> K;

	T = min(N, M);
	U = max(N, M);

	if (N <= M) {
		for (int i = 0; i < N; i++) cin >> arr[0][i];
		for (int i = 0; i < M; i++) cin >> arr[1][i];
	}
	else {
		for (int i = 0; i < N; i++) cin >> arr[1][i];
		for (int i = 0; i < M; i++) cin >> arr[0][i];
	}

	int cnt = 0;
	for (int j = 0; j < T; j++) {
		if (T - j < ans) break;

		for (int i = 0; i < U; i++) {
			if (U - i < ans) break;
			if (check[j][i]) continue;

			if (arr[0][j] == arr[1][i]) {
				cnt = 1;
				check[j][i] = true;
				for (int k = 1; k < T; k++) {
					if (j + k >= T || i + k >= U) break;
					if (arr[0][j + k] != arr[1][i + k]) break;
					check[j + k][i + k] = true;

					cnt += 1;
				}
				ans = max(ans, cnt);
			}
		}
	}

	cout << ans << '\n';

	return 0;
}