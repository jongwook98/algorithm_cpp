#include<iostream>
#include<deque>

using namespace std;

// 이동할 수 있는 칸의 범위가 10^9 이므로
// 더 이상 이동할 수 없을 때 break 시키는 조건이 있어야 시간초과가 나지 않는다

typedef struct {
	int y, x;
}pos;

char Map[1000][1000];
deque<pos> dq[10];

int rep[10];
int dqsize[10];
int ans[10];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, P;
	cin >> N >> M >> P;

	for (int idx = 1; idx <= P; idx++) cin >> rep[idx];

	int blank = 0;
	char temp;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> temp;
			Map[y][x] = temp;
			if (temp == '.') blank++;
			else if (temp >= '1' && temp <= '9') {
				dq[temp - '0'].push_back({ y, x });
				ans[temp - '0']++;
			}
		}
	}

	bool flag = true;
	while (flag && blank > 0) {
		flag = false;
		for (int idx = 1; idx <= P; idx++) {
			for (int r = 0; r < rep[idx]; r++) {
				dqsize[idx] = dq[idx].size();
				if (dqsize[idx] == 0) break;

				while (dqsize[idx]--) {
					int cy = dq[idx].front().y; int cx = dq[idx].front().x; dq[idx].pop_front();
					char cur = idx + '0';

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] == '.') {
							Map[ny][nx] = cur;
							dq[idx].push_back({ ny, nx });
							ans[idx]++;
							blank--;

							flag = true;
						}
					}
				}
			}
		}
	}

	for (int idx = 1; idx <= P; idx++) cout << ans[idx] << " ";
	cout << '\n';

	return 0;
}