#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int DP[10001][10001];
int V[101];
int W[101];
vector<pair<int, int>> v;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, k;
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		cin >> W[i] >> V[i] >> k;
		for (int j = 1; k > 0; j <<= 1) {
			int ix = min(j, k);
			v.push_back({ W[i] * ix, V[i] * ix });
			k -= ix;
		}
	}

	int cnt = 1;
	for (pair<int, int> info : v) {
		for (int j = 1; j <= M; j++) {
			if (j - info.first >= 0) DP[cnt][j] = max(DP[cnt - 1][j], DP[cnt - 1][j - info.first] + info.second);
			else DP[cnt][j] = DP[cnt - 1][j];
		}
		cnt++;
	}

	/*for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 9; j++) {
			cout << DP[i][j] << " ";
		}
		cout << '\n';
	}*/

	cout << DP[v.size()][M] << '\n';

	return 0;
}
