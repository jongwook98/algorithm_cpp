// map으로 문제 해결

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

int N, M;
map<vector<int>, int> m;
vector<int> v;
vector<int> ans;

bool check[9];

void dfs(int size) {
	if (size == M) {
		if (m.count(ans) > 0) {
			return;
		}
		else {
			for (int iter : ans) {
				cout << iter << " ";
			}
			cout << '\n';
			m[ans] = 1;
		}
	}
	
	int idx = 0;
	for (int iter : v) {
		if (check[idx] == false) {
			check[idx] = true;
			ans.push_back(iter);
			dfs(size + 1);
			ans.pop_back();
			check[idx] = false;
		}
		idx++;
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int A;
	for (int i = 0; i < N; i++) {
		cin >> A;
		v.push_back(A);
	}

	sort(v.begin(), v.end());

	dfs(0);


	return 0;
}