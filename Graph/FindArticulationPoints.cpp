// O(V+E)

#include<bits/stdc++.h>
using namespace std;
class U_Graph{
    private:
        vector<int> visited;
        vector<int> init_time;
        vector<int> low_time;
        vector<int> articulations_points;
        vector<vector<int>> adj_list;
        int no_of_vertices,timer;
    public:
        U_Graph(int no_of_vertices){
            this->visited = vector<int>(no_of_vertices,0);
            this->init_time = vector<int> (no_of_vertices,0);
            this->low_time = vector<int> (no_of_vertices,0);
            this->adj_list = vector<vector<int>>(no_of_vertices);
            this->no_of_vertices = no_of_vertices;
            this->timer = 1;
        }
        void add_edge(int src,int dst){
            adj_list[src].push_back(dst);
            adj_list[dst].push_back(src);
        }
        void find_articulations_points_helper(int v,int parent){
            init_time[v]=low_time[v]=timer++;
            visited[v]=1;
            int childs=0;
            for(int i = 0 ; i < adj_list[v].size();i++){
                int child = adj_list[v][i];
                if(child==parent)continue;
                if(visited[child]){
                    low_time[v] = min(low_time[v],low_time[child]);
                }
                else{
                    childs++;
                    find_articulations_points_helper(child,v);
                    low_time[v] = min(low_time[v],low_time[child]);
                    if(parent!=-1 && init_time[v]<=low_time[child]){ // = is for if there is cycle of length 2 i.ethere are two edges 1. current to kid and 2. kid to current
                        articulations_points.push_back(v);
                    }
                }
            }
            if(parent==-1 && childs>1){
                articulations_points.push_back(v);
            }
        }
        vector<int> find_articulations_points(){
            if(no_of_vertices==0)
                return this->articulations_points;
            for(int i = 0 ; i < no_of_vertices ;i++){
                if(!this->visited[i]){
                    find_articulations_points_helper(i,-1);
                }
            }
            return articulations_points;
        }
};

int main() {
    int no_of_vertices = 7;
    U_Graph g1(5); 
    g1.add_edge(1, 0); 
    g1.add_edge(0, 2); 
    g1.add_edge(2, 1); 
    g1.add_edge(0, 3); 
    g1.add_edge(3, 4); 
    vector<int> V;
    V = g1.find_articulations_points();
    for(int i = 0 ; i < V.size() ;i++){
        cout<<V[i]<<endl;
    } 
    
}
