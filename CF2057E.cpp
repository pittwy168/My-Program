
//TO DO
#include<bits/stdc++.h>
#define int  long long 
using namespace std;

const int N=410, mod=998244353, INF=1e18;
int T, m,n, q, p[N], d[N], head[N], cnt;
bool fx[N][N];

struct pt{
	int u,v,w;	
} a[N*N];

bool cmp(pt a, pt b){
	return a.w<b.w;
}

int find(int x) {
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
} 

void merge(int x,int y) {
	p[find(x)] = p[y];	
}



struct edge{
    int to, next, dis;	
} e[2*N];

inline void add_edge( int u, int v, int d ){
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

vector<int> eg[N][N],c[N];

void dfs(int u, int f){
	fx[u][u]=1;
	c[u].push_back(u);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==f) continue;
		d[v]=e[i].dis;		
		dfs(v,u);
		for(int j=0;j<c[v].size();j++){
			c[u].push_back(c[v][j]);
			fx[u][c[v][j]]=1;
		} 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(fx[u][i]!=fx[u][j]) eg[i][j].push_back(d[u]);
		}
	}
}

void work(){
	cin>>n>>m>>q;
	cnt=0;
	for(int i=1;i<=n;i++){
		p[i]=i;
		head[i]=0;
		c[i].clear();
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			eg[i][j].clear();
			fx[i][j]=0;
		} 
	}
	for(int i=1;i<=m;i++){
		//int u,v,w; 
		cin>>a[i].u>>a[i].v>>a[i].w;	
	} 
	sort(a+1,a+m+1, cmp);
	for(int i=1;i<=m;i++){
		int u0=find(a[i].u), v0=find(a[i].v);
		if(u0!=v0){
			add_edge(a[i].u, a[i].v, a[i].w);
			add_edge(a[i].v, a[i].u, a[i].w);
			merge(u0,v0);
		}
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			sort(eg[i][j].begin(),eg[i][j].end());
			reverse(eg[i][j].begin(),eg[i][j].end());
		} 
	}	
	for(int i=1;i<=q;i++){
		int u,v,k; cin>>u>>v>>k;
		if(u>v) swap(u,v);
		cout<<eg[u][v][k-1]<<endl;
	}
	return;
}
signed main(){
	cin>>T;
	while(T--){
		work();	
	}
	return 0;
}


