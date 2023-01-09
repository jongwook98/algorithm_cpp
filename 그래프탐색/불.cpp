#include<iostream>
#include<deque>
#include<cstring>

using namespace std;

// 탈출 한 순간 나머지 반복문을 건너뛰어 여러번 출력이 안되도록 해야한다. !

typedef struct {
	int y, x;
}pos;

char Map[1000][1000];
bool check[1000][1000];

deque<pos> dq;
deque<pos> fire;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		memset(check, false, sizeof(check));
		memset(Map, 0, sizeof(Map));

		int w, h;
		cin >> w >> h;

		char temp;

		dq.clear();
		fire.clear();

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				cin >> temp;
				Map[y][x] = temp;

				if (temp == '@') {
					dq.push_back({ y, x });
					check[y][x] = true;
					Map[y][x] = '.';
				}
				else if (temp == '*') fire.push_back({ y, x });
			}
		}

		int time = 0;
		bool flag = false;

		while (!dq.empty()) {
			int dq_rep = dq.size(); int fire_rep = fire.size();
			time++;

			while (fire_rep--) {
				int cy = fire.front().y; int cx = fire.front().x; fire.pop_front();

				for (int i = 0; i < 4; i++) {
					int ny = cy + dy[i]; int nx = cx + dx[i];

					if (ny >= 0 && ny < h && nx >= 0 && nx < w && Map[ny][nx] == '.') {
						Map[ny][nx] = '*';
						fire.push_back({ ny, nx });
					}
				}
			}

			while (dq_rep--) {
				int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();
				
				if (flag) break;

				for (int i = 0; i < 4; i++) {
					int ny = cy + dy[i]; int nx = cx + dx[i];

					if (ny >= 0 && ny < h && nx >= 0 && nx < w && !check[ny][nx]) {
						if (Map[ny][nx] == '.') {
							check[ny][nx] = true;
							dq.push_back({ ny, nx });
						}
					}
					else if (ny < 0 || ny >= h || nx < 0 || nx >= w) {
						cout << time << '\n';
						flag = true;
						break;
					}
				}
			}

			if (flag) break;
		}

		if (!flag) cout << "IMPOSSIBLE" << '\n';
	}

	return 0;
}