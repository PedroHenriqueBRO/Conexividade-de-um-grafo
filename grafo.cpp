#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
//0=branco,1=cinza,2=preto
void remove(vector<vector<int>>&G,int pos){ 
	G[pos].clear(); 
	for(int i=0;i<G.size();i++){ 
		for(int j=0;j<G[i].size();j++){ 
			if(G[i][j]==pos){ 
				G[i].erase(G[i].begin()+j); 
			} 
		} 
	} 
}

int DFS(int &tempo,int atual,const vector<vector<int>> &G, vector<int> &visitado,vector<pair<int,int>>&inifim,vector<bool>&verticescorte) {
	visitado[atual]=1;
	inifim[atual].first=tempo++;
	int melhor=tempo;
	for(int i=0;i<G[atual].size();i++){
		int v=G[atual][i];
		int cand;
		if(visitado[v]==0){
			cand = DFS(tempo,v,G,visitado,inifim,verticescorte);
			if(cand>=inifim[atual].first){
				verticescorte[atual]=true;
			}	
			melhor=min(cand,melhor);
		}else{
			melhor =min(inifim[v].first,melhor);
		}

	}
	inifim[atual].second=tempo++;
	visitado[atual]=2;	
	return melhor;

}
void _DFS(int &tempo,int atual,const vector<vector<int>> &G, vector<int> &visitado,vector<pair<int,int>>&inifim,vector<bool>&verticescorte) {
	visitado[atual]=1;
	inifim[atual].first=tempo++;
	bool primeiro=true;
	for(int i=0;i<G[atual].size();i++){
		int v=G[atual][i];
		if(visitado[v]==0){
			if(!primeiro){
				verticescorte[atual]=true;
			}
			DFS(tempo,v,G,visitado,inifim,verticescorte);
			primeiro=false;
		}
	}
	inifim[atual].second=tempo++;
	visitado[atual]=2;
}
void algoritmoDePonte2(vector<vector<int>>&G){
	int chave3=0;
	vector<vector<pair<int, int>>> pares(G.size(), vector<pair<int, int>>(G.size(), {-1, -1}));
	for(int i=0;i<G.size();i++){

		vector<int>visitado(G.size(),0);
		vector<pair<int,int>>inifim(G.size(),{-1,-1});
		vector<bool>verticescorte(G.size(),false);
		vector<vector<int>>aux=G;
		int tempo=0;
		remove(aux,i);
		int pos=i+1;
		if(i+1==G.size()){
			pos=0;
		}
		_DFS(tempo,pos,aux,visitado,inifim,verticescorte);
		for(int j=0;j<verticescorte.size();j++){
			if(verticescorte[j]==true){
				chave3++;
				if(chave3==1){
					cout<<"Grafo 2-conexo."<<endl;
				}
				if(pares[j][i].first==-1){
				pares[i][j].first=i;
				pares[i][j].second=j;
				}
			}
	}
}
for(const auto& p:pares){
	for(int i=0;i<p.size();i++){
		if(p[i].first!=-1){
			cout<<p[i].first<<" "<<p[i].second<<endl;
		}
	}
}
if(chave3==0){
	cout<<"Grafo 3-conexo."<<endl;
}
}
void algoritmoDePonte(vector<vector<int>> &G) {
	vector<int>visitado(G.size(),0);
	vector<pair<int,int>>inifim(G.size(),{-1,-1});
	vector<bool>verticescorte(G.size(),false);
	int tempo=0;
	_DFS(tempo,0,G,visitado,inifim,verticescorte);
	int chave=0;
	for(int i=0;i<verticescorte.size();i++){
		if(verticescorte[i]==true){
			chave++;
			if(chave==1){
				cout<<"Grafo 1-conexo."<<endl;
			}	
			cout<<i<<endl;
		}
	}
	if(chave==0){
		algoritmoDePonte2(G);
	}
}


int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n);

	for (int i = 0; i < m; i++) {
		int are1, are2;
		cin >> are1 >> are2;
		G[are1].push_back(are2);
		G[are2].push_back(are1);
	}
	algoritmoDePonte(G);

	return 0;
}
