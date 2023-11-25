#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
#include <queue>
using namespace std;

#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_YELLOW "\033[1;33m"  
#define ANSI_COLOR_RED "\033[1;31m"  
#define ANSI_COLOR_ORANGE "\033[1;38;5;208m"
#define ANSI_COLOR_GREEN "\033[1;32m"   
#define ANSI_COLOR_CELESTE "\033[36m"

struct Position
{
    int row;
    int col;

    Position(int r,int c):row(r),col(c){}
};



void printmaze(const vector<vector<char>>& maze, size_t eRow, size_t eCol,size_t endRow, size_t endCol) {
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (i == eRow && j == eCol && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            } else if (i == endRow && j == endCol && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            }else if (maze[i][j]=='*'){
                cout<<ANSI_COLOR_ORANGE<<'*'<<ANSI_COLOR_RESET<<' ';
            }else if (maze[i][j]=='+'){
                cout<<ANSI_COLOR_CELESTE<<'+'<<ANSI_COLOR_RESET<<' ';
            }else {
                cout << maze[i][j] << ' ';
            }
        }
        cout<<endl;
    }
}

void printMazesolution(vector<vector<char>>& maze, const Position& start, const Position& end, const vector<Position>& path) {
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (i == start.row && j == start.col && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            } else if (i == end.row && j == end.col && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            } else if (maze[i][j]=='+'){
                cout<<ANSI_COLOR_CELESTE<<'+'<<ANSI_COLOR_RESET<<' ';
            }
            
            
            else {
                bool isPath = false;
                for (const auto& pos : path) {
                    if (i == pos.row && j == pos.col) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << ANSI_COLOR_GREEN << '*' << ANSI_COLOR_RESET << ' ';
                }else if (maze[i][j]=='*'){
                cout<<ANSI_COLOR_ORANGE<<'*'<<ANSI_COLOR_RESET<<' ';
                } 
                else {
                    cout << maze[i][j] << ' ';
                }
            }
        }
        cout<<endl;
    }
}

//DFS
bool caminoDFS(vector<vector<char>>& maze,Position current,const Position& end,vector<Position>& path){
    if (current.row<0 || current.row>=maze.size() || current.col<0 || current.col>=maze[current.row].size())
    {
        return false;
    }

    if (current.row == end.row && current.col==end.col)
    {
        path.push_back(current);
        return true;
    }

    if (maze[current.row][current.col]==' ' || maze[current.row][current.col]=='e')
    {
        path.push_back(current);

        maze[current.row][current.col]='*';
        
        if (caminoDFS(maze, {current.row - 1, current.col}, end, path) ||
            caminoDFS(maze, {current.row + 1, current.col}, end, path) ||
            caminoDFS(maze, {current.row, current.col - 1}, end, path) ||
            caminoDFS(maze, {current.row, current.col + 1}, end, path)) {
            return true;
        }

        path.pop_back();
    }
    return false; 
}

bool caminoBFS(vector<vector<char>>& maze,const Position& star,const Position& end,vector<Position>& path){
    // Verificar si estamos fuera de los limites del laberinto
    if (star.row<0 || star.row>=maze.size() || star.col<0 || star.col>=maze[star.row].size()){
       return false; 
    }

    queue<Position> queue;
    vector<vector<bool>> visited(maze.size(),vector<bool>(maze[0].size(),false));
    vector<vector<Position>> parent(maze.size(),vector<Position>(maze[0].size(),Position(-1,-1)));
    
    queue.push(star);
    visited[star.row][star.col]=true;

    while (!queue.empty()){
        Position current=queue.front();
        queue.pop();
        maze[current.row][current.col]='*';
        if (current.row==end.row && current.col==end.col){
            Position backtrack=end;
            while (!(backtrack.row==star.row && backtrack.col==star.col)){
                path.push_back(backtrack);
                backtrack=parent[backtrack.row][backtrack.col];
            }
            // Revertir el camino para tener la dirección correcta
            reverse(path.begin(),path.end());
            return true;
        }
        
        //Explorar en las 4 direcciones
        vector<Position> directions={{-1,0}, {1,0},{0,-1},{0,1}};

        for(const auto& dir:directions){
            int newrow=current.row+dir.row;
            int newcol=current.col+dir.col;

            if (newrow>=0 && newrow<maze.size()&&newcol>=0&&newcol<maze[newrow].size()&&
            maze[newrow][newcol]!='+' && !visited[newrow][newcol])
            {
                queue.push({newrow,newcol});
                visited[newrow][newcol]=true;
                parent[newrow][newcol]=current;
            } 
        }
    }
    return false;
}

void datastart(vector<vector<char>> maze, int& starrow, int& startcol) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'e') {
                starrow = i;
                startcol = j;
                break;
            }
        }
    }
}

void dataend(vector<vector<char>> maze, int& endrow, int& endcol) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 's') {
                endrow = i;
                endcol = j;
                break;
            }
        }
    }
}

int main(){

    ifstream file("maze.txt");
    vector<vector<char>> maze;
    string line;
    while (getline(file,line))
    {
        vector<char> row;

        for(char c:line){
            row.push_back(c);
        }
        maze.push_back(row);
    }

    file.close();
    
    
    int starrow=0,startcol=0;
    datastart(maze,starrow,startcol);
    // int starrow=1,startcol=1;
    
    int endrow=0,endcol=0;
    dataend(maze,endrow,endcol);
    // int endrow=19,endcol=31;
    
    //cout<<starrow<<" "<<startcol<<endl;
    //cout<<endrow<<" "<<endcol<<endl;

    // maze[starrow][startcol]='e';
    // maze[endrow][endcol]='s';

    //printmaze(maze,starrow,startcol,endrow,endcol);

    int seleccion;
    cout<<setw(10)<<"MENU"<<endl;
    cout<<setw(2)<<"1.Jugar laberinto"<<endl;
    cout<<setw(2)<<"2.Solucion con algoritmo DFS"<<endl;
    cout<<setw(2)<<"3.Solucion con algoritmo BFS"<<endl;
    cout<<setw(2)<<"4.Exit"<<endl;
    cout<<"Seleccione: ";cin>>seleccion;


    if (seleccion==1){
        int starrow=0,startcol=0;
        datastart(maze,starrow,startcol);

        // Encontrar la posición final "s"
        int endrow=0,endcol=0;
        dataend(maze,endrow,endcol);

        printmaze(maze,starrow,startcol,endrow,endcol);

        char move;
        while (true)
        {
            cout<< "Ingresa la direccion de movimiento (w/a/s/d para arriba/izquierda/abajo/derecha, q para salir): ";
            cin>>move;
            if (move=='q')
            {
                break;
            }
            
            int newrow=starrow;
            int newcol=startcol;

            if (move=='w' && starrow>0 && maze[starrow-1][startcol]!='+')
            {
                newrow--;
            }else if (move=='a' && startcol>0 && maze[starrow][startcol-1]!='+')
            {
                newcol--;   
            }else if (move=='s' && starrow<maze.size()-1 && maze[starrow+1][startcol]!='+')
            {
                newrow++;
            }else if (move=='d' && startcol<maze[starrow].size()-1 && maze[starrow][startcol+1]!='+')
            {
                newcol++;
            }
            if (starrow==endrow && startcol==endcol)
            {
                cout<<"¡Felicidades! ¡Has encontrado el camino!"<<endl;
                break;
            }
            
            //Marcar trayectoria
            maze[starrow][startcol]=' ';
            maze[starrow][startcol]='*';
            maze[newrow][newcol]='e';

            // Actualizar la posición actual
            starrow=newrow;
            startcol=newcol;
            
            printmaze(maze,starrow,startcol,endrow,endcol);
        }
    }else if (seleccion==2){
        
        // int startrow=0,startcol=0;
        // datastart(maze,startrow,startcol);

        // int endrow=0,endcol=0;
        // dataend(maze,endrow,endcol);

        // vector<Position> path;

        // if (caminoDFS(maze,{startrow,startcol},{endrow,endcol},path))
        // {
        //     cout<<"Camino encontrado: "<<endl;
        //     maze[1][1]='e';
        //     maze[19][31]='s';
        //     printMazesolution(maze,{startrow,startcol},{endrow,endcol},path);
        // }else
        // {
        //     cout<<"No se encontro un camino desde 'e' hasta 's'. "<<endl;
        // }



        int slc;
        cout<<setw(10)<<"SUBMENU"<<endl;
        cout<<setw(2)<<"1.Posicion de inicio y final por defecto"<<endl;
        cout<<setw(2)<<"2.Cambiar de posicion"<<endl;
        cout<<"Seleccione: ";cin>>slc;
        if (slc==1)
        {
            int startrow=1,startcol=1;
            int endrow=19,endcol=31;
            maze[startrow][startcol]='e';
            maze[endrow][endcol]='s';
            
            vector<Position> path;

            if (caminoDFS(maze,{startrow,startcol},{endrow,endcol},path))
            {
                cout<<"Camino encontrado: "<<endl;
                maze[1][1]='e';
                printMazesolution(maze,{startrow,startcol},{endrow,endcol},path);
            }else
            {
                cout<<"No se encontro un camino desde 'e' hasta 's'. "<<endl;
            }
        }else if (slc==2)
        {
            int startrow=0,startcol=0;
            int endrow=0,endcol=0;
            srand(time(nullptr));

            do {
                startrow = rand() % maze.size();
                startcol = rand() % maze[startrow].size();
                endrow = rand() % maze.size();
                endcol = rand() % maze[endrow].size();
            } while ((startrow == endrow && startcol == endcol) || maze[startrow][startcol] == '+' || maze[endrow][endcol] == '+');

            maze[startrow][startcol] = 'e';
            maze[endrow][endcol] = 's';

            int tmp1=startrow;
            int tmp2=startcol;

            vector<Position> path;

            if (caminoDFS(maze,{startrow,startcol},{endrow,endcol},path))
            {
                cout<<"Camino encontrado: "<<endl;
                maze[tmp1][tmp2]='e';
                printMazesolution(maze,{startrow,startcol},{endrow,endcol},path);
            }else
            {
                cout<<"No se encontro un camino desde 'e' hasta 's'. "<<endl;
            }
        }else
        {
            cout<<" ";
        }  
    }else if (seleccion==3){
        //Encontrar la posicion inicial
        int startrow=0,startcol=0;
        datastart(maze,startrow,startcol);

        //Encontrar la posicion final
        int endrow=0,endcol=0;
        dataend(maze,endrow,endcol);

        vector<Position> pathBFS;
        if (caminoBFS(maze,{startrow,startcol},{endrow,endcol},pathBFS))
        {
            cout<<"Camino encontrado con BFS"<<endl;
            maze[1][1]='e';
            maze[19][31]='s';
            printMazesolution(maze,{startrow,startcol},{endrow,endcol},pathBFS);
        }else
        {
            cout<<"No se encontro un camino desde 'e' hasta 's'. "<<endl;
        }
    }

    else
    {
        cout<<"";
    }
}





