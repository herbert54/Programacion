#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// template<typename T1>
// struct printstring{
//     T1 _c;
//     printstring(T1 c=' '):_c(c){}
//     template<typename T>
//     void operator()(T s){
//         cout<<s<<_c;
//     }
// };

// int main(){
//     // printstring line(4);
//     // line('\n');

//     // printstring execl('!');
//     // execl("Ingrese un entero valido");

//     string v[4]={"hola","mundo","en","c++"};
//     for_each(v,v+v->size(),printstring('\n'));

//     vector<string> m={"hola","mundo","en","c++"};
//     for_each(m.begin(),m.end(),printstring(' '));
    
//     // vector<dato> v;

//     void* p;
//     int i=3;
//     p=&i;

//     double d=4.5;
//     p=&d;
// }

//FUNCION CALLBACKS
// void print(vector<int> v){
//     for_each(v.begin(),v.end(),[](int x){cout<<x<<" ";});
//     cout<<endl;
// }

bool comparador(int x1,int x2){
    if (x1>x2){
        return true;        
    }
    return false;   
}

void bubblesort(vector<int> &A,bool (*comparador)(int, int)){
    for (int i = 0; i < A.size()-1; i++)
    {
        for (int j = 0; j < A.size()-i-1; j++)
        {
            if (comparador(A[j],A[j+1])){
                swap(A[j],A[j+1]);
            }
        }
    }
}

bool no_decre(int a,int b){
    return a>b;
}

bool no_ascen(int a,int b){
    return a<b;
}

bool no_decre_mod(int a,int b){
    return(a)>abs(b);
}




// int main(){
//     vector<int> v={5,-3,1,2,2,0,4,-7,4};
//     print(v);

//     bubblesort(v,no_decre);
//     print(v);
//     cout<<endl;
// }

struct Cifrar
{
    int a,b;
    Cifrar(int a_,int b_):a(a_),b(b_){}
    char operator()(char x_char){
        int x=x_char-65;
        int c=(a*x+b)%26;
        char c_char=c+65;
        return c_char;
    }
};

// int main(){
//     Cifrar C(2,6);

//     cout<<C('A')<<endl;
//     cout<<C('Z')<<endl;
//     cout<<C('M')<<endl;

//     // string texto="PROGRAMACION";
//     // string cifrado="";

//     // for (char c:texto)
//     // {
//     //     cifrado+=C(c);
        
//     // }
//     // cout<<cifrado;
// }



template<typename T>
void print(vector<T> v){
    for_each(v.begin(),v.end(),[](T x){cout<<x<<" ";});
    cout<<endl;
}

// int main(){
//     string fligs="CDET";
//     vector<string> desk(52);

//     int n=-1;
//     generate(desk.begin(),desk.end(),[&](){
//         n++;
//         return to_string(1+n%13 )+ fligs[n/13];
//     });
//     print(desk);
//     srand(time(nullptr));
//     random_shuffle(desk.begin(),desk.end());
//     print(desk);
// }




int main(){
    int **M=new int*[3];
    for(int i=0;i<3;i++)
    M[i]=new int[3];
    M[0][0]=1;M[0][1]=2;M[0][2]=3;
    M[1][0]=4;M[1][1]=5;M[1][2]=6;
    M[2][0]=7;M[2][1]=8;M[2][2]=9;

    print(M);

    cout<<endl;
    Transformer transformer1("SUMA",3);
    modificar_matriz(M,transformer1);
}

