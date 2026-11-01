#include<bits/stdc++.h>
using namespace std;
int rodcutdp(int idx, int n, vector<int>&price,
             vector<vector<int>>&dp)
{
    if(idx==0)
        return n*price[0];

    if(dp[idx][n]!=-1)
        return dp[idx][n];

    int nottake = rodcutdp(idx-1,n,price,dp);

    int take = INT_MIN;
    int rodlen = idx+1;

    if(rodlen<=n)
    {
        take = price[idx] +
               rodcutdp(idx,n-rodlen,price,dp);
    }

    return dp[idx][n] = max(take,nottake);
}
int rodcut(int idx,int n, vector<int>&price)
{
   if(idx==0) return n*price[idx];

   int nottake= 0+ rodcut(idx-1,n,price);
   int take=INT_MIN;
   int rodlen= idx+1;
   if(rodlen <= n)
{
    take = price[idx] + rodcut(idx, n-rodlen, price);
}
   return max(take, nottake);
}

int main()
{
    int n; cin>>n;
    vector<int>price(n);

      for(int i=0; i<n; i++)
        cin>>price[i];

       cout<< rodcut(n-1, n ,price);

}
/*
#include<bits/stdc++.h>
using namespace std;

int rodcut(int idx, int n, vector<int>&price,
           vector<vector<int>>&dp,
           vector<vector<int>>&choice)
{
    if(idx==0)
    {
        choice[idx][n] = 1;
        return n*price[0];
    }

    if(dp[idx][n]!=-1)
        return dp[idx][n];

    int nottake = rodcut(idx-1,n,price,dp,choice);

    int take = INT_MIN;
    int rodlen = idx+1;

    if(rodlen<=n)
    {
        take = price[idx] +
               rodcut(idx,n-rodlen,price,dp,choice);
    }

    if(take > nottake)
    {
        choice[idx][n] = 1;
        return dp[idx][n] = take;
    }
    else
    {
        choice[idx][n] = 0;
        return dp[idx][n] = nottake;
    }
}

int main()
{
    int n;
    cin>>n;

    vector<int>price(n);

    for(int i=0;i<n;i++)
        cin>>price[i];

    vector<vector<int>>dp(n,vector<int>(n+1,-1));
    vector<vector<int>>choice(n,vector<int>(n+1,-1));

    int ans = rodcut(n-1,n,price,dp,choice);

    cout<<"Maximum Profit: "<<ans<<endl;

    // Print selected rod lengths
    cout<<"Selected rod lengths: ";

    int idx=n-1;
    int rem=n;

    while(rem>0 && idx>=0)
    {
        if(idx==0)
        {
            for(int i=0;i<rem;i++)
                cout<<1<<" ";
            break;
        }

        if(choice[idx][rem]==1)
        {
            cout<<idx+1<<" ";
            rem -= (idx+1);
        }
        else
        {
            idx--;
        }
    }

    cout<<endl;
}
*/
