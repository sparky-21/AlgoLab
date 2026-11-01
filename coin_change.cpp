#include<bits/stdc++.h>
using namespace std;
int solve(int s,int k,vector<int>c)
{
    if(s==0) return 0;
    int temp=INT_MAX;
    for(int i=0; i<k; i++)
    {
        if(s>=c[i])
        {
            temp=min(temp,1+solve(s-c[i],k,c));
        }
    }
    return temp;
}
int s2(int n)
{
    if(n==0|| n==1) return 1;
    return s2(n-1)+s2(n-2);
}
int main()
{
    cout<<"coin "<<endl;
    int s;
    cin>>s;
    int k;
    cin>>k;
    vector<int>c(k);
    for(int i=0; i<k; i++) cin>>c[i];
    cout<< solve(s,k,c)<<endl;
    int n ;
    cout<<"stair : ";
    cin>>n;
    cout<< s2(n)<<endl;



}
