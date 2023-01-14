#include<iostream>
#include<deque>

using namespace std;

// deque구조에 들어온 시간을 측정하기 위해
// dq size를 계산하여 동일한 시간에 들어온 토마토를 처리하고
// 다음 하루가 지난것으로 하고 -> dq size 계산

typedef struct {
	int y, x;
}pos;

int Map[1000][1000];
int check[1000][1000];

deque<pos> dq;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int M, N;
	cin >> M >> N;

	int cnt = 0;
	int day = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int temp;
			cin >> temp;

			Map[y][x] = temp;

			if (temp == 1) {
				dq.push_back({ y, x });
				check[y][x] = 1;
			}
			else if(temp == 0) cnt++;
		}
	}

	while (!dq.empty() && cnt > 0) {
		int rep = dq.size();
		day++;

		while (rep--) {
			int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i]; int nx = cx + dx[i];

				if (ny >= 0 && ny < N && nx >= 0 && nx < M && check[ny][nx] == 0 && Map[ny][nx] == 0) {
					Map[ny][nx] = 1;
					cnt--;

					check[ny][nx] = check[cy][cx] + 1;
					dq.push_back({ ny, nx });
				}
			}
		}
	}

	if (cnt > 0) cout << -1 << '\n';
	else cout << day << '\n';

	return 0;
}