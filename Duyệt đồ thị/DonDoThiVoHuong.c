#include <stdio.h>
#include <stdlib.h>
#define MAX_Vertices 20
#define MAX_Length 20
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
    return G->A[x][y] !=0;
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

//khai bao cau truc cua danh sach lien ket List
typedef struct
{
    int size;// so phan tu
    int Data[MAX_Length];
}List;
void makenullList(List *L){
    L->size = 0;
}
//them phan tu vao cuoi danh sach
void push_back(List *L, int x){
    L->Data[L->size]= x;
    L->size++;
}
//lay gia tri cua phan tu
int element_at(List *L, int i){
    return L->Data[i-1];
}
//tim cac dinh lien ke voi dinh i
List neighbors(Graph *G, int i){
    List L;
    makenullList(&L);
    int k;
    for(k = 1; k<=G->n;k++){
        if(G->A[k][i]==1)
            push_back(&L, k);
    }
    return L;
}

int main()
{
    Graph G;

    FILE *f = fopen("DonDoThiVoHuong.txt", "r");
    int n, m; // so dinh-so cung
    fscanf(f, "%d%d", &n, &m);
    init_Graph(&G, n);
    int u, v, k;
    for (k = 1; k <= m; k++)
    {
        fscanf(f, "%d%d", &u, &v);
        add_Edge(&G, u, v);
    }
    fclose(f);
    printf("Bac cua cac dinh la : \n");
    int i;
    for (i = 1; i <= G.n; i++)
        printf("Degree(%d) = %d\n", i, degree(&G, i));

    printf("Dinh lien ke cua cac dinh la : \n");
    for(i=1;i<=G.n;i++){
        printf("Cac dinh lien ke cua dinh %d : [", i);
        List L = neighbors(&G,i);
        int j;
        for(j=1;j<=L.size;j++){
             printf("%d ", element_at(&L,j));
        }
        printf("]\n");
    }
    
    return 0;
}