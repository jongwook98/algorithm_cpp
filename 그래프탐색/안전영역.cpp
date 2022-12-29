#include<iostream>
#include<deque>
#include<algorithm>
#include<cstring>

using namespace std;

typedef struct {
	int y, x;
}pos;

deque<pos> dq;

int Map[101][101];
int ans = 1;

bool check[101][101];

int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> Map[y][x];
		}
	}

	for (int h = 1; h < 100; h++) {
		
		memset(check, false, sizeof(check));
		int cnt = 0;

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (!check[y][x] && Map[y][x] > h) {
					cnt++;
					check[y][x] = true;
					dq.push_back({ y, x });

					while (!dq.empty()) {
						int cy = dq.front().y; int cx = dq.front().x;
						dq.pop_front();
						for (int i = 0; i < 4; i++) {
							int ny = cy + dy[i]; int nx = cx + dx[i];
							if (ny >= 1 && ny <= N && nx >= 1 && nx <= N) {
								if (!check[ny][nx] && Map[ny][nx] > h) {
									check[ny][nx] = true;
									dq.push_back({ ny, nx });
								}
							}
						}
					}
				}
			}
		}

		if (cnt == 0) break;
		ans = max(ans, cnt);
	}

	cout << ans << '\n';

	return 0;
}