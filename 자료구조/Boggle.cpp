// 반례가 생각 안나는 문제
// 인터넷 반례들은 맞는데 10%에서 틀
// 소요시간 4h

#include<iostream>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<vector>

using namespace std;
int ans_sum = 0;
int ans_num = 0;

int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char board[4][4];
bool check[4][4];

string ret;

set<vector<char>> set_ch;

int getpoint(int idx) {
	if (idx < 3) return 0;
	else if (idx < 5) return 1;
	else if (idx == 5) return 2;
	else if (idx == 6) return 3;
	else if (idx == 7) return 5;
	else return 11;
}

struct Trie {
	map<char, pair<Trie*, int>> mm;

	void insert(vector<char>& v, int idx) {
		if (v.size() == idx) {
			if (mm.find('&') == mm.end()) {
				Trie* trie = new Trie;
				mm.insert({ '&', {trie, getpoint(idx)} });
			}
			return;
		}
		if (mm.find(v[idx]) == mm.end()) {
			Trie* trie = new Trie;
			mm.insert({ v[idx], {trie, 0} });
		}
		mm[v[idx]].first->insert(v, idx + 1);
	}

	Trie* search(vector<char>& ch_v, char c) {
		if (mm.find(c) != mm.end()) {
			ch_v.push_back('&');
			if (mm[c].first->mm.find('&') != mm[c].first->mm.end() && (set_ch.find(ch_v) == set_ch.end())) {
				//for (char c : ch_v) cout << c << " ";
				//cout << '\n';
				ans_num += 1;
				ans_sum += mm[c].first->mm['&'].second;
				set_ch.insert(ch_v);

				if (ret.size() <= ch_v.size()) {
					string temp;
					for (char c : ch_v) temp += c;
					if (ret.size() < ch_v.size()) ret = temp;
					else if (temp < ret) ret = temp;
				}
			}
			ch_v.pop_back();
			return mm[c].first;
		}
		return nullptr;
	}

	void debug(int d) {
		for (auto& i : mm) {
			cout << d << " : " << i.first << '\n';
			i.second.first->debug(d + 1);
		}
	}
};


void dfs(Trie* trie, vector<char>& ch_v, int y, int x) {
	for (int d = 0; d < 8; d++) {
		Trie* next;

		int ny = y + dy[d]; int nx = x + dx[d];
		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4 && !check[ny][nx]) {
			ch_v.push_back(board[ny][nx]);
			next = trie->search(ch_v, board[ny][nx]);
			if (next != nullptr) {
				check[ny][nx] = true;
				dfs(next, ch_v, ny, nx);
				check[ny][nx] = false;
			}
			ch_v.pop_back();
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	cin.ignore();

	string str;
	Trie* root = new Trie;

	for (int i = 0; i < n; i++) {
		getline(cin, str);
		vector<char> v(str.size());

		int j = 0;
		for (char ch : str) v[j++] = ch;

		root->insert(v, 0);
	}
	getline(cin, str);

	int b;
	cin >> b;
	cin.ignore();

	//root->debug(0);
	while (b--) {
		ans_num = 0;
		ans_sum = 0;
		for (int i = 0; i < 4; i++) {
			getline(cin, str);
			int j = 0;
			for (char ch : str) board[i][j++] = ch;
		}

		set_ch.clear();
		ret.clear();

		vector<char> ch_v;
		memset(check, false, sizeof(check));

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				Trie* trie;

				ch_v.push_back(board[y][x]);
				trie = root->search(ch_v, board[y][x]);

				if (trie != nullptr) {
					check[y][x] = true;
					dfs(trie, ch_v, y, x);
					check[y][x] = false;
				}
				ch_v.pop_back();
			}
		}
		*(ret.end() - 1) = NULL;
		cout << ans_sum << " " << ret << " " << ans_num << '\n';

		if (b > 0) getline(cin, str);
	}
	return 0;
}