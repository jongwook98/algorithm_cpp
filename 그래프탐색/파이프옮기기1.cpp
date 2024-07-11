#include<iostream>

using namespace std;

int dp[17][17][3];
bool Map[17][17];

int N;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;
	
	bool is_wall;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> is_wall;
			Map[i][j] = is_wall;
		}
	}

	dp[1][2][0] = 1;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i + j < 4) continue;

			if (Map[i][j] == false) {
				dp[i][j][0] = dp[i][j - 1][0] + dp[i][j - 1][1];
				dp[i][j][2] = dp[i - 1][j][1] + dp[i - 1][j][2];

				if (Map[i - 1][j] == false && Map[i][j - 1] == false) {
					dp[i][j][1] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2];
				}
			}
		}
	}

	cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2] << '\n';

	return 0;
}