//Hyudnai_Autoeve_Problem_1 -> Alligning the Robot Arms in Coveyer Belts using the array code(Double Point)
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>

// arms_rows는 2차원 배열 arms의 행 길이, arms_cols는 2차원 배열 arms의 열 길이 입니다.
int solution(int n, int m, int** arms, size_t arms_rows, size_t arms_cols) {
    int cycle = 2 * (n - 1);

    for (int t = 0; t <= 10000; t++) {
        for (int target = 1; target <= n; target++) {
            int all_match = 1;

            for (int i = 0; i < m; i++) {
                int start = arms[i][0];
                int dir = arms[i][1];
                int move = (dir == 1) ? t : (cycle - t % cycle) % cycle;
                int pos = start + ((dir == 1) ? move : -move);

                if (pos < 1) pos = 2 - pos;
                if (pos > n) pos = 2 * n - pos;

                if (pos != target) {
                    all_match = 0;
                    break;
                }
            }

            if (all_match) return t;
        }
    }

    return -1;
}

int main() {
    int n = 4;
    int m = 5;

    // arms 배열 동적 생성
    int** arms = (int**)malloc(sizeof(int*) * m);
    arms[0] = (int[]){1, 1};
    arms[1] = (int[]){2, 1};
    arms[2] = (int[]){4, -1};
    arms[3] = (int[]){3, -1};
    arms[4] = (int[]){3, 1};

    int result = solution(n, m, arms, m, 2);
    printf("Result: %d\n", result); // 예상 출력: 5

    free(arms); // 동적 할당 해제 (주의: 배열 요소는 스택이므로 따로 해제 필요 없음)

    return 0;
}