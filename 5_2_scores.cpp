/*
Q2. 
2 arrays given
a = [1, 2, 3, 4, 5]
b = [6, 7, 8, 9, 10]
Value of an array is the total score of elements, 
and score of element is 1 if it is less than or equal to D and 2 if it is greater than D, 
Find D such that A_score - B_Score is maximum
 
constraints -
0 <= D <= 1e9
1 <= a[i] <= 1e8
1 <= b[i] <= 1e8
1 <= a.size(), b.size() <= 1e5

*/

#include <bits/stdc++.h>
using namespace std;
int maxDiffD(const vector<int> &a, const vector<int> &b)
{
    vector<int> sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    set<int> s;
    for (int x : sa)s.insert(x);
    for (int x : sb)s.insert(x);

    vector<int> c;
    c.push_back(*s.begin() - 1);
    for (int x : s)
        c.push_back(x);
    c.push_back(*s.rbegin() + 1);

    int mx = INT_MIN, bestD = 0;
    for (int d : c)
    {
        int ca = upper_bound(sa.begin(), sa.end(), d) - sa.begin();
        int cb = upper_bound(sb.begin(), sb.end(), d) - sb.begin();

        int as = ca + (sa.size() - ca) * 2;
        int bs = cb + (sb.size() - cb) * 2;

        int diff = as - bs;
        if (diff > mx)
        {
            mx = diff;
            bestD = d;
        }
    }
    return bestD;
}
int main()
{
    int t;cin >> t;
    while (t--){
        int n, m;cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++)cin >> a[i];
        for (int i = 0; i < m; i++)cin >> b[i];
        cout << "Optimal D: " << maxDiffD(a, b) << endl;
    }
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n; 
    
    vector<int> a(n), b(n), all;
    
    for(int i = 0; i<n; i++) cin>>a[i], all.push_back(a[i]);
    for(int i = 0; i<n; i++) cin>>b[i], all.push_back(b[i]);
    
    int m = all.size();
    
    int ans = 0;
    
    for(int i = 0; i<m; i++){
        int x, y;
        int val1 = upper_bound(a.begin(), a.end(), all[i]) - a.begin();
        int val2 = upper_bound(b.begin(), b.end(), all[i]) - b.begin();
        
        if(val1 == n) x = 0;
        else x = n + 1 - val1;
        
        if(val2 == n) y = 0;
        else y = n + 1 - val2;
        
        // cout<<all[i]<<" : "<<x<<" "<<y<<endl;
        
        ans = max(ans, x - y);
    }
    cout<<ans<<endl;
    return 0;
}
*/
