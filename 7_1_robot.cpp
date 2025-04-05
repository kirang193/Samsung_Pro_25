// Given an array where each index i contains garbage value.

// - Deploying a robot at any index costs 'm'.
// - A robot can clean garbage at its current index and move only to i+1.
// - At any moment, the cost is the sum of remaining uncleaned garbage.

// Find the minimum cost to clean all garbage, allowing any number of robots to be deployed at any index.

// 3 1 4 1 5 
// m = 2 -> 8

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mx=1e5+1;
ll dp[20][mx];
ll m,n,i;
vector<long long> A;
ll solve(int in, int l){
    if(in==n)return 0;
    if(dp[in][l]!=-1)return dp[in][l];
    dp[in][l]=min((ll)m+solve(in+1,in),(ll)(in-l)*A[in]+solve(in+1,l));
    return dp[in][l];
}
int main() {
    n = 20;
    m = 100;
    A={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1};
    memset(dp,-1,sizeof(dp));
    for(i=0;i<n;i++){
        if(A[i]!=0){break;}
    }
    if(i==n){
        cout<<0<<endl;
    }else{
        ll ans= m + solve(i+1,i);
        cout << ans << "\n";
    }
    return 0;
}
//ans=m+f(i+1,i)
//f(in,l)
/*
    if(in==n)return 0;
    if(dp[in][l]!=-1)return dp[in][l];
    dp[in][l]=min((ll)m+solve(in+1,in),(in-l)*A[in]+solve(in+1,l));
    return dp[in][l];
*/