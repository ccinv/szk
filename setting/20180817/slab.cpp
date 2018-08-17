#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
#define maxn 100009
using namespace std;
int n,k,p[maxn],dp[maxn][109];
struct ding {
    int l,r;
} a[maxn],b[maxn];
struct ding2 {
    int node,val;
};
deque<ding2>q[maxn];
bool cmp(ding t1,ding t2)
{
    return t1.l==t2.l?t1.r>t2.r:t1.l<t2.l;
}
int main()
{
    freopen("slab.in","r",stdin);
    freopen("slab.out","w",stdout);
    scanf("%d%d",&n,&k);
    b[0]=(ding) {
        0,0
    };
    for (int i=1; i<=n; i++) scanf("%d%d",&a[i].l,&a[i].r);
    if (k>=n)
    {
        printf("0\n");
        return 0;
    }
    sort(a+1,a+1+n,cmp);
    int maxx=-1,cnt=0;
    for (int i=1; i<=n; i++)
    {
        b[++cnt]=a[i];
    }
    if (k<0) k=0;
    n=cnt;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=min(k,i); j++)
        {
            int now=j-1;
            if (now>0) {
                while ((!q[now].empty())&&(b[q[now].front().node].r<b[i].l))
                {
                    ding2 to=q[now].front();
                    p[now]=max(p[now],to.val+b[to.node].r);
                    q[now].pop_front();
                }
                dp[i][j]=max(dp[i][j],p[now]+b[i].r-b[i].l);
                if (!q[now].empty())
                    dp[i][j]=max(dp[i][j],q[now].front().val+b[i].r);
            } else dp[i][j]=b[i].r-b[i].l;
            int nowv=dp[i][j]-b[i].r;
            now=j;
            while ((!q[now].empty())&&(q[now].back().val<nowv))
                q[now].pop_back();
            q[now].push_back((ding2) {
                i,nowv
            });
        }
    }
    int ans=0;
    for (int i=1; i<=n; i++)
        ans=max(ans,dp[i][k]);
    printf("%d\n",ans);
    return 0;
}
