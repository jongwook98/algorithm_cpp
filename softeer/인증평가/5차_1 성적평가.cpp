#include<iostream>
#include<queue>
#include<vector>

// 나의 풀이 생각
// 점수에 따른 등수 출력이므로 정렬을 하거나 priority_queue로 구현

using namespace std;

typedef struct {
	int sc, idx;
}score;

struct compare {
	bool operator()(score a, score b) {
		return a.sc < b.sc;
	}
};

priority_queue<score, vector<score>, compare> pq[4];
int total[100000];

queue<int> q;

int info[4][100000];

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	int sco;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < N; i++) {
			cin >> sco;
			pq[j].push({ sco, i });
			total[i] += sco;
		}
	}

	for (int i = 0; i < N; i++) {
		pq[3].push({ total[i], i });
	}

	int cnt;
	for (int j = 0; j < 4; j++) {
		int cur_sc = -1;
		int grade = 1;
		while (!pq[j].empty()) {
			score p;
			p = pq[j].top();
			pq[j].pop();
			if (cur_sc != p.sc) {
				cnt = q.size();
				while (!q.empty()) {
					int cur_idx = q.front();
					q.pop();
					info[j][cur_idx] = grade;
				}
				grade += cnt;
			}
			q.push(p.idx);
			cur_sc = p.sc;
		}
		while (!q.empty()) {
			int cur_idx = q.front();
			q.pop();
			info[j][cur_idx] = grade;
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < N; i++) {
			cout << info[j][i] << " ";
		}
		cout << '\n';
	}
	return 0;
}