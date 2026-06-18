#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    if (!(cin >> s)) return 0;
    
    string ans = "";
    set<char> st;
    
    for (char c : s) {
        st.insert(c);
        if (st.size() == 4) {
            ans += c;
            st.clear();
        }
    }
    
    if (st.find('A') == st.end()) ans += 'A';
    else if (st.find('C') == st.end()) ans += 'C';
    else if (st.find('G') == st.end()) ans += 'G';
    else ans += 'T';
    
    cout << ans << "\n";
    
    return 0;
}
