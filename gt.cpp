    /*
 * Define C to be the given sequence of numbers.
 * Notice that the answer to a query is either x, x or x, x + 1. (or -1 -1)
 * The first case (x, x) is obvious. If C[i] = v, l <= i <= r, then obviously i, i is the right answer.
 * The second case (x, x+1) is less obvious, but there's never a case where we must take the lca of more than
 * two adjacent numbers in the array.
 *
 * Now this problem can be solved by maintaining two arrays of sets A, B.
 * A[v] handles the first case; it contains integers x where C[x] = v.
 * B[v] handles the second case; it contains integers x where lca(C[x], C[x+1]) = v.
 *
 * When handling queries of type 1, simply update A, B accordingly.
 */ 
    #define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
    #include <bits/stdc++.h>
    using namespace std;
    #define sqr 400
    #define mid (l+r)/2
    #define pb push_back
    #define ppb pop_back
    #define fi first
    #define se second
    #define lb lower_bound
    #define ub upper_bound
    #define ins insert
    #define era erase
    #define C continue
    #define mem(dp,i) memset(dp,i,sizeof(dp))
    #define mset multiset
    typedef long long ll;
    typedef short int si;
    typedef long double ld;
    typedef pair<int,int> pi;
    typedef pair<ll,ll> pll;
    typedef vector<int> vi;
    typedef vector<ll> vll;
    typedef vector<pi> vpi;
    typedef vector<pll> vpll;
    const ll mod=1e9+7;
    const ll inf= 4e18;
    const ld pai=acos(-1);
    int n , m , q;
    vi v[200009];
    int w[200009] , dp[200009][20] , a[200009];
    set<int>s[200009],t[200009];
    void dfs(int node,int p){
            dp[node][0]=p;
            w[node]=w[p]+1;
            for ( auto u : v[node]){
                    if ( u == p ) C ;
                    dfs ( u, node ) ;
            }
    }
    void build () {
            dfs ( 0,0 );
            for ( int j =1 ;j < 20 ;j ++ ) {
                    for ( int i =0 ;i < n ;i ++ ) {
                            dp[i][j] = dp[dp[i][j-1]][j-1];
                    }
            }
    }
    int lca(int a,int b ){
            if ( w[a] < w[b] ) swap ( a , b );
            int l = w[a] - w[b];
            for ( int i =0 ;i <20 ;i ++ ){
                    if ( ( l & ( 1<<i ) ) ) a= dp[a][i];
            }
            if ( a == b ) return a ;
            for ( int i = 19 ; i>=0 ;i -- ){
                    if ( dp[a][i] != dp[b][i] ) {
                            a=dp[a][i];
                            b=dp[b][i];
                    }
            }
            return dp[a][0];
    }
    int main (){
            fast;
            cin >> n >> m >> q ;
            for ( int i =0 ;i < n-1 ;i ++ ) {
                    int a,b;
                    cin >> a >> b ;
                    a -- , b -- ;
                    v[a].pb ( b );
                    v[b].pb ( a );
            }
            build();
            for ( int i =0 ;i < m ;i ++ ) {
                    cin >> a[i];
                    a[i] -- ;
                    s[a[i]].ins ( i ) ;
                    if ( i ) {
                            t[lca(a[i],a[i-1])].ins(i);
                    }
            }
            while ( q -- ) {
                    int ty ;
                    cin >> ty ;
                    if ( ty == 1 ){
                            int pos , id ;
                            cin >> pos >> id ;
                            pos -- , id -- ;
                            s [ a[pos] ] .era(pos);
                            s [ id     ] .ins(pos);
                            if ( pos ) t[lca(a[pos],a[pos-1])].era(pos);
                            if ( pos<m-1) t[lca(a[pos],a[pos+1])].era(pos+1);
                            a[pos]=id;
                            if ( pos ) t[lca(a[pos],a[pos-1])].ins(pos);
                            if ( pos<m-1) t[lca(a[pos],a[pos+1])].ins(pos+1);
                    }
                    if ( ty == 2 ){
                            int l ,r , node;
                            cin >> l >> r >> node;
                            l -- ,r -- , node -- ;
                            auto it = s[node].lb(l);
                            if ( it != s[node].end() && *it<=r) {
                                    cout << *it+1 <<" " << *it+1 << endl;
                                    C;
                            }
                            it = t[node].ub(l);
                            if ( it !=t[node].end() && *it<=r ) {
                                    cout << *it <<" "<<*it+1<<endl;
                                    C;
                            }
                            cout << -1 <<" "<< -1 << endl;
     
                    }
            }
    }
