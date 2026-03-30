#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Movie {
    int start, end;
    bool operator<(const Movie& other) const {
        if (end == other.end) return start < other.start;
        return end < other.end;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<Movie> movies(n);
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].start >> movies[i].end;
    }

    sort(movies.begin(), movies.end());

    multiset<int> end_times;
    for (int i = 0; i < k; ++i) {
        end_times.insert(0);
    }

    int max_movies = 0;

    for (int i = 0; i < n; ++i) {
        auto it = end_times.upper_bound(movies[i].start);
        
        if (it != end_times.begin()) {
            --it; 
            end_times.erase(it);
            end_times.insert(movies[i].end);  
            max_movies++;
        }
    }

    cout << max_movies << "\n";
    return 0;
}