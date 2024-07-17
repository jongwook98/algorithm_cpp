#include<iostream>
#include<algorithm>

using namespace std;

long long int mul(long long A, long long B, long long C) {
	if (B == 1) return A % C;

	long long int k = mul(A, B / 2, C) % C;

	if (B % 2 == 0) return k * k % C;
	else return k * k % C * A % C;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	long long int A, B, C;
	cin >> A >> B >> C;

	cout << mul(A, B, C);

	return 0;
}