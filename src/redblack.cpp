#include "redblack.hpp"

Tree *nill, *temp;

void inicilizarTree(Tree **raiz){
    nill = new Tree();
    nill->color = black;
    nill->infos.key = -1;
    (*raiz) = nill;
}

void rotacaoSimplesEsquerda(Tree **raiz, Tree *child){

    Tree *x, *y;
    x = child;

    y = child->right; //aux
    x->right = y->left; //item

    if(y->left != nill){
        y->left->father = x;
    }

    y->father = x->father;

    if(x->father == nill){
        *raiz = y;
    }
    else{
        if(x == x->father->left){
            x->father->left = y;
        }
        else{
            x->father->right = y;
        }
    }

    y->left = x;
    x->father = y;
}

void rotacaoSimplesDireita(Tree **raiz, Tree *child){
    
    Tree *x, *y;

    x = child;
    y = child->left;
    x->left = y->right;

    if(y->right != nill){
        y->right->father = x;
    }

    y->father = x->father;
    
    if(x->father == nill){
        *raiz = y;
    }
    else{
        if(x == x->father->right){
            x->father->right = y;
        }
        else{
            x->father->left = y;
        }
    }

    y->right = x;
    x->father = y;
}

void insertFixUp(Tree **raiz, Tree *child){
    
    Tree *tio;
    while((child != *raiz) && (child->father->color == red)){
        if(child->father == child->father->father->left){
            tio = child->father->father->right;
            //caso 1:
            if((tio != NULL) && (tio->color == red)){
                child->father->color = black;
                tio->color = black;
                child->father->father->color = red;
                child = child->father->father;
                
            }
            else{
                //caso 2
                if(child == child->father->right){
                    child = child->father;
                    rotacaoSimplesEsquerda(raiz, child);
                }
                //caso 3
                child->father->color = black;
                child->father->father->color = red;
                rotacaoSimplesDireita(raiz, child->father->father);
            }
        }
        else{
            tio = child->father->father->left;
            //caso 1
            if((tio != NULL) && (tio->color == red)){
                child->father->color = black;
                tio->color = black;
                child->father->father->color = red;
                child = child->father->father;
            
            }
            else{      
                //caso 2
                if(child == child->father->left){
                    child = child->father;
                    rotacaoSimplesDireita(raiz, child);
                }
                //caso 3
                child->father->color = black;
                child->father->father->color = red;
                rotacaoSimplesEsquerda(raiz, child->father->father);      
            }

        }

  }

  (*raiz)->color = black;
}

void preordem(Tree *t){
    if(!(t == NULL) && t->infos.key!=-1){
        printf("%d - %s\t", t->infos.key, t->color ? "black" : "red");
        cout << endl;
        preordem(t->left); 
        preordem(t->right); 
    }
}

void pesquisa(Tree **t, Tree **aux, Record r){

    if(*t == nill){
        printf("[ERROR]: Node not found!");
        return;
    }

    if((*t)->infos.key > r.key){ pesquisa(&(*t)->left, aux, r); return;}
    if((*t)->infos.key < r.key){ pesquisa(&(*t)->right, aux, r); return;}

    *aux = *t;
}

void transplante(Tree **raiz, Tree *u, Tree *v){

    if(u->father == nill){ // caso u seja a raiz
        *raiz = v;
    }
    else if(u == u->father->left){ //atualizar u.p.direita se u é um filho à esquerda.
        u->father->left = v;        // if -> é o filho esquerdo
    }
    else{
        u->father->right = v;
    }
    v->father = u->father;
    

}

Tree* tree_Minimum(Tree *x){

    Tree* aux = x;

    while(aux->left != nill){
        aux = aux->left;
    }

    return aux;
}

void deleteFixUp(Tree **raiz, Tree *x){ // para restaurar a propriedade da REdBlack
    // dentro do caso 4 ...
    Tree *w;
    //w=x;

    while(x!=*raiz && x->color == black){
        //cout << " aqui " << endl << endl << endl;
        if(x == x->father->left){   // x esta do lado esquerdo 
            w = x->father->right;  // irmão de X
            if(w->color == red){                                    // case 1
                w->color = black;
                x->father->color = red;
                rotacaoSimplesEsquerda(raiz,x->father);
                w = x->father->right; // atualizando quem é o irmão
            }
            else if(w->left->color == black && w->right->color == black){    // case 2
                w->color = red;
                x = x->father;
            }
            else if(w->right->color ==  black){                        // case 3
                w->left->color = black;
                w->color = red;
                rotacaoSimplesDireita(raiz,w);
                w = x->father->right;
            }
            else{
                w->color = x->father->color;                               // case 4
                x->father->color = black;
                w->right->color = black;
                rotacaoSimplesEsquerda(raiz,x->father);
                x = (*raiz);
            }  
        }
        else{                    
            w = x->father->left;  // irmão de X
            if(w->color == red){                                    // case 1
                w->color = black;
                x->father->color = red;
                rotacaoSimplesDireita(raiz,x->father);
                w = x->father->left; // atualizando quem é o irmão
            }
            else if(w->right->color == black && w->left->color == black){    // case 2
                w->color = red;
                x = x->father;
            }
            else if(w->left->color ==  black){                        // case 3
                w->right->color = black;
                w->color = red;
                rotacaoSimplesEsquerda(raiz,w);
                w = x->father->left;
            }
            else{
                w->color = x->father->color;                               // case 4
                x->father->color = black;
                w->left->color = black;
                rotacaoSimplesDireita(raiz,x->father);
                x = (*raiz);
            }
        }
    }

    x->color = black;
}

void deleteTree(Tree **tree, Tree *z){

    Tree *y, *x;
    y = z;

    bool yCorOriginal = y->color;

    if(z->left == nill){                // caso 1
        x = z->right;
        transplante(tree,z,z->right);
    }
    else if(z->right == nill){          // caso 1 
        x = z->left;
        transplante(tree,z, z->left);
    }
    else{                               // caso 2
        y = tree_Minimum(z->right); //23
        yCorOriginal = y->color;
        x = y->right; //null

        if(y->father == z){
            x->father = y;          
            
        }
        else{
            transplante(tree,y,y->right);
            y->right = z->right;
            y->right->father = y;
        }

        transplante(tree,z,y);
        y->left = z->left;
        y->left->father = y;
        y->color = z->color;
    }

    if(yCorOriginal == black){
        deleteFixUp(tree,x);
        // x é nulo não tem filhos nem pai...
    }
}

void insertTree(Tree **tree , Tree **father, Tree **raiz, Record infos){
  
    if(*tree == nill){
        *tree = new Tree();
        (*tree)->left = nill; 
        (*tree)->right = nill; 
        (*tree)->father = father != tree ? *father : nill;
        (*tree)->color = red;                                         //red: vermelho  black:preto
        (*tree)->infos = infos; 
        insertFixUp(raiz, *tree);
    } 
    else{ 

        if(infos.key < (*tree)->infos.key){
            insertTree(&(*tree)->left, tree, raiz, infos);
            return;
        }
        if(infos.key > (*tree)->infos.key){
            insertTree(&(*tree)->right, tree, raiz, infos);
            return;
        }
    }
}


