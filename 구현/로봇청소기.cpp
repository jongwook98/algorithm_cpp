#include<iostream>

using namespace std;

typedef struct {
	int y, x, dir;
}info;

bool map[50][50];
bool check[50][50];

int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, r, c, d;
	cin >> N >> M >> r >> c >> d;

	int cy = r;
	int cx = c;
	int cd = d;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}

	while (true) {
		bool fig = true;
		check[cy][cx] = true;
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[(cd + 3) % 4];
			int nx = cx + dx[(cd + 3) % 4];
			if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (!check[ny][nx] && !map[ny][nx]) {
					cy = ny; cx = nx;
					fig = false;
					cd = (cd + 3) % 4;
					break;
				}
			}
			cd = (cd + 3) % 4;
		}
		if (fig) {
			int ny = cy + dy[(cd + 2) % 4];
			int nx = cx + dx[(cd + 2) % 4];
			if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (!map[ny][nx]) {
					cy = ny; cx = nx;
				}
				else break;
			}
			else break;
		}
	}
	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (check[y][x] == true) ans++;
		}
	}

	cout << ans << '\n';
	return 0;
}
