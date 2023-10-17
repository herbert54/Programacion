#include <iostream>
#include <forward_list>
#include <unordered_set>

using namespace std;

/*------ ELIMINACION DE NODOS DUPLICADOS */

template<typename T>
void removeduplicates(forward_list<T>& mylist){
    unordered_set<T> seen;
    auto current=mylist.begin();
    auto previos=mylist.before_begin();

    while (current!=mylist.end())
    {
        if (seen.find(*current)!=seen.end())
        {
            //ELIMINA EL NODO DUPLICADO
            current=mylist.erase_after(previos);
        }else
        {
            //Agrega el valor a la lista de elementos vistos
            seen.insert(*current);
            //AVANZA AL SIGUIENTE NODO
            previos=current;
            ++current;
        }    
    }
}

// int main(){
//     forward_list<int> mylist={1,2,3,2,4,5,3,6,7};

//     cout<<"Lista original: ";
//     for(const auto& value:mylist){
//         cout<<value<<" ";
//     }
//     cout<<endl;

//     removeduplicates(mylist);

//     cout<<"Lista sin duplicados: ";
//     for(const auto&value:mylist){
//         cout<<value<<" ";
//     }
// }

/*---------PALINDROMO----------*/

template<typename T>
bool espalindromo(const forward_list<T>& mylist){
    if (mylist.empty()|| next(mylist.begin())==mylist.end()) 
    {
        return true;
    }
    
    auto slow=mylist.begin();
    auto fast=mylist.begin();
    forward_list<T> firsthalf;

    while (fast!=mylist.end()&&next(fast)!=mylist.end())        
    {
        firsthalf.push_front(*slow);
        slow++;
        fast++;
        fast++;
    }

    // Si la lista tiene un número impar de elementos, avanzamos el puntero "slow" una posición más
    if (fast!=mylist.end())
    {
        slow++;
    }

    // Comparamos la primera mitad de la lista original con la segunda mitad reversa
    auto it1=firsthalf.begin();
    auto it2=slow;

    while (it1!=firsthalf.end()&&it2!=mylist.end())
    {
        if (*it1!=*it2)
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
    
}

// int main() {
//     std::forward_list<int> myList1 = {1, 2, 3, 2, 1};
//     std::forward_list<int> myList2 = {1, 2, 3, 4, 5};

//     std::cout << "Lista 1 es un palindromo: " << espalindromo(myList1) << std::endl;
//     std::cout << "Lista 2 es un palindromo: " << espalindromo(myList2) << std::endl;

//     return 0;
// }


template<typename T>
class stack
{
private:
    forward_list<T> data;
public:
    void push(const T& value){
        data.push_front(value);
    }

    void pop(){
        if (!empty())
        {
            data.pop_front();
        }
    }

    T top(){
        if (!empty())
        {
            return data.front();
        }
        throw out_of_range("La pila esta vacía");
    }

    bool empty(){
        return data.empty();
    }
};

// template<typename T>
// class queue
// {
// private:
//     forward_list<T> data;
// public:
//     void push(const T& value) {
//         data.push_front(value);
//     }

//     void pop() {
//         if (!empty()) {
//             data.pop_back();
//         }
//     }

//     T front() {
//         if (!empty()) {
//             return data.back();
//         }
//         throw std::out_of_range("La cola está vacía");
//     }

//     bool empty() {
//         return data.empty();
//     }
// };
int main(){
    stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    cout<< "Top of the stack: " << myStack.top()<<endl;
    myStack.pop();
    cout<< "Top of the stack after pop: " << myStack.top()<<endl;

    // queue<int> myQueue;
    // myQueue.push(1);
    // myQueue.push(2);
    // myQueue.push(3);

    // std::cout << "Front of the queue: " << myQueue.front() << std::endl;
    // myQueue.pop();
    // std::cout << "Front of the queue after pop: " << myQueue.front() << std::endl;

}






/*----REALIZANDO SUMA DE ELEMENTOS OPUESTOS-----*/

#include <iostream>
#include <list>

// int main() {
//     std::list<int> numeros{9,1,2,1,2,6,12,9};

//     std::list<int> sumas;

//     while (numeros.size() > 1) {
//         int suma = numeros.front() + numeros.back();
//         sumas.push_back(suma);
//         numeros.pop_front();
//         numeros.pop_back();
//     }

//     // Si la lista original tiene un elemento restante, sumarlo consigo mismo
//     if (!numeros.empty()) {
//         int valor_medio = numeros.front();
//         sumas.push_back(valor_medio * 2);
//     }

//     // Mostrar las sumas
//     int contador = 1;
//     for (const int& resultado : sumas) {
//         std::cout << "Suma " << contador << ": " << resultado << std::endl;
//         contador++;
//     }

//     return 0;
// }
