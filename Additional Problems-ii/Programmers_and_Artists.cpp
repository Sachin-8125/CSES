#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Applicant {
    long long x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, n;
    if (!(cin >> a >> b >> n)) return 0;

    vector<Applicant> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
    }

    sort(v.begin(), v.end(), [](const Applicant& A, const Applicant& B) {
        return (A.x - A.y) > (B.x - B.y);
    });

    vector<long long> pref(n + 1, 0);
    priority_queue<long long, vector<long long>, greater<long long>> pq_a;
    long long sum_a = 0;
    
    for (int i = 0; i < n; i++) {
        if (a > 0) {
            pq_a.push(v[i].x);
            sum_a += v[i].x;
            if (pq_a.size() > a) {
                sum_a -= pq_a.top();
                pq_a.pop();
            }
        }
        if (pq_a.size() == a) {
            pref[i + 1] = sum_a;
        }
    }

    vector<long long> suff(n + 1, 0);
    priority_queue<long long, vector<long long>, greater<long long>> pq_b;
    long long sum_b = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (b > 0) {
            pq_b.push(v[i].y);
            sum_b += v[i].y;
            if (pq_b.size() > b) {
                sum_b -= pq_b.top();
                pq_b.pop();
            }
        }
        if (pq_b.size() == b) {
            suff[i] = sum_b;
        }
    }

    long long max_skill = 0;
    for (int i = a; i <= n - b; i++) {
        max_skill = max(max_skill, pref[i] + suff[i]);
    }

    cout << max_skill << "\n";
    return 0;
}