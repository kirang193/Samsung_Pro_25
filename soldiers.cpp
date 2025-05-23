/*
    each node of the tree represents a military unit. We are given the no. of soldiers in each     unit.
    we need to balance the tree such that
        all nodes belonging to the same parent node have the same subtree sum
        we can only balance by deleting some soldiers from a node 
        we should remove the minimum no. of soldiers(total)
    return the no. of soldiers total after balancing

    constraints:
        N<=500
        node.val<=100
        depth<=100
    input form:(for each of the n nodes)
        parent index, soldiers in that unit
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAXN = 505;

vector<int> tree[MAXN];
int soldiers[MAXN];
int n;
int totalRemoved = 0;

// Stores total soldiers in the subtree rooted at node `u`
int dfs(int u) {
    vector<int> childSums;
    int subtotal = 0;

    for (int v : tree[u]) {
        int sub = dfs(v);
        childSums.push_back(sub);
    }

    // If leaf node, return its value
    if (childSums.empty()) return soldiers[u];

    // Find target sum to match all children to (maximum that we can reduce others to)
    int minCost = INT_MAX;
    int totalSum = 0;

    for (int target : childSums) {
        int cost = 0;
        for (int s : childSums) {
            if (s < target) {
                cost = INT_MAX; // can't increase
                break;
            }
            cost += s - target;
        }
        if (cost < minCost) {
            minCost = cost;
            totalSum = target * childSums.size();
        }
    }

    totalRemoved += minCost;
    return soldiers[u] + totalSum;
}

int main() {
    cin >> n;
    vector<int> parent(n);
    int root = -1;

    for (int i = 0; i < n; ++i) {
        cin >> parent[i] >> soldiers[i];
        if (parent[i] == -1) {
            root = i;
        } else {
            tree[parent[i]].push_back(i);
        }
    }

    int finalSum = dfs(root);
    cout << finalSum << endl;
    return 0;
}
