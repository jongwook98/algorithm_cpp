#include<iostream>
#include<deque>
#include<stack>

using namespace std;

int check[100001];
int from[100001];

deque<int> dq;
stack<int> s;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, K;
	cin >> N >> K;

	check[N] = 1;
	dq.push_back(N);

	while (!dq.empty() && check[K] == 0) {
		int cur = dq.front(); dq.pop_front();

		if (K > cur) {
			if (cur + 1 <= 100000 && check[cur + 1] == 0) {
				check[cur + 1] = check[cur] + 1;
				from[cur + 1] = cur;
				dq.push_back(cur + 1);
			}
			if (cur * 2 <= 100000 && check[cur * 2] == 0) {
				check[cur * 2] = check[cur] + 1;
				from[cur * 2] = cur;
				dq.push_back(cur * 2);
			}
			if (cur - 1 >= 0 && check[cur - 1] == 0) {
				check[cur - 1] = check[cur] + 1;
				from[cur - 1] = cur;
				dq.push_back(cur - 1);
			}
		}
		else if (cur - 1 >= 0 && check[cur - 1] == 0) {
			check[cur - 1] = check[cur] + 1;
			from[cur - 1] = cur;
			dq.push_back(cur - 1);
		}
	}

	int cur = K;
	s.push(cur);
	while (cur != N) {
		cur = from[cur];
		s.push(cur);
	}
	
	cout << check[K] - 1 << '\n';
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}

	return 0;
}