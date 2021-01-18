// O(V+E)

#include<bits/stdc++.h>
using namespace std;

void find_bridges_helper(int v,vector<int> &visited,vector<int> &init_time,vector<int> &low_time,vector<pair<int,int>> &bridges,vector<vector<int>> &adj_list,int parent,int &timer){
    init_time[v]=low_time[v]=timer++;
    visited[v]=1;
    for(int i = 0 ; i < adj_list[v].size();i++){
        int child = adj_list[v][i];
        if(child==parent)continue;
        if(visited[child]){
            low_time[v] = min(low_time[v],low_time[child]);
        }
        else{
            find_bridges_helper(child,visited,init_time,low_time,bridges,adj_list,v,timer);
            low_time[v] = min(low_time[v],low_time[child]);
            if(init_time[v]<low_time[child]){
                bridges.push_back(make_pair(v,child));
            }
        }
    }
}
vector<pair<int,int>> find_bridges(vector<vector<int>> &adj_list){
    vector<pair<int,int>> bridges;
    int no_of_vertices = adj_list.size();
    if(no_of_vertices==0)return bridges;
    
    vector<int> visited(no_of_vertices,0);
    vector<int> init_time(no_of_vertices,0);
    vector<int> low_time(no_of_vertices,0);
    
    for(int i = 0 ; i < no_of_vertices ;i++){
        if(!visited[i]){
            int timer = 1;
            find_bridges_helper(i,visited,init_time,low_time,bridges,adj_list,-1,timer);
        }
    }
    return bridges;
}
int main() {
    int no_of_vertices = 7;
    vector<vector<int>> adj_list(no_of_vertices);
    adj_list[0]={1,2};
    adj_list[1]={0,2,3,4,6};
    adj_list[2]={0,1};
    adj_list[3]={1,4};
    adj_list[4]={1,5};
    adj_list[5]={3,4};
    adj_list[6]={1};
    
    
    vector<pair<int,int>> bridges =  find_bridges(adj_list);
    for(int i = 0; i < bridges.size() ;i++)
        cout<<bridges[i].first<<"----"<<bridges[i].second<<endl;
    
}
