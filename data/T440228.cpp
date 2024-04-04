#include<iostream>
#define lson u*2
#define rson u*2+1
#define int long long
using namespace std;
const int MAXN = 1e5+114;
const int inf = 1e9;
const int mod = 1e16;

int point[MAXN*4],mn[MAXN*4],mx[MAXN*4];
int ctag[MAXN*4],xtag[MAXN*4],ptag[MAXN*4],cbool[MAXN*4];

void print(int u);

void tag1(int u,int l,int r){//ctag
    int mid = (l+r)/2;
    if(cbool[u] == 1){
        xtag[lson] = xtag[rson] = 1;
        ptag[lson] = ptag[rson] = 0;
        mn[lson] = ctag[u];
        mn[rson] = ctag[u];
        mx[lson] = ctag[u];
        mx[rson] = ctag[u];
        point[lson] = ((mid-l+1)*ctag[u])%mod;
        point[rson] = ((r-mid)*ctag[u])%mod;
        cbool[u] = 0;
    }
}

void tag2(int u){
    xtag[lson] = (xtag[u]*xtag[lson])%mod;
    xtag[rson] = (xtag[u]*xtag[rson])%mod;
    ptag[lson] = (xtag[u]*ptag[lson])%mod;
    ptag[rson] = (xtag[u]*ptag[rson])%mod;
    ptag[lson] = (ptag[u]+ptag[lson])%mod;
    ptag[rson] = (ptag[u]+ptag[rson])%mod;
    mx[lson] = (mx[lson]*xtag[lson]+ptag[lson])%mod;
    mn[lson] = (mn[lson]*xtag[lson]+ptag[lson])%mod;
    mx[rson] = (mx[rson]*xtag[rson]+ptag[rson])%mod;
    mn[rson] = (mn[rson]*xtag[rson]+ptag[rson])%mod;
    point[lson] = (xtag[lson]*point[lson])%mod;
    point[lson] = (ptag[lson]+point[lson])%mod;
    point[rson] = (xtag[rson]*point[rson])%mod;
    point[rson] = (ptag[rson]+point[rson])%mod;
    xtag[u] = 1;
    ptag[u] = 0;
}

void pushup(int u){
    int ll,rr;
    ll = (point[lson]*xtag[lson]+ptag[lson])%mod;
    rr = (point[rson]*xtag[rson]+ptag[rson])%mod;

    point[u] = (ll+rr)%mod;
    mn[u] = min(mn[lson],mn[rson]);
    mx[u] = max(mx[lson],mx[rson]);
}

void pushdown(int u,int l,int r){
    tag1(u,l,r),tag2(u);
}

void build(int u,int l,int r){
    //cout<<l<<" "<<r<<endl;
    if(l==r){
        cin>>point[u];
        mx[u] = point[u];
        mn[u] = point[u];
        return;
    }
    int mid = (l+r)/2;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(u);
}

int n,q;
//L,R is target
void update1(int u,int l,int r,int L,int R,int d){
    //  cout<<u<<" "<<l<<" "<<r<<endl;
    if(L<=l && r<=R){
        mn[u] = d;
        mx[u] = d;
        point[u] = ((r-l+1)*d)%mod;
        cbool[u] = 1;
        ctag[u] = d;
        pushdown(u,l,r);
        return;
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    // cout<<mid<<endl;
    if(L<=mid) update1(lson,l,mid,L,R,d);
    if(R>=mid+1) update1(rson,mid+1,r,L,R,d);
    // cout<<u<<endl;
    pushup(u);
}

void update2(int u,int l,int r,int L,int R,int d){
    if(L<=l && r<=R){
        // xtag[u]*=d;
        // ptag[u]*=d;
        // point[u]*=xtag[u];
        // point[u]+=ptag[u];
        point[u]=(d*point[u])%mod;
        mx[u]=(d*mx[u])%mod;
        mn[u]=(d*mn[u])%mod;
        xtag[u]=(d*xtag[u])%mod;
        ptag[u]=(d*ptag[u])%mod;
        pushdown(u,l,r);
        return;
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    if(L<=mid) update2(lson,l,mid,L,R,d);
    if(R>=mid+1) update2(rson,mid+1,r,L,R,d);
    pushup(u);
}
void update3(int u,int l,int r,int L,int R,int d){
    // cout<<u<<" "<<l<<" "<<r<<endl;
    // print(4);cout<<endl;
    if(L<=l && r<=R){
        ptag[u]=(d+ptag[u])%mod;
        mx[u]=(d+mx[u])%mod;
        mn[u]=(d+mn[u])%mod;
        point[u]=(d*(r-l+1)+point[u])%mod;
        pushdown(u,l,r);
        return;
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    if(L<=mid) update3(lson,l,mid,L,R,d);
    if(R>=mid+1) update3(rson,mid+1,r,L,R,d);
    
    
    pushup(u);
}



int query_mx(int u,int l,int r,int L,int R){
    if(L<=l && r<=R){
        return mx[u];
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    int res = -inf;
    if(L<=mid) res = max(res,query_mx(lson,l,mid,L,R));
    if(R>=mid+1) res = max(res,query_mx(lson,mid+1,r,L,R));
    return res;
}

int query_mn(int u,int l,int r,int L,int R){
    if(L<=l && r<=R){
        return mn[u];
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    int res = inf;
    if(L<=mid) res = min(res,query_mn(lson,l,mid,L,R));
    if(R>=mid+1) res = min(res,query_mn(lson,mid+1,r,L,R));
    return res;
}

int query_sum(int u,int l,int r,int L,int R){
    if(L<=l && r<=R){
        return point[u];
    }
    pushdown(u,l,r);
    int mid = (l+r)/2;
    int res = 0;
    if(L<=mid) res = (res+query_sum(lson,l,mid,L,R))%mod;
    if(R>=mid+1) res = (res+query_sum(lson,mid+1,r,L,R))%mod;
    return res;
}

signed main(){
    cin>>n>>q;
    for(int i = 1;i<=n*4+114;i++) xtag[i] = 1;
    build(1,1,n);
    int id,l,r,x;
    while(q--){
        cin>>id>>l>>r>>x;
        if(id == 1){
            update1(1,1,n,l,r,x);
            cout<<query_sum(1,1,n,1,n)%mod<<" "<<(query_mx(1,1,n,1,n)-query_mn(1,1,n,1,n)+mod)%mod<<endl;
        }
        else if(id == 2){
            update2(1,1,n,l,r,x);
            cout<<query_sum(1,1,n,1,n)%mod<<" "<<(query_mx(1,1,n,1,n)-query_mn(1,1,n,1,n)+mod)%mod<<endl;
        }
        else if(id == 3){
            update3(1,1,n,l,r,x);
            cout<<query_sum(1,1,n,1,n)%mod<<" "<<(query_mx(1,1,n,1,n)-query_mn(1,1,n,1,n)+mod)%mod<<endl;
        }
    }
    //print(4);

}


void print(int n){
    int p = 1;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=(1<<(i-1));j++){
            cout<<mx[p++]<<" ";
        }
        cout<<endl;
    }
}