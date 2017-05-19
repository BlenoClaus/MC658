/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "transportation.h"

///Preencher aqui para facilitar a correcao. 
// Nome1: Bleno Humberto Claus
// RA1: 145444
// Nome2: 
// RA2:

///
// PL function
///
			//ListBpGraph::Node adjNode = g.target(e);	

bool pl(ListBpGraph& g, ListBpGraph::EdgeMap<int> &c, ListBpGraph::NodeMap<int> &v, ListBpGraph::EdgeMap<int> &sol, int tMax){
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);
	model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
	env.set(GRB_DoubleParam_TimeLimit, tMax);	
	
	/*ListBpGraph::EdgeMap<GRBVar> x(g);
	for (ListBpGraph::EdgeIt eb(g); eb!=INVALID; ++eb){
		x[eb] = model.addVar(0.0, GRB_INFINITY, c[eb], GRB_CONTINUOUS, "x");
	}	
	model.update();
	
	for (ListBpGraph::RedNodeIt nr(g) ; nr!=INVALID; ++nr){
		GRBLinExpr expr;
		for (ListBpGraph::IncEdgeIt e(g, nr); e!=INVALID; ++e){
			expr += x[e] ;	
		}
		model.addConstr(expr == v[nr]);
	}
	model.update();

	for (ListBpGraph::BlueNodeIt nb(g) ; nb!=INVALID; ++nb){
		GRBLinExpr expr;
		for (ListBpGraph::IncEdgeIt e(g, nb); e!=INVALID; ++e){
			expr += x[e] ;	
		}
		model.addConstr(expr == v[nb]);
	}
	model.update();
	
	try {
	    model.optimize(); 
	} catch(GRBException e)	{
		cerr << e.getMessage();
	}

	for (ListBpGraph::EdgeIt eb(g); eb!=INVALID; ++eb){
		sol[eb] = x[eb].get(GRB_DoubleAttr_X);
	}
	*/
	return true;
}
