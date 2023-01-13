#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

// 방문정보 배열을 좌표 + 부순 벽의 개수를 인덱스로 정보 갱신
// 벽을 부순경우와 부수지 않은 경우의 시간은 동일하므로
// 방문정보와 값을 비교하지 않아도 됨

typedef struct {
	int y, x;
	int b;
}pos;

int check[1000][1000][11];
char Map[1000][1000];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

deque<pos> dq;

int ans = int(1e9);

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, K;
	cin >> N >> M >> K;

	if (N == 1 && M == 1) {
		cout << 1 << '\n';
		return 0;
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) cin >> Map[y][x];
	}

	check[0][0][0] = 1;
	dq.push_back({ 0, 0, 0 });

	while (!dq.empty()) {
		int cy = dq.front().y; int cx = dq.front().x; int cb = dq.front().b;
		dq.pop_front();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if (ny == N - 1 && nx == M - 1) ans = min(ans, check[cy][cx][cb] + 1);

			else if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (Map[ny][nx] == '0' && check[ny][nx][cb] == 0) {
					check[ny][nx][cb] = check[cy][cx][cb] + 1;
					dq.push_back({ ny, nx, cb });
				}
				else if (Map[ny][nx] == '1' && cb + 1 <= K && check[ny][nx][cb + 1] == 0) {
					check[ny][nx][cb + 1] = check[cy][cx][cb] + 1;
					dq.push_back({ ny, nx, cb + 1 });
				}
			}
		}
	}

	if (ans == int(1e9)) cout << -1 << '\n';
	else cout << ans << '\n';

	return 0;
}