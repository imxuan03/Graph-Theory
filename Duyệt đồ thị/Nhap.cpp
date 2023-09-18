#include <stdio.h>

#define Max_ 20

typedef struct{
	int u,v;
}Edge;
typedef struct 
{
	/* data */
	int n, m;
	Edge edges[Max_];
}Graph;
//khoi tao
void init_graph(Graph *G, int n){
	G->n=n;
	G->m=0;
}
void add_edge(Graph *G, int u, int v){
	G->edges[G->m].u=u;
	G->edges[G->m].v=v;
	G->m++;

}
int adjacent(Graph *G, int u,int v){
	//u v co ke nhau khong
	for(int i =0;i<G->m;i++){
		if( (G->edges[i].u==u&&G->edges[i].v==v) ||
		(G->edges[i].v==u&&G->edges[i].u==v)){
			return 1;
		}
	}
			
	return 0;
}

// khai bao hang doi
#define Max_Element 100
typedef struct Nhap
{
	/* data */
	int top;
	int data[Max_Element];
}Stack;
void makenullStack(Stack *S){
	S->top=-1;
}
void push_Stack(Stack *S, int x){
	S->top++;
	S->data[S->top]=x;
}
int top(Stack S){
	return S.data[S.top];
}
void pop(Stack *S){
	S->top--;
}
int isEmpty(Stack S){
	return S.top==-1;
}
//======================

int mark[Max_Element];
int parent[Max_Element];
void DFS(Graph *G, int x, int mark[]){
	Stack S;
	makenullStack(&S);
	push_Stack(&S, x);
	parent[x]=-1;

	while(!isEmpty(S)){
		int u = top(S);
		pop(&S);

		if(mark[u]==1)
			continue;

		mark[u]=1;

		for(int i =1;i<=G->n;i++){
			if(adjacent(G,u,i)&&mark[i]==0){
				push_Stack(&S,i);	
				parent[i]=u;		
			}
		}

	}


}

int main(){
	Graph G;
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(int i =0;i<m;i++){
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}	
	for(int i =1;i<=G.n;i++){
		mark[i]=0;
		parent[i]=0;
	}
	for(int i =1;i<=n;i++){
		if(mark[i]==0)
			DFS(&G, i, mark);
	}
	for(int i =1;i<=n;i++){
		printf("%d %d\n", i, parent[i]);
	}
}
