/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "knapsack.h"

///Preencher aqui para facilitar a correcao. 
// Nome1: Daniel Ricci
// RA1: 145781
// Nome2: Bleno Humberto Claus
// RA2: 145444

vector<int> currentSol;
int currentP = 0;

void printVector(vector<int> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

int checkSolution(vector<int> sol, vector<int> p, vector<int> w, vector<int> c, int B, int d){
	
	int banda = 0, nclasses = 0, pgto = 0;
	vector<int> classes(1000, 0);
	
	cout << "Checking solution: ";
	printVector(sol);
	
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
	
	if(k < n){
		temp[k] = 1;
		int n = checkSolution(temp, p, w, c, B, d);
		if(n > 0){
			if(n > currentP){
				currentP = n;
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
	
	fill(sol.begin(), sol.end(), 0);
	vector<int> temp = sol;
	currentSol = temp;
	backtrack(n, d, B, p, w, c, sol, t, 0, temp);
	sol = currentSol;
	return true;
	
}


/*
if(k == n){
		return checkSolution(sol, p, w, c, B, d);	
	}
	
	vector<int> solAux = sol ;	
	int aux = checkSolution(sol, w, c, B, d);
	if(aux > -1){
	  	if(aux > curBstSol){
			curBstValue = aux;
			curBstSol = sol;
		}
	}
		
	solAux[k] = 1;
	return max(backtrack(n, d, B, p, w, c, sol, t, k+1),backtrack(n, d, B, p, w, c, solAux, t, k+1);  ); */

///
// Branch and Bound function
///
bool bnb(int n, int d, int B, vector<int> &p, vector<int> &w, vector<int> &c, vector<int> &sol, int t){
	return false;
}
