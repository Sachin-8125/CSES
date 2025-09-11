#include <bits/stdc++.h>
using namespace std;

// Function to solve the problem
void solve(vector<long long>& arr, long long X, long long N) {
    vector<vector<long long>> vec(N, vector<long long>(2));
    for (int i = 0; i < N; i++) {
        vec[i] = arr[i];
        vec[i][1] = i + 1;
    }

    sort(vec.begin(), vec.end());

    for (long long ptr1 = 0; ptr1 < N - 2; ptr1++) {
        long long ptr2 = ptr1 + 1;
        long long ptr3 = N - 1;

        while (ptr2 < ptr3) {
            long long currentSum = vec[ptr1] + vec[ptr2] + vec[ptr3];
            if (currentSum == X) {
                cout << vec[ptr1][1] << " " << vec[ptr2][1] << " " << vec[ptr3][1] << "\n";
                return;
            }
            else if (currentSum > X) {
                ptr3--;
            }
            else {
                ptr2++;
            }
        }
    }
    cout << "IMPOSSIBLE";
}

int main() {
    long long N, X;
    cin >> N >> X;
    vector<long long> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];
    solve(arr, X, N);
    return 0;
}