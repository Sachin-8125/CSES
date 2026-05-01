#include<iostream>
#include<vector>
using namespace std;

#define ll long long
const int mod = 1e9 + 7;

vector<int> dp(5005);
vector<vector<int> > trie(1e6 + 5, vector<int>(26));
vector<bool> isEndOfWord(1e6 + 5);
int trieNodeCount = 0;

//function to insert the word in trie
void insertInTrie(string& word){
    int currNode = 0;
    for (char& ch : word) {
        if (!trie[currNode][ch - 'a'])
            trie[currNode][ch - 'a'] = ++trieNodeCount;
        currNode = trie[currNode][ch - 'a'];
    }
    isEndOfWord[currNode] = true;
}

//function to count no of ways
int countWays(int start, string& S){
    int currNode = 0, ways = 0;
    for (int i = start; i < S.size(); i++) {
        if (!trie[currNode][S[i] - 'a']) return ways;
        currNode = trie[currNode][S[i] - 'a'];
        if (isEndOfWord[currNode]) ways = (ways+dp[i+1])%mod; 
    }
    return ways;
}

//helper function
void solve(string& S, int K, string word[]){
    for(int i=0;i<K;i++){
        insertInTrie(word[i]);
    }
    dp[S.size()] = 1; //base case
    for(int i=S.size()-1; i>=0; i--){
        dp[i] = countWays(i, S);
    }
    cout<<dp[0];
}
int main(){
    string S;
    int K;
    cin>>S>>K;
    string arr[K];
    for(int i=0;i<K;i++){
        cin>>arr[i];
    }
    solve(S,K,arr);
    return 0;
}