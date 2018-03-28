#include <bits/stdc++.h>
using namespace std;

#define oo 0x3f3f3f3f
#define mp make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for(int i=a;i<=b;++i)
#define FD(i,a,b) for(int i=a;i>=b;--i)
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

#define N 260005
char str[N], s[N];
int n, p[N], l, r, q, m; LL ans;
struct Seg { int l, r; LL s; } T[N * 120];
int rt1[N], rt2[N], rt3[N], rt4[N], rt5[N], rt6[N], cnt;

inline int min(int a, int b) { return a < b ? a : b; }

#define MID (l+r)/2
int mod(int k, int l, int r, int pos, int v) {
    assert(l <= pos && pos <= r);
    int x = ++cnt; T[x] = T[k]; T[x].s += v;
    if (l == r) return x;
    if (pos <= MID) T[x].l = mod(T[x].l, l, MID, pos, v);
    else T[x].r = mod(T[x].r, MID + 1, r, pos, v);
    return x;
}
int ll, rr, si;
void query(int x, int l, int r) {
    if (l > rr || r < ll) return ;
    if (l >= ll && r <= rr) { ans += T[x].s * si; return ; }
    query(T[x].l, l, MID); query(T[x].r, MID + 1, r);
}
void query(int x, int l, int r, int _ll, int _rr, int _si) {
    ll = _ll; rr = _rr; si = _si; query(x, l, r);
}

int main(void) {
    freopen("gene.in", "r", stdin);
    freopen("gene.out", "w", stdout);
    n = read(); q = read();
    scanf("%s", str + 1);
    FO(i, 1, 2 * n) if (i & 1) s[i] = '#'; else s[i] = str[i >> 1];
    s[2 * n | 1] = '#'; n = n << 1 | 1;
    int c = 0, r = 0; p[1] = 0;
    FO(i, 1, n) {
        if (r > i) p[i] = min(p[2 * c - i], r - i);
        else p[i] = 1;
        while (p[i] < i && s[i + p[i]] == s[i - p[i]]) ++p[i];
        if (i + p[i] > r) r = i + p[i], c = i;
    }
    FO(i, 1, n) {
        int pos = -p[i] + i + 2;
        rt1[i] = mod(rt1[i - 1], -2, 2 * n, pos, p[i] / 2);
        rt2[i] = mod(rt2[i - 1], -2, 2 * n, pos, i / 2);
        rt3[i] = mod(rt3[i - 1], -2, 2 * n, pos, 1);

        pos += 2 * p[i] - 4;
        rt4[i] = mod(rt4[i - 1], -2, 2 * n, pos, p[i] / 2);
        rt5[i] = mod(rt5[i - 1], -2, 2 * n, pos, (i + 1) / 2);
        rt6[i] = mod(rt6[i - 1], -2, 2 * n, pos, 1);
    }
    while (q--) {
        l = read() * 2; r = read() * 2; m = (l + r) >> 1; ans = 0;
        if (r - l <= 15) {
            FO(i, l, m) ans += min(p[i] / 2, (i - l) / 2 + 1);
            FO(i, m + 1, r) ans += min(p[i] / 2, (r - i) / 2 + 1);
            printf("%lld\n", ans);
            continue;
        }
        query(rt1[m], -2, 2 * n, l, 2 * n, 1); query(rt1[l - 1], -2, 2 * n, l, 2 * n, -1); // store p[i]/2
        query(rt2[m], -2, 2 * n, -2, l - 1, 1); query(rt2[l - 1], -2, 2 * n, -2, l - 1, -1); // store i/2
        query(rt3[m], -2, 2 * n, -2, l - 1, 1 - l / 2); query(rt3[l - 1], -2, 2 * n, -2, l - 1, l / 2 - 1);

        query(rt4[r], -2, 2 * n, -2, r, 1); query(rt4[m], -2, 2 * n, -2, r, -1);
        query(rt5[r], -2, 2 * n, r + 1, 2 * n, -1); query(rt5[m], -2, 2 * n, r + 1, 2 * n, 1);
        query(rt6[r], -2, 2 * n, r + 1, 2 * n, r / 2 + 1); query(rt6[m], -2, 2 * n, r + 1, 2 * n, -r / 2 - 1);
        printf("%lld\n", ans);
    }
    return 0;
}

