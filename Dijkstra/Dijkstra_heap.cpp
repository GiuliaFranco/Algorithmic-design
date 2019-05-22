#include <list>
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<utility>
using namespace std;

// Size of array will be V (number of vertices in graph)
class Graph{
public:
  int V;
  list < pair<int,int> > adList [30];  //dest,weight
  Graph(int vert):V(vert){}
   void addEdge(int src,int d,int w){
	adList[src].push_back(make_pair(d,w));
	adList[d].push_back(make_pair(src,w));
  }
};

class MinHeap{
public:
	int size;      
    	int capacity; 
    	int *pos;     
    	vector<pair <int,int> > Node_arr;  //vertex num,distance 
	MinHeap(int c):capacity(c),size(0){
		pos=new int[c];
	}
        int Left(int idx){return 2 * idx + 1;}
	int Right(int idx){return 2 * idx + 2;}
	void minHeapify(int idx){
		int m, left, right;
           	m = idx;
           	left = Left(idx);
    		right = Right(idx);
    		if (left < size && this->Node_arr[left].second < this->Node_arr[m].second )
      			m = left;
    		if (right < size &&this-> Node_arr[right].second < this->Node_arr[m].second )
      			m = right;
    		if (m != idx){
			swap(this->pos[Node_arr[m].first],this->pos[Node_arr[idx].first]);
        		swap(this->Node_arr[m],this->Node_arr[idx]);
			this->minHeapify(m);
		}
	}
	bool isEmpty(){  
		if(size==0) return true;
		else return false;
	}
	int* extractMin(){
		if (!isEmpty()){
		pair<int,int> r=Node_arr[0];
                pos[Node_arr[0].first]=size-1;
                Node_arr[0]=Node_arr[size - 1];
                pos[Node_arr[size - 1].first] = 0;
                size--;
                this->minHeapify(0);
		int *p=&r.first;
                return p;  
		}
		return NULL;
	}
	void decreaseKey(int v, int d){
    		int i = pos[v];
    		Node_arr[i].second= d;
    		while (i && Node_arr[i].second < Node_arr[(i-1)/2].second){
		swap(pos[Node_arr[i].first],pos[Node_arr[(i-1)/2].first]);
	     	swap(Node_arr[i],Node_arr[(i - 1) / 2]);
        	i = (i - 1) / 2;
    		}
	};
	bool isInMinHeap(int v){
   		if (pos[v] < size) return true;
   		else return false;
	}


};

void print(int* dist, int n)
{
    cout<<"Vertex   Distance "<<endl;
    for (int i = 0; i < n; ++i)
        cout<<i<<"        "<<dist[i]<<endl;
}


void Init(int src,int *dist,MinHeap* minHeap,int V){
   for (int v = 0; v < V; v++){
        dist[v] = INT_MAX;
        minHeap->Node_arr.push_back( make_pair(v, dist[v]) );
        minHeap->pos[v] = v;
    }		
   dist[src] = 0;
    minHeap->Node_arr[src]= make_pair(src, dist[src]);
    minHeap->pos[src]=src;
    minHeap->decreaseKey(0,0);
    minHeap->size = V;

}

void relax(MinHeap* minHeap,int u,int *dist,list< pair<int, int> >::iterator p){
	 int v = p->first;
             if (minHeap->isInMinHeap(v) && dist[u] != INT_MAX &&  p->second + dist[u] < dist[v])
            {
                dist[v] = dist[u] +  p->second;
                minHeap->decreaseKey(v, dist[v]);
            }
}

void dijkstra(Graph* graph, int src){
    int V = graph->V;
    int dist[V];      
    MinHeap* minHeap=new MinHeap(V);
    Init(src,dist,minHeap,V);
    while (!minHeap->isEmpty())
    {
	int u =(*minHeap->extractMin()); 
	list< pair<int, int> > ::iterator p = graph->adList[u].begin();
	while(p!=graph->adList[u].end()){
	    relax(minHeap,u,dist,p);	
	    p++;
        }
    }
    print(dist, V);
}

int main(){

	int V = 5;
	Graph* graph=new Graph(V);
	graph->addEdge(0, 1, 4);
	graph->addEdge(0, 3, 8);
    	graph->addEdge(1, 2, 8);
	graph->addEdge(1, 4, 11);
        graph->addEdge(2, 3, 7);
        graph->addEdge(2, 4, 2);
	graph->addEdge(3, 4, 9);
	clock_t begin = clock();
	dijkstra(graph, 0);
	clock_t end = clock();
	cout<<"computed time for a graph of dimension "<<V<<"  is  "<<double(end - begin) / CLOCKS_PER_SEC<<endl;

	int V_long = 30;
    	Graph* graph_big = new Graph(V_long);
    	graph_big->addEdge(0, 1, 4);
    	graph_big->addEdge(0, 7, 8);
    	graph_big->addEdge(1, 2, 8);
    	graph_big->addEdge(1, 7, 11);
    	graph_big->addEdge(2, 3, 7);
    	graph_big->addEdge(2, 8, 2);
    	graph_big->addEdge(2, 5, 4);
    	graph_big->addEdge(3, 4, 9);
    	graph_big->addEdge(3, 5, 14);
    	graph_big->addEdge(4, 5, 10);
    	graph_big->addEdge(5, 6, 2);
    	graph_big->addEdge(6, 7, 1);
    	graph_big->addEdge(6, 8, 6);
    	graph_big->addEdge(7, 8, 7);
    	graph_big->addEdge(8, 11, 3);
    	graph_big->addEdge(8, 9, 7);
    	graph_big->addEdge(9, 10, 4);
    	graph_big->addEdge(10, 14, 7);
    	graph_big->addEdge(10, 11, 17);
    	graph_big->addEdge(11, 14, 5);
    	graph_big->addEdge(11, 12, 8);
    	graph_big->addEdge(12, 13, 4);
    	graph_big->addEdge(13, 14, 7);
   	graph_big->addEdge(14, 16, 7);
    	graph_big->addEdge(14, 15, 6);
    	graph_big->addEdge(15, 16, 9);
    	graph_big->addEdge(16, 17, 8);
    	graph_big->addEdge(17, 19, 2);
    	graph_big->addEdge(18, 21, 5);
    	graph_big->addEdge(19, 22, 7);
	graph_big->addEdge(20, 22, 7);
    	graph_big->addEdge(21, 23, 4);
    	graph_big->addEdge(22, 26, 6);
    	graph_big->addEdge(23, 25, 9);
    	graph_big->addEdge(24, 27, 8);
    	graph_big->addEdge(25, 26, 2);
    	graph_big->addEdge(26, 28, 7);
    	graph_big->addEdge(26, 27, 6);
    	graph_big->addEdge(27, 28, 9);
    	graph_big->addEdge(28, 29, 8);
	clock_t begin_1 = clock();
	dijkstra(graph_big, 0);
	clock_t end_1 = clock();
        cout<<"computed time for a graph of dimension "<<V_long<<"  is  "<<double(end_1 - begin_1) / CLOCKS_PER_SEC<<endl;
	return 0;
}
