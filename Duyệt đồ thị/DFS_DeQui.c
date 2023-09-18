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
//===============
// Khai bao cau truc ngan xep
typedef struct
{
    int data[MAX_Element];
    int size;

} Stack;

void makenullStack(Stack *S)
{
    S->size = 0;
}
// them mot phan tu vao trong ngan xep
void push_Stack(Stack *S, int x)
{
    S->data[S->size] = x;
    S->size++;
}
// lay mot phan tu trong Stack
int top(Stack *S)
{
    return S->data[S->size - 1];
}
int emptyStack(Stack *S)
{
    return S->size == 0;
}
// xoa mot phan tu thuoc Stack
void pop(Stack *S)
{
    S->size--;
}
List dept_first_search(Graph *G, int x)
{
    Stack S;
    makenullStack(&S);
    push_Stack(&S, x);

    List list_bfs;
    makenullList(&list_bfs);
    // khoi tao tat ca cac dinh chua duyet

    int mark[MAX_Vertices], i, j;

    for (i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
    }
    while (!emptyStack(&S))
    {
        int u = top(&S);
        pop(&S);
        if (mark[u] == 1)
        {
            continue;
        }
        // duyet dinh u
        //  printf("%d :", u);
        push_back(&list_bfs, u);
        mark[u] = 1;

        List L;
        L = neighbors(G, u);
        for (i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0)
            {
                push_Stack(&S, v);
            }
        }                                                                                                
    }
    return list_bfs;
}
//==================================
int mark[MAX_Vertices];
int parent[MAX_Vertices];
void DFS_Recursion(Graph *G, int u, int p){
    if(mark[u]==1)
        return;

    //danh dau parent
    parent[u]=p;

    // printf("Duyet %d \n", u);
    mark[u]=1;
    List list = neighbors(G, u);
    int i;
    for(i=1;i<=list.size;i++){
        int v = element_at(&list, i);
        DFS_Recursion(G,v,u);
    }

}
int main()
{
    Graph G;

    freopen("DFS_DeQui.txt","r",stdin);

    int n, m;
    scanf("%d%d", &n, &m);
    init_Graph(&G,n);
    int i, j, u ,v;
    //them cac cung vao Graph
    for(i=1;i<=m;i++){
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }
    
    for(i = 1;i<=n;i++){
        mark[i]=0;
        parent[i]=0;
    }
    for(i=1;i<=G.n;i++){
        if(mark[i]==0){
            DFS_Recursion(&G,i,0);
        }
    }  
    for(i=1;i<=G.n;i++){
        printf("\nParent %d la %d ", i, parent[i]);
    }
    
    return 0;
}