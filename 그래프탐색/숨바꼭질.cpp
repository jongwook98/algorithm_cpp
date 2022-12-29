#include<iostream>
#include<deque>

using namespace std;

int check[100001];
deque<int> dq;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, K;
	cin >> N >> K;

	dq.push_front(N);
	check[N] = 1;

	int cur;
	while (!dq.empty() && !check[K]) {
		cur = dq.front();
		dq.pop_front();

		if (cur + 1 <= 100000 && !check[cur + 1]) {
			dq.push_back(cur + 1);
			check[cur + 1] = check[cur] + 1;
		}
		if (cur - 1 >= 0 && !check[cur - 1]) {
			dq.push_back(cur - 1);
			check[cur - 1] = check[cur] + 1;
		}
		if (cur * 2 <= 100000 && !check[cur * 2]) {
			dq.push_back(cur * 2);
			check[cur * 2] = check[cur] + 1;
		}
	}

	cout << check[K] - 1 << '\n';

	return 0;
}