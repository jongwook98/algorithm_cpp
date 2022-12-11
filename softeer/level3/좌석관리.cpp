#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

// 빡센 구현, unordered_map

typedef struct {
	int y, x;
	bool ate;
}info;

bool check[21][21];
int score[21][21];

bool empty_p[21][21];

int place;
int init_place;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

unordered_map<int, info> um;
string str;

void find_empty_place(int id, int N, int M) {
	memset(score, 0, sizeof(score));

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			if (!check[y][x] && !empty_p[y][x]) {
				for (int cy = 1; cy <= N; cy++) {
					for (int cx = 1; cx <= M; cx++) {
						if (check[cy][cx]) {
							int deg = pow(y - cy, 2) + pow(x - cx, 2);
							if (score[y][x] == 0) score[y][x] = deg;
							else score[y][x] = min(score[y][x], deg);
						}
					}
				}
			}
		}
	}

	int ty, tx;
	int max_p = 0;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			if (!check[y][x]) {
				if (score[y][x] > max_p) {
					ty = y; tx = x;
					max_p = score[y][x];
				}
			}
		}
	}

	um[id] = { ty, tx, false };
	check[ty][tx] = true;
	cout << id << " gets the seat (" << ty << ", " << tx << ")." << '\n';
	init_place -= 1;
}

void in_com(int id, int N, int M) {
	if (um.find(id) != um.end()) {
		auto iter = um[id];
		if (iter.ate) cout << id << " already ate lunch." << '\n';
		else cout << id << " already seated." << '\n';
	}
	else {
		memset(empty_p, false, sizeof(empty_p));
		place = init_place;

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= M; x++) {
				if (check[y][x]) {
					for (int i = 0; i < 4; i++) {
						int ny = y + dy[i];
						int nx = x + dx[i];

						if (ny >= 1 && ny <= N && nx >= 1 && nx <= M) {
							if (!empty_p[ny][nx]) {
								empty_p[ny][nx] = true;
								place -= 1;
							}
						}
					}
				}
			}
		}

		if (place > 0) {
			if (place == N * M) {
				um[id] = { 1, 1, false };
				check[1][1] = true;
				init_place -= 1;
				cout << id << " gets the seat (1, 1)." << '\n';
			}
			else find_empty_place(id, N, M);
		}
		else cout << "There are no more seats." << '\n';
	}
}

void out_com(int id) {
	if (um.find(id) != um.end()) {
		auto iter = um[id];
		if (iter.ate) cout << id << " already left seat." << '\n';
		else {
			int y = iter.y;
			int x = iter.x;

			check[y][x] = false;
			init_place += 1;
			um[id] = { y, x, true };
			cout << id << " leaves from the seat (" << y << ", " << x << ")." << '\n';
		}
	}
	else cout << id << " didn't eat lunch." << '\n';
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, M, Q;
	cin >> N >> M >> Q;

	init_place = N * M; place = N * M;

	int id;
	while (Q--) {
		cin >> str >> id;
		if (str == "In") in_com(id, N, M);
		else if (str == "Out") out_com(id);
	}

	return 0;
}