/*Q3. There's a cost of removing stone, the cost is different if it has one neighbour,
 two neighbours and it's zero if no neighbour.
Within a given sequence of stones, find minimum cost to remove all of them.
 Each stone had different costs for each neighbour condition 
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


long long min_removal_cost(int n, const vector<long long>& a, const vector<long long>& b) {
    // dp[i][0] = min cost for stones 1..i if stone i+1 is removed before stone i
    // dp[i][1] = min cost for stones 1..i if stone i+1 is removed after stone i
    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));
   
    // Base case for the first stone
    dp[1][0] = 0;
    dp[1][1] = a[0];
   
    // Fill dp table for stones 2..n
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = min(dp[i - 1][0] + a[i - 1], dp[i - 1][1] + 0);
        dp[i][1] = min(dp[i - 1][0] + b[i - 1], dp[i - 1][1] + a[i - 1]);
    }
   
    // The answer is dp[n][0] because stone n+1 doesn't exist
    return dp[n][0];
}


int main() {
    int n;
    cin >> n;
   
    vector<long long> a(n), b(n);
    // Read cost array a (cost if stone is removed before its neighbor)
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // Read cost array b (cost if stone is removed after its neighbor)
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
   
    cout << min_removal_cost(n, a, b) << endl;
    return 0;
}
