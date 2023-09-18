#include <stdio.h>
#include <stdlib.h>
#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_Element 40
typedef struct
{
    int n; // so dinh
    int A[MAX_Vertices][MAX_Vertices];
} Graph;
void init_Graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++) // so dong
    {
        for (j = 1; j <= G->n; j++) // so cot
        {
            G->A[i][j] = 0;
        }
    }
}
void add_Edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}
// kiem tra 2 diem co la lang gieng cua nhau hay la khong
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}
// int adjacent(Graph G, int x, int y){
//     return G.A[x][y]==1;
// }

// tinh bac cua dinh
int degree(Graph *G, int x)
{
    int deg = 0, i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->A[i][x] == 1)
            deg++;
    }
    return deg;
}
// int degree(Graph G, int x){
//     int deg =0, i;
//     for(i =1; i<=G.n;i++){
//         if(G.A[i][x]==1)
//             deg++;
//     }
//     return deg;
// }

// khai bao cau truc cua danh sach lien ket List
typedef struct
{
    int size; // so phan tu
    int Data[MAX_Length];
} List;
void makenullList(List *L)
{
    L->size = 0;
}
// them phan tu vao cuoi danh sach
void push_back(List *L, int x)
{
    L->Data[L->size] = x;
    L->size++;
}
// lay gia tri cua phan tu
int element_at(List *L, int i)
{
    return L->Data[i - 1];
}
// tim cac dinh lien ke voi dinh i
List neighbors(Graph *G, int i)
{
    List L;
    makenullList(&L);
    int k;
    for (k = 1; k <= G->n; k++)
    {
        if (G->A[k][i] == 1)
            push_back(&L, k);
    }
    return L;
}
// cai dat cau truc hang doi
// khai bao cau truc hang doi
typedef struct
{
    int data[MAX_Element];
    int front, rear;
} Queue;
void makenullQueue(Queue *Q)
{
    Q->front = -1;
    Q->rear = -1;
}
int emptyQueue(Queue Q)
{
    return Q.front == -1;
}
int fullQueue(Queue Q)
{
    return (Q.rear - Q.front + 1) == MAX_Element;
}
int front(Queue Q)
{
    return Q.data[Q.front];
}
// ham xoa o dau hang
void deQueue(Queue *Q)
{
    if (!emptyQueue(*Q))
    {
        Q->front++;
        if (Q->front > Q->rear)
        {
            makenullQueue(Q);
        }
    }
}
// them phan tu vao cuoi hang
void enQueue(Queue *Q, int x)
{
    if (!fullQueue(*Q))
    {
        if (emptyQueue(*Q))
        {
            Q->front++;
        }
        else if (Q->rear == MAX_Element - 1)
        {
            int i;
            for (i = Q->front; i <= Q->rear; i++)
            {
                Q->data[i - Q->front] = Q->data[i];
            }
            Q->front = 0;
            Q->rear = Q->rear - Q->front;
        }
        Q->rear++;
        Q->data[Q->rear] = x;
    }
}
int top_Queue(Queue *Q)
{
    return Q->data[Q->front];
}
//=======================================
List breath_first_search(Graph *G, int x)
{
    Queue Q;
    makenullQueue(&Q);

    int mark[MAX_Vertices];
    int i;
    for (i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
    }
    List l_BFS;
    makenullList(&l_BFS);
    enQueue(&Q, x);
    while (!emptyQueue(Q))
    {
        int k = top_Queue(&Q);
        deQueue(&Q);

        if (mark[k] == 1)
            continue;

        push_back(&l_BFS, k);
        mark[k] = 1;
        List list = neighbors(G, k);
        for (i = 1; i <= list.size; i++)
        {
            int v = element_at(&list, i);
            if (mark[v] == 0)
                enQueue(&Q, v);
        }
    }
    return l_BFS;
}
int main()
{
    Graph G;
    freopen("BFS.txt", "r", stdin);
    int n, m, u, v, i, j;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%d ", G.A[i][j]);
        }
        printf("\n");
    }

    int mark_bfs[MAX_Vertices];
    for (j = 1; j <= G.n; j++)
    {
        mark_bfs[j] = 0;
    }

    for (j = 1; j <= G.n; j++)
    {
        if (mark_bfs[j] == 0)
        {
            List list_bfs = breath_first_search(&G, j);
            for (i = 1; i <= list_bfs.size; i++)
            {   int v = element_at(&list_bfs, i);
                printf("%d ", v);
                mark_bfs[v]=1;
            }
        }
    }

    return 0;
}