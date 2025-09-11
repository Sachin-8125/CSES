#include <iostream>
using namespace std;

int main() {
    int low = 1, high = 1000000000;
    while (low < high) {
        int mid = low + (high - low) / 2;
        cout << "? " << mid << endl;
        cout.flush(); 
        string response;
        cin >> response; 
        response=="YES" ? low=mid+1 : high=mid;
    }
    cout << "! " << low << endl;
    cout.flush();
    return 0;
}
