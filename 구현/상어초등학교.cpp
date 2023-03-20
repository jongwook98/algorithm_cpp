#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

typedef struct {
	int score;
	int empty;
	int y;
	int x;
}info;

struct compare {
	bool operator()(info a, info b) {
		if (a.score != b.score) return a.score < b.score;
		if (a.empty != b.empty) return a.empty < b.empty;
		if (a.y != b.y) return a.y > b.y;
		return a.x > b.x;
	}
};

int stu[401][4];
int Map[20][20];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int ans = 0;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	memset(Map, 0, sizeof(Map));

	int N;
	cin >> N;

	int num, a, b, c, d;

	for (int i = 0; i < N * N; i++) {
		cin >> num >> a >> b >> c >> d;
		stu[num][0] = a; stu[num][1] = b; stu[num][2] = c; stu[num][3] = d;

		priority_queue<info, vector<info>, compare> pq;

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (Map[y][x] != 0) continue;

				int score = 0, empty = 0;

				for (int j = 0; j < 4; j++) {
					int ny = y + dy[j]; int nx = x + dx[j];

					if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
						if (Map[ny][nx] == 0) empty++;
						if (Map[ny][nx] == a || Map[ny][nx] == b || Map[ny][nx] == c || Map[ny][nx] == d) score++;
						pq.push({ score, empty, y, x });
					}
				}
			}
		}

		auto iter = pq.top();
		Map[iter.y][iter.x] = num;
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			int cur = Map[y][x];
			int score = 0;

			for (int j = 0; j < 4; j++) {
				int ny = y + dy[j]; int nx = x + dx[j];

				if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
					int nur = Map[ny][nx];
					if (nur == stu[cur][0] || nur == stu[cur][1] || nur == stu[cur][2] || nur == stu[cur][3]) score++;
				}
			}
			if (score > 0) ans += pow(10, score - 1);
		}
	}
	cout << ans << '\n';
}