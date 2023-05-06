// Number Grid
//
// Problem name: Number Grid
// Problem Link: https://cses.fi/problemset/task/1157
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

// Consider a two-dimensional grid whose rows and columns are 1-indexed. 
// Each square contains the smallest nonnegative integer 
// that does not appear to the left on the same row or above on the same column.
// Your task is to calculate the value at square (y,x).
// reduz pra nim com duas pilhas

#include <bits/stdc++.h>
 
int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", (x-1) ^ (y-1));
    return 0;
}