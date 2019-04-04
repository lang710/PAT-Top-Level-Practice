#include <iostream>
#include <utility>
#include <set>
#include <vector>

using namespace std;

void dfs(vector<vector<int>> visit,int sx,int sy,vector<pair<int,int>> &path,vector<pair<int,int>> prev){
    if(visit[sx][sy]==1){
        visit[sx][sy]=0;
        path.emplace_back(make_pair(sx,sy));
        prev.emplace_back(make_pair(sx,sy));
    }
    if(sx-1>=0&&visit[sx-1][sy==1)
        return dfs(visit,sx-1,sy,path,prev);
    if(sx+1<visit.size()&&visit[sx+1][sy]==1)
        return dfs(visit,sx+1,sy,path,prev);
    if(sy-1>=0&&visit[sx][sy-1]==1)
        return dfs(visit,sx,sy-1,path,prev);
    if(sy+1<visit[0].size()&&visit[sx][sy+1]==1)
        return dfs(visit,sx,sy+1,path,prev);
    
    prev.pop_back();
    if(!prev.empty())
        return dfs(visit,prev.back().first,prev.back().second,path,prev);
}

void remain(int R,int N,int M,char **map,vector<vector<int>> visit,set<vector<vector<int>>> &solutions,int sx,int sy,int K){
    if(R==0){
        vector<pair<int,int>> path,prev;
        dfs(visit,sx,sy,path,prev);
        if(path.size()==K)
            solutions.insert(visit);
        return;
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(visit[i][j]==1){
                if(i-1>=0&&visit[i-1][j]==0&&map[i-1][j]=='.'){
                    vector<vector<int>> visitX=visit;
                    visitX[i-1][j]=1;
                    remain(R-1,N,M,map,visitX,solutions,sx,sy,K);
                }
                if(i+1<N&&visit[i+1][j]==0&&map[i+1][j]=='.'){
                    vector<vector<int>> visitX=visit;
                    visitX[i+1][j]=1;
                    remain(R-1,N,M,map,visitX,solutions,sx,sy,K);
                }
                if(j-1>=0&&visit[i][j-1]==0&&map[i][j-1]=='.'){
                    vector<vector<int>> visitX=visit;
                    visitX[i][j-1]=1;
                    remain(R-1,N,M,map,visitX,solutions,sx,sy,K);
                }
                if(j+1<M&&visit[i][j+1]==0&&map[i][j+1]=='.'){
                    vector<vector<int>> visitX=visit;
                    visitX[i][j+1]=1;
                    remain(R-1,N,M,map,visitX,solutions,sx,sy,K);
                }
            }
        }
    }
}

void fill(char **map,int N,int M,int K,pair<int,int> *can_circle,int cc_size){
    vector<vector<int>> visit(N,vector<int>(M,0));
    for(int i=0;i<cc_size;i++){
        visit[can_circle[i].first-1][can_circle[i].second]=1;
        visit[can_circle[i].first+1][can_circle[i].second]=1;
        visit[can_circle[i].first][can_circle[i].second-1]=1;
        visit[can_circle[i].first][can_circle[i].second+1]=1;
    }
    set<vector<vector<int>>> solutions;
    remain(K-cc_size*4,N,M,map,visit,solutions,can_circle[0].first-1,can_circle[0].second,K);

    cout<<solutions.size()<<endl;
    /*for(auto iter=solutions.begin();iter!=solutions.end();iter++){
        for(auto ite=iter->begin();ite!=iter->end();ite++){
            for(auto it=ite->begin();it!=ite->end();it++){
                cout<<*it<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }*/

}


int main(){

    int N,M,K,H;
    cin>>N>>M>>K>>H;
    char **map=new char*[N];
    for(int i=0;i<N;i++)
        map[i]=new char[M];
    auto *can_circle=new pair<int,int>[H+1];
    int cc_size=0;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) {
            cin >> map[i][j];
            if (map[i][j] == 'O' && i * j) {
                can_circle[cc_size] = make_pair(i, j);
                cc_size++;
            }
        }

    if(cc_size==H)
        fill(map,N,M,K,can_circle,cc_size);

}

/*
 *
3 5 8 1
. . . O .
. O . . .
. . . . .
 */

/*
 * 算法思想：
 * 1、找出所有可以被围起来的动物
 * 2、洞的数量H和动物的数量X应满足，H==X或者H+1==X
 * 3、选择需要被围起来的动物，使其四连接填充为障碍物
 * 4、令已经填充好的障碍物满足四连接特性
 */
