#include <stdio.h>

#define Max_ 100

typedef struct{
	int u, v;
	int w;
}Edge;
typedef struct{
	Edge edges[Max_];
	int n, m;
}Graph;
void init_Graph(Graph *G, int n){
	G->n =n;
	G->m=0;
}
void add_Edge(Graph *G, int u, int v, int w){
	G->edges[G->m].u=u;
	G->edges[G->m].v=v;
	G->edges[G->m].w=w;
	
	G->m++;
}

int parent[Max_];

int findRoot(int u){
	while(parent[u]!=u)
		u=parent[u];
		
	return u;
}

int Kruskal(Graph *G, Graph *T){
	//sap xep cac cung theo thu tu tang dan
	for(int i =0;i<G->m-1;i++){
		for(int j =i+1; j<G->m;j++){
			if(G->edges[i].w>G->edges[j].w){
				Edge temp = (G->edges[i]);
				(G->edges[i])= (G->edges[j]);
				(G->edges[j])=temp;
			}
		}
	}
	
	//khoi tao T 
	init_Graph(T, G->n);
	for(int u =1;u<=G->n;u++){
		parent[u]=u;
	}
	
	int sum_w=0;
	
	//duyet qua cac cung cua G da sap xep
	for(int e =0;e<G->m;e++){
		int u = G->edges[e].u;
		int v = G->edges[e].v;
		int w = G->edges[e].w;
		
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		if(root_u!=root_v){
			add_Edge(T, u,v, w);
			
			parent[root_v]=root_u;
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
	printf("%d\n", Kruskal(&G, &T));
	
	for(int i =0;i<T.n-1;i++){
	    if(T.edges[i].u>T.edges[i].v)
	        printf("%d %d %d\n",T.edges[i].v,T.edges[i].u,T.edges[i].w);
	    else
		    printf("%d %d %d\n",T.edges[i].u,T.edges[i].v,T.edges[i].w);
	}
	
	
	return 0;
}