#include <bits/stdc++.h>
using namespace std;
void solve();
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.setf(ios::fixed);
    cout.precision(10);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
void solve()
{
    int n;
    cin >> n;

    map<int, vector<int>> mp;
    int maxm = 0;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;

        maxm = max(maxm, r);
        maxm = max(maxm, l);
        if (l != 0)
        {
            mp[l].push_back(i);
        }
        if (r != 0)
        {
            mp[r].push_back(i);
        }
    }
    // cout<<((int)mp[maxm].size())<<endl;
    // cout<<(mp[maxm][0])<<endl;
    vector<int> count(maxm + 1, 0);
    for (auto &it : mp)
    {
        auto v = it.second;
        sort(v.begin(), v.end());
        int sz = (int)v.size();
        int ans = 1;
        for (int i = 1; i < sz; i++)
        {
            ans += (v[i] - v[i - 1]);
            ans++;
        }
        count[it.first] = ans;
        // debug(it.first,ans);
    }
    // cout<<maxm<<endl;
    // cout<<mp[maxm][0]<<endl;
    vector<vector<int>> dp(maxm + 1, vector<int>(n + 2, -1));

    auto f = [&](int l, int pos, auto &&f)->int
    {
        if (l == 0)
        {
            return abs(pos - n);
        }

        if (dp[l][pos] != -1)
            return dp[l][pos];
        int left = mp[l][0];
        int sz = (int)mp[l].size();
        int right = mp[l][sz - 1];
        // debug(left,right,l);
        cout<<left<<" "<<right<<" "<<l<<" "<<pos<<endl;
        int res = abs(pos - left) + count[l] + f(l - 1, right, f);
        res = min(res, abs(pos - right) + count[l] + f(l - 1, left, f));

        return dp[l][pos] = res;
    };

    int ans = f(maxm, 0, f);

    cout << ans << endl;
}
/*
#include <bits/stdc++.h>
using namespace std;
int f(int l, int pos, auto& dp, auto& mp, int n, auto& count){
    if(l==0)return (n-pos);
    if(dp[l][pos]!=-1)return dp[l][pos];
    int left = mp[l][0];
    int sz = (int)mp[l].size();
    int right = mp[l][sz-1];
    int res=abs(pos-left)+count[l]+f(l-1,right,dp,mp,n,count);
    res=min(res,abs(pos-right)+count[l]+f(l-1,left,dp,mp,n,count));
    return dp[l][pos]=res;
}
int main(){
    int n;cin>>n;
    map<int,vector<int>>mp;
    int maxi=0;
    for(int i=0;i<n;i++){
        int l,r;cin>>l>>r;
        maxi=max({maxi,l,r});
        if(l!=0)mp[l].push_back(i);
        if(r!=0)mp[r].push_back(i);
    }
    vector<int>count(maxi+1,0);
    for(auto &x:mp){
        auto v=x.second;
        sort(v.begin(),v.end());
        int ans=int(v.size());
        for(int i=1;i<v.size();i++){
            ans+=v[i]-v[i-1];
        }
        count[x.first]=ans;
    }
    vector<vector<int>>dp(maxi+1,vector<int>(maxi+1,-1));
    int ans=f(maxi,0, dp, mp, n, count);
    cout<<ans<<endl;
    return 0;
}
*/