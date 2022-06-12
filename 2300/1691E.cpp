#include<bits/stdc++.h>
using namespace std;
#define ll long long
// when you got tle but tc is right do this and make as global as possible
//#define endl "\n"   
const ll MAX =1000000000000000000;
ll mod= 1000000000;
long double pi=3.141592653589793238;
void pls()
{
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);
#endif
}
/*   DON'T STUCK ON SINGLE APPROACH AND ALWAYS STUCK ON QUESTION :)*/
const ll N=3e5+2;
 class DSU{
  public:
       vector<int> parent;
       vector<int> rank;

       DSU(int n)
       {
             parent.resize(n);
             rank.resize(n);
             for(int i=0;i<n;i++)
                 rank[i]=1,parent[i]=i;
       }
       void Union(int u,int v)
       {

           // cout<<u<<" "<<v<<endl;
           int pu=findd(u);
           int pv=findd(v);
           if(pu==pv) return ;
           if(rank[pu]<rank[pv])
           {
                 parent[pu]=pv;
                 rank[pv]+=rank[pu];
                 rank[pu]=0;
           }
           else
           {
                     parent[pv]=pu;
                  rank[pu]+=rank[pv];
                  rank[pv]=0;
           }
       }    
       int findd(int i)
       {
               if (parent[i] != i)
                 parent[i] = findd(parent[i]);
             return parent[i];
       }

};
bool intersect(pair<ll,ll> &a,pair<ll,ll> &b)
{
      if(a.second<b.first || a.first>b.second)
        return false;
    return true;
}
void solve()
{  
   int t;cin>>t;while(t--)
   {
    
    ll n; cin>>n;    
    DSU  dsu(n);
    vector<pair<pair<ll,ll>,ll>> bl,re;
    set<pair<ll,ll>> bluer,blue,redr,red;
    vector<pair<ll,ll>> ran[n];
    for(int i=0;i<n;i++)
    {
           ll l,r,c; cin>>c>>l>>r;
           ran[i].push_back({l,r});
           if(c==1)  // blue
           {
                bl.push_back({{l,r},i});
           }
           else
           {    
                re.push_back({{l,r},i});
           }
    }
    sort(bl.begin(),bl.end());
    sort(re.begin(),re.end());
    ll j=0;
    for(int i=0;i<re.size();i++)
    {
            ll l=re[i].first.first;
            ll ri=re[i].first.second;
            ll ii=re[i].second;
            // cout<<l<<" fds"<<ri<<endl;
           while(!bluer.empty() && bluer.begin()->first<l)
            {
                  ll ix=bluer.begin()->second;
                  bluer.erase(bluer.begin());
                  blue.erase({ran[ix][0].first,ix});
            }
            ll a=-1,b=-1;


            if(!blue.empty())
            {
                b=blue.begin()->second;
            }
        
            if(b!=-1 && intersect(ran[b][0],re[i].first))
            {
                dsu.Union(b,ii);
            }

            while(j<bl.size() && bl[j].first.first<=re[i].first.second)
            {
                    if(intersect(bl[j].first,re[i].first))
                    {
                         dsu.Union(ii,bl[j].second);
                    }
                    bluer.insert({bl[j].first.second,bl[j].second});
                    blue.insert({bl[j].first.first,bl[j].second});
                    j++;            
            }

    }
    ll res=0;
    for(int i=0;i<n;i++)
    {

         if(dsu.findd(i)==i)
            res++;
    }
    cout<<res<<endl;



   }
}
int main(){pls(); solve(); return 0;}