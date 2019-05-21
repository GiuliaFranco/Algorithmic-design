#include <iostream>
#include <climits>
#include <ctime>
#include <cstdlib>
using namespace std;

int min(int ** a,int vertex){
	int def_min=INT_MAX, index;
	for(int i=0;i<vertex;i++){
		if(a[1][i]==0){
			def_min=min(a[0][i],def_min);
			index=i;
		}
	}
	return index;
};

void init(int vertex,int **mat,int S){
	 for(int j=0;j<2;j++){ mat[j]=(int*)malloc(sizeof(int)*vertex);}
        for(int i=0;i<vertex;i++){
                mat[0][i]=INT_MAX;
                mat[1][i]=0; //not visited

        }
        mat[0][S]=0;   //dist to source vertex set to zero

};

void relax(int **G,int **mat,int vertex){
	int u=min(mat,vertex);  //any vertex not yet visited and with min distance
                mat[1][u]=1;
                for(int j=0;j<vertex;j++){
                        if(mat[1][j]==0 && G[u][j] && mat[0][u]!=INT_MAX && mat[0][u]+G[u][j]<mat[0][j]){
                                mat[0][j]=mat[0][u]+G[u][j];
                        }
                }
};
void Dijkstra(int ** G,int S,int vertex){
	int **mat=(int**)malloc(sizeof(int*)*2);
	//initialize all vertex to inf and not visited
	init(vertex,mat,S);
	int i=0;
	while(i!=vertex-1){
		relax(G,mat,vertex);
		i++;
	}
	for(int j=0;j<2;j++){ free(mat[j]);}
        free(mat);
};
//contain all vertices not yet finalized
void Fill_graph(int ** G,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			G[i][j]=rand() % 50;		
        	}
	}
};


int main()
{
	
	for(int n=10;n<250;n+=10){
		int **array;
		array = new int *[n];
		for(int i = 0; i <n; i++) array[i] = new int[n];
		Fill_graph(array,n);
		clock_t begin = clock();
		Dijkstra(array,0,n);
		clock_t end = clock();
		cout<<n<<" "<<double(end - begin) / CLOCKS_PER_SEC<<endl;
		for(int i = 0; i <n; i++) free(array[i]);
		free(array);
	}
	return 0;	                        
}	


