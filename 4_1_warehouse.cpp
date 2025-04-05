/*
Test - 4 

Q1. There is 2d Matrix of size h*w representing the city.
Each cell can be 0,1,2,3,4
0-> road
1->Tree
3-> warehouse
4-> Airport

There is a truck parked at the Garage, Truck’s task is to go to the warehoutyse (one or many at a time) , load the goods and unload the truck at the airport.
There is no limit on the number of goods a truck can carry.

There is a cost associated with a truck.
Cost is (Number of blocks it has moved * (1+Number of goods truck carries)) like 
To move one block cost is 1 on an empty truck in
Cost is 2 if truck has 1 good
3 if the truck has 2 goods. 
……….
You have to tell how many maximum goods can be unloaded at airport using at max C cost

Constraints
Number of test cases - 50
h,w belongs to (2,40)
c belongs to (5,2000)
There can be at max 13 warehouses
Truck cannot pass a tree, if it is at any warehouse truck can or cannot load the goods, similarly if it's at an airport it's not necessary to unload the goods.
But starting point is fixed ie garage.

*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


typedef long long ll;
const ll INF = 1e9;
const ll dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};


void bfs(int sx, int sy, vector<vector<ll>> &dist, const vector<vector<ll>> &mat) {
    int h = mat.size(), w = mat[0].size();
    queue<pair<ll, ll>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < h && ny < w && mat[nx][ny] != 1 && dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}


void solve() {
    int t; cin >> t;
    while (t--) {
        ll h, w, c, gx, gy, ax, ay;
        cin >> h >> w >> c;
        vector<vector<ll>> mat(h, vector<ll>(w));
        vector<pair<ll, ll>> warehouses;
       
        for (ll i = 0; i < h; i++)
            for (ll j = 0; j < w; j++) {
                cin >> mat[i][j];
                if (mat[i][j] == 2) gx = i, gy = j;
                if (mat[i][j] == 4) ax = i, ay = j;
                if (mat[i][j] == 3) warehouses.emplace_back(i, j);
            }
       
        vector<vector<ll>> ds(h, vector<ll>(w, INF)), dd(h, vector<ll>(w, INF));
        bfs(gx, gy, ds, mat);
        bfs(ax, ay, dd, mat);
       
        ll max_goods = 0;
        for (auto [wx, wy] : warehouses) {
            ll cost = c - ds[wx][wy];
            if (cost > 0) {
                cost = (cost / dd[wx][wy]) - 1;
                if (cost > 0) max_goods = max(max_goods, cost);
            }
        }
        cout << max_goods << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
}



// #include <bits/stdc++.h>
// using namespace std;
// using ll=long long;
// int h,w,c;
// vector<vector<int>>v;

// int main(){
//     h=6,w=6,c=18;
//     v.resize(h,vector<int>(w));
//     vector<pair<int,int>>warehouses;
//     vector<int>dx={1,0,-1,0},dy={0,1,0,-1};
//     int gx=0,gy=0,ax=h-1,ay=w-1;
//     v={
//         {2,0,0,0,0,0},
//         {0,1,1,1,0,0},
//         {0,0,3,0,3,0},
//         {0,0,0,0,0,0},
//         {1,0,3,0,0,0},
//         {0,0,0,0,0,4}
//     };
//     for(int i=0;i<h;i++){
//         for(int j=0;j<w;j++){
//             if(v[i][j]==3){
//                 warehouses.push_back({i,j});
//             }
//         }
//     }
//     vector<vector<int>>vis(h,vector<int>(w,0)),dis(h,vector<int>(w,-1));
//     queue<pair<int,int>>q;q.push({0,0});vis[0][0]=1;
//     int lvl=0,k;
//     while(!q.empty()){
//         k=q.size();lvl++;
//         for(int i=0;i<k;i++){
//             auto it=q.front();q.pop();
//             int x=it.first,y=it.second;
//             for(int j=0;j<4;j++){
//                 int nx=x+dx[j],ny=y+dy[j];
//                 if(nx>=0 && nx<h && ny>=0 && ny<w && !vis[nx][ny] && v[nx][ny]!=1){
//                     vis[nx][ny]=1;
//                     dis[nx][ny]=lvl;
//                     q.push({nx,ny});
//                 }
//             }
//         }
//     }

//     vector<vector<int>>vis2(h,vector<int>(w,0)),dis2(h,vector<int>(w,-1));
//     q.push({h-1,w-1});vis2[h-1][w-1]=1;
//     lvl=0;
//     while(!q.empty()){
//         k=q.size();lvl++;
//         for(int i=0;i<k;i++){
//             auto it=q.front();q.pop();
//             int x=it.first,y=it.second;
//             for(int j=0;j<4;j++){
//                 int nx=x+dx[j],ny=y+dy[j];
//                 if(nx>=0 && nx<h && ny>=0 && ny<w && !vis2[nx][ny] && v[nx][ny]!=1){
//                     vis2[nx][ny]=1;
//                     dis2[nx][ny]=lvl;
//                     q.push({nx,ny});
//                 }
//             }
//         }
//     }
//     int max_goods=-1;
//     for(int i=0;i<warehouses.size();i++){
//         int x=warehouses[i].first,y=warehouses[i].second;
//         if(dis[x][y]!=-1 && dis2[x][y]!=-1){
//             int goods=(c-dis[x][y])/dis2[x][y]-1;
//             max_goods=max(goods,max_goods);
//         }        
//     }
//     cout<<max_goods<<endl;
//     return 0;
// }.
