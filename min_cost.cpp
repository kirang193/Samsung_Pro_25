#include <bits/stdc++.h>
using namespace std;
 
#define ll                   long long int
#define sdefine              string s; cin>>s;
#define vll                  vector<ll>
#define pll                  pair<ll,ll>
#define vvll                 vector<vll>
#define vpll                 vector<pll>
#define mll                  map<ll,ll>
#define pb                   push_back
#define ppb                  pop_back
#define ff                   first
#define ss                   second
#define set_bits(a)          __builtin_popcountll(a)
#define sz(x)                ((int)(x).size())
#define all(x)               (x).begin(), (x).end()
#define forl(i,a,b)          for(int i=a;i<b;i++)
#define yesno(x,y)           if (x==y) cout<<"YES"<<endl; else cout<<"NO"<<endl;
#define endl                 "\n"
#define display(a,x,y)       { for (int i=x;i<y;i++) cout<<a[i]<<" "; cout<<endl; }
// #define int                  long long
#define IOS                  std::cin.tie(nullptr)->sync_with_stdio(false);
const int MAXN=2E5+1;
vector<ll>values(MAXN);
vector<ll>g[MAXN];
vector<ll>subtree_sum(MAXN),dist(MAXN);
ll maxi=0;
void precalc(int node, int p){
    subtree_sum[node]=values[node];
    dist[node]=0;
    for(auto &x:g[node]){
        if(x!=p){
            precalc(x,node);
            subtree_sum[node]+=subtree_sum[x];
            dist[node]+=(dist[x]+subtree_sum[x]);
        }
    }
}
void reroot(int node, int p){
    maxi=max(maxi,dist[node]);
    for(auto &x:g[node]){
        if(x!=p){
            subtree_sum[node]-=subtree_sum[x];
            dist[node]-=(dist[x]+subtree_sum[x]);
 
            subtree_sum[x]+=subtree_sum[node];
            dist[x]+=(dist[node]+subtree_sum[node]);
 
            reroot(x,node);
 
            subtree_sum[x]-=subtree_sum[node];
            dist[x]-=(dist[node]+subtree_sum[node]);
 
            subtree_sum[node]+=subtree_sum[x];
            dist[node]+=(dist[x]+subtree_sum[x]);
 
        }
    }
}
int32_t main()
{ 
    IOS
    int t=1;
    // std::cin>>t;
    while (t--)
    {
        int n;cin>>n;
        for(int i=1;i<=n;i++)cin>>values[i];
        for(int i=0;i<n-1;i++){
            int x,y;cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        precalc(1,-1);
 
        reroot(1,-1);
 
        cout<<maxi;
 
    }
 
    return 0;
}