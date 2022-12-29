#include<iostream>
#include<deque>

using namespace std;

deque<int> dq;
int check[1000001];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int F, S, G, U, D;
	cin >> F >> S >> G >> U >> D;

	dq.push_back(S);
	check[S] = 1;

	int cur;
	while (!dq.empty() && !check[G]) {
		cur = dq.front();
		dq.pop_front();

		if (cur + U <= F && !check[cur + U]) {
			dq.push_back(cur + U);
			check[cur + U] = check[cur] + 1;
		}
		if (cur - D >= 1 && !check[cur - D]) {
			dq.push_back(cur - D);
			check[cur - D] = check[cur] + 1;
		}
	}

	if (!check[G]) cout << "use the stairs" << '\n';
	else cout << check[G] - 1 << '\n';

	return 0;
}