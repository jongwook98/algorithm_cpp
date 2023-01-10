#include<iostream>
#include<string>
#include<deque>

using namespace std;

// 주어진 문제 조건 확실히 확인하고 코드 작성할 때 한번에 잘 하기

// 시작 칸 -> 끝 칸 동일할 수 있음,, 시작 칸 끝 칸 포함해서 세야함
// 불가능 할 대 -1 출력

typedef struct {
	int y, x;
	int f;
}pos;

char Map[1000][1000];
int check[1000][1000][2];

string str;

deque<pos> dq;

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
		cin >> str;
		int idx = 0;
		for (char ch : str) Map[y][idx++] = ch;
	}

	if (N == 1 && M == 1) {
		cout << 1 << '\n';
		return 0;
	}

	dq.push_back({ 0, 0, false });
	check[0][0][0] = 1;

	while (!dq.empty()) {
		int cy = dq.front().y; int cx = dq.front().x; int able = dq.front().f;
		dq.pop_front();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i]; int nx = cx + dx[i];

			if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (ny == N - 1 && nx == M - 1) {
					cout << check[cy][cx][able] + 1 << '\n';
					return 0;
				}
				else if (check[ny][nx][able] == 0 && Map[ny][nx] == '0') {
					check[ny][nx][able] = check[cy][cx][able] + 1;
					dq.push_back({ ny, nx, able });
				}
				else if (able == 0 && Map[ny][nx] == '1') {
					check[ny][nx][1] = check[cy][cx][0] + 1;
					dq.push_back({ ny, nx, 1 });
				}
			}
		}
	}

	cout << -1 << '\n';

	return 0;
}