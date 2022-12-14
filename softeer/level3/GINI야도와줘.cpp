#include<iostream>
#include<queue>

using namespace std;

// BFS 두 가지로 해결

typedef struct {
	int y, x;
}pos;

char Map[50][50];
bool check[50][50];

queue<pos> car;
queue<pos> rain;

pos mv[] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int R, C;
	cin >> R >> C;
	cin.ignore();

	char info;

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> info;
			Map[y][x] = info;
			if (info == 'W') {
				car.push({ y, x });
				check[y][x] = true;
			}
			else if (info == '*') rain.push({ y, x });
		}
	}

	int ans = 0;
	bool success = false;
	while (true) {
		ans += 1;
		int rep_car = car.size();
		int rep_rain = rain.size();

		while (rep_rain--) {
			pos cur = rain.front();
			rain.pop();

			for (int i = 0; i < 4; i++) {
				int ny = cur.y + mv[i].y;
				int nx = cur.x + mv[i].x;

				if (ny >= 0 && ny < R && nx >= 0 && nx < C) {
					if (Map[ny][nx] == 'W' || Map[ny][nx] == '.') {
						Map[ny][nx] = '*';
						rain.push({ ny, nx });
					}
				}
			}
		}

		while (rep_car--) {
			pos cur = car.front();
			car.pop();

			for (int i = 0; i < 4; i++) {
				int ny = cur.y + mv[i].y;
				int nx = cur.x + mv[i].x;

				if (ny >= 0 && ny < R && nx >= 0 && nx < C) {
					if (!check[ny][nx] && (Map[ny][nx] == '.' || Map[ny][nx] == 'H')) {
						check[ny][nx] = true;
						if (Map[ny][nx] == 'H') {
							success = true;
							break;
						}
						else {
							car.push({ ny, nx });
						}
					}
				}
			}
		}
		if (success || car.empty()) break;
	}

	if (success) cout << ans << '\n';
	else cout << "FAIL" << '\n';

	return 0;
}