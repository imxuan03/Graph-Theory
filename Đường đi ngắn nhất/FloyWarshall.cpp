#include <stdio.h>
#define Max_ 100
#define NO_EDGE 99999
typedef struct
{
    /* data */
    int n, m;
    int A[Max_][Max_];
} Graph;
void init_Graph(Graph *G, int n)
{
    G->n = n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // khoi tao
            G->A[i][j] = NO_EDGE;
        }
    }
}
void add_Edge(Graph *G, int u, int v, int w)
{

        G->A[u][v] = w;
 
}
/// thuat toan
#define oo 99999

int pi[Max_][Max_];
int next[Max_][Max_];

void FloyWarshall(Graph *G){
    for(int u =1;u<=G->n;u++){
        for(int v =1 ; v<=G->n;v++){
            pi[u][v]=oo;
            next[u][v]=-1;
        }
    }

    for(int u =1 ;u<=G->n;u++){
        pi[u][u]=0;
    }
        

    for(int u =1;u<=G->n;u++){
        for(int v =1 ; v<=G->n;v++){
            if(G->A[u][v]!=NO_EDGE){
                pi[u][v]=G->A[u][v];
                next[u][v]=v;

            }
        }
    }
    for(int k =1;k<=G->n;k++){
        for(int u =1;u<=G->n;u++){
            for(int v =1 ; v<=G->n;v++){
                if(pi[u][v]==oo)
                    continue;

                if(pi[u][k]+pi[k][v]<pi[u][v]){
                    pi[u][v]=pi[u][k]+pi[k][v];
                    next[u][v]=next[u][k];
                }
            }
        }
    }

}


int main(){
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);

    init_Graph(&G, n);

    for(int i =0;i<m;i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_Edge(&G, u, v,w);
    }
    FloyWarshall(&G);
    for(int u =1;u<=n;u++){
        for(int v =1 ; v<=n;v++){
            printf("%d -> %d: ", u, v);
            if(pi[u][v]!=oo)
                printf("%d\n", pi[u][v]);
            else    
                printf("NO PATH\n");
        }
    }

    return 0;
}