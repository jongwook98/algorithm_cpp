#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 이진 탐색

vector<long long> vc;
vector<long long> vd;

long long user_MAX(long long a, long long b) {
	if (a > b) return a;
	else return b;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, T;
	cin >> N >> T;

	int idx;
	long long left, right, mid, ans, cs, ds, pre = 0;

	bool flag;

	while (T--) {
		vc.clear(); vd.clear();

		cin >> cs;
		vc.push_back(cs);

		left = cs; right = cs;

		for (int i = 0; i < N - 1; i++) {
			cin >> ds >> cs;
			vd.push_back(ds);
			vc.push_back(cs);

			left = min(left, cs);
			right = max(right, cs + ds);
		}

		ans = 0;
		while (left <= right) {
			flag = false;
			idx = 0;
			pre = 0;
			mid = (left + right) / 2;

			for (long long c : vc) {
				if (idx == 0) {
					if (c - mid < 0 && mid - c > vd[idx]) {
						flag = true;
						break;
					}
				}
				else if (idx == N - 1) {
					if (c - mid < 0 && mid - c > vd[idx - 1] - pre) {
						flag = true;
						break;
					}
				}
				else {
					if (c - mid < 0 && mid - c > vd[idx - 1] - pre + vd[idx]) {
						flag = true;
						break;
					}
				}
				if (idx == 0) pre = user_MAX(0, mid - c);
				else pre = user_MAX(0, mid - c - (vd[idx - 1] - pre));

				idx++;
			}
			if (flag) right = mid - 1;
			else {
				left = mid + 1;
				ans = mid;
			}
		}

		cout << ans << '\n';
	}

	return 0;
}