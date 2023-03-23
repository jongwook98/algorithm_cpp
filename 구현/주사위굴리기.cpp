#include<iostream>
#include<vector>
#include<deque>

using namespace std;

int N, M;
int Y, X;

int Map[20][20];

int dy[] = { 0, 0, -1, 1 };
int dx[] = { 1, -1, 0, 0 };

//					  윗1 3 아래6 4  윗1 2 아래6 5
deque<int> dice[2] = { {0, 0, 0, 0}, {0, 0, 0, 0} };
vector<int> ord;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int K, ist;
	cin >> N >> M >> Y >> X >> K;

	for (int y = 0; y < N; y++) for (int x = 0; x < M; x++) cin >> Map[y][x];

	for (int i = 0; i < K; i++) {
		cin >> ist; ord.push_back(ist - 1);
	}

	for (int mv : ord) {
		int ny = Y + dy[mv]; int nx = X + dx[mv];
		if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
			if (mv == 0) {
				dice[0].push_front(dice[0].back()); dice[0].pop_back();
				dice[1][0] = dice[0][0]; dice[1][2] = dice[0][2];
			}
			else if (mv == 1) {
				dice[0].push_back(dice[0].front()); dice[0].pop_front();
				dice[1][0] = dice[0][0]; dice[1][2] = dice[0][2];
			}
			else if (mv == 2) {
				dice[1].push_front(dice[1].back()); dice[1].pop_back();
				dice[0][0] = dice[1][0]; dice[0][2] = dice[1][2];
			}
			else if (mv == 3) {
				dice[1].push_back(dice[1].front()); dice[1].pop_front();
				dice[0][0] = dice[1][0]; dice[0][2] = dice[1][2];
			}

			if (Map[ny][nx] == 0) {
				Map[ny][nx] = dice[0][2];
			}
			else {
				dice[0][2] = Map[ny][nx]; dice[1][2] = Map[ny][nx];
				Map[ny][nx] = 0;
			}

			cout << dice[0][0] << '\n';
			Y = ny; X = nx;
		}
	}

	return 0;
}