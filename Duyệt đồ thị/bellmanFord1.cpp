#include <stdio.h>

#define Max_ 100


typedef struct 
{
    /* data */
    int u, v , w;
}Edge;

typedef struct 
{
    /* data */
    int m, n;
    Edge edges[Max_];
}Graph;

void initGraph(Graph *G, int n){
    G->n=n;
    G->m=0;
}
void addEdge(Graph *G, int u, int v, int w){
    G->edges[G->m].u=u;
    G->edges[G->m].v=v;
    G->edges[G->m].w=w;
    G->m++;
}
//==========================
//thuat toan
#define oo 99999
int pi[Max_];
int p[Max_];

void bellmanFord(Graph *G, int s){
    for(int i =1;i<=G->n;i++)
    {
        pi[i]=oo;
    }
    pi[s]=0;
    p[s]=-1;

    for(int i =1;i<G->n;i++){

        for(int j=0;j<G->m;j++){
            int u = G->edges[j].u;
            int v = G->edges[j].v;
            int w = G->edges[j].w;

            if(pi[u]==oo)
                continue;

            if(pi[u]+ w <pi[v]){
                pi[v]=pi[u]+w;
                p[v]=u;
            }
        }

    }

}


int main(){
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);

    initGraph(&G, n);

    for(int i =0;i<m;i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(&G, u, v,w);
    }

    bellmanFord(&G, 1);

    for(int i =1;i<=n;i++){
        printf("pi[%d] = %d, p[%d] = %d\n",i,pi[i], i, p[i]);
    }
        
    
    return 0;
}
