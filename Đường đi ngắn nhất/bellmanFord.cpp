#include <stdio.h>

#define Max_ 100

typedef struct{
    int u, v, w;
}Edge;
typedef struct 
{
    /* data */
    int n,m;
    Edge edges[Max_];
}Graph;

void initGraph(Graph *G, int n){
    G->n=n;
    G->m=0;
}
void add_Edge(Graph *G, int u, int v, int w){
    G->edges[G->m].u=u;
    G->edges[G->m].v=v;
    G->edges[G->m].w=w;
    G->m++;
}
/// thuat toan
#define oo 99999
int pi[Max_];
int p[Max_];
int negative =0;
void bellmanFord(Graph *G, int s){
        
    for(int i =1;i<=G->n;i++){
        pi[i]=oo;
    }

    pi[s]=0;
    p[s]=-1;

    for(int i =1;i<G->n;i++){

        for(int j = 0;j<G->m;j++){
            int u = G->edges[j].u;
            int v = G->edges[j].v;
            int w = G->edges[j].w;

            if(pi[u]==oo)
                continue;

            if(pi[u]+w<pi[v]){
                pi[v]=pi[u]+w;
                p[v]=u;
            }

        }

    }

    for(int j = 0;j<G->m;j++){
            int u = G->edges[j].u;
            int v = G->edges[j].v;
            int w = G->edges[j].w;

            if(pi[u]==oo)
                continue;

            if(pi[u]+w<pi[v]){
                negative=1;
                break;
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
        add_Edge(&G, u, v,w);
    }
    int s;
    scanf("%d", &s);
    bellmanFord(&G, s);

    if(negative==1){
        printf("negative cycle");
    }else{
        printf("ok");
    }

    return 0;
}