//Hyundai_Autoever_Problem_2 -> Checking the cross point between several pipes of the water tower
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Outlet_rows는 2차원 배열의 outlet의 행 길이, outlet_rows의 행 길이, outlet_cols는 2차원 배열 outlet의 열 길이.
//pipe_rows는 2차원 배열의 pipe의 행 길이, pipe_cols는 2차원 배열의 pipe의 열 길이.

long long* solution(int** outlet, size_t outlet_rows, size_t outlet_cols, int** pipe, size_t pipe_rows, size_t pipe_cols)
{
    #define MAX_POINTS 3000
    #define INF 1000000000000000000LL

    typedef struct {
        long long x, y;
    } Point;

    typedef struct {
        int to;
        long long cost;
    } Edge;

    Point points[MAX_POINTS];
    int point_count = 0;

    Edge graph[MAX_POINTS][10];
    int edge_count[MAX_POINTS] = {0};

    long long dist[MAX_POINTS];
    bool visited[MAX_POINTS];

    // 절댓값 함수
    long long abs_ll(long long a) {
        return a < 0 ? -a : a;
    }

    // 좌표 같은지 체크
    bool same_point(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }

    // 좌표 배열에 추가 및 인덱스 반환
    int get_point_index(long long x, long long y) {
        for (int i = 0; i < point_count; ++i) {
            if (points[i].x == x && points[i].y == y) return i;
        }
        points[point_count].x = x;
        points[point_count].y = y;
        return point_count++;
    }

    // 간선 추가 (양방향)
    void add_edge(int a, int b, long long cost) {
        graph[a][edge_count[a]++] = (Edge){b, cost};
        graph[b][edge_count[b]++] = (Edge){a, cost};
    }

    // 다익스트라 알고리즘 (O(N^2))
    void dijkstra(int start) {
        for (int i = 0; i < point_count; ++i) {
            dist[i] = INF;
            visited[i] = false;
        }
        dist[start] = 0;

        for (int i = 0; i < point_count; ++i) {
            int u = -1;
            for (int j = 0; j < point_count; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                    u = j;
            }

            if (u == -1) break;
            visited[u] = true;

            for (int k = 0; k < edge_count[u]; ++k) {
                int v = graph[u][k].to;
                long long cost = graph[u][k].cost;
                if (dist[v] > dist[u] + cost)
                    dist[v] = dist[u] + cost;
            }
        }
    }

    // 파이프 데이터로 그래프 구성
    for (int i = 0; i < pipe_rows; ++i) {
        int x1 = pipe[i][0], y1 = pipe[i][1], x2 = pipe[i][2], y2 = pipe[i][3];
        int a = get_point_index(x1, y1);
        int b = get_point_index(x2, y2);
        long long cost = abs_ll(x1 - x2) + abs_ll(y1 - y2);
        add_edge(a, b, cost);
    }

    // 시작점 (0,0)
    int start = get_point_index(0, 0);

    dijkstra(start);

    // 결과 배열 동적 할당
    long long* answer = (long long*)malloc(sizeof(long long) * outlet_rows);

    // 각 배출구까지 거리 조회
    for (int i = 0; i < outlet_rows; ++i) {
        int x = outlet[i][0];
        int y = outlet[i][1];
        int idx = get_point_index(x, y);
        answer[i] = dist[idx];
    }
    return answer;
}