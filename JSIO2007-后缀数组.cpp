#include "cstdio"
#include "vector"
#include "iostream"
#include "cstring"
#include "queue"
#include "algorithm"
#include "set"

using namespace std;
typedef long long LL;
const int N = 1e5 + 7;


char s[N << 1];
int sa[N << 2], rk[N << 2], oldrk[N << 2];
int gw;

void solve() {
    memset(s, 0, sizeof s);
    scanf("%s", s);

    int len = strlen(s);
    memcpy(s + len, s, sizeof(char) * len);
    int len2 = len * 2;
    for (int i = 0; i < len2; i++) {
        sa[i] = i;
        rk[i] = s[i];
    }

    int w = 1;
    while (w < len2) {
        gw = w;
        sort(sa, sa + len2, [](int a, int b) {
            if (rk[a] == rk[b])
                return rk[a + gw] < rk[b + gw];
            return rk[a] < rk[b];
        });
        memcpy(oldrk, rk, sizeof rk);

        int rankCnt = -1;
        for (int i = 0; i < len2; i++) {
            if (i > 0 &&
                oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                rk[sa[i]] = rankCnt;
            } else {
                rk[sa[i]] = ++rankCnt;
            }
        }
        w <<= 1;
    }
    for (int i = 0; i < len2; i++) {
        //printf("%d ", sa[i]);
        if (sa[i] < len) {
            printf("%c", s[sa[i] + len - 1]);
        }
    }
    puts("");
}

int main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    //ios::sync_with_stdio(false);
    solve();

}
