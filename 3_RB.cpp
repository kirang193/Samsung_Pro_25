#include <iostream>
#include <map>
#include <string>
using namespace std;


int main(){
    string s;
    cin >> s;
    int n = s.size(), maxLen = 0, prefix = 0;
    map<int, int> first;
    first[0] = -1;


    for (int i = 0; i < n; i++){
        prefix += (s[i] == 'R' ? 1 : -1);
        if (first.find(prefix) == first.end())
            first[prefix] = i;
        else {
            int len = i - first[prefix];
            if (len > maxLen) maxLen = len;
        }
    }
   
    cout << n - maxLen << "\n";
    return 0;
}


/*
You will be given a necklace having only red and blue stones in it. Your task is to make the number of blue and red stones equal. 
Stones can only be removed from either the left or right end. 
Return the minimum number of stones that are to be removed to complete the given task.

For eg, input: BBRRBRBRBRBBR
            output: 1

//  try this
Length of string - (longest length of subarray with equal no of “A” and ‘B’) 
/*
*/