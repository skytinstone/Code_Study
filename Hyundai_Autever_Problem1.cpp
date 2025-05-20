//대표문제 1 : 강의실 배정
//N개의 강의가 주어질 때, 겹치지 않게 최대한 많은 강의를 배정하는 문제입니다.
//유형 : 그리디 알고리즘, 정렬
//풀이 포인트 : 종료 시간을 기준으로 정렬한 후, 이전 강의의 종료 시간보다 시작 시간이 크거나 같은 강의를 선택합니다. 

#include <iostream>
#include <vector>
using namespace std;

// 컨베이어 벨트 로봇 정렬 함수
int solution(int n, int m, const vector<vector<int>>& arms) {
    int cycle = 2 * (n - 1);

    for (int t = 0; t <= 10000; ++t) {
        for (int target = 1; target <= n; ++target) {
            bool all_match = true;

            for (int i = 0; i < m; ++i) {
                int start = arms[i][0];
                int dir = arms[i][1];
                int move = (dir == 1) ? t : (cycle - t % cycle) % cycle;
                int pos = start + ((dir == 1) ? move : -move);

                if (pos < 1) pos = 2 - pos;
                if (pos > n) pos = 2 * n - pos;

                if (pos != target) {
                    all_match = false;
                    break;
                }
            }

            if (all_match) return t;
        }
    }

    return -1;
}

// ✅ 예시 입력은 main 함수 안에 작성
int main() {
    // 예시 입력
    int n = 4;
    vector<vector<int>> arms = {
        {1, 1},
        {2, 1},
        {4, -1},
        {3, -1},
        {3, 1}
    };
    int m = arms.size();

    // solution 함수 호출 및 결과 출력
    int result = solution(n, m, arms);
    cout << "Result: " << result << endl;  // 예상 출력: 5

    return 0;
}
