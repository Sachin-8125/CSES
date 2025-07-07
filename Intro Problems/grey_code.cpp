#include <bits/stdc++.h>
using namespace std;

vector<string> graycode(int n) {
    if (n == 1) {
        return {"0", "1"};
    }
    vector<string> prevGrayCode = graycode(n - 1);
    vector<string> reversedPrevGrayCode = prevGrayCode;
    reverse(reversedPrevGrayCode.begin(), reversedPrevGrayCode.end());
    int prevSize = prevGrayCode.size();
    int index = 0;
    while (index < prevSize) {
        string appendedZero = "0" + prevGrayCode[index];
        prevGrayCode[index] = "1" + reversedPrevGrayCode[index];
        prevGrayCode.push_back(appendedZero);
        index++;
    }
    return prevGrayCode;
}

int main() {
    int n;
    cin>>n;
    vector<string> res = graycode(n);
    for (auto code : res)
        cout << code << "\n";
    return 0;
}
