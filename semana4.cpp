#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

// template<class T>
// T Max(T a,T b){
//     cout<<"T max(T a,T b): ";
//     return a>b?a:b;
// }

// template <>
// char Max(char a,char b){
//     cout<<"Especializacion max(T a,T b): "<<endl;
//     return a>b?a:b;
// }


// template<class T>
// struct Foo{
//     Foo(){cout<<"Plantilla Original"<<endl;}
// };

// template <>
// struct Foo<int>{
//     Foo(){cout<<"Plantilla Especializada"<<endl;}
// };
// template<typename... T>
// void foo(T... xs){
//     cout<<sizeof...(xs);
// }

/*return (xs + ...)   ->  1+ (2+(3+(4 +5 )))
  return (... + xs)   -> (((1+2)+3 )+ 4)+5)*/

template<class... Ts>
auto suma(Ts... args){
    return (args+...);
}

// template<typename... Ts>
// void print(Ts... args){
//     (cout<<...<<args)<<endl;
// }

void print(){cout<<endl;}

template<typename T,typename... Ts>
void print(T arg,Ts...args){
    cout<<arg;
    print(args...);
}

//EJERCICIO 1

template<typename T1,typename T2>
char suma(T1 a,T2 b){
    return a+b;
}

int suma(int a,int b){
    return a+b;
}

//EJERCICIO 2
template<typename T1,typename T2>
void sumar(T1** m1,T2** m2,int filas,int columnas){
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            m1[i][j]+=m2[i][j];
        }    
    } 
}


template<typename T1,typename T2>
void sumar(T1** m1,T2 s,int filas,int columnas){
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            m1[i][j]+=s;
        }    
    } 
}


//EJERCICIO 3
template<typename T>
T max(vector<T> vec){
    T maximo=vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i]>maximo)
        {
            maximo=vec[i];
        }
        
    }
    return maximo;
};

template<>
string max(vector<string> vec){
    string maximo=vec[0];
    int maximo_sz=maximo.size();

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].size()>maximo_sz)
        {
            maximo=vec[i];
            maximo_sz=maximo.size();
        }
        
    }   
    return maximo;
}

// int main(){
//     cout<<Max(2,1)<<endl;
//     cout<<Max('a','b')<<endl;
//     cout<<Max(0.7,1.5)<<endl;
//     Foo<float> obj1;
//     Foo<char> objt2;
//     Foo<int> obj3;
//     cout<<suma(1)<<endl;
//     cout<<suma(1,2)<<endl;
//     cout<<suma(1,2,3.5,0.5,5)<<endl;   
//     print(1,2,3,4,5);
//     print("Hola",1,"Mundo");


//     //Ejercicio 1
//     cout<<suma(3,4)<<endl;
//     cout<<suma('A',1)<<endl;
//     cout<<suma(1,'B')<<endl;
//     cout<<suma('<','>')<<endl;


//     //EJERCICIO 2
//     int** m1=new int*[5];
//     double** m2=new double*[5];

//     for (int i = 0; i < 5; i++)
//     {
//         m1[i]=new int[5];
//         m2[i]=new double[5];
//     }
//     for (int i = 0; i < 5; i++)
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             m1[i][j]=rand()%10;
//             m2[i][j]=(double)(rand()%10000)/10000;
//         }
        
//     }

//     auto** mr1=sumar(m2,m1,5,5);
//     auto** mr2=sumar(m2,5.6,5,5);

//     for (int i = 0; i < 5; i++)
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             cout<<fixed<<setprecision(4)<<mr1[i][j]<<" ";
//         }
//         cout<<endl;
//     }
    
//     for (int i = 0; i < 5; i++)
//     {
//         delete[] m1[i];
//         delete[] m2[i];
//     }


//     EJERCICIO 3
//     vector<int> v1={1,2,67,2,23,77,-5};
//     cout<<max(v1)<<endl;
// }

template<typename ...Ts>
double sumainv(Ts ...args){
    return ((1.0/args)+...);
}

template<typename ...Ts>
double mArmonica(Ts ... args){
    return (double)sizeof...(args)/sumainv(args...);
}


//EJERCICIO 2
template<typename ...Ts>
double sumacua(Ts ...args){
    return (pow(args,2)+...);
}
template<typename ...Ts>
double norma2(Ts ...args){
    return sqrt(sumacua(args...)) ;
}

// template<typename ...Ts>double norma2(Ts... args){

// return sqrt((pow(args,2)+...));
// }

//EJERCICIO 4
template<typename ...Ts>
double foo(Ts... args){
    return (args-...);
}

//EJERCICIO 5
template<typename T>
int maxnum(T a,T b){
    return a>b?a:b;
}
template<class T,class ...Ts>
int maxnum(T a,T b,Ts... args){
    return args...;
}
template<class T>
class Vec
{
private:
    vector<T> vec;
public:
    void push_back_many(T arg){
        vec.push_back(arg);
    }

    template<typename T0,typename...Ts>
    void push_back_many(T0 arg,Ts...args){
        vec.push_back(arg);
        push_back_many(args...);
    }


void print(){
    for (int e:vec)
    {
        cout<<e<<" ";
    }
    
}
};

int main(){
    
    // cout<<mArmonica(1,2,3,4,5)<<endl;
    // cout<<mArmonica(1.2,1.2,1.2)<<endl;
    // cout<<norma2(3,4)<<endl;
    //cout<<foo(4,4,5,6)<<endl;
    cout<<maxnum(3,4,5,6)<<endl;
    
}