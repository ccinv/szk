#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for (int i=(a);i<=(b);++i)
#define FD(i,a,b) for (int i=(a);i>=(b);--i)
#define FE(i,G,x) for(int i=G.h[x];~i;i=G.v[i].nxt)
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

#define N 2005
int fa[N], x[N], y[N], w[N], id[N], n, m, mx, mn, ans;
double ww, ANS, p;

#define sqr(x) ((x)*(x))
bool cmp1(int x, int y) { return w[x] < w[y]; }
bool cmp2(int x, int y) { return sqr(w[x] - p) < sqr(w[y] - p); }
int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }
void kru() {
    FO(i, 1, n) fa[i] = i;
    int cnt = 0;
    FO(ix, 1, m) {
        int i = id[ix];
        int xx = find(x[i]), yy = find(y[i]);
        if (xx == yy) continue;
        fa[xx] = yy;
        ans += w[i]; ww += sqr(w[i] - p);
        if (++cnt == n - 1) break;
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    n = read(); m = read(); ANS = oo;
    FO(i, 1, m) { x[i] = read(); y[i] = read(); w[i] = read(); id[i] = i; }
    sort(id + 1, id + 1 + m, cmp1); kru(); mx = ans;
    ans = 0; reverse(id + 1, id + 1 + m); kru(); mn = ans;
    FO(i, mx, mn) {
        p = (double)i / (n - 1);
        sort(id + 1, id + 1 + m, cmp2);
        ans = 0; ww = 0; kru();
        if (ans == i) ANS = min(ANS, ww);
    }
    printf("%.5lf\n", sqrt(ANS / (n - 1)));
    return 0;
}