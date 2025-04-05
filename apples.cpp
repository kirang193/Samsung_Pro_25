/*
🍎 Apple Game - Right Turn Only

Mr. Sam-Sung Na purchased a newly released game.

This game is played on an N x N map. The goal of the game is to eat the apples in order.

Rules:
- Apples appear on the map according to their number, starting from 1.
- Apple 2 appears only after Apple 1 is eaten, Apple 3 after Apple 2, and so on.
- You cannot eat an apple out of order.
- You cannot move into cells marked as traps (-1 on the map).

Movement:
- The player starts at the top-left corner of the map (0, 0).
- The player initially moves to the right (→).
- The player continues to move in the current direction unless:
    - They hit a wall
    - They hit a trap
    - They make a right turn
- Due to a keyboard malfunction, the player can only make right turns.
- Left turns and backward movement are not possible.

Goal:
- Eat all apples in order while making the minimum number of right turns.
- If it's impossible to eat all the apples in order, return -1.

Input:
- First line: T, number of test cases.
- For each test case:
  - First line: N (size of the map)
  - Next N lines: N integers each representing the map
    - 0: empty cell
    - -1: trap
    - Positive integers: apple numbers (1 to M)

Output:
- For each test case, print "#t ans"
  - t = test case number starting from 1
  - ans = minimum number of right turns needed to eat all apples
  - If impossible, print -1

Constraints:
- 5 ≤ N < 60
- 2 ≤ M ≤ 150

*/

#include<bits/stdc++.h>
using namespace std; 
int main(){
    int n,m;cin>>n>>m;
    vector<vector<int>>v(n,vector<int>(m));
    int apples=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>v[i][j];
            apples=max(v[i][j],apples);
        }
    }
    // cout<<apples<<endl;
    deque<array<int,4>>dq;
    vector dp(n,vector(m,vector(apples+1,vector(4,INT_MAX))));
    dq.push_back({0,0,v[0][0]==1,0});
    dp[0][0][v[0][0]==1][0]=0;
    vector<int>dx={0,1,0,-1},dy={1,0,-1,0};

    auto move=[&](int x, int y, int cnt, int dir, int d, int f){
        int nx=x+dx[dir],ny=y+dy[dir];
        if(!(nx>=0 and nx<n and ny>=0 and ny<m and v[nx][ny]!=-1))return;
        int ncnt=cnt+(v[nx][ny]==(cnt+1));
        if(dp[nx][ny][ncnt][dir]>d){
            if(f){
                dq.push_back({nx,ny,ncnt,dir});
            }else{
                dq.push_front({nx,ny,ncnt,dir});
            }
            dp[nx][ny][ncnt][dir]=d;
        }
    };
    while(!dq.empty()){
        auto [x,y,cnt,dir] = dq.front();
        dq.pop_front();

        move(x,y,cnt,dir,dp[x][y][cnt][dir],0);
        move(x,y,cnt,(dir+1)%4,dp[x][y][cnt][dir]+1,1);
    }
    int ans=INT_MAX;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //cout<<i<<" "<<j<<endl;
            for(int k=0;k<4;k++){
                //cout<<dp[i][j][apples][k]<<" "; 
                ans=min(ans,dp[i][j][apples][k]);
            }
            //cout<<endl;
        }
    }
    cout<<ans<<endl;


    return 0;
}

/*
#include <bits/stdc++.h>
#define int long long int
#define endl "\n"
#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(__null);
 
using namespace std;
 
const int INF = 1e18;
 
signed main() {
    fastio()
 
    int n, m;
    cin >> n >> m;
 
    int cnt = 0;
    vector v(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
            cnt = max(cnt, v[i][j]);
        }
    }
 
    deque<array<int, 4>> dq;
    vector dp(n, vector(m, vector(cnt + 1, vector(4, INF))));
    dq.push_back({0, 0, v[0][0] == 1, 0}), dp[0][0][v[0][0] == 1][0] = 0;
 
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
 
    auto move = [&](int x, int y, int cnt, int dir, int d, int f) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (!(nx >= 0 && nx < n && ny >= 0 && ny < m && v[nx][ny] != -1)) return;
 
        int ncnt = cnt + (v[nx][ny] == cnt + 1);
        if (dp[nx][ny][ncnt][dir] > d) {
            if (!f) dq.push_front({nx, ny, ncnt, dir});
            else dq.push_back({nx, ny, ncnt, dir});
            dp[nx][ny][ncnt][dir] = d;
        }
    };
 
    while (!dq.empty()) {
        auto [x, y, cnt, dir] = dq.front();
        dq.pop_front();
 
        move(x, y, cnt, dir, dp[x][y][cnt][dir], 0);
        move(x, y, cnt, (dir + 1) % 4, dp[x][y][cnt][dir] + 1, 1);
    }
 
    int ans = INF;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 4; k++)
                ans = min(ans, dp[i][j][cnt][k]);
 
    cout << ans << endl;
 
    return 0;
}*/
