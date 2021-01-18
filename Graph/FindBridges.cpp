// O(V+E)

#include<bits/stdc++.h>
using namespace std;
class U_Graph{
    private:
        vector<int> visited;
        vector<int> init_time;
        vector<int> low_time;
        vector<pair<int,int>> bridges;
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
        void find_bridges_helper(int v,int parent){
            init_time[v]=low_time[v]=timer++;
            visited[v]=1;
            for(int i = 0 ; i < adj_list[v].size();i++){
                int child = adj_list[v][i];
                if(child==parent)continue;
                if(visited[child]){
                    low_time[v] = min(low_time[v],low_time[child]);
                }
                else{
                    find_bridges_helper(child,v);
                    low_time[v] = min(low_time[v],low_time[child]);
                    if(init_time[v]<low_time[child]){
                        bridges.push_back(make_pair(v,child));
                    }
                }
            }
        }
        vector<pair<int,int>> find_bridges(){
            if(no_of_vertices==0)
                return this->bridges;
            for(int i = 0 ; i < no_of_vertices ;i++){
                if(!this->visited[i]){
                    find_bridges_helper(i,-1);
                }
            }
            return bridges;
        }
};

int main() {
    int no_of_vertices = 7;
    U_Graph g1(no_of_vertices);
    g1.add_edge(1, 0); 
    g1.add_edge(0, 2); 
    g1.add_edge(2, 1); 
    g1.add_edge(0, 3); 
    g1.add_edge(3, 4);
    
    vector<pair<int,int>> V = g1.find_bridges();
    for(int i = 0 ; i < V.size() ;i++){
        cout<<V[i].first<<" --------- "<<V[i].second<<endl;
    }
}
