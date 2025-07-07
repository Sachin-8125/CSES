#include <bits/stdc++.h>
using namespace std;

set<string> solve(string S){
    int N = S.length();
    sort(S.begin(), S.end());
    set<string> uniqueStrings;
    do {
        uniqueStrings.insert(S);
    } while (next_permutation(S.begin(), S.end()));
    return uniqueStrings;
}

int main(){
    string S;
    cin>>S;
    set<string> uniqueStrings = solve(S);
    cout << uniqueStrings.size() << "\n";
    for (string str : uniqueStrings) {
        cout << str << "\n";
    }
}
