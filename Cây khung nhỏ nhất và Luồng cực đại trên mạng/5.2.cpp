#include <stdio.h>

#define Max_ 100
#define NO_EDGE 0

typedef struct{
	int n, m;
	int A[Max_][Max_];
}Graph;
void init_Graph(Graph *G, int n){
	G->n =n;
	G->m=0;
	for(int i =1;i<=n;i++){
		for(int j =1;j<=n;j++){
			G->A[i][j]=0;
		}
	}
}
void add_Edge(Graph *G, int u, int v, int w){
	G->A[u][v]=w;
	G->A[v][u]=w;
	
	G->m++;
}

//cac bien ho tro
#define oo 99999
int pi[Max_];
int p[Max_];
int mark[Max_];

int Prim(Graph *G, Graph *T, int s){
	for(int u =1;u<=G->n;u++){
		pi[u]=oo;
		p[u]=-1;
		mark[u]=0;
	}
	
	pi[s]=0;
	
	int u;
	for(int i =1;i<G->n;i++){
		
		int min = oo;
		for(int x = 1;x<=G->n;x++){
			if(mark[x]==0 && pi[x]<min){
				min=pi[x];
				u=x;
			}
		}
		
		mark[u]=1;
		
		for(int v = 1; v<=G->n;v++){
			if(G->A[u][v]!=NO_EDGE){
				if(mark[v]==0 && pi[v]> G->A[u][v]){
					pi[v]=G->A[u][v];
					p[v]=u;
				}
			}
		}
		
	}
	
	init_Graph(T, G->n);
	int sum_w=0;
	for(int u =1; u<=G->n;u++){
		if(p[u]!=-1){
			int w = G->A[p[u]][u];
			add_Edge(T, p[u], u, w);
			sum_w+=w;
		}
	}
	return sum_w;
}

int main(){
	
	int n, m;
	scanf("%d%d", &n, &m);
	Graph G;
	Graph T;
	
	init_Graph(&G, n);
	for(int i =0;i<m;i++){
		int u,v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_Edge(&G, u, v, w);
	}
	
	printf("%d\n", Prim(&G, &T, 1));
	
	for(int i =1;i<=T.n;i++){
		for(int j =1;j<=T.n;j++){
			if(T.A[i][j]!=NO_EDGE && i<j)
				printf("%d %d %d\n",i, j, T.A[i][j] );
		}
	}
	

	return 0;
}