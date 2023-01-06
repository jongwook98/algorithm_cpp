#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

// 가로 세로 N, M 으로 달랐다.. 이것 때문에 5번 틀림
// 문제 조건 잘 확인할 것

typedef struct {
	int y, x;
}pos;

queue<pos> q;

bool check[500][500];
int Map[500][500];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M;
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) cin >> Map[y][x];
	}

	int cnt = 0;
	int ans = 0;
	int temp;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (!check[y][x] && Map[y][x]) {
				temp = 1;
				cnt++;
				check[y][x] = true;
				q.push({ y, x });
				ans = max(ans, temp);
				while (!q.empty()) {
					int cy = q.front().y; int cx = q.front().x; q.pop();

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
							if (!check[ny][nx] && Map[ny][nx]) {
								check[ny][nx] = true;
								q.push({ ny, nx });
								temp++;
								ans = max(ans, temp);
							}
						}
					}
				}
				
			}
		}
	}

	cout << cnt << '\n' << ans << '\n';

	return 0;
}