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
    if (u == v)
    {
        G->A[u][u] = w;
    }
    else
    {
        G->A[u][v] = w;
        G->A[v][u] = w;
    }
}
//=======================
// thuat toan
#define oo 99999
int mark[Max_];
int pi[Max_];
int p[Max_];

void MooreDijkstra(Graph *G, int s)
{

    for (int i = 1; i <= G->n; i++)
    {
        pi[i] = oo;
        mark[i] = 0;
    }
    pi[s] = 0;
    p[s] = -1;

    for (int i = 1; i < G->n; i++)
    {
        int u;

        int min_pi = oo;
        for (int j = 1; j <= G->n; j++)
        {
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }
        }

        // 2
        mark[u] = 1;
        // 3
        for (int v = 1; v <= G->n; v++)
        {
            if (G->A[u][v] != NO_EDGE && mark[v] == 0)
            {
                if (pi[u] + G->A[u][v] < pi[v])
                {
                    pi[v] = pi[u] + G->A[u][v];
                    p[v] = u;
                }
            }
        }
    }
}

int main()
{

    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_Edge(&G, u, v, w);
    }

    // MooreDijkstra(&G, 1);
    // for(int i =1;i<=n;i++){
    //     printf("pi[%d] = %d, p[%d] = %d\n",i,pi[i], i, p[i]);
    // }
    int s, t;
    scanf("%d%d", &s, &t);

    MooreDijkstra(&G, s);
    printf("%d", pi[t]);

    return 0;
}
