#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int count_steps(long long x, long long y) {
    int steps = 0;
    while (x != 1 || y != 1) {
        if (x > y) {
            if (y == 1) {
                steps += (x - 1);
                break;
            }
            steps += x / y;
            x %= y;
        } else {
            if (x == 1) {
                steps += (y - 1);
                break;
            }
            steps += y / x;
            y %= x;
        }
    }
    return steps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    int target_sum = n + 2;
    int min_steps = 1e9;
    int best_x = -1;
    
    for (int x = 1; x <= target_sum / 2; ++x) {
        if (gcd(x, target_sum) == 1) {
            int y = target_sum - x;
            int steps = count_steps(x, y);
            if (steps < min_steps) {
                min_steps = steps;
                best_x = x;
            }
        }
    }
    
    int x = best_x;
    int y = target_sum - x;
    string path = "";
    
    while (x != 1 || y != 1) {
        if (x > y) {
            if (y == 1) {
                path.append(x - 1, '0');
                break;
            }
            path.append(x / y, '0');
            x %= y;
        } else {
            if (x == 1) {
                path.append(y - 1, '1');
                break;
            }
            path.append(y / x, '1');
            y %= x;
        }
    }
    
    reverse(path.begin(), path.end());
    cout << path << "\n";
    
    return 0;
}