#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

// 벽 부수고 이동하기2 에서 낮과 밤 정보만 추가하여 해결
// + 다음 좌표로 이동하기 위한 for 문 돌리기 전에 낮 -> 밤, 밤 -> 낮으로 시간 보내는 한 줄 추가

typedef struct {
	int y, x;
	int b, t;
}pos;

int check[1000][1000][11][2];
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

	check[0][0][0][0] = 1;
	dq.push_back({ 0, 0, 0, 0 });

	while (!dq.empty()) {
		int cy = dq.front().y; int cx = dq.front().x; int cb = dq.front().b; int ct = dq.front().t;
		dq.pop_front();

		if (check[cy][cx][cb][1 - ct] == 0) {
			check[cy][cx][cb][1 - ct] = check[cy][cx][cb][ct] + 1;
			dq.push_back({ cy, cx, cb, 1 - ct });
		}

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if (ny == N - 1 && nx == M - 1) ans = min(ans, check[cy][cx][cb][ct] + 1);

			else if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (Map[ny][nx] == '0' && check[ny][nx][cb][1 - ct] == 0) {
					check[ny][nx][cb][1 - ct] = check[cy][cx][cb][ct] + 1;
					dq.push_back({ ny, nx, cb, 1 - ct });
				}
				else if (Map[ny][nx] == '1' && ct == 0 && cb + 1 <= K && check[ny][nx][cb + 1][1 - ct] == 0) {
					check[ny][nx][cb + 1][1 - ct] = check[cy][cx][cb][ct] + 1;
					dq.push_back({ ny, nx, cb + 1, 1 - ct });
				}
			}
		}
	}

	if (ans == int(1e9)) cout << -1 << '\n';
	else cout << ans << '\n';

	return 0;
}