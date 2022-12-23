#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int score[100000][2];
int DP[100000][2];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		memset(score, 0, sizeof(score));
		memset(DP, 0, sizeof(DP));

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++)	cin >> score[j][i];
		}

		DP[0][0] = score[0][0];
		DP[0][1] = score[0][1];
		DP[1][0] = score[0][1] + score[1][0];
		DP[1][1] = score[0][0] + score[1][1];

		for (int i = 2; i < N; i++) {
			DP[i][0] = max({ DP[i - 1][1], DP[i - 2][0], DP[i - 2][1] }) + score[i][0];
			DP[i][1] = max({ DP[i - 1][0], DP[i - 2][1], DP[i - 2][0] }) + score[i][1];
		}

		cout << max(DP[N - 1][0], DP[N - 1][1]) << '\n';
	}

	return 0;
}