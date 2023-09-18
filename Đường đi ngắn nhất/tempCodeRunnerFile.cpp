#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define MAX_N 500
#define NO_EDGE 99999

typedef struct{
	int n;
	int W[MAX_N][MAX_N];
}Graph;

void init_graph(Graph *G,int n){
	G->n = n;
	for(int i = 1;i<=n;i++)
		for(int j = 1; j<=n;j++)
			G->W[i][j] = NO_EDGE;
}

void add_edge(Graph *G,int u,int v, int w){
	G->W[u][v] = w;
}

//Thuat toan FLoyd - Warshall tim duong di ngan nhat giua moi cap dinh
#define oo 99999

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void FloydWarshall(Graph *pG){
	int u,v,k;
	for( u = 1; u<=pG->n;u++)
		for(v = 1; v<= pG->n; v++){
			pi[u][v] = oo;
			next[u][v] = -1;
		}
	for(u = 1;u<=pG->n;u++)
		pi[u][u] = 0;
		
	for(u = 1;u <= pG->n;u++)
		for(v = 1; v<= pG->n; v++){
			if(pG->W[u][v] != NO_EDGE){
				pi[u][v] = pG->W[u][v]; // di truc tiep tu u -> v
				next[u][v] = v;
			}
		}
	
	for(k = 1;k<=pG->n; k++)
		for(u = 1;u <= pG->n;u++){
			if(pi[u][k]==oo )
				continue;
			for(v = 1; v<= pG->n; v++){
			    if(pi[k][v]==oo )
				    continue;
				    
				if(pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
			}
		}
		
			
				
	
	// Kiem tra chu trinh am (neu can thiet)
}

int main(){
	Graph G;
	int n, m, u, v, w, e;

	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e=1; e<=m; e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
		G.W[u][v]=w;
	}
	FloydWarshall(&G);
	for(u=1; u<=G.n; u++)
		for(v=1; v<=G.n; v++){
 		    if(pi[u][v]==oo){
 				printf("%d -> %d: NO PATH\n",u,v);
 			}
 			else
				printf("%d -> %d: %d \n",u,v,pi[u][v]);
		}
			
	return 0;
}