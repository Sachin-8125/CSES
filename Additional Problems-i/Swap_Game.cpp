#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

const vector<pair<int, int>> moves = {
    {0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8}, 
    {0, 3}, {3, 6}, {1, 4}, {4, 7}, {2, 5}, {5, 8}
};

unordered_map<string, int> dist;

void bfs() {
    string start = "123456789";
    queue<string> q;
    
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        
        int d = dist[curr];
        
        for (auto& p : moves) {
            string next_state = curr;
            swap(next_state[p.first], next_state[p.second]);
            
            if (dist.find(next_state) == dist.end()) {
                dist[next_state] = d + 1;
                q.push(next_state);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    bfs();
    
    string target = "";
    for (int i = 0; i < 9; ++i) {
        char c;
        cin >> c;
        target += c;
    }
    
    cout << dist[target] << "\n";
    
    return 0;
}