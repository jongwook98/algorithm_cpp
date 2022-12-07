#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

struct compare {
	bool operator()(int a, int b) {
		return a < b;
	}
};

vector<int> v;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	unsigned long long B;
	cin >> N >> B;

	long long left = 1;
	long long right = 2000000000;

	int ai;
	for (int i = 0; i < N; i++) {
		cin >> ai;
		v.push_back(ai);
	}

	sort(v.begin(), v.end(), compare());

	int ans = 0;
	unsigned long long C;
	while (left <= right) {
		bool flag = false;
		C = 0;

		// !주의 : right, left 모두 최대가 될 때, int의 범위를 벗어나므로 long long으로 해야 해결됨,
		long long mid = (left + right) / 2;

		for (int i : v) {
			if (i >= mid) break;
			C += pow(mid - i, 2);
			if (C > B) {
				flag = true;
				break;
			}
		}

		if (flag) right = mid - 1;
		else {
			left = mid + 1;
			ans = mid;
		}
	}

	cout << ans << '\n';

	return 0;
}