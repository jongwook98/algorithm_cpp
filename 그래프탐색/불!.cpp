#include<iostream>
#include<deque>

using namespace std;

typedef struct {
	int y, x;
}pos;

char Map[1000][1000];
bool ch_jh[1000][1000];
bool ch_fi[1000][1000];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

deque<pos> JH;
deque<pos> FI;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int R, C;
	cin >> R >> C;

	char temp;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> temp;
			Map[y][x] = temp;
			if (temp == 'J') {
				JH.push_back({ y, x });
				ch_jh[y][x] = true;
			}
			else if (temp == 'F') {
				FI.push_back({ y, x });
				ch_fi[y][x] = true;
			}
		}
	}

	int ans = 0;
	while (!JH.empty() || !FI.empty()) {
		int re_jh = JH.size(); int re_fi = FI.size();
		ans++;
		while (re_jh--) {
			int cy = JH.front().y; int cx = JH.front().x; JH.pop_front();

			if (Map[cy][cx] == 'F') continue;

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				if (ny >= 0 && ny < R && nx >= 0 && nx < C && !ch_jh[ny][nx] && Map[ny][nx] == '.') {
					ch_jh[ny][nx] = true;
					JH.push_back({ ny, nx });
				}
				else if (ny < 0 || ny >= R || nx < 0 || nx >= C) {
					cout << ans << '\n';
					return 0;
				}
			}
		}
		while (re_fi--) {
			int cy = FI.front().y; int cx = FI.front().x; FI.pop_front();

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];
				if (ny >= 0 && ny < R && nx >= 0 && nx < C && !ch_fi[ny][nx] && Map[ny][nx] == '.') {
					ch_fi[ny][nx] = true;
					Map[ny][nx] = 'F';
					FI.push_back({ ny, nx });
				}
			}
		}
	}

	cout << "IMPOSSIBLE" << '\n';

	return 0;
}