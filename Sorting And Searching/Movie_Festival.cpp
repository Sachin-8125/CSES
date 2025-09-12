#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<pair<int, int>>& movies, int N) {
    sort(movies.begin(), movies.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second < p2.second;  // Compare based on ending time
    });
    int timeElapsed = 0, moviesWatched = 0;
    for (int i = 0; i < N; i++) {
        if (movies[i].first >= timeElapsed) {
            moviesWatched++;
            timeElapsed = movies[i].second;  
        }
    }
    return moviesWatched;
}
int main() {
    int N;
    cin>>N;
    vector<pair<int, int>> movies(N);
    for(int i=0;i<N;i++){
        cin>>movies[i].first>>movies[i].second;
    }
    cout << solve(movies, N) << endl;
    return 0;
}
