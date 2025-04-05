/*
The Korea Expressway Corporation is planning to expand the road where the volume of traffic is high.
In order to expand the road, all of the roadside trees planted nearby the road have to be chopped down.
To do the course of action, they should rent a logging robot which is developed by Samsung Electronics.
However, the rental fee of the logging robot is obviously high due to its high production cost.
Thus, the development of an operation software which allows logging trees within the shortest time is needed.

The logging robot has following features:

1.The logging robot can move forward and backward. And to get moved by 1, it takes 1 minute.

2.The roadside trees to the left or right can be cut and loaded which requires 1 minute.

3.Trees can be loaded in the order of their cut. Also only a tree which length is shorter or equal in length to the previous one can be loaded. (refer to Fig.1)

4.If there are trees on both sides such as to the left and right, without moving each can be cut and loaded by following the third requirement (above).

5.The logging robot can load infinite number of trees.

The information of the road to expand is as follows:

The road is given as a straight line with a length of N. The first point of the road is the starting point (point 0) and the last point (where N is located) is the ending point.

1.On each side of the road there will be one tree at most after every 1 unit length with varying lengths (it is possible that there is no tree)

2.On both sides to the starting and ending point there are no trees planted.

3.The logging robot starts moving from the starting point, chops down all trees along the way, transport them and it reaches the ending point.

Suppose a road with N=5 as demonstrated in [Fig.2] is given.

The beginning part of the road 0 is the starting point of the robot and 5 the ending point.
The logging robot moves forward, backward, chops down all trees on the left, right side of the road, transports them and must reach point 5.

The logging robot can move as follows:

=>
Point0 -> Point3 (chops down tree with a length of 3)
-> Point4 (chops down tree with a length of 2)
-> Point2 (chops down tree with a length of 2)
-> Point4 (chops down tree with a length of 1)
-> Point5 (moves to the ending point)
The total time is 13 minutes. (time needed to chop down: 4 minutes, time needed to move: 9 minutes)
However, if the robot follows the moves as given below, the total time becomes 11 minutes and the rental fee can be reduced.

=>
Point0 -> Point3 (chops tree with a length of 3)
-> Point2 (chops down tree with a length of 2)
-> (Standing still) (chops down tree with a length of 1)
-> Point4 (chops down tree with a length of 2)
-> Point5 (moves to the ending point)
(time needed to chop down: 4 minutes, time needed to move: 7 minutes)

Given the information of the road, write a program that finds the minimum time (in minute unit) that is needed in order to chop down all trees along the way from the starting to the end point.

The correct answer in [Fig.2] is 11.

Constraints:

The length of the road N is given as an integer that is greater than or equal to 5 and less than or equal to 1,000. (5 ≤ N ≤ 1,000)

On each side of the road there is one tree at most after every 1 unit length (it is possible that there is no tree)

The length of a tree L is given as an integer that is greater than or equal to 1 and less than or equal to 1,000. (1 ≤ L ≤ 1,000)

The starting point of the logging robot is given as point 0 on the map and the ending point as N.

There are no trees on both sides of the starting and ending point.

There is no situation where there are no trees at all on the road.
*/

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
