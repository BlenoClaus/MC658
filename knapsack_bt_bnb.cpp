/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "knapsack.h"
#include <time.h>

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

void printVector(vector<int> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
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
	return !stop;
	
}

///
// Branch and Bound function
///
bool bnb(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t){

	return false;
}
