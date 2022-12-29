#include<iostream>
#include<deque>
#include<cstring>
#include<algorithm>

using namespace std;

typedef struct {
	int y, x;
}pos;

deque<pos> dq;

bool check[300][300];
int Map[300][300];
int sub_Map[300][300];

int cnt;

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> Map[y][x];
		}
	}

	bool flag = true;

	while (flag) {
		cnt++;
		flag = false;

		memset(check, false, sizeof(check));
		memset(sub_Map, 0, sizeof(sub_Map));

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (!check[y][x] && Map[y][x] > 0) {

					if (flag) {
						cout << cnt - 1 << '\n';
						return 0;
					}
					else flag = true;

					check[y][x] = true;
					dq.push_back({ y, x });

					int cy, cx;
					while (!dq.empty()) {
						cy = dq.front().y; cx = dq.front().x;
						dq.pop_front();

						for (int i = 0; i < 4; i++) {
							int ny = cy + dy[i]; int nx = cx + dx[i];
							if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
								if (!check[ny][nx] && Map[ny][nx] > 0) {
									check[ny][nx] = true;
									dq.push_back({ ny, nx });
								}
								else if (Map[ny][nx] == 0) {
									sub_Map[cy][cx]++;
								}
							}
						}
					}
				}
			}
		}
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) Map[y][x] = max(0, Map[y][x] - sub_Map[y][x]);
		}
	}

	cout << '0' << '\n';

	return 0;
}