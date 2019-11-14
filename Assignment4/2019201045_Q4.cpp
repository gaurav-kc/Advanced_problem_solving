#include <iostream>
#include <string.h>
#include <vector>

typedef long int li;
using namespace std;

unsigned long long int t = 0;

void dfs(li v,vector<vector<li>> &adj,vector<bool> &visited,vector<li> &vt,vector<li> &lt,vector<li> &result,int parent=-1)
{
    visited[v] = true;
    vt[v] = lt[v] = t++;
    li children=0;
    for (li to : adj[v])
    {
        if (visited[to])
        {
            lt[v] = min(lt[v], vt[to]);
        }
        else
        {
            dfs(to,adj,visited,vt,lt,result,v);
            lt[v] = min(lt[v], lt[to]);
            if (lt[to] >= vt[v] && parent!=-1)
            {
                result.push_back(v);
            }
            children++;
        }
    }
    if(parent == -1 && children > 1)
    {
        result.push_back(v);
    }
}

vector<li> findpts(vector<vector<li>> &adj)
{
    vector<bool> visited(adj.size(),false);
    vector<li> vt(adj.size(),-1);
    vector<li> lt(adj.size(),-1);
    vector<li> result;
    for (int i = 0; i < adj.size(); ++i)
    {
        if (!visited[i])
        {
            dfs(i,adj,visited,vt,lt,result);
        }
    }
    return result;
}

int main()
{
    li n;
    cin>>n;
    vector<vector<li>> adj(n);
    li ip1,ip2,m;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        cin>>ip1;
        cin>>ip2;
        adj[ip1].push_back(ip2);
        adj[ip2].push_back(ip1);
    }
    vector<li> points;
    points = findpts(adj);
    for(auto i : points)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}
