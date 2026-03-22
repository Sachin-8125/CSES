#include <iostream>
#include <cstdlib>

using namespace std;

int current_I = -1;

int do_reverse(int L, int R) {
    if (L >= R) return current_I;

    cout << L << " " << R << endl;
    
    int I;
    cin >> I;
    
    if (I == 0) exit(0);
    
    current_I = I;
    return I;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    cout << 1 << " " << 1 << endl;
    cin >> current_I;
    if (current_I == 0) return 0; 

    for (int i = 2; i <= n; ++i) {
        long long K = 1LL * i * (i - 1) / 2;
        int I_new = do_reverse(1, i);
        int I_curr = do_reverse(1, i); 
        
        long long delta_I = (long long)I_new - I_curr;
        int c = (K - delta_I) / 2;
        
        if (c > 0) {
            int k = i - c;
            do_reverse(k, i - 1);
            do_reverse(k, i);
        }
    }
    return 0;
}