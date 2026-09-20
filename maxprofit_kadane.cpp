#include<bits/stdc++.h>
using namespace std;
// best sol :)

/*int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int profit = 0;
        for(int i=0;i<prices.size();i++){
           int  cost = prices[i]-mini;
            profit = max(profit,cost);
            mini = min(mini , prices[i]);
        }
        return profit ;
    }
    */

//my sol -_-

    /* int maxProfit(vector<int>& prices) {
         if(prices.size()<2) return 0;
        vector<int>cng;
        for(int i=1;i<prices.size();i++)
        {
            cng.push_back(prices[i]-prices[i-1]);
        }
        int i=0; int mpro=cng[0]; int prosum=cng[0];
        for( i=1;i<cng.size();i++)
        {
           int v1=cng[i];
           int v2= prosum+cng[i];
           prosum=max(v2,v1);
           mpro=max(mpro,prosum);
        }
        if(mpro>0) return mpro;
        else return 0;


    }*/
