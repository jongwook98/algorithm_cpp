#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

typedef struct {
	int y, x;
	int time;
}pos;

int fish[7] = { 0, };
int Map[20][20] = { 0, };

int fs = 2, fy, fx;
int ec = 0;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

bool check[20][20];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int n;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> n;
			Map[y][x] = n;

			if (n > 0 && n < 9) fish[n]++;
			else if (n == 9) {
				fy = y; fx = x;
				Map[y][x] = 0;
			}
		}
	}

	int ans = 0;
	while (true) {
		int eable = 0;
		for (int i = 1; i < fs; i++) {
			eable += fish[i];
		}
		if (eable == 0) break;

		queue<pos> q;
		q.push({ fy, fx, 0 });

		memset(check, false, sizeof(check));
		check[fy][fx] = true;

		int ct = -1, cy = 0, cx = 0;
		while (!q.empty()) {
			pos cur = q.front(); q.pop();

			if (ct == -1 && Map[cur.y][cur.x] > 0 && Map[cur.y][cur.x] < fs) {
				ct = cur.time;
				cy = cur.y; cx = cur.x;
			}
			else if (cur.time <= ct && Map[cur.y][cur.x] > 0 && Map[cur.y][cur.x] < fs) {
				if (cy > cur.y) {
					cy = cur.y; cx = cur.x;
				}
				else if (cy == cur.y && cx > cur.x) cx = cur.x;
			}
			if (ct == -1 || cur.time < ct) {
				for (int i = 0; i < 4; i++) {
					int ny = cur.y + dy[i]; int nx = cur.x + dx[i];

					if (ny >= 0 && ny < N && nx >= 0 && nx < N && !check[ny][nx]) {
						if (Map[ny][nx] <= fs) {
							q.push({ ny, nx, cur.time + 1 });
							check[ny][nx] = true;
						}
					}
				}
			}
		}
		if (ct < 0) break;

		Map[cy][cx] = 0; fish[Map[cy][cx]]--; ec++;
		if (ec >= fs) {
			ec = 0;
			fs++;
		}
		fy = cy; fx = cx; ans += ct;
	}

	cout << ans << '\n';
}