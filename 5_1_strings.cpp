/*Test - 5 
Q1.
You are given an array of strings. You can merge two strings, arr[i] and arr[j], only if,
i < j  and the last letter of arr[i] == first letter of arr[j]
Eg, you have two strings -> “123” and “389” -> after merging it becomes “123389”
You can keep merging strings like this, but the ‘final’ string you form must be such that the first letter of the string should be the same as the last letter.
Eg, after merging several strings, the ‘final’ string becomes -> “123389…………1”
Print the max length of the ‘final’ string that can be formed in this way.
Test case - 1:
Array of strings = [“14”, “123”, “323”, “321”,  “421”, “535”]
Possible ‘final’ strings -> “323”, “535”, “14421”, “123323321”, “123321”
Ans = 9 (which is the length of “123323321”) 
Test case – 2:
Array of strings = [“14”, “15”, “89”, “22”]
Possible ‘final’ strings -> “22”
Ans = 2 (which is the length+ of “22”)
1 <= ai <=1e9.  1 <=N<= 1e5
/*
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mx = 1e5+1;
vector<string>v;
int n;
long long dp[mx][10][10];
long long solve(int i, int st, int end){
  if(i==n){
    return (st==end)?0:INT_MIN;
  }
  if(dp[i][st][end]!=-1) return dp[i][st][end];
  ll ans=solve(i+1, st, end);
  if(st==end) ans=max(ans, 0LL);
  if(v[i][0]-'0'==end) ans= max( ans, solve(i+1,st,v[i].back()-'0')+(int)v[i].size());
  return dp[i][st][end]=ans;
}
int main(){
  int t;cin>>t;
  while(t--){
    cin>>n;
    v.resize(n);
    memset(dp,-1,sizeof (dp));
    for(int i=0;i<n;i++)cin>>v[i];
    int ans = 0;
    for(int i=0;i<n;i++){
      ans=max((ll)ans,solve(i,v[i][0]-'0',v[i][0]-'0'));
    }
    cout<<ans<<endl;
  }
}
/*
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
int main() {
    fastio;
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<string> v(n);
        for (auto &s : v) cin >> s;
       
        vector<vector<ll>> mp(10, vector<ll>(10, 0));
       
        for (ll i = n - 1; i >= 0; i--) {
            int first = v[i][0] - '0', last = v[i].back() - '0';
            for (ll j = 0; j <= 9; j++) {
                if (mp[last][j] != 0) {
                    mp[first][j] = max(mp[first][j], mp[last][j] + (ll)v[i].length());
                }
            }
            mp[first][last] = max(mp[first][last], (ll)v[i].length());
        }
       
        ll res = 0;
        for (ll i = 0; i <= 9; i++) {
            res = max(res, mp[i][i]);
        }
       
        cout << res << "\n";
    }
    return 0;
}

*/
