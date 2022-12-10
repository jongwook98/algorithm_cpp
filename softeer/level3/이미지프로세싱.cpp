#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

typedef struct {
	int y, x;
}pos;

int Map[128][128];
bool check[128][128];
queue<pos> q;

pos mv[] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int H, W;
	cin >> H >> W;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) cin >> Map[y][x];
	}

	int Q;
	cin >> Q;
	while (Q--) {
		int i, j, c, color;
		cin >> i >> j >> c;

		memset(check, false, sizeof(check));

		color = Map[i - 1][j - 1];
		Map[i - 1][j - 1] = c;
		q.push({ i - 1, j - 1 });

		check[i - 1][j - 1] = true;

		while (!q.empty()) {
			int cy = q.front().y;
			int cx = q.front().x;
			q.pop();

			for (int d = 0; d < 4; d++) {
				int ny = cy + mv[d].y;
				int nx = cx + mv[d].x;

				if (ny >= 0 && ny < H && nx >= 0 && nx < W) {
					if (!check[ny][nx] && Map[ny][nx] == color) {
						check[ny][nx] = true;
						Map[ny][nx] = c;
						q.push({ ny, nx });
					}
				}
			}
		}
	}

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) cout << Map[y][x] << " ";
		cout << '\n';
	}

	return 0;
}