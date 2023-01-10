#include<iostream>
#include<cstring>
#include<stack>

using namespace std;

int fol[100001];
bool check[100001];
bool check_dfs[100001];

int ans = 0;

stack<int> s;

void dfs(int st, int cur, int N) {

	if (!check_dfs[fol[cur]] && !check[fol[cur]]) {
		check_dfs[fol[cur]] = true;
		s.push(fol[cur]);
		dfs(st, fol[cur], N);
	}
	else if (check_dfs[fol[cur]] && !check[fol[cur]]) {
		int temp = fol[cur];
		bool flag = true;

		while (flag && !s.empty()) {
			check[s.top()] = true;
			if (s.top() == temp) flag = false;
			s.pop();
		}
	}
};

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		ans = 0;
		memset(fol, 0, sizeof(fol));
		memset(check, false, sizeof(check));
		memset(check_dfs, false, sizeof(check_dfs));
		while (!s.empty()) s.pop();

		for (int i = 1; i <= N; i++) cin >> fol[i];

		for (int i = 1; i <= N; i++) {
			if (!check[i]) {
				while (!s.empty()) s.pop();
				dfs(i, i, N);
			}
		}

		for (int i = 1; i <= N; i++) {
			if (!check[i]) ans++;
			else cout << " pass : " << i << '\n';
		}

		cout << ans << '\n';
	}


	return 0;
}