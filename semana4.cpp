#include <iostream>
#include <vector>
using namespace std;

// Definición de la clase Nodo
class Nodo {
public:
  int dato;
  Nodo* left;
  Nodo* right;

  // Constructor
  Nodo(int dato) {
    this->dato = dato;
    left = nullptr;
    right = nullptr;
  }
};

// Definición de la clase BST (Árbol Binario de Búsqueda)
class BST {
private:
    Nodo* raiz;
    Nodo* insertarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarhojaleftAux(Nodo* nodo,int dato);
    Nodo* buscarhojarightAux(Nodo* nodo,int dato);


    // Funciones auxiliares para imprimir los nodos en diferentes órdenes
    void imprimirEnOrdenAux(Nodo* nodo);
    void imprimirPreOrdenAux(Nodo* nodo);
    void imprimirPostOrdenAux(Nodo* nodo);
    int calcularAlturaAux(Nodo* nodo);

    // Ejercicio 1:
    Nodo* encontrarSucesorAux(Nodo*, int);

    // EJERCICIO 2:
    bool esArbolAVLAux(Nodo* Nodo);

    //Ejercicio 3:
    Nodo* hojaIzquierda(Nodo* nodo);
    Nodo* hojaDerecha(Nodo* nodo);

    //EJERCICIO 1B
    Nodo* padreAux(Nodo*, int);

    Nodo* LCAAux(Nodo*,int);

public:
    // Constructor
    BST();
    BST(vector<int> preorden);

    //----------TAREA----------//
    Nodo* LCA(int,int);
    vector<int> camino(int,int);




    ~BST();
    void insertarNodo(int dato);
    Nodo* buscarNodo(int dato);
    Nodo* buscarhojaleft(int dato);
    Nodo* buscarhojaright(int dato);

  // Funciones para imprimir los nodos en diferentes órdenes
    void imprimirEnOrden();
    void imprimirPreOrden();
    void imprimirPostOrden();
    void destruirArbol(Nodo*);
    int calcularAltura();

    // Ejercicio 1a:
    Nodo* encontrarSucesor(int);

    //Ejercicio 2a:
    bool esArbolAVL();

    //Ejercicio 3a:

    int maximo();
    int minimo();

    //Ejercicio 1b:
    Nodo* padre(int);

};

// Constructor
BST::BST(): raiz(nullptr) {}

// Constructor
BST::BST(vector<int> preorden) {
  raiz = nullptr;
  for (int i = 0; i < preorden.size(); i++) {
    insertarNodo(preorden[i]);
  }
}

Nodo* BST::LCA(int a,int b){
    Nodo* n=padre(a);
    if (LCAAux(n,b)!=buscarNodo(b))
    {
      return LCA(n->dato,b);
    }
    else{
      return buscarNodo(n->dato); 
    }
}

Nodo* BST::LCAAux(Nodo* nodo,int b){
  if (nodo == nullptr || nodo->dato == b)
    return nodo;

  if (b < nodo->dato)
    return buscarNodoAux(nodo->left, b);
  else
    return buscarNodoAux(nodo->right, b);
}

// Insertar un nodo en el árbol
void BST::insertarNodo(int dato) {
  raiz = insertarNodoAux(raiz, dato);
}

// Función auxiliar para insertar un nodo en el árbol
Nodo* BST::insertarNodoAux(Nodo* nodo, int dato) {
  if (nodo == nullptr)
    return new Nodo(dato);

  if (dato < nodo->dato)
    nodo->left = insertarNodoAux(nodo->left, dato);
  else if (dato > nodo->dato)
    nodo->right = insertarNodoAux(nodo->right, dato);
  return nodo;
}

// Buscar un nodo en el árbol
Nodo* BST::buscarNodo(int dato) {
  return buscarNodoAux(raiz, dato);
}

// Función auxiliar para buscar un nodo en el árbol
Nodo* BST::buscarNodoAux(Nodo* nodo, int dato) {
  if (nodo == nullptr || nodo->dato == dato)
    return nodo;

  if (dato < nodo->dato)
    return buscarNodoAux(nodo->left, dato);
  else
    return buscarNodoAux(nodo->right, dato);
}



// Función para imprimir los nodos en orden
void BST::imprimirEnOrden() {
  imprimirEnOrdenAux(raiz);
  cout << endl;
}

// Función auxiliar para imprimir los nodos en orden
void BST::imprimirEnOrdenAux(Nodo* nodo) {
  if (nodo == nullptr) {
    return;
  }

  imprimirEnOrdenAux(nodo->left);
  cout << nodo->dato << " ";
  imprimirEnOrdenAux(nodo->right);
}

// Función para imprimir los nodos en preorden
void BST::imprimirPreOrden() {
  imprimirPreOrdenAux(raiz);
  cout << endl;
}

// Función auxiliar para imprimir los nodos en preorden
void BST::imprimirPreOrdenAux(Nodo* nodo) {
  if (nodo == nullptr) {
    return;
  }

  cout << nodo->dato << " ";
  imprimirPreOrdenAux(nodo->left);
  imprimirPreOrdenAux(nodo->right);
}

// Función para imprimir los nodos en postorden
void BST::imprimirPostOrden() {
  imprimirPostOrdenAux(raiz);
  cout << endl;
}

// Función auxiliar para imprimir los nodos en postorden
void BST::imprimirPostOrdenAux(Nodo* nodo) {
  if (nodo == nullptr) {
    return;
  }

  imprimirPostOrdenAux(nodo->left);
  imprimirPostOrdenAux(nodo->right);
  cout << nodo->dato << " ";
}

BST::~BST() {
  destruirArbol(raiz);
}

// Función auxiliar para destruir el árbol utilizando un recorrido PostOrden
void BST::destruirArbol(Nodo* nodo) {
  if (nodo == nullptr) {
    return;
  }

  // Recorrer el subárbol izquierdo
  destruirArbol(nodo->left);

  // Recorrer el subárbol derecho
  destruirArbol(nodo->right);

  // Eliminar el nodo actual
  delete nodo;
}

// Altura del Arbol
int BST::calcularAltura() {
  return calcularAlturaAux(raiz);
}

// Función auxiliar para calcular la altura de un nodo
int BST::calcularAlturaAux(Nodo* nodo) {
  if (nodo == nullptr)
    return 0;

  return 1 + max(calcularAlturaAux(nodo->left), calcularAlturaAux(nodo->right));
}

// Ejercicio 1:
Nodo* BST::encontrarSucesor(int dato) {
    return encontrarSucesorAux(raiz, dato);
}

// Función auxiliar para encontrar el sucesor de un nodo
Nodo* BST::encontrarSucesorAux(Nodo* nodo, int dato) {
    if (nodo == nullptr)
        return nullptr;
    if (nodo->dato <= dato)
        return encontrarSucesorAux(nodo->right, dato);
    else{
        Nodo* sucesor = encontrarSucesorAux(nodo->left, dato);
        if (sucesor == nullptr)
            return nodo;
        else
            return sucesor;
    }
}

//EJERCICIO 2
bool BST::esArbolAVL(){
  return esArbolAVLAux(raiz);
}

bool BST::esArbolAVLAux(Nodo* nodo){
  if (nodo==nullptr)
  {
    return true;
  }

  int alturaIzq=calcularAlturaAux(nodo->left);
  int alturaDer=calcularAlturaAux(nodo->right);
  int diferenciaAltura=abs(alturaIzq-alturaDer);

  if (diferenciaAltura>1)
  {
    return false;
  }

  return esArbolAVLAux(nodo->left) && esArbolAVLAux(nodo->right); 
}

//EJERCICIO 3
int BST::maximo(){
  return hojaDerecha(raiz)->dato;
}
Nodo* BST::hojaDerecha(Nodo* nodo){
  if (nodo->right==nullptr)
  {
    return nodo;
  }
  return hojaDerecha(nodo->right);  
}

int BST::minimo(){
  return hojaIzquierda(raiz)->dato;
}

Nodo* BST::hojaIzquierda(Nodo* nodo){
  if (nodo->left==nullptr)
  {
    return nodo;
  }
  return hojaIzquierda(nodo->left);
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
  Nodo* n=buscarNodo(dato);
  return buscarhojaleftAux(n,dato);
}

Nodo* BST::buscarhojaleftAux(Nodo* nodo,int dato){
  if (nodo->left!=nullptr)
  {
    return nodo->left;
  }
  else{
    return nullptr;
  }
}

Nodo* BST::buscarhojaright(int dato){
  Nodo* n=buscarNodo(dato);
  return buscarhojarightAux(n,dato);
}

Nodo* BST::buscarhojarightAux(Nodo* nodo,int dato){
  if (nodo->right!=nullptr)
  {
    return nodo->right;
  }
  else{
    return nullptr;
  }
}

int main() {
    // int x=55;
    // int a=25,b=65;
    // vector<int> pre_order = {50,30,20,10,25,40,70,60,55,65,80,75,90};
    // BST arbol(pre_order);
    // //arbol.imprimirPreOrden();
    // Nodo* padre=arbol.padre(x);
    // //cout<<"El padre de "<<x<<" es: "<<padre->dato<<endl;
    // Nodo* lca1=arbol.LCA(a,b);
    // cout<<"El ancestro comun es "<<lca1->dato<<endl;
    // Nodo* buscar=arbol.buscarhojaleft(60);
    // //cout<<"La hoja left: "<<buscar->dato<<endl;

    // Nodo* e=arbol.buscarNodo(35);
    // //cout<<"nodo: "<<e<<endl;


    BST arbol;

    arbol.insertarNodo(25);
    arbol.insertarNodo(20);
    arbol.insertarNodo(36);
    arbol.insertarNodo(10);
    arbol.insertarNodo(22);
    arbol.insertarNodo(30);
    arbol.insertarNodo(40);
    arbol.insertarNodo(5);
    arbol.insertarNodo(12);
    arbol.insertarNodo(28);
    arbol.insertarNodo(38);
    arbol.insertarNodo(48);
    arbol.insertarNodo(2);
    arbol.insertarNodo(7);
    arbol.insertarNodo(16);
    arbol.insertarNodo(26);
    arbol.insertarNodo(44);
    arbol.insertarNodo(51);

    //arbol.imprimirPreOrden();
    Nodo* buscar=arbol.buscarhojaleft(48);
    cout<<"La hoja left: "<<buscar->dato<<endl;
    Nodo* bsc=arbol.buscarhojaright(48);
    cout<<"La hoja right: "<<bsc->dato<<endl;
    
}
