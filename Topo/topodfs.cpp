#include <stdio.h>

#define Max_ 100

typedef struct
{
    /* data */
    int u, v;
} Edge;
typedef struct
{
    /* data */
    Edge edges[Max_];
    int n, m;
} Graph;
void init_Graph(Graph *G, int n)
{
    G->n = n;
    G->m=0;
}
void add_Edge(Graph *G, int u, int v)
{
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->m++;
}
int adjacent(Graph *G, int u, int v)
{
    for (int i = 0; i < G->m; i++)
    {
        if (G->edges[i].u == u && G->edges[i].v == v)
            return 1;
    }
    return 0;
}
// khai bao hang doi
typedef struct
{
    /* data */
    int front, rear;
    int A[Max_];
} Queue;
void makenullQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
}
int isEmptyQueue(Queue Q)
{
    return Q.front == -1;
}
void enQueue(Queue *Q, int x)
{
    if (isEmptyQueue(*Q))
    {
        Q->front++;
    }
    Q->rear++;
    Q->A[Q->rear] = x;
}
void deQueue(Queue *Q)
{
    Q->front++;
    if (Q->front > Q->rear)
        makenullQueue(Q);
}
int front(Queue Q)
{
    return Q.A[Q.front];
}
// khai bao cau truc list
typedef struct
{
    /* data */
    int size;
    int data[Max_];
} List;
void makenullList(List *L)
{
    L->size = 0;
}
int isEmptyList(List L)
{
    return L.size == 0;
}
void push(List *L, int x)
{
    L->data[L->size] = x;
    L->size++;
}
void pop(List *L)
{
    L->size--;
}
int element_at(List L, int i){
    return L.data[i-1];
}

int mark[Max_];
void dfs(Graph *G,int u, List *L){
	mark[u]=1;
	for(int v =1;v<=G->n;v++){
		if(adjacent(G, u, v)){
			if(mark[v]==0)
				dfs(G, v, L);
		}
	}
	push(L, u);
}
void topo_sort(Graph *G, List *L)
{



	for(int i =1;i<=G->n;i++){
    	mark[i]=0;
	}

	makenullList(L);
	for(int i =1;i<=G->n;i++){
		if(mark[i]==0)
			dfs(G, i,L);
	}
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_Graph(&G, n);

    for(int i =0;i<m;i++){
        int u, v;
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }
	List L;
	topo_sort(&G, &L);
	for(int i = L.size;i>=1;i--){
		printf("%d ", element_at(L, i));
	}
}