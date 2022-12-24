#include<iostream>

using namespace std;

long long DP[100][100];
long long path[100][100];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> path[i][j];
	}

	DP[0][0] = 1;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (y == N - 1 && x == N - 1) continue;

			int ny = y + path[y][x];
			int nx = x + path[y][x];

			if (ny >= 0 && ny < N) DP[ny][x] += DP[y][x];
			if (nx >= 0 && nx < N) DP[y][nx] += DP[y][x];
		}
	}

	cout << DP[N - 1][N - 1] << '\n';

	return 0;
}