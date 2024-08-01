// DFS, int 형 check
// 소요 시간 50m, 실행 시간 36ms

#include<iostream>
#include<string>

using namespace std;

int Map[1001][1001];
int N, M;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int ans = 0;
bool rep = false;

int check[1001][1001];

void move(int y, int x) {
	int ny = y + dy[Map[y][x]]; int nx = x + dx[Map[y][x]];

	if (check[ny][nx] == 2) rep = true;
	else if (check[ny][nx] == 0) {
		check[ny][nx] = 1;
		move(ny, nx);
		check[ny][nx] = 2;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin.ignore();

	for (int i = 0; i < N; i++) {
		string str;
		getline(cin, str);

		int j = 0;
		for (char ch : str) {
			if (ch == 'U') Map[i][j++] = 0;
			else if (ch == 'D') Map[i][j++] = 1;
			else if (ch == 'L') Map[i][j++] = 2;
			else if (ch == 'R') Map[i][j++] = 3;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (check[i][j] == 2) continue;
			rep = false;

			move(i, j);

			if (!rep) ans += 1;
		}
	}

	cout << ans;

	return 0;
}