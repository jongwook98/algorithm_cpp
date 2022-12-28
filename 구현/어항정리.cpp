#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

int bowl[101][101];
int b_copy[101][101];

int minval;

int dy;
int dx;
int cx;
int nx;

int cnt;
int ans;

int K;

vector<int> v;

void first(int N);
void rotate(int N);
void second(int N, bool check);
void arrange(int N, bool check);
void third(int N);

void third(int N) {
	if (cnt >= 2) {
		cnt = 0;
		second(N, true);
		return;
	}
	if (cnt == 0) {
		for (int y = 1; y <= dy; y++) {
			for (int x = cx; x < cx + dx; x++) {
				bowl[dy * 2 - y + 1][N - x + 1] = bowl[y][x];
				bowl[y][x] = 0;
			}
		}
	}
	else if (cnt == 1) {
		for (int y = 1; y <= dy; y++) {
			for (int x = cx; x < cx + dx; x++) {
				bowl[dy * 2 - y + 1][N + (cx - x)] = bowl[y][x];
				bowl[y][x] = 0;
			}
		}
	}
	cx += dx;
	dy *= 2;
	dx /= 2;

	/*for (int y = 8; y >= 1; y--) {
		for (int x = 1; x <= 8; x++) cout << bowl[y][x] << " ";
		cout << '\n';
	}*/
	cnt++;
	third(N);
}

void arrange(int N, bool check) {
	int idx = 1;
	for (int x = cx; x <= N; x++) {
		for (int y = 1; y <= dy; y++) {
			if (bowl[y][x] == 0) break;
			bowl[1][idx++] = bowl[y][x];
			if (y != 1) bowl[y][x] = 0;
		}
	}
	//for (int x = 1; x <= N; x++) cout << bowl[1][x] << " ";
	//cout << '\n';

	dy = 1;
	dx = N / 2;
	cx = 1;
	nx = N;

	if (check == false)	third(N);
	else {
		v.clear();

		int MAX = 0, MIN = 100000;
		for (int x = 1; x <= N; x++) {
			if (x == 1) minval = bowl[1][x];
			else if (minval > bowl[1][x]) {
				v.clear();
				minval = bowl[1][x];
			}
			if (minval == bowl[1][x]) v.push_back(x);
			MAX = max(MAX, bowl[1][x]);
			MIN = min(MIN, bowl[1][x]);
		}
		if (MAX - MIN <= K) {
			cout << ans << '\n';
			return;
		}
		else first(N);
	}
	
}

void second(int N, bool check) {
	//cout << "cx : " << cx << " dx : " << dx << " dy : " << dy << " nx : " << nx << '\n';
	memset(b_copy, 0, sizeof(b_copy));
	for (int y = 1; y <= dy; y++) {
		for (int x = cx; x <= N; x++) {
			b_copy[y][x] = bowl[y][x];
		}
	}

	int temp;

	/*for (int y = 8; y >= 1; y--) {
		for (int x = 1; x <= 8; x++) cout << bowl[y][x] << " ";
		cout << '\n';
	}*/

	for (int y = 1; y <= dy; y++) {
		for (int x = cx; x <= N; x++) {
			if (b_copy[y][x] == 0) continue;

			if (b_copy[y][x + 1] != 0 && abs(b_copy[y][x] - b_copy[y][x + 1]) >= 5) {
				temp = int(abs(b_copy[y][x] - b_copy[y][x + 1]) / 5);
				if (b_copy[y][x] > b_copy[y][x + 1]) {
					bowl[y][x] -= temp;
					bowl[y][x + 1] += temp;
				}
				else {
					bowl[y][x + 1] -= temp;
					bowl[y][x] += temp;
				}
			}
			if (b_copy[y + 1][x] != 0 && abs(b_copy[y][x] - b_copy[y + 1][x]) >= 5) {
				temp = int(abs(b_copy[y][x] - b_copy[y + 1][x]) / 5);
				if (b_copy[y][x] > b_copy[y + 1][x]) {
					bowl[y][x] -= temp;
					bowl[y + 1][x] += temp;
				}
				else {
					bowl[y + 1][x] -= temp;
					bowl[y][x] += temp;
				}
			}
		}
	}
	
	/*for (int y = 8; y >= 1; y--) {
		for (int x = 1; x <= 8; x++) cout << bowl[y][x] << " ";
		cout << '\n';
	}*/

	arrange(N, check);
}

void rotate(int N) {
	if (nx > N) {
		second(N, false);
		return;
	}

	for (int y = 1; y <= dy; y++) {
		for (int x = cx; x < cx + dx; x++) {
			bowl[dx - (x - cx) + 1][cx + dx + y - 1] = bowl[y][x];
			bowl[y][x] = 0;
		}
	}

	cx += dx;
	if (dy == dx) dy += 1;
	else dx += 1;
	nx += dy;
	
	rotate(N);
}

void first(int N) {
	ans++;
	for (int idx : v) bowl[1][idx] += 1;

	dy = 1;
	dx = 1;
	nx = 2;
	cx = 1;

	rotate(N);
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N >> K;

	int cur;
	for (int i = 1; i <= N; i++) {
		cin >> cur;
		if (minval == 0) minval = cur;
		else if (minval > cur) {
			v.clear();
			minval = cur;
		}
		bowl[1][i] = cur;
		if (minval == cur) v.push_back(i);
	}

	first(N);

	return 0;
}