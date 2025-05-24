#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

void DFS(int pos, vector<vector<int>> &G, vector<string> &visitado) {
  stack<int> pilha;
  pilha.push(pos);
  while (pilha.size() != 0) {
    int v = pilha.top();
    pilha.pop();
    if (visitado[v] == "Branco") {
      visitado[v] = "Cinza";
      for (const auto &adj : G[v]) {
        if (visitado[adj] == "Branco") {
          pilha.push(adj);
        }
      }
      visitado[v] = "Preto";
    }
    if (visitado[v] == "Negado") {
      for (const auto &adj : G[v]) {
        if (visitado[adj] == "Branco") {
          pilha.push(adj);
          break;
        }
      }
    }
  }
}
bool conexo(vector<vector<int>> &G, int pos, vector<string> visitado) {
  DFS(pos, G, visitado);
  for (int i = 0; i < visitado.size(); i++) {
    if (visitado[i] == "Negado") {
      continue;
    }
    if (visitado[i] != "Preto") {
      return false;
    }
  }
  return true;
}
bool conexividade1(vector<vector<int>> &G) {
  vector<int> vqd;
  bool chave = false;
  for (int i = 0; i < G.size(); i++) {
    vector<string> visitado(G.size(), "Branco");
    visitado[i] = "Negado";
    bool c = conexo(G, i, visitado);
    if (c == false) {
      vqd.push_back(i);
      chave = true;
    }
  }
  if (chave) {
    cout << "Grafo 1-conexo." << endl;
  }
  for (const auto &v : vqd) {
    cout << v << endl;
  }
  return chave;
}

bool conexividade2(vector<vector<int>> &G) {
  vector<pair<int, int>> pares;
  bool chave = false;
  for (int i = 0; i < G.size(); i++) {
    vector<string> visitado(G.size(), "Branco");
    visitado[i] = "Negado";
    bool c = false;
    for (int j = i + 1; j < G.size(); j++) {
      visitado[j] = "Negado";
      c = conexo(G, i, visitado);
      if (c == false) {
        pair<int, int> par;
        par.first = i;
        par.second = j;
        pares.push_back(par);
      }
      visitado[j] = "Branco";
    }
  }
  if (pares.size() != 0) {
    cout << "Grafo 2-conexo." << endl;
  } else {
    return false;
  }
  for (const auto &vs : pares) {
    cout << vs.first << " " << vs.second << endl;
  }
  return true;
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
  if (!conexividade1(G)) {
    if (!conexividade2(G)) {
      cout << "Grafo 3-conexo." << endl;
    }
  }
  return 0;
}
