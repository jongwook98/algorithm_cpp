#include<iostream>
#include<deque>

using namespace std;

typedef struct {
	int y, x;
}pos;

bool check_RGB[100][100];
bool check_RB[100][100];

char Map[100][100];
deque<pos> dq;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) cin >> Map[y][x];
	}

	int RGB = 0; int RB = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!check_RGB[y][x]) {
				dq.push_back({ y, x });
				check_RGB[y][x] = true;

				RGB++;

				while (!dq.empty()) {
					int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();
					char cur = Map[cy][cx];

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && !check_RGB[ny][nx]) {
							if (Map[ny][nx] == cur) {
								check_RGB[ny][nx] = true;
								dq.push_back({ ny, nx });
							}
						}
					}
				}
			}
			if (!check_RB[y][x]) {
				dq.push_back({ y, x });
				check_RB[y][x] = true;

				RB++;

				while (!dq.empty()) {
					int cy = dq.front().y; int cx = dq.front().x; dq.pop_front();
					char cur = Map[cy][cx];

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i]; int nx = cx + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && !check_RB[ny][nx]) {
							if (cur != 'B' && Map[ny][nx] != 'B') {
								check_RB[ny][nx] = true;
								dq.push_back({ ny, nx });
							}
							else if (cur == 'B' && Map[ny][nx] == 'B') {
								check_RB[ny][nx] = true;
								dq.push_back({ ny, nx });
							}
						}
					}
				}
			}
		}
	}

	cout << RGB << " " << RB << '\n';

	return 0;
}