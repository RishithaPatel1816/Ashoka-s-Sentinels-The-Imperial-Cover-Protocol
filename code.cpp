#include <bits/stdc++.h>
using namespace std;

class Sentinel{
    private:
        int id;
        string name;
        int rank;
    public:
        Sentinel(int a,string b,int c){id=a;name=b;rank=c;}
        //virtual int countHigherRanked()=0;
    friend class Kingdom;
    friend bool compareArmy(const Sentinel* s1,const Sentinel*s2);
};

class Senapati : public Sentinel{
    public:
        //constructor
        Senapati(int a,string b) : Sentinel(a,b,1){};
        // int countHigherRanked()override{
        //     //return no of people of higher ran
        // }
};

class Dandanayaka : public Sentinel{
    public:
        //constructor
        Dandanayaka(int a,string b) : Sentinel(a,b,2){};
        // int countHigherRanked()override{
        //     //return no of people of higher ran
        // }
};

class Chaturangini : public Sentinel{
    public:
        //constructor
        Chaturangini(int a,string b) : Sentinel(a,b,3){};
        // int countHigherRanked()override{
        //     //return no of people of higher ran
        // }
};

bool compareArmy(const Sentinel* s1,const Sentinel* s2){
    if(s1->rank==s2->rank){return s1->id<s2->id;}
    return s1->rank<s2->rank;
}

class Graph{
    private:
        map<int,vector<int>> edges;
        vector<pair<int,int>> arr;
        int vertices;
        int m;
    public: 
        Graph(int x){
            vertices=x;
            m=0;
        }
        //now we will 
        void addEdge(int u,int v){
            edges[u].push_back(v);
            edges[v].push_back(u);
            arr.push_back({u,v});
            m++;
            return;
        }
        int vertexCover(){
            vector<vector<int>> dp(vertices,vector<int>(2,-1));
            vector<bool> visited(vertices,false);
            visited[0]=true;
            dp[0][1]=finddp(0,1,dp,0);
            dp[0][0]=finddp(0,0,dp,0);

            int vertexCover=min(dp[0][0],dp[0][1]);
            cout<<vertexCover<<endl;
            return vertexCover;
        }
        int finddp(int u,int z,vector<vector<int>>& dp,int parent){
            if(dp[u][z]!=-1){return dp[u][z];}
            //if z is one we have to add one so .
            if(z==1){
                dp[u][z]=1;
                for(auto v : edges[u]){
                    if(v!=parent){
                        dp[u][z]=dp[u][z]+min(finddp(v,0,dp,u),finddp(v,1,dp,u));
                    }
                }
            }
            else{
                dp[u][z]=0;
                for(auto v : edges[u]){
                    if(v!=parent){
                        dp[u][z]=dp[u][z]+finddp(v,1,dp,u);
                    }
                    //cout<<"cur dp val "<<dp[u][z]<<endl;
                }
            }
            return dp[u][z];
        }
};

class Kingdom{
    private:
        vector<Sentinel*> arr;
        vector<Sentinel*> copyArr;
        int dandanayakas;
        int senapatis;
        int chaturangis;
        bool q2Done;
        bool q1Done;
        int q1Ans;
        Graph* g;
    public:
        Kingdom(){
            dandanayakas=0;senapatis=0;chaturangis=0;q2Done=false;q1Done=false;
        }
        void takeInput(int n){
            arr.resize(n);
            copyArr.resize(n);
            for(int i=0;i<n;i++){
                string name;
                string position;
                cin>>name>>position;
                int rank;
                if(position=="SENAPATI"){
                    senapatis++;
                    Sentinel* man=new Senapati(i,name);
                    arr[i]=man;
                }
                else if(position=="DANDANAYAKA"){
                    dandanayakas++;
                    Sentinel* man=new Dandanayaka(i,name);
                    arr[i]=man;
                }
                else{
                    chaturangis++;
                    Sentinel* man=new Chaturangini(i,name);
                    arr[i]=man;
                }
            }
            copyArr=arr;
        }
        void makeGraph(int n){
            g=new Graph(n);
            int m=n-1;
            for(int i=0;i<m;i++){
                int u,v;
                cin>>u>>v;
                g->addEdge(u,v);
            }
        }
        void handleQueries(int q){
            while(q--){
                int query;
                cin>>query;
                if(query==1){
                    //we have to return minimum no. of vertex cover
                    if(q1Done){cout<<q1Ans<<endl;}
                    else{
                        q1Ans=g->vertexCover();
                        q1Done=true;
                    }
                }
                else if(query==2){
                    //print the sorted array
                    if(!q2Done){sortAndPrint();q2Done=true;}
                    else{
                        for(int i=0;i<arr.size();i++){
                            cout<<arr[i]->id<<" ";
                        }
                        cout<<endl;
                    }
                }
                else{
                    int node;
                    cin>>node;
                    cout<<findHigherRank(node)<<endl;
                }
            }
        }
        void sortAndPrint(){
            sort(arr.begin(),arr.end(),compareArmy);
            for(int i=0;i<arr.size();i++){
                cout<<arr[i]->id<<" ";
            }
            cout<<"\n";
        }
        int findHigherRank(int node){
            if(copyArr[node]->rank==1){return 0;}
            else if(copyArr[node]->rank==2){
                return senapatis;
            }
            else{
                return senapatis+dandanayakas;
            }
        }
};

int main(){
    int n;cin>>n;
    Kingdom kosala;
    kosala.makeGraph(n);
    kosala.takeInput(n);
    int q;cin>>q;
    kosala.handleQueries(q);
    return 0;
}
