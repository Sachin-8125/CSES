#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the number of possible game outcomes
long long solve(int n, int a, int b) {
  if (a == 0 && b == 0) return 1;
  if (a < 0 || b < 0) return 0;
  if (a > n || b > n) return 0;
  return solve(n, a - 1, b) + solve(n, a, b - 1);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, a, b;
    cin >> n >> a >> b;
    cout << solve(n, a, b) << endl;
  }
  return 0;
}