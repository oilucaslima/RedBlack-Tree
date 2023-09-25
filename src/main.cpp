#include "redblack.hpp"

int main(){

    int reg[] = {10,2,7,5,3,9,16,4,11,1,6,23,14,6};

	Tree *raiz;
	Tree *z;
	Record r,pes;

	inicilizarTree(&raiz);

	for(int i=0; i<13; i++){
		r.key = reg[i];
		insertTree(&raiz, &raiz, &raiz, r);
    }	
	
  	preordem(raiz);
	pes.key = 16;
	pesquisa(&raiz,&z,pes);
	deleteTree(&raiz,z);
	cout << endl;
	preordem(raiz);	

    return 0;
}