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
void topo_sort(Graph *G, List *L)
{
    int d[Max_];
    for(int i =1;i<=G->n;i++){
        d[i]=0;
        //tinh bat vao
        for(int j =1;j<=G->n;j++){
            if(adjacent(G, j, i))
                d[i]++;
        }
    }

    Queue Q;
    makenullQueue(&Q);
    for(int i =1;i<=G->n;i++){
        if(d[i]==0){
            enQueue(&Q, i);
        }
    }
    
    makenullList(L);

    while(!isEmptyQueue(Q)){
        int u = front(Q);
        deQueue(&Q);
        push(L, u);

        //xoa dinh u, giam bac vao cua cac dinh v ke u
        for(int v = 1; v<=G->n;v++){
            if(adjacent(G, u, v)){
                d[v]--;
                if(d[v]==0)
                    enQueue(&Q, v);
            }
        }
    }

}

int d[Max_];
#define oo 99999

int max(int x, int y){
	return (x>y)?x:y;
}
int min(int x, int y){
	return (x<y)?x:y;
}

int main()
{
    int n;
    scanf("%d", &n);
    Graph G;
    init_Graph(&G, n+2);
    int alpha = n+1, beta = n+2;
    
    d[alpha]=0;
    //doc danh sach cac cong viec
    for(int u = 1;u<=n;u++){
    	scanf("%d", &d[u]);
    	int x;
		do{
    		scanf("%d", &x);
    		if(x>0){
    			add_Edge(&G, x, u);
			}
		}while(x>0);
	}
	//them cung noi alpha voi cac dinh co bac vao = 0 vao alpha
	for(int u =1;u<=n;u++){
		int deg_neg =0;
		for(int x=1;x<=n;x++){
			if(adjacent(&G, x, u))
				deg_neg++;
		}
		
		if(deg_neg==0)
			add_Edge(&G, alpha, u);
	}
	//them cung noi cac dinh co bac ra = 0 va0 beta
	for(int u =1;u<=n;u++){
		int deg_pos =0;
		for(int v=1;v<=n;v++){
			if(adjacent(&G, u,v)){
				deg_pos++;
			}
		}
		
		if(deg_pos==0)
			add_Edge(&G, u, beta);
	}
	List L;
	topo_sort(&G, &L);
	//tinh t[u]
	int t[Max_];
	t[alpha]=0;
	
	for(int j=2;j<=L.size;j++){
		int u = element_at(L, j);
		t[u]=-oo;
		for(int x =1;x<=G.n;x++){
			if(adjacent(&G, x, u))
				t[u]= max(t[u], t[x]+d[x]);
		}
	}

	//tinh T[u]
	int T[Max_];
	T[beta]=t[beta];
	for(int j = L.size-1;j>=1;j--){
		int u = element_at(L,j);
		T[u]=+oo;
		for(int v = 1;v<=G.n;v++){
			if(adjacent(&G, u, v))
				T[u]=min(T[u], T[v]-d[u]);
		}
	}
	
	for(int i =1;i<=n;i++){
		printf("%d %d\n", t[i], T[i]);
	}

}