/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "knapsack.h"
#include <time.h>
#include <queue> 

///Preencher aqui para facilitar a correcao. 
// Nome1: Daniel Ricci
// RA1: 145781
// Nome2: Bleno Humberto Claus
// RA2: 145444

vector<int> currentSol;
int currentP = 0;
int startTime;
int currentTime;
bool stop = false;

struct User {
	int index, classe, peso, valor ;
};
typedef struct User User ;

struct Node {
	int nivel, ganho, limite ;
	double peso ;
};
typedef struct Node Node ;

bool cmp(User u1, User u2){
	double r1 = (double) u1.valor/u1.peso ;	
	double r2 = (double) u2.valor/u2.peso ;
	return r1 > r2 ;
}

void sortBy(vector<User> users){
	sort(users.begin(), users.end(), cmp);
}

void printVector(vector<int> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

int bound(Node no, int n, int w, vector<User> users){
	if (no.peso >= w) return 0;
	
	int ganhoLimite = no.ganho ;
	int j = no.nivel + 1;
	int pesoTotal = no.peso;
	
	while ((j < n) && (pesoTotal + users[j].peso <= w)){
		pesoTotal += users[j].peso;
		ganhoLimite += users[j].valor;
		j++;
	}
	
	if (j < n) ganhoLimite += (w - pesoTotal) * users[j].valor/users[j].peso ;
	
	return ganhoLimite;
}

int checkSolution(vector<int> sol, vector<int> p, vector<int> w, vector<int> c, int B, int d){
	
	int banda = 0, nclasses = 0, pgto = 0;
	vector<int> classes(1000, 0);
	
	//cout << "Checking solution: ";
	//printVector(sol);
	
	for(int i = 0; i < sol.size(); i++){
		if(sol[i] == 1){
			if(classes[c[i]] == 0){
				classes[c[i]] = 1;
				nclasses++;
			}
			banda += w[i];
			pgto += p[i];	
		}
	}
	
	banda += (nclasses - 1) * d;
	
	if(banda <= B) return pgto;
	else return -1;
}

void backtrack(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t, int k, vector<int> temp){
	
	currentTime = time(0);
	double time = difftime(currentTime, startTime);
	
	if(time >= t){
		stop = true;
	}
	
	if(k < n && !stop){
		temp[k] = 1;
		int aux = checkSolution(temp, p, w, c, B, d);
		if(aux > 0){
			if(aux > currentP){
				currentP = aux;
				currentSol = temp;
			}
			backtrack(n, d, B, p, w, c, sol, t, k+1, temp);
		}
		temp[k] = 0;
		backtrack(n, d, B, p, w, c, sol, t, k+1, temp);
	}
	
}

///
// Bactracking function: 
///
bool bt(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t){
	
	startTime = time(0);
	fill(sol.begin(), sol.end(), 0);
	vector<int> temp = sol;
	currentSol = temp;
	backtrack(n, d, B, p, w, c, sol, t, 0, temp);
	sol = currentSol;
	if(stop){
		cout << "Timeout! Melhor resposta encontrada: " << endl;
	}
	cout << "Custo: " << currentP << endl;
	return !stop;
	
}

///
// Branch and Bound function
///
bool bnb(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t){
	
	vector<User> users ;
	
	for(int i = 0; i < n; i++){
		User user;
		user.index = i;
		user.valor = p[i];
		user.classe = c[i];
		user.peso = w[i];
		users.push_back(user);
	}
		
	sortBy(users);
	queue<Node> Q;
    Node u, v;
 
    u.nivel = -1;
    u.ganho = u.peso = 0;
    Q.push(u);

    int maximoGanho = 0;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
 
        if (u.nivel == -1) v.nivel = 0;
        if (u.nivel == n-1) continue;
 
        v.nivel = u.nivel + 1;
        v.peso = u.peso + users[v.nivel].peso;
        v.ganho = u.ganho + users[v.nivel].valor;
 
        if (v.peso <= B && v.ganho > maximoGanho)
            maximoGanho = v.ganho;
 
        v.limite = bound(v, n, B, users);
 
        if (v.limite > maximoGanho)
            Q.push(v);
 
        v.peso = u.peso;
        v.ganho = u.ganho;
        v.limite = bound(v, n, B, users);
        if (v.limite > maximoGanho)
            Q.push(v);
    }		
	
	cout << maximoGanho << endl;

	return false;
}
