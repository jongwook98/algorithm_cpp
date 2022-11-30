#include<iostream>
#include<string>
#include<vector>

using namespace std;

typedef struct {
	int y, x;
}pos;

typedef struct {
	char L, R;
}pa;

vector<pa> v;

pos hh[25];
string str1;
string str2;

char code[5][5];
bool alpha[25];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	getline(cin, str1, '\n');
	getline(cin, str2, '\n');

	int idx = 0;
	int y, x;
	int to_i;

	for (char ch : str2) {
		to_i = ch - 'A';
		if (to_i > 9) to_i -= 1;
		if (!alpha[to_i]) {
			alpha[to_i] = true;
			y = idx / 5;
			x = idx % 5;
			code[y][x] = ch;
			hh[to_i] = { y, x };
			idx += 1;
		}
	}

	for (char ch = 'A'; ch <= 'Z'; ch++) {
		to_i = ch - 'A';
		if (to_i == 9) continue;
		else if (to_i > 9) to_i -= 1;

		if (!alpha[to_i]) {
			alpha[to_i] = true;
			y = idx / 5;
			x = idx % 5;
			code[y][x] = ch;
			hh[to_i] = { y, x };
			idx += 1;
		}
	}



	char pair[2]; idx = 0;
	for (char ch : str1) {
		if (idx == 0) {
			pair[idx++] = ch;
			pair[1] = 'A' - 1;
		}
		else if (pair[0] == ch) {
			if (ch == 'X') pair[1] = 'Q';
			else pair[1] = 'X';
			v.push_back({ pair[0], pair[1] });

			pair[0] = ch; pair[1] = 'A' - 1;
		}
		else {
			pair[idx] = ch;
			v.push_back({ pair[0], pair[1] });
			idx = 0;
		}
	}

	if (pair[1] == 'A' - 1) {
		pair[1] = 'X';
		v.push_back({ pair[0], pair[1] });
	}

	string ans;
	pos yx1, yx2;
	for (pa ch : v) {
		to_i = ch.L - 'A';
		if (to_i > 9) to_i -= 1;
		yx1 = hh[to_i];

		to_i = ch.R - 'A';
		if (to_i > 9) to_i -= 1;
		yx2 = hh[to_i];

		if (yx1.y == yx2.y) {
			ans += code[yx1.y][(yx1.x + 1) % 5];
			ans += code[yx2.y][(yx2.x + 1) % 5];
		}
		else if (yx1.x == yx2.x) {
			ans += code[(yx1.y + 1) % 5][yx1.x];
			ans += code[(yx2.y + 1) % 5][yx2.x];
		}
		else {
			ans += code[yx1.y][yx2.x];
			ans += code[yx2.y][yx1.x];
		}
	}

	cout << ans << '\n';

	return 0;
}