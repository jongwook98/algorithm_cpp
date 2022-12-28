#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool check[101];
bool scheck[101];
bool fin[101];

vector<int> v[101];
vector<int> ans;
vector<int> fin_ans;

int arr[101];

void dfs(int N, int cur) {

	for (int iter : v[cur]) {
		//cout << "cur : " << cur << " iter : " << iter << '\n';
		if (!scheck[iter] && !check[cur]) {
			//cout << "pass" << '\n';
			check[cur] = true;
			scheck[iter] = true;
			ans.push_back(iter);

			dfs(N, iter);

			ans.pop_back();
			scheck[iter] = false;
			check[cur] = false;
		}
	}	
	if (ans.size() > 0) {
		for (int i = 1; i <= N; i++) {
			if (check[i] != scheck[i]) return;
		}
		for (int iter : ans) {
			if (!fin[iter]) {
				fin_ans.push_back(iter);
				check[iter] = true;
				scheck[iter] = true;
				fin[iter] = true;
				//cout << iter << " ";
			}
		}
		//cout << '\n';
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int comp;
	for (int i = 1; i <= N; i++) {
		cin >> comp;
		v[comp].push_back(i);
	}
	for (int i = 1; i <= N; i++) {
		if (!v[i].empty() && !check[i]) dfs(N, i);
	}

	//for (int iter : fin_ans) cout << iter << '\n';

	sort(fin_ans.begin(), fin_ans.end());
	cout << fin_ans.size() << '\n';
	for (int iter : fin_ans) cout << iter << '\n';

	return 0;
}