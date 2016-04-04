/************************************************/
/*          LOGICAMENTE NO COMPILA              */
/************************************************/


/* NeighOperator => Abstract class*/
class NeighOperatorKP : public AbstractNeighOperator  {

	SolutionKP* generateNeigh(SolutionKP* sCurrent, int pos) {
		//DEMASIADO FACIL
		;
		//Se puede restar uno y hacer el valor absoluto
	}
};

//Una clase para la mejor mejora y otra para la primera mejora
class FirstNeighExplorator : public AbstractNeighOperator {
//Explorar una solucion respecto a un operador de vecindario
protected:
	Random *random;
	AbstractProblemInstance/*Instance*/ *problemInstance;

public:
	FirstNeighExplorator(AbstractProblemInstance* problemInstance, Random *random) {
		this.random = random;
		this.problemInstance = problemInstance;
	}

	Solution* exploreNg(Solution* sCurrent, AbstractNeighOperator *operator) {
		Solution *neighSol = NULL;

		int numPosibilities = operator.getNumPosParam();

		for (unsigned int i = 0; i < numPosibilities; i++) {
			neighSol = operator.generateNeigh(sCurrent, i);
			problemInstance.evaluate(neighSol);

			if(instance.isBetter(neighSol, sCurrent))
				return neighSol;
		}

		neighSol = operator.generateNeigh(sCurrent, pos);

		return neighSol;
	}
};

class BestNeighExplorator : public AbstractNeighOperator {
};

//Llamar a la semilla en el main


class LocalSearch {
	protected:
		AbstractNeighOperator *operator;
		Random* random;
		AbstractNeighExplorator* explorator;

	public:
		LocalSearch(...)  {
			this.random =random;
			this.operator = operator;
			this.explorator = explorator;
		}

		//Explora el vecindario actual y escoger una solucion, hasta que la mejor solucion no sea mejor que la solucion actual ¿¿¿???
		Solution* applyLS(Solution* initialSol) {
			Solution* currentSol = initalSOl->copy();
			Solution* neigh = explorator.exploreNg(currentSol);

			while(neigh not NULL) {
				currentSol->copy(neigh);
				neigh = explorator.exploreNg(currentSol);
			}

			delete neigh;
			return currentSol;
		}
}