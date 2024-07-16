// map 사용법, 분할 정복 개념을 이해하기 좋았던 문제.
// 스스로 해결 x
// 문제의 입력이 1,000,000,000,000,000,000까지 가능하기 때문에, long long으로 다룬다.
// 저만큼의 수를 선형으로 풀기에는 시간 초과를 예상할 수 있다.
// 탐색이 필요한 문제가 아니기에 분할 정복으로 문제를 해결해야 한다.
// 
// 저만큼의 수 제한은 2로 계속 분할하는 것 외에는 힘듦을 알 수 있다.
//
// F[2n] = F[n]x(2F[n-1] + F[n])
// F[2n + 1] = F[n + 1] ^ 2 + F[n] ^ 2
//
// F[n] = F[n/2]x(2F[n/2-1] + F[n/2])
// F[n] = F[(n + 1) / 2] ^ 2 + F[(n - 1) / 2] ^ 2

#include<iostream>
#include<map>

#define DIV 1000000007LL

using namespace std;

map<long long, long long> f;

long long fibo(long long n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 1;
	if (f.count(n) > 0) return f[n];

	if (n % 2 == 0) {
		long long m = n / 2;
		long long temp1 = fibo(m - 1); long long temp2 = fibo(m);
		f[n] = ((2LL * temp1 + temp2) * temp2) % DIV;
		return f[n];
	}
	long long m = (n + 1) / 2;
	long long temp1 = fibo(m); long long temp2 = fibo(m - 1);
	f[n] = (temp1 * temp1 + temp2 * temp2) % DIV;
	return f[n];
}

int main() {
	ios_base::sync_with_stdio(false);
	long long N;
	cin >> N;

	cout << fibo(N);

	return 0;
}