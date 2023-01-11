#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

// 말과 같이 움직인 횟수, 좌표 deque를 활용하여
// 특수 움직임 + 좌표의 방문정보를 저장하여 목적지까지 도착하는지 확인

typedef struct {
	int y, x;
	int spent;
}pos;

int check[200][200][30];
bool Map[200][200];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int sy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int sx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

deque<pos> dq;

int ans = int(1e9);

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int K, W, H;
	cin >> K >> W >> H;

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) cin >> Map[y][x];
	}
	dq.push_back({ 0, 0, 0 });

	while (!dq.empty()) {
		int cy = dq.front().y; int cx = dq.front().x; int cur = dq.front().spent; dq.pop_front();

		if (cy == H - 1 && cx == W - 1) ans = min(ans, check[cy][cx][cur]);

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if ((ny >= 0 && ny < H && nx >= 0 && nx < W) && Map[ny][nx] == 0 &&
				(check[ny][nx][cur] == 0 || check[ny][nx][cur] > check[cy][cx][cur] + 1)) {
				check[ny][nx][cur] = check[cy][cx][cur] + 1;
				dq.push_back({ ny, nx, cur });
			}
		}

		if (cur < K) {
			for (int i = 0; i < 8; i++) {
				int ny = cy + sy[i]; int nx = cx + sx[i];

				if ((ny >= 0 && ny < H && nx >= 0 && nx < W) && Map[ny][nx] == 0 &&
					(check[ny][nx][cur + 1] == 0 || check[ny][nx][cur + 1] > check[cy][cx][cur] + 1)) {
					check[ny][nx][cur + 1] = check[cy][cx][cur] + 1;
					dq.push_back({ ny, nx, cur + 1 });
				}
			}
		}
	}

	if (ans != int(1e9)) cout << ans << '\n';
	else cout << -1 << '\n';

	return 0;
}