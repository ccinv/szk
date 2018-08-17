#include<bits/stdc++.h>
using namespace std;
int n,a[4000010],l,r,mid,ans;
bool _get(int x){ return !(x<=mid);}
bool check()
{
    for (int i=1;i<=n-1;i++)
    {
        if (_get(a[n+i-1])==_get(a[n+i])) return _get(a[n+i]);
        if (_get(a[n-i+1])==_get(a[n-i])) return _get(a[n-i+1]);
    }
    return _get(a[1]);
}
int main()
{
//	freopen("mid.in","r",stdin);
//	freopen("mid.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=2*n-1;i++) scanf("%d",&a[i]);
    l=1;r=2*n-1;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (!check()) r=mid-1,ans=mid;else l=mid+1;
    }
    cout<<ans;
}

