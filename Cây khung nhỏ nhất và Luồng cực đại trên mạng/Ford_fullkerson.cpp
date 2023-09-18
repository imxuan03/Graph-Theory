#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define NO_EGDE 0
#define oo 99999

typedef struct{
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n;                                                 
}Graph;
void init_Graph(Graph *G, int n){
	G->n= n;

}

//cac bien ho tro
typedef struct{
	int dir;
	int p;
	int sigma;
}Lable;

Lable lables[MAXN]; //nhan cac dinh

void init_flow(Graph *G){
	for(int i = 1;i<=G->n;i++){
		for(int j = 1; j<=G->n;j++){
			G->F[i][j] = 0;
			
		}
	}
}

//Khai bao cau truc hang doi
typedef struct{
	int front, rear;
	int data[200];
}Queue;
void makenullQueue(Queue *Q){
	Q->front = -1;
	Q->rear=-1;
}
int isEmptyQueue(Queue Q){
	return Q.front == -1;
}
void enQueue(Queue *Q, int x){
	if(isEmptyQueue(*Q)){
		Q->front++;
	}
	Q->rear++;
	Q->data[Q->rear]=x;
}
void deQueue(Queue *Q){
	Q->front++;
	if(Q->front>Q->rear){
		makenullQueue(Q);
	}
}
int top(Queue Q){
	return Q.data[Q.front];
}
int min(int a, int b){
	return (a>b)?b:a;
}

int FordFullkerson(Graph *G, int s, int t){
	//1. Khoi tao luong
	init_flow(G);
	int max_flow = 0;
	
	//2. Lap
	Queue Q;
	do{
		//buoc 1
		for(int u =1 ; u<=G->n;u++)
			lables[u].dir = 0;
			
		//gan nhan s
		lables[s].dir +=1;
		lables[s].p = s;
		lables[s].sigma = oo;
		
		//khoi tao Q
		makenullQueue(&Q);
		enQueue(&Q, s);
		
		//Buoc 2
		int found = 0;
		while(!isEmptyQueue(Q)){
			int u = top(Q);
			deQueue(&Q);
			
			
			for(int v =1 ; v<=G->n;v++){
				if(G->C[u][v]!=NO_EGDE&&lables[v].dir == 0 && G->F[u][v]<G->C[u][v]){
					lables[v].dir +=1;
					lables[v].p=u;
					lables[v].sigma = min(lables[u].sigma, G->C[u][v] - G->F[u][v]);
					enQueue(&Q, v);
				}
			}
			
			for(int x = 1; x<= G->n;x++){
				if(G->C[x][u]!=NO_EGDE &&lables[x].dir == 0 && G->F[x][u]>0){
					lables[x].dir =-1;
					lables[x].p=u;
					lables[x].sigma = min(lables[u].sigma, G->F[u][x]);
					enQueue(&Q, x);
				}
			}
			
			if(lables[t].dir != 0){
				found =1;
				break;
			}
		}
		
		//buoc 3
		if(found ==1){
			int sigma = lables[t].sigma;
			
			int u =t;
			while(u!=s){
				int p = lables[u].p;
				if(lables[u].dir>0)
					G->F[p][u]+=sigma;
				else
					G->F[u][p] -=sigma;
				
				u = p;
			}
			
			max_flow += sigma;
			
		}
		if(found!=1)
			break;
	}while(1);
	
	return max_flow;
}
int main(){
	Graph G;
	int m , n;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for(int e=0;e<m;e++){
		int u , v, c;
		scanf("%d%d%d", &u, &v, &c);
		G.C[u][v]=c;
	}
	int max_flow = FordFullkerson(&G, 1, n);
	printf("Max flow: %d\n", max_flow);
	
	//in S, T
	//in S
	printf("S: ");
	for(int u =1;u<=n;u++)
		if(lables[u].dir != 0)
			printf("%d ",u);
			
	printf("\nT: ");
	for(int u =1;u<=n;u++)
		if(lables[u].dir == 0)
			printf("%d ",u);
	
	return 0;
}