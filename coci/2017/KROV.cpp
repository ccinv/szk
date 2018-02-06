#include <bits/stdc++.h>
using namespace std;

#define oo 1e18
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define FO(i,a,b) for(int i=a;i<=b;++i)
#define FD(i,a,b) for(int i=a;i>=b;--i)
#define FE(i,G,x) for(int i=G.h[x];~i;i=G.v[i].nxt)
#define lowbit(x) (x&(-x))
typedef long long LL;
typedef pair<int, int> PII;

template <class T> inline bool chkmin(T& x, T y) { return x > y ? x = y, true : false; }
template <class T> inline bool chkmax(T& x, T y) { return x < y ? x = y, true : false; }

inline int read(void) {
    int x, f = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

namespace Treap {

struct node {
    node* ls, *rs;
    int pri, key, size, tag;
    LL sum;
    void add(int x) { tag += x; sum += x * size; key += x; }
    void upd() {
        size = 1 + (ls ? ls->size : 0) + (rs ? rs->size : 0);
        sum = key + (ls ? ls->sum : 0) + (rs ? rs->sum : 0);
    }
    void pushdown() {
        if (ls) ls->add(tag);
        if (rs) rs->add(tag);
        tag = 0;
    }
    node() { ls = rs = NULL; }
}* root, *rootr;
typedef pair<node*, node*> decr;

inline int ran() {
    static int x = 23333;
    return x ^= x << 13, x ^= x>>17, x ^= x << 5;
}
inline int size(node* x) { return x ? x->size : 0; }

node* merge(node* x, node* y) {
    if (!(x && y)) return x ? x : y;
    if (x->pri < y->pri) {
        if (x->tag) x->pushdown();
        x->rs = merge(x->rs, y); x->upd();
        return x;
    } else {
        if (y->tag) y->pushdown();
        y->ls = merge(x, y->ls); y->upd();
        return y;
    }
}
decr split(node* x, int n) {
    if (!x) return decr(NULL, NULL);
    if (x->tag) x->pushdown(); decr ret;
    if (size(x->ls) >= n) {
        ret = split(x->ls, n);
        x->ls = ret.se; x->upd();
        ret.se = x;
    } else {
        ret = split(x->rs, n - size(x->ls) - 1);
        x->rs = ret.fi; x->upd();
        ret.fi = x;
    }
    return ret;
}
inline LL query(node*& root, int k, LL q) {
    decr x = split(root, k);
    LL ans = 0;
    if (x.fi) ans -= x.fi->sum - x.fi->size * q;
    if (x.se) ans += x.se->sum - x.se->size * q;
    root = merge(x.fi, x.se);
    return ans;
}
int getkth(node* x, int y) {
    if (!x) return 0; if (x->tag) x->pushdown();
    return (y < x->key) ? getkth(x->ls, y) : getkth(x->rs, y) + size(x->ls) + 1;
}
inline void ins(node*& root, int x) {
    node* t = new node;
    t->pri = ran(); t->key = x; t->sum = x; t->size = 1;
    int k = getkth(root, x);
    decr p = split(root, k);
    root = merge(merge(p.fi, t), p.se);
}
inline void remove(int y) {
    int k = getkth(rootr, y);
    decr z = split(rootr, k - 1);
    decr q = split(z.se, 1);
    delete q.fi;
    rootr = merge(z.fi, q.se);
}

}
using namespace Treap;

int n, mx, a[100005];
LL ans;

inline LL ck(int pos, int x) {
    LL ans = 0;
    int k = getkth(root, x); ans += query(root, k, x);
    k = getkth(rootr, x); ans += query(rootr, k, x);
    ans += abs(a[pos] - x);
    return ans;
}
inline void pd(int x) {
    int l = max(x, n - x + 1), r = mx;
    while (l < r) {
        int m = l + r >> 1, mm = m + r >> 1;
        if (ck(x, m) < ck(x, mm)) r = mm;
        else l = m + 1;
    }
    if (ck(x, l - 1) < ck(x, l)) l--; l = max(l, max(x, n - x + 1));
    ans = min(ans, ck(x, l));
}

int main(void) {
    n = read(); ans = oo; mx = n;
    FO(i, 1, n) a[i] = read(), mx = max(mx, a[i]);
    FD(i, n, 2) ins(rootr, a[i] + i - 1);
    FO(i, 1, n) {
        pd(i);
        ins(root, a[i]); root->add(1);
        if (i != n) remove(a[i + 1] + 1);
        if (i < n - 1) rootr->add(-1);
    }
    cout << ans << endl;
    return 0;
}