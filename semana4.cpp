#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

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

class BST {
private:
    Nodo* raiz;
    Nodo* insertarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarNodoAux(Nodo* nodo, int dato);

    // Funciones auxiliares para imprimir los nodos en diferentes órdenes
    void imprimirPreOrdenAux(Nodo* nodo);

    Nodo* padreAux(Nodo*, int);

    Nodo* LCAAux(Nodo*,int);
    vector<int> caminoAux(Nodo*,int,int);
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

  // Funciones para imprimir los nodos en diferentes órdenes
    void imprimirPreOrden();
    void destruirArbol(Nodo*);

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

BST::~BST() {
  destruirArbol(raiz);
}

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


// vector<int> BST::camino(int inicio, int fin) {
//     // Buscar los nodos correspondientes a los datos de inicio y fin
//     Nodo* inicioNodo = buscarNodo(inicio);
//     Nodo* finNodo = buscarNodo(fin);
//     Nodo* lcanodo =LCA(inicio,fin);
//     // Verificar si ambos nodos existen en el árbol
//     if (inicioNodo == nullptr || finNodo == nullptr) {
//         // Al menos uno de los nodos no está presente en el árbol
//         // Puedes manejar esto de acuerdo a tus necesidades (lanzar una excepción, devolver un vector vacío, etc.)
//         return vector<int>();
//     }

//     // Obtener el camino desde el nodo de inicio hasta el nodo de fin
//     vector<int> caminoVector = caminoAux(lcanodo, inicio, fin);

//     return caminoVector;
// }

// vector<int> BST::caminoAux(Nodo* nodo, int inicio, int fin) {
//     vector<int> caminoVector;

//     // Si el nodo actual es nulo o es el nodo de inicio
//     if (nodo == nullptr || nodo->dato == inicio) {
//         caminoVector.push_back(inicio);
//         return caminoVector;
//     }

//     // Buscar en el subárbol izquierdo
//     if (inicio < nodo->dato) {
//         vector<int> izquierda = caminoAux(nodo->left, inicio, fin);
//         caminoVector.insert(caminoVector.end(), izquierda.begin(), izquierda.end());
//     }

//     // Si el nodo actual es parte del camino, agregarlo al vector
//     caminoVector.push_back(nodo->dato);

//     // Buscar en el subárbol derecho
//     if (fin > nodo->dato) {
//         vector<int> derecha = caminoAux(nodo->right, inicio, fin);
//         caminoVector.insert(caminoVector.end(), derecha.begin(), derecha.end());
//     }

//     return caminoVector;
// }

vector<int> BST::camino(int inicio, int fin) {
    // Buscar los nodos correspondientes a los datos de inicio y fin
    Nodo* inicioNodo = buscarNodo(inicio);
    Nodo* finNodo = buscarNodo(fin);
    Nodo* lcanodo =LCA(inicio,fin);
    // Verificar si ambos nodos existen en el árbol
    if (inicioNodo == nullptr || finNodo == nullptr) {
        // Al menos uno de los nodos no está presente en el árbol
        // Puedes manejar esto de acuerdo a tus necesidades (lanzar una excepción, devolver un vector vacío, etc.)
        return vector<int>();
    }

    // Obtener el camino desde el nodo de inicio hasta el nodo de fin
    vector<int> caminoVector = caminoAux(lcanodo, inicio, fin);

    return caminoVector;
}

vector<int> BST::caminoAux(Nodo* nodo, int inicio, int fin) {
    vector<int> caminoVector;

    // Si el nodo actual es nulo o es el nodo de inicio
    if (nodo == nullptr || nodo->dato == inicio) {
        caminoVector.push_back(inicio);
        return caminoVector;
    }

    // Buscar en el subárbol izquierdo
    if (inicio < nodo->dato) {
        vector<int> izquierda = caminoAux(nodo->left, inicio, fin);
        caminoVector.insert(caminoVector.end(), izquierda.begin(), izquierda.end());
    }

    // Si el nodo actual es parte del camino, agregarlo al vector
    caminoVector.push_back(nodo->dato);

    // Si el nodo actual es el nodo de fin, detener la búsqueda
    if (nodo->dato == fin) {
        return caminoVector;
    }

    // Buscar en el subárbol derecho
    if (fin > nodo->dato) {
        vector<int> derecha = caminoAux(nodo->right, inicio, fin);
        caminoVector.insert(caminoVector.end(), derecha.begin(), derecha.end());
    }

    return caminoVector;
}



int main() {
    int x=55,y=75;
    vector<int> pre_order = {50,30,20,10,25,40,70,60,55,65,80,75,90};
    BST arbol(pre_order);

    vector<int> camino1 = arbol.camino(x,y);
    for (int nodo : camino1) {
        cout << nodo << " ";
    }
}
