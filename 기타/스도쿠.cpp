// 처음 푼 풀이
// 30분, 2168KB, 1228ms
// set으로 조건을 확인하지 않고
// bool 형식으로 확인하면 더 빠른가? => 약 10배 빠름

/*
#include<iostream>
#include<string>
#include<set>
#include<vector>

using namespace std;

int Map[9][9];

set<int> col[9];
set<int> row[9];
set<int> squ[3][3];

vector<pair<int, int>> v;

void solve(int idx) {
	if (idx == v.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << Map[i][j];
			}
			cout << '\n';
		}

		exit(0);
	}

	int y = v[idx].first; int x = v[idx].second;

	for (int i = 1; i <= 9; i++) {
		if (row[y].count(i) > 0 || col[x].count(i) > 0 || squ[y / 3][x / 3].count(i) > 0) continue;
		
		row[y].insert(i);
		col[x].insert(i);
		squ[y / 3][x / 3].insert(i);

		Map[y][x] = i;

		solve(idx + 1);

		squ[y / 3][x / 3].erase(i);
		col[x].erase(i);
		row[y].erase(i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str;

	for (int i = 0; i < 9; i++) {
		getline(cin, str);
		int j = 0, num;
		for (char iter : str) {
			num = iter - '0';
			Map[i][j] = num;
			
			if (num > 0) {
				col[j].insert(num);
				row[i].insert(num);
				squ[i / 3][j / 3].insert(num);
			}
			else {
				v.push_back({ i, j });
			}
			j++;
		}
	}

	solve(0);

	return 0;
}
*/

// 2024 KB, 156ms

#include<iostream>
#include<string>
#include<vector>

using namespace std;

int Map[9][9];
bool check[27][10];

vector<pair<int, int>> v;

void solve(int idx) {
	if (idx == v.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << Map[i][j];
			}
			cout << '\n';
		}
		exit(0);
	}

	int y = v[idx].first; int x = v[idx].second;

	for (int i = 1; i <= 9; i++) {
		if (check[y][i] == true || check[9 + x][i] == true || check[18 + (y / 3) * 3 + x / 3][i] == true) continue;

		check[y][i] = true;
		check[9 + x][i] = true;
		check[18 + (y / 3) * 3 + x / 3][i] = true;

		Map[y][x] = i;

		solve(idx + 1);

		check[y][i] = false;
		check[9 + x][i] = false;
		check[18 + (y / 3) * 3 + x / 3][i] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str;

	for (int i = 0; i < 9; i++) {
		getline(cin, str);
		int j = 0, num;
		for (char iter : str) {
			num = iter - '0';
			Map[i][j] = num;

			if (num > 0) {
				check[i][num] = true;
				check[9 + j][num] = true;
				check[18 + (i / 3) * 3 + j / 3][num] = true;
			}
			else {
				v.push_back({ i, j });
			}
			j++;
		}
	}

	solve(0);

	return 0;
}