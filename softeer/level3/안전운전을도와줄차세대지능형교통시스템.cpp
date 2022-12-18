#include<iostream>
#include<deque>
#include<vector>

using namespace std;

typedef struct {
	int y, x, d, t; // d 들어온 방향
}info1;

typedef struct {
	int f_d, y, x, t_d; // f_d 들어온 방향, t_d 나가는 방향
}info2;

int Map[100][100][4];
bool check[100][100][5]; // 4는 통합해서 있었는지 // 0 ~ 3 각자 방향 이미 들어왔다면 들어가지 않도록

deque<info1> dq;
vector<info2> v[13];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);

	// 방향 0 N, 1 E, 2 S, 3 W
	v[1].push_back({ 1, -1, 0, 0 });
	v[1].push_back({ 1, 0, 1, 1 });
	v[1].push_back({ 1, 1, 0, 2 });

	v[2].push_back({ 0, 0, -1, 3 });
	v[2].push_back({ 0, -1, 0, 0 });
	v[2].push_back({ 0, 0, 1, 1 });

	v[3].push_back({ 3, 1, 0, 2 });
	v[3].push_back({ 3, 0, -1, 3 });
	v[3].push_back({ 3, -1, 0, 0 });

	v[4].push_back({ 2, 0, 1, 1 });
	v[4].push_back({ 2, 1, 0, 2 });
	v[4].push_back({ 2, 0, -1, 3 });

	// 방향 0 N, 1 E, 2 S, 3 W
	v[5].push_back({ 1, -1, 0, 0 });
	v[5].push_back({ 1, 0, 1, 1 });

	v[6].push_back({ 0, 0, -1, 3 });
	v[6].push_back({ 0, -1, 0, 0 });

	v[7].push_back({ 3, 1, 0, 2 });
	v[7].push_back({ 3, 0, -1, 3 });

	v[8].push_back({ 2, 0, 1, 1 });
	v[8].push_back({ 2, 1, 0, 2 });

	// 방향 0 N, 1 E, 2 S, 3 W
	v[9].push_back({ 1, 0, 1, 1 });
	v[9].push_back({ 1, 1, 0, 2 });

	v[10].push_back({ 0, -1, 0, 0 });
	v[10].push_back({ 0, 0, 1, 1 });

	v[11].push_back({ 3, 0, -1, 3 });
	v[11].push_back({ 3, -1, 0, 0 });

	v[12].push_back({ 2, 1, 0, 2 });
	v[12].push_back({ 2, 0, -1, 3 });

	int N, T;
	cin >> N >> T;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int t = 0; t < 4; t++) cin >> Map[y][x][t];
		}
	}

	dq.push_back({ 0, 0, 0, 0 });

	int ans = 0;

	check[0][0][0] = true;
	check[0][0][4] = true;
	info1 pos;

	//int y, x, d, t; // d 들어온 방향
	//int f_d, y, x, t_d; // f_d 들어온 방향, t_d 나가는 방향

	while (!dq.empty()) {
		pos = dq.front();

		//cout << pos.y << pos.x << pos.d << pos.t << '\n';

		dq.pop_front();
		int sign = Map[pos.y][pos.x][pos.t % 4];

		for (info2 iter : v[sign]) {
			if (pos.d == iter.f_d) {
				int ny = pos.y + iter.y;
				int nx = pos.x + iter.x;

				if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
					if (pos.t < T) {//!check[ny][nx][iter.t_d] && pos.t < T) { // 중복 방지를 위해서 들어가지 않도록 만들었는데
																			   // 해당 코드를 넣으면 에러 발생
																			   // !.중복 방지를 할 거 였다면 시간 % 4 까지 check를 했어야함.!
						dq.push_back({ ny, nx, iter.t_d, pos.t + 1 });
						check[ny][nx][iter.t_d] = true;
						check[ny][nx][4] = true;
					}
				}
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) if (check[y][x][4]) ans++;
	}

	cout << ans << '\n';

	return 0;
}