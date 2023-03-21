#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

vector<int> a;

bool check[5];
int arr[5];

int N = 3;

void permutation(int r, int cur) {
	if (r == 3) {
		for (int iter : a) cout << iter << " ";
		cout << '\n';
	}

	for (int i = cur; i < 5; i++) {
		if (check[i]) continue;

		check[i] = true;
		a.push_back(arr[i]);
		permutation(r + 1, cur + 1);
		a.pop_back();
		check[i] = false;
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	memset(check, false, sizeof(check));

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	permutation(0, 0);
}