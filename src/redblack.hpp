#ifndef REDBLACK_HPP 
#define REDBLACK_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum type {black,red};

typedef struct Record{
    int key;
}Record;

typedef struct Tree{
    Record infos;
    Tree *right = nullptr, *left = nullptr;
    Tree *father = nullptr;
    enum type color;
}Tree;

void inicilizarTree(Tree **raiz);

void rotacaoSimplesEsquerda(Tree **raiz, Tree *child);

void rotacaoSimplesDireita(Tree **raiz, Tree *child);

void insertFixUp(Tree **raiz, Tree *child);

void insertTree(Tree ** tree , Tree **father, Tree **raiz, Record infos);

void preordem(Tree *t);

Tree* tree_Minimum(Tree *x);

void pesquisa(Tree **t, Tree **aux, Record r);

void transplante(Tree **raiz, Tree *u, Tree *v);

void deleteFixUp(Tree **raiz, Tree *x);

void deleteTree(Tree **tree, Tree *z);

#endif