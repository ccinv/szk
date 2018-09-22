#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=(G).h[x];~i;i=(G).v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

inline LL read(void) {
    LL x, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

#define N 100005
set<int,greater<int> > S1;
multiset<int,greater<int> > S2;
int n,k,g[N],f[N],l,pos[N];
PII a[N];

bool cmp(int x,int y){ return a[x].se<a[y].se; }

int main(void) {
	n=read();k=read();
	FO(i,1,n) a[i].fi=read(),a[i].se=read(),pos[i]=i;
	sort(a+1,a+1+n);sort(pos+1,pos+1+n,cmp);
	FO(i,1,n) g[i]=a[i].se-a[i].fi;
	FO(i,2,k){
		FO(j,1,i-1) S2.insert(g[j]-a[j].se);l=1;
		FO(j,i,n){
			while (l<=n&&a[pos[l]].se<a[j].fi){
				// no longer overlap
				S2.erase(S2.find(g[pos[l]]-a[pos[l]].se));
				S1.insert(g[pos[l]]);++l;
			}
			f[j]=-1e9;
			if (!S2.empty()) chkmax(f[j],*S2.begin()+a[j].se);
			if (!S1.empty()) chkmax(f[j],*S1.begin()+a[j].se-a[j].fi);
			S2.insert(g[j]-a[j].se);
		}
		S1.clear();S2.clear();
		FO(j,1,n) g[j]=f[j];
	}
	printf("%d\n",*max_element(g+1,g+1+n));
	cerr<<"TIME: "<<(double)clock() / CLOCKS_PER_SEC<<endl;
    return 0;
}
