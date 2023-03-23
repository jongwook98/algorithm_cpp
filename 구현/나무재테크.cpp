#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

int N;

int Map[10][10];
int addMap[10][10];

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

typedef struct {
	int y, x;
	int age;
}info;

vector<info> tree;
vector<info> newtree;
vector<info> dead_tree;

bool compare(info a, info b) {
	return a.age < b.age;
}

void spring() {
	for (info t : tree) {
		if (Map[t.y][t.x] < t.age) {
			dead_tree.push_back(t);
		}
		else {
			Map[t.y][t.x] -= t.age;
			newtree.push_back({ t.y, t.x, t.age + 1 });
		}
	}

	tree.clear();
	for (info t : newtree) tree.push_back(t);
	newtree.clear();
}

void summer() {
	for (info t : dead_tree) {
		Map[t.y][t.x] += int(t.age / 2);
	}
	dead_tree.clear();
}

void fall() {
	for (info t : tree) {
		if (t.age % 5 == 0) {
			for (int i = 0; i < 8; i++) {
				int ny = t.y + dy[i]; int nx = t.x + dx[i];

				if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
					newtree.push_back({ ny, nx, 1 });
				}
			}
		}
	}
	for (info t : tree) newtree.push_back(t);
	tree.clear();

	for (info t : newtree) tree.push_back(t);
	newtree.clear();
}

void winter() {
	for (int y = 0; y < N; y++) for (int x = 0; x < N; x++) Map[y][x] += addMap[y][x];
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int M, K;
	cin >> N >> M >> K;

	for (int x = 0; x < N; x++) for (int y = 0; y < N; y++) {
		Map[y][x] = 5;
		cin >> addMap[y][x];
	}

	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		tree.push_back({ y - 1, x - 1, z });
	}

	sort(tree.begin(), tree.end(), compare);
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}

	cout << tree.size() << '\n';

	return 0;
}