#include <iostream>
#include <vector>
using namespace std;

vector<int> computeLPS(const string &pattern)
{
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0, i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int countSubstringKMP(const string &text, const string &pattern)
{
    if (pattern.empty())
        return 0;

    int n = text.length(), m = pattern.length();
    vector<int> lps = computeLPS(pattern);

    int i = 0, j = 0, count = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            count++;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return count;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str, sub;
    cin >> str >> sub;
    cout << countSubstringKMP(str, sub) << endl;

    return 0;
}