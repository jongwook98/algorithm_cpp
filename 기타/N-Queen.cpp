// N queen 문제
// 이미 놓여진 퀸으로 놓을 수 없는 공간을 탐색해야함
// 해결 코드는 인터넷 보고 참고

#include<iostream>

using namespace std;

int N;
int cnt = 0;
int board[15];

// 놓을 수 있는 공간 탐색
int promising(int idx) {
	for (int i = 0; i < idx; i++) {
		if (board[idx] == board[i] || idx - i == abs(board[i] - board[idx])) {
			return 0;
		}
	}
	return 1;
}

// 위에서 부터 차례로 놓기 시작, 각 줄에 하나는 놓아야 하기 때문에
void nqueen(int idx) {

	if (idx == N) {
		cnt++;
		return;
	}

	for (int i = 0; i < N; i++) {
		board[idx] = i;
		if (promising(idx)) {
			nqueen(idx + 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	nqueen(0);
	cout << cnt;

	return 0;
}
