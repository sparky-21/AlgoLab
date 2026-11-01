#include<bits/stdc++.h>
using namespace std;
int clmstr(int n) // recursion
{
    if(n==1 || n==2) return n;

    return clmstr(n-1)+clmstr(n-2);
}
int clmstrdphelper(int n, vector<int>&dp) //memoization
{
    if(n==1 || n==2) return n;

    if (dp[n]!=-1) return dp[n];

  return dp[n]= clmstrdphelper(n-1,dp)+clmstrdphelper(n-2,dp);
}
int clmstrdp(int n) //memoization
{
    vector<int>dp(n+1,-1);
    dp[1]= 1;
    dp[2]=2;
   return clmstrdphelper(n,dp);

}
int clmstrtab(int n) //tabulation
{
    if(n==1 || n==2) return n;

int prev1=1;
int prev2=2;
int res = prev2;
    for(int i=3;i<=n;i++)
    {
       res= prev1+prev2;

       prev1=prev2;
       prev2= res;
    }

    return res;
}

int main()
{
    int n ; cin >>n ;
    cout<< clmstr(n)<<endl;
    cout<< clmstrdp(n)<<endl;
    cout<< clmstrtab(n)<<endl;
}
