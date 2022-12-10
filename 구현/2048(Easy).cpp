#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct {
	int y, x;
}point;

int init_Map[20][20];
int game_Map[20][20];

int ans;

vector<int> v;

void move(int N, int dir) {

	/*
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) cout << game_Map[y][x] << " ";
		cout << '\n';
	}
	cout << '\n';
	*/

	if (dir == 0) {
		for (int y = 0; y < N; y++) {
			int cur = 0;
			int place = N - 1;
			for (int x = N - 1; x > -1; x--) {
				if (cur == 0 && game_Map[y][x] != 0) cur = game_Map[y][x];
				else if (cur != 0 && cur == game_Map[y][x]) {
					game_Map[y][place--] = cur * 2;
					game_Map[y][x] = 0;
					cur = 0;
				}
				else if (cur != 0 && game_Map[y][x] != 0) {
					game_Map[y][place--] = cur;
					cur = game_Map[y][x];
				}
			}
			if (cur != 0) game_Map[y][place--] = cur;

			for (int x = place; x > -1; x--) game_Map[y][x] = 0;
		}
	}
	if (dir == 1) {
		for (int x = 0; x < N; x++) {
			int cur = 0;
			int place = N - 1;
			for (int y = N - 1; y > -1; y--) {
				if (cur == 0 && game_Map[y][x] != 0) cur = game_Map[y][x];
				else if (cur != 0 && cur == game_Map[y][x]) {
					game_Map[place--][x] = cur * 2;
					game_Map[y][x] = 0;
					cur = 0;
				}
				else if (cur != 0 && game_Map[y][x] != 0) {
					game_Map[place--][x] = cur;
					cur = game_Map[y][x];
				}
			}
			if (cur != 0) game_Map[place--][x] = cur;

			for (int y = place; y > -1; y--) game_Map[y][x] = 0;
		}
	}
	if (dir == 2) {
		for (int y = 0; y < N; y++) {
			int cur = 0;
			int place = 0;
			for (int x = 0; x < N; x++) {
				if (cur == 0 && game_Map[y][x] != 0) cur = game_Map[y][x];
				else if (cur != 0 && cur == game_Map[y][x]) {
					game_Map[y][place++] = cur * 2;
					game_Map[y][x] = 0;
					cur = 0;
				}
				else if (cur != 0 && game_Map[y][x] != 0) {
					game_Map[y][place++] = cur;
					cur = game_Map[y][x];
				}
			}
			if (cur != 0) game_Map[y][place++] = cur;

			for (int x = place; x < N; x++) game_Map[y][x] = 0;
		}
	}
	if (dir == 3) {
		for (int x = 0; x < N; x++) {
			int cur = 0;
			int place = 0;
			for (int y = 0; y < N; y++) {
				if (cur == 0 && game_Map[y][x] != 0) cur = game_Map[y][x];
				else if (cur != 0 && cur == game_Map[y][x]) {
					game_Map[place++][x] = cur * 2;
					game_Map[y][x] = 0;
					cur = 0;
				}
				else if (cur != 0 && game_Map[y][x] != 0) {
					game_Map[place++][x] = cur;
					cur = game_Map[y][x];
				}
			}
			if (cur != 0) game_Map[place++][x] = cur;

			for (int y = place; y < N; y++) game_Map[y][x] = 0;
		}
	}
}

void play(int N) {
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) game_Map[y][x] = init_Map[y][x];
	}

	for (int dir : v) {
		move(N, dir);
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			ans = max(ans, game_Map[y][x]);
		}
	}
}

void dfs(int N) {
	if (v.size() > 4) return play(N);

	for (int i = 0; i < 4; i++) {
		v.push_back(i);
		dfs(N);
		v.pop_back();
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> init_Map[y][x];
		}
	}

	dfs(N);

	cout << ans << '\n';

	return 0;
}