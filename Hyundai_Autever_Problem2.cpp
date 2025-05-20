//대표문제 1 : 강의실 배정
//N개의 강의가 주어질 때, 겹치지 않게 최대한 많은 강의를 배정하는 문제입니다.
//유형 : 그리디 알고리즘, 정렬
//풀이 포인트 : 종료 시간을 기준으로 정렬한 후, 이전 강의의 종료 시간보다 시작 시간이 크거나 같은 강의를 선택합니다. 

#include <vector>
#include <limits>
using namespace std;

vector<long long> solution(const vector<vector<int>>& outlet, const vector<vector<int>>& pipe) {
    const long long INF = 1e18;

    struct Point {
        long long x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Edge {
        int to;
        long long cost;
    };

    vector<Point> points;
    vector<vector<Edge>> graph;

    auto abs_ll = [](long long a) -> long long { return a < 0 ? -a : a; };

    auto get_point_index = [&](long long x, long long y) -> int {
        for (int i = 0; i < (int)points.size(); ++i)
            if (points[i].x == x && points[i].y == y) return i;
        points.push_back({x, y});
        graph.emplace_back();
        return (int)points.size() - 1;
    };

    auto add_edge = [&](int a, int b, long long cost) {
        graph[a].push_back({b, cost});
        graph[b].push_back({a, cost});
    };

    // 파이프 연결
    for (const auto& p : pipe) {
        int x1 = p[0], y1 = p[1], x2 = p[2], y2 = p[3];
        int a = get_point_index(x1, y1);
        int b = get_point_index(x2, y2);
        long long cost = abs_ll(x1 - x2) + abs_ll(y1 - y2);
        add_edge(a, b, cost);
    }

    int start = get_point_index(0, 0);

    // 다익스트라 (O(N^2))
    int n = (int)points.size();
    vector<long long> dist(n, INF);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
        }
        if (u == -1) break;
        visited[u] = true;

        for (auto& e : graph[u]) {
            if (dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
            }
        }
    }

    // 결과 저장
    vector<long long> answer;
    for (const auto& o : outlet) {
        int idx = get_point_index(o[0], o[1]);
        answer.push_back(dist[idx]);
    }

    return answer;
}

int main() {
    vector<vector<int>> outlet = {{2, 0}, {2, 2}};
    vector<vector<int>> pipe = {{0, 0, 2, 0}, {2, 0, 2, 2}};

    vector<long long> result = solution(outlet, pipe);

    for (auto d : result) {
        cout << d << " ";  // 2 4
    }
    cout << "\n";
}