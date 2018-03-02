#include <bits/stdc++.h>
using namespace std;

#define oo 1000000000
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for(int i=a;i<=b;++i)
#define FD(i,a,b) for(int i=a;i>=b;--i)
#define FE(i,G,x) for(int i=G.h[x];i!=-1;i=G.v[i].nxt)
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

template <class T> T reads() {
    T x = 0;
    static int f;
    static char c;
    for (f = 1; !isdigit(c = getchar()); ) if (c == '-') f = -1;
    for (x = 0; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    return x * f;
}
#define read   reads<int>
#define readll reads<LL>

#define C (1<<20)*5+5
int n, a[45], b[45], h[45];
int T[C], L[C], R[C], rt = 0, cnt;

LL k, ans;

#define MID (l+r>>1)
#define S(x) ((x)?(x):((x)=++cnt))
void add(int& x, LL l, LL r, LL pos) {
    T[S(x)]++; int xx = x;
    while (l != r) {
        if (pos <= MID) xx = S(L[xx]), r = MID;
        else xx = S(R[xx]), l = MID + 1;
        T[xx]++;
    }
}
int que(int x, LL l, LL r, LL ll, LL rr) {
    if (!x || l > rr || r < ll) return 0;
    if (l >= ll && r <= rr) return T[x];
    return que(L[x], l, MID, ll, rr) + que(R[x], MID + 1, r, ll, rr);
}
void dfs1(int x, LL y, int hi) {
    if (x == 0) { add(rt, 1, k, min(k, y)); ans += y >= k; return ; }
    if (hi >= a[x]) dfs1(x - 1, y + b[x], a[x]);
    dfs1(x - 1, y, hi);
}
void dfs2(int x, LL y, int hi) {
    if (x > n) { ans += que(rt, 1, k, max(k - y, 0ll), k) + (y >= k); return ; }
    if (hi <= a[x]) dfs2(x + 1, y + b[x], a[x]);
    dfs2(x + 1, y, hi);
}

int main(void) {
    n = read(); k = readll();
    FO(i, 1, n) a[i] = read(), b[i] = read(), h[i] = i;
    FO(i, 1, n - 1) FO(j, i + 1, n) if (a[h[i]] > a[h[j]]) swap(h[i], h[j]);
    FO(i, 1, n) {
        if (h[i] <= n / 2) dfs1(h[i] - 1, b[h[i]], a[h[i]]);
        else dfs2(h[i] + 1, b[h[i]], a[h[i]]);
    }
    printf("%lld\n", ans);
    return 0;
}