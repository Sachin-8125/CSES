#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    // DFS to verify if the string can be cleanly partitioned with a specific candidate removed
    bool canPartition(int index, const string& s, unordered_set<int>& required, int max_len) {
        if (index == s.length()) {
            return required.empty();
        }
        
        // Numbers from 1 to N don't have leading zeros
        if (s[index] == '0') return false; 

        int num = 0;
        // Try extracting numbers of different lengths (1 digit, 2 digits, etc.)
        for (int i = index; i < s.length() && (i - index + 1) <= max_len; ++i) {
            num = num * 10 + (s[i] - '0');
            
            if (required.count(num)) {
                required.erase(num); // "Use" this number
                
                if (canPartition(i + 1, s, required, max_len)) {
                    return true;
                }
                
                required.insert(num); // Backtrack
            }
        }
        return false;
    }

public:
    int findMissingNumber(int n, string s) {
        // Step 1: Count expected vs. actual digit frequencies
        vector<int> counts(10, 0);
        
        // Count what we SHOULD have
        for (int i = 1; i <= n; ++i) {
            int temp = i;
            while (temp > 0) {
                counts[temp % 10]++;
                temp /= 10;
            }
        }

        // Subtract what we ACTUALLY have
        for (char c : s) {
            counts[c - '0']--;
        }

        // Step 2: Collect the exact missing digits
        vector<int> missing_digits;
        for (int i = 0; i < 10; ++i) {
            while (counts[i] > 0) {
                missing_digits.push_back(i);
                counts[i]--;
            }
        }

        // Step 3: Generate all valid permutations of the missing digits
        vector<int> candidates;
        sort(missing_digits.begin(), missing_digits.end());
        
        do {
            if (missing_digits[0] == 0) continue; // No leading zeros
            
            int num = 0;
            for (int d : missing_digits) {
                num = num * 10 + d;
            }
            // Candidate must be within the valid range
            if (num > 0 && num <= n) {
                candidates.push_back(num);
            }
        } while (next_permutation(missing_digits.begin(), missing_digits.end()));

        // Remove duplicates (e.g., if missing digits are 2 and 2, permutation generates 22 twice)
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        // Step 4: The Optimization (Bypasses DFS entirely for single candidates)
        if (candidates.size() == 1) {
            return candidates[0]; 
        }

        // Step 5: If multiple candidates exist (like 12 and 21), verify with DFS
        int max_len = to_string(n).length();
        for (int cand : candidates) {
            unordered_set<int> required;
            for (int i = 1; i <= n; ++i) {
                if (i != cand) required.insert(i);
            }

            // If the string cleanly parses using this candidate as the missing one, we found it
            if (canPartition(0, s, required, max_len)) {
                return cand;
            }
        }

        return -1; // Fallback, though standard inputs will return inside the loop
    }
};

int main() {
    Solution sol;
    
    int n1 = 10;
    string s1 = "1098253471";
    cout << "Missing number for N=" << n1 << " is: " << sol.findMissingNumber(n1, s1) << "\n";
    // Expected Output: 6
    
    return 0;
}