#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

bool query(int i, int j)
{
    cout << "? " << i << " " << j << endl;
    string response;
    cin >> response;
    return response == "YES";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 1);
    stable_sort(indices.begin(), indices.end(), query);
    vector<int> ans(n + 1);
    for (int i = 0; i < n; ++i)
    {
        ans[indices[i]] = i + 1;
    }
    cout << "!";
    for (int i = 1; i <= n; ++i)
    {
        cout << " " << ans[i];
    }
    cout << endl;

    return 0;
}