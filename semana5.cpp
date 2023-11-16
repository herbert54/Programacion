#include <iostream>
#include <algorithm>
#include <vector>
#include <vector>
#include <fstream>

#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_YELLOW "\033[1;33m"  
#define ANSI_COLOR_RED "\033[1;31m"  
#define ANSI_COLOR_ORANGE "\033[1;38;5;208m"

// void printmaze(const vector<vector<char>>& maze){
//     for(const auto& row:maze){
//         for(char cell:row){
//             cout<<cell<<' ';
//         }
//         cout<<endl;
//     }
// }

void printmaze(const std::vector<std::vector<char>>& maze, size_t eRow, size_t eCol,size_t endRow, size_t endCol) {
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (i == eRow && j == eCol && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            } else if (i == endRow && j == endCol && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            }else if (maze[i][j]=='x'){
                cout<<ANSI_COLOR_ORANGE<<'x'<<ANSI_COLOR_RESET<<' ';
            }else {
                cout << maze[i][j] << ' ';
            }
        }
        std::cout << std::endl;
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
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j]=='e')
            {
                starrow=i;
                startcol=j;
                break;
            }
        }
    }

    // Encontrar la posición final "s"
    int endrow=0,endcol=0;
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j]=='s')
            {
                endrow=i;
                endcol=j;
                break;
            }  
        }
    }
    
    
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
        maze[starrow][startcol]='x';


        maze[starrow][startcol]=' ';
        maze[newrow][newcol]='e';

        // Actualizar la posición actual
        starrow=newrow;
        startcol=newcol;

        printmaze(maze,starrow,startcol,endrow,endcol);
    }
    
    
    
}
