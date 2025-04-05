// Problem Statement:
// A company issues gift certificates with unique serial numbers (numeric only).
// The digit sum of all serial numbers issued on the same day is S.
// Given A (max serial number) and S, find how many valid serial numbers exist.

// Constraints:
// 1 <= A < 10^100  (A can be very large)
// 1 <= S <= 1000    (Digit sum limit)

// Output:
// Return the count of valid serial numbers modulo 10^9 + 7.

// Example Cases:
// A = 101, S = 3 → Answer: 4  (Valid: 21, 12, 3, 30)
// A = 172, S = 3 → Answer: 7  (Valid: 3, 12, 21, 30, 102, 111, 120)
// A = 50, S = 4  → Answer: 5  (Valid: 4, 40, 13, 31, 22)
// A = 999, S = 500 → Answer: 0 (Max digit sum is 27, so no valid numbers)

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int solve(int pos, int remSum, bool tight, const string &A, vector<vector<vector<int>>> &dp) {
    if (remSum < 0) return 0;  // If remaining sum is negative, return 0
    if (pos == A.size()) return remSum == 0;  // Check if sum is exactly S

    if (dp[pos][remSum][tight] != -1) return dp[pos][remSum][tight];

    int limit = tight ? (A[pos] - '0') : 9;
    int ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        ans = (ans + solve(pos + 1, remSum - digit, tight && (digit == limit), A, dp)) % MOD;
    }

    return dp[pos][remSum][tight] = ans;
}

int main() {
    string A;
    int S;
    cin >> A >> S;

    int n = A.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(S + 1, vector<int>(2, -1)));

    cout << solve(0, S, 1, A, dp) << endl;
    return 0;
}
/*
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MOD = 1e9 + 7;

int dp[101][1001]; // Memoization DP array

int digitDP(const string &A, int pos, bool tight, int sum) {
    if (sum < 0) return 0; 
    if (pos == A.size()) return sum == 0;

    if (!tight && dp[pos][sum] != -1) return dp[pos][sum];

    int limit = tight ? (A[pos] - '0') : 9, result = 0;
    for (int d = 0; d <= limit; d++) 
        result = (result + digitDP(A, pos + 1, tight && (d == limit), sum - d)) % MOD;

    return tight ? result : (dp[pos][sum] = result);
}

int countValidSerials(const string &A, int S) {
    if (S > A.size() * 9) return 0; // Early exit if S is too large
    memset(dp, -1, sizeof(dp));
    return digitDP(A, 0, true, S);
}

int main() {
    string A;
    int S;
    cin >> A >> S;
    cout << countValidSerials(A, S) << endl;
    return 0;
}

*/

//solve(A,0,1,S)
// if(S<=0)return 0;
//if(i==A.size())return S==0;
//if(!tight && dp[i][S]!=-1)return dp[i][S]
// int limit=(tight?(A[i]-'0'):9),result=0;
// for(int d=0;d<=limit;d++){
//  result=(result+solve(A,i+1,tigit&&(d==limit),sum-d))%mod;
//}return tight?result:(dp[i][S]=result);

/*
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int s; 
string A; 
int helper(int pos, int sum, int tight, vector<vector<vector<int>>>& dp){
    // base 
    if(pos == A.length()){
        if(sum == s) return 1;
        else return 0;
    }
    if(dp[pos][sum][tight] != -1) return dp[pos][sum][tight];
    int res = 0, limit = 9;
    // transition
    if(tight == 1){limit = A[pos] - '0';}
    for(int i = 0; i <= limit; i++)
        res += (helper(pos + 1, sum + i, tight && (i == limit), dp) % mod);
    return dp[pos][sum][tight] = res % mod;
}

int main(){
    cin>>s;
    cin>>A;
    vector<vector<vector<int>>> dp(101, vector<vector<int>>(901, vector<int>(2, -1)));
    int ans = helper(0, 0, 1, dp);
    cout<<ans<<endl;
    return 0;
}*/