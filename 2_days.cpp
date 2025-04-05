// given in 2025 pro test1

#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(ll ind, ll days, ll &mini, ll as, ll bs, ll &asum, ll &bsum, ll &n, ll &m, vector<pair<ll, ll>> &v)
{
    if (ind == n)
    {
        ll total = asum + bsum * days;
        if (total - as - bs <= m)
        {
            mini = min(mini, days);
        }
        return;
    }
    solve(ind + 1, days + 1, mini, as + v[ind].second, bs + (v[ind].first) * (days + 1), asum, bsum, n, m, v);
    solve(ind + 1, days, mini, as, bs, asum, bsum, n, m, v);
}

int main()
{
    ll T;
    cin >> T;
    for (ll t = 1; t <= T; t++)
    {
        ll n, M;
        cin >> n >> M;
        vector<pair<ll, ll>> v;
        ll asum = 0, bsum = 0;
        for (ll i = 0; i < n; i++)
        {
            ll a, b;
            cin >> a >> b;
            v.push_back({b, a});
            asum += a;
            bsum += b;
        }
        sort(v.begin(), v.end());

        if (asum <= M)
        {
            cout << "#" << t << " " << 0 << "\n";
        }
        else
        {
            ll mini = INT_MAX;
            solve(0, 0, mini, 0, 0, asum, bsum, n, M, v);
            if (mini == INT_MAX)
            {
                mini = -1;
            }
            cout << "#" << t << " " << mini << "\n";
        }
    }
    return 0;
}

/*
Test - 2
You are in charge of maintaining inventory for a warehouse. You have an initial stock of goods given by an array A of size N.

Your day starts off by getting an inflow of goods given by another array B of size N (so the stock becomes A[i] = A[i]+B[i] for all i). 

After that, you can choose any one good, and export it, making its stock 0. Before you leave, you have to report the total stock of all items in the warehouse to the headquarters. 

Your task is to find the minimum number of days required to make the total stock of all items <= K, where K is given.
*/
