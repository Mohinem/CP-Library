#include<bits/stdc++.h>
using namespace std;

const int N=100000+50;

int main(){
    ios::sync_with_stdio(false);
    
    
    return 0;
}
/*

Mistakes to take care of-

1. For string s, s+=a is similar to appending to s. s = s + a takes O|s| + O|a| time. 
Relevant problem where I made mistake - https://codeforces.com/contest/1326/problem/D2

2. Try using constant value of N to declare arrays, etc. Else you might get hacked / FST.
Relevant problem where I made a mistake - https://codeforces.com/contest/1307/problem/D

3. While exponentiation, divide the power by mod-1 of phi(mod) for large value, because the exponent will repeat according to Fermat's Little Theorem / Euler's Theorem.
Relevant problem where I made a mistake - https://codeforces.com/contest/1332/problem/E
*/
