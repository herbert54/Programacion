#include <iostream>
#include <vector>
using namespace std;

struct Nodo
{
    int dato;
    Nodo* left;
    Nodo* right;

    Nodo(int dato){
        this->dato=dato;
        left=nullptr;
        right=nullptr;
    }
};

class BST{
    private:
        Nodo* raiz;
        Nodo* insertarnodoaux(Nodo* nodo,int dato);
        Nodo* buscarnodoaux(Nodo* nodo,int dato);
        Nodo* buscarhojaleftAux(Nodo* Nodo,int dato);
        Nodo* buscarhojarightAux(Nodo* nodo,int dato);
    //Funciones auxiliares para imprimir los nodos en diferentes órdenes
        void imprimirEnOrdenAux(Nodo* nodo);
        void imprimirPreOrdenAux(Nodo* nodo);
        void imprimirPostOrdenAux(Nodo* nodo);
        int sizeAux(Nodo* nodo);
        int heightAux(Nodo* nodo);

    //EJERCICIO 1
        Nodo* encontrarSucesorAux(Nodo*,int);
    
    //EJERCICIO 1B
        Nodo* padreAux(Nodo*,int);
    public:
        BST();
        BST(vector<int> preorden);

        //-------TAREA-----------//

        Nodo* LCA(int,int);
        vector<int> camino(int,int);

        //-----------------------//

        ~BST();
        void insertarnodo(int dato);
        Nodo* buscarnodo(int dato);
        Nodo* buscarhojaleft(int dato);
        Nodo* buscarhojaright(int dato);
        // Funciones para imprimir los nodos en diferentes órdenes
        void imprimirEnOrden();
        void imprimirPreOrden();
        void imprimirPostOrden();
        void destruirArbol(Nodo*);
        int size();
        int height();

        //EJERCICIO 1
        Nodo* encontrarSucesor(int);

        //EJERCICIO 1B
        Nodo* padre(int);
};
BST::BST(): raiz(nullptr) {}

BST::BST(vector<int> preorden){
    raiz=nullptr;
    for (int i = 0; i < preorden.size(); i++)
    {
        insertarnodo(preorden[i]);
    }
}

Nodo* BST::LCA(int a,int b){
    Nodo* n=padre(a);
    Nodo* d=buscarnodoaux(n,b);
    Nodo* l=buscarhojaleft(n->dato);
    Nodo* r=buscarhojaright(n->dato);
    if (d->dato==b)
    {
        return n;
    }
    else
    {
        return LCA(n->dato,b);
    }
    
    

    
}




void BST::insertarnodo(int dato){
    raiz=insertarnodoaux(raiz,dato);
}

//FUNCION AUXILIAR PARA INSERTAR UN NODO EN EL ARBOL
Nodo* BST::insertarnodoaux(Nodo* nodo,int dato){
    if (nodo==nullptr)
    {
        return new Nodo(dato);
    }
    if (dato<nodo->dato)
    {
        nodo->left=insertarnodoaux(nodo->left,dato);
    }
    else if (dato>nodo->dato)
    {
        nodo->right=insertarnodoaux(nodo->right,dato);
    }
    return nodo;   
}

Nodo* BST::buscarnodo(int dato){
    return buscarnodoaux(raiz,dato);
}

Nodo* BST::buscarnodoaux(Nodo* nodo,int dato){
    if (nodo==nullptr || nodo->dato==dato)
    {
        return nodo;
    }
    if (dato<nodo->dato)
    {
        return buscarnodoaux(nodo->left,dato);
    }
    else
    {
        return buscarnodoaux(nodo->right,dato);
    }  
}
void BST::imprimirEnOrden(){
    imprimirEnOrdenAux(raiz);
    cout<<endl;
}

void BST::imprimirEnOrdenAux(Nodo* nodo){
    if (nodo==nullptr)
    {
        return;
    }

    imprimirEnOrdenAux(nodo->left);
    cout<<nodo->dato<<" ";
    imprimirEnOrdenAux(nodo->right);
}

void BST::imprimirPreOrden(){
    imprimirPreOrdenAux(raiz);
    cout<<endl;
}

void BST::imprimirPreOrdenAux(Nodo* nodo){
    if (nodo==nullptr)
    {
        return; 
    }
    
    cout<<nodo->dato<<" ";
    imprimirPreOrdenAux(nodo->left);
    imprimirPreOrdenAux(nodo->right);
}

void BST::imprimirPostOrden(){
    imprimirPostOrdenAux(raiz);
    cout<<endl;
}
void BST::imprimirPostOrdenAux(Nodo* nodo){
    if (nodo==nullptr)
    {
        return; 
    }
    imprimirPostOrdenAux(nodo->left);
    imprimirPostOrdenAux(nodo->right);
    cout<<nodo->dato<<" ";
}

BST::~BST(){
    destruirArbol(raiz);
}

void BST::destruirArbol(Nodo* nodo){
    if (nodo==nullptr)  
    {
        return;
    }
    
    destruirArbol(nodo->left);
    destruirArbol(nodo->right);
    delete nodo;
}

int BST::size(){
    return sizeAux(raiz);
}

int BST::sizeAux(Nodo* nodo){
    if (nodo==nullptr)
    {
        return 0;
    }
    return 1 + sizeAux(nodo->left)+sizeAux(nodo->right);
}

//ALTURA DEL ARBOL
int BST::height(){
    return heightAux(raiz);
}

int BST::heightAux(Nodo* nodo){
    if (nodo==nullptr)
    {
        return 0;
    }
    return 1 + max(heightAux(nodo->left),heightAux(nodo->right));
}

//EJERCICIO 1
Nodo* BST::encontrarSucesor(int dato){
    return encontrarSucesorAux(raiz,dato);
}

Nodo* BST::encontrarSucesorAux(Nodo* nodo,int dato){
    if (nodo==nullptr)
    {
        return nullptr;
    }
    if (nodo->dato<=dato)
    {
        return encontrarSucesorAux(nodo->right,dato);
    }
    else
    {
        Nodo* sucesor=encontrarSucesorAux(nodo->left,dato);
        if (sucesor==nullptr)
        {
            return nodo;
        }
        else
        {
            return sucesor;
        }
    }  
}

//EJERCICIO 1B
Nodo* BST::padre(int x){
    return padreAux(raiz,x);
}

Nodo* BST::padreAux(Nodo* nodo,int x){
    if (nodo==nullptr)
    {
        return nullptr;
    }
    if (raiz->dato==x) // x es la raiz 50
    {
        return nullptr;
    }

    if (nodo->left!=nullptr && nodo->left->dato==x ) // buscamos padre de 30 
    {
        return nodo;    
    }
    if (nodo->right!=nullptr && nodo->right->dato==x)
    {
        return nodo;
    }

    if (x<nodo->dato)
    {
        return padreAux(nodo->left,x);
    }

    else
    {
        return padreAux(nodo->right,x);
    }   
}

Nodo* BST::buscarhojaleft(int dato){
    Nodo* n=buscarnodo(dato);
    return buscarhojaleftAux(n,dato); 
 
}
Nodo* BST::buscarhojaleftAux(Nodo* nodo,int dato){
    if (nodo->left!=nullptr )
    {
        return nodo->left;
    }
    else{
        return nullptr;
    }
}

Nodo* BST::buscarhojaright(int dato){
    Nodo* n=buscarnodo(dato);
    return buscarhojaleftAux(n,dato); 
 
}
Nodo* BST::buscarhojarightAux(Nodo* nodo,int dato){
    if (nodo->right!=nullptr )
    {
        return nodo->right;
    }
    else{
        return nullptr;
    }
}
int main() {

    int x=55;
    int a=10,b=40;
    vector<int> pre_order = {50,30,20,10,25,40,70,60,55,65,80,75,90};
    BST arbol(pre_order);
    arbol.imprimirPreOrden();
    Nodo* padre=arbol.padre(x);
    //cout<<"El padre de "<<x<<" es: "<<padre->dato<<endl;
    Nodo* lca1=arbol.LCA(a,b);
    cout<<"El ancestro comun es "<<lca1->dato<<endl;
    Nodo* buscar=arbol.buscarhojaleft(60);
    //cout<<"La hoja left: "<<buscar->dato<<endl;

    Nodo* e=arbol.buscarnodo(35);
    //cout<<"nodo: "<<e<<endl;
}

