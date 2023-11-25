#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
#include <queue>
#include <limits>

using namespace std;

#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_YELLOW "\033[1;33m"
#define ANSI_COLOR_RED "\033[1;31m"
#define ANSI_COLOR_ORANGE "\033[1;38;5;208m"
#define ANSI_COLOR_GREEN "\033[1;32m"
#define ANSI_COLOR_CELESTE "\033[1;36m"


class Position{
public:
    int row;
    int col;
    Position():row(0),col(0){}
    Position(int r,int c):row(r),col(c){}
};

class DFS{
private:
    vector<vector<char>> maze;
    Position start,end;
    vector<Position> path;

    bool validarPosicion(const Position& pos)const{
        return pos.row>=0 && pos.row <maze.size() && pos.col>= 0 && pos.col<maze[pos.row].size();
    }
    bool caminoDFS(Position current,const Position& end){
        if (!validarPosicion(current)) {
            return false;
        }

        if (current.row == end.row && current.col == end.col) {
            path.push_back(current);
            return true;
        }

        if (maze[current.row][current.col] == ' ' || maze[current.row][current.col] == 'e') {
            path.push_back(current);

            maze[current.row][current.col] = '*';

            if (caminoDFS({current.row - 1, current.col}, end) ||
                caminoDFS({current.row + 1, current.col}, end) ||
                caminoDFS({current.row, current.col - 1}, end) ||
                caminoDFS({current.row, current.col + 1}, end)) {
                return true;
            }
            path.pop_back();
        }
        return false;
    }

public:
    DFS(const string& filename){
        ifstream file(filename);
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
    }

    void datastartend();
    void printMazeSolution() const;
    bool solucionDFS(){
        return caminoDFS(start,end);
    }
};

void DFS::datastartend(){
    for (int i = 0; i < maze.size(); i++){
        for (int j = 0; j < maze[i].size(); j++){
            if (maze[i][j]=='e'){
                start.row=i;
                start.col=j;
            }else if (maze[i][j]=='s'){
                end.row=i;
                end.col=j;
            }  
        }
    }
}

void DFS::printMazeSolution()const{
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (i == start.row && j == start.col && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            }else if (i == end.row && j == end.col && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            }else if (maze[i][j]=='+')
            {
                cout<<ANSI_COLOR_CELESTE<<'+'<<ANSI_COLOR_RESET<<' ';
            }else{
                bool isPath = false;
                for (const auto& pos : path) {
                    if (i == pos.row && j == pos.col) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << ANSI_COLOR_GREEN << '*' << ANSI_COLOR_RESET << ' ';
                } else if (maze[i][j] == '*') {
                    cout << ANSI_COLOR_ORANGE << '*' << ANSI_COLOR_RESET << ' ';
                } else {
                    cout << maze[i][j] << ' ';
                }
            }
        }
        cout << endl;
    }
}

class BFS{
private:
    vector<vector<char>> maze;
    Position start,end;
    bool validarposicion(Position& pos){
        return pos.row >= 0 && pos.row < maze.size() && pos.col >= 0 && pos.col < maze[pos.row].size();
    }
    bool caminoBFS(Position& star,Position& end,vector<Position>& path){

        
        queue<Position> queue;
        vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
        vector<vector<Position>> parent(maze.size(), vector<Position>(maze[0].size(), Position(-1, -1)));

        queue.push(star);
        visited[star.row][star.col] = true;

        while (!queue.empty()) {
            Position current = queue.front();
            queue.pop();
            maze[current.row][current.col] = '*';

            if (current.row == end.row && current.col == end.col) {
                Position backtrack = end;
                while (!(backtrack.row == star.row && backtrack.col == star.col)) {
                    path.push_back(backtrack);
                    backtrack = parent[backtrack.row][backtrack.col];
                }
                reverse(path.begin(), path.end());
                return true;
            }

            vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

            for (const auto& dir : directions) {
                int newrow = current.row + dir.row;
                int newcol = current.col + dir.col;

                if (newrow >= 0 && newrow < maze.size() && newcol >= 0 && newcol < maze[newrow].size() &&
                    maze[newrow][newcol] != '+' && !visited[newrow][newcol]) {
                    queue.push({newrow, newcol});
                    visited[newrow][newcol] = true;
                    parent[newrow][newcol] = current;
                }
            }
        }
        return false;
    }
public:
    BFS(const string& filename){
        ifstream file(filename);
        string line;
        while (getline(file,line)){
            vector<char> row;
            for(char c:line){
                row.push_back(c);
            }
            maze.push_back(row);
        }
        file.close();
    }

    void datastarend();
    void printMazeSolution(vector<Position>& path);

    vector<Position> solucionBFS(){
        vector<Position> pathBFS;
        if (caminoBFS(start,end,pathBFS))
        {
            return pathBFS;
        }else{
            return {};
        } 
    }
};

void BFS::datastarend(){
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'e') {
                start = Position(i, j);
            } else if (maze[i][j] == 's') {
                end = Position(i, j);
            }
        }
    }
}

void BFS::printMazeSolution(vector<Position>& path){
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (i == start.row && j == start.col && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            }else if (i == end.row && j == end.col && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            }else if (maze[i][j]=='+')
            {
                cout<<ANSI_COLOR_CELESTE<<'+'<<ANSI_COLOR_RESET<<' ';
            }else{
                bool isPath = false;
                for (const auto& pos : path) {
                    if (i == pos.row && j == pos.col) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << ANSI_COLOR_GREEN << '*' << ANSI_COLOR_RESET << ' ';
                } else if (maze[i][j] == '*') {
                    cout << ANSI_COLOR_ORANGE << '*' << ANSI_COLOR_RESET << ' ';
                } else {
                    cout << maze[i][j] << ' ';
                }
            }
        }
        cout << endl;
    }
}

class Dijkstra{
private:
    vector<vector<char>> maze;
    Position start,end;

    bool isValidPosition(const Position& pos) const {
        return pos.row >= 0 && pos.row < maze.size() && pos.col >= 0 && pos.col < maze[pos.row].size();
    }

    int calcularDistancia(const Position& pos1,const Position& pos2)const{
        return abs(pos1.row - pos2.row) + abs(pos1.col - pos2.col);
    }

    bool caminodijkstra(const Position& start, const Position& end, vector<Position>& path)const{
        priority_queue<pair<int,Position>,vector<pair<int,Position>>,greater<pair<int,Position>>> pq;
        vector<vector<int>> distance(maze.size(), vector<int>(maze[0].size(), numeric_limits<int>::max()));
        vector<vector<Position>> parent(maze.size(), vector<Position>(maze[0].size(), Position(-1, -1)));
    
        pq.push({0,start});
        distance[start.row][start.col]=0;

        while (!pq.empty()){
            Position current=pq.top().second;
            pq.pop();
            if (current.row==end.row && current.col==end.col){
                Position backtrack=end;
                while (!(backtrack.row==start.row && backtrack.col==start.col))
                {
                    path.push_back(backtrack);
                    backtrack = parent[backtrack.row][backtrack.col];
                }
                reverse(path.begin(), path.end());
                return true;
            }
            vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

            for (const auto& dir : directions) {
                int newrow = current.row + dir.row;
                int newcol = current.col + dir.col;
                Position newPosition(newrow,newcol);   

                if (isValidPosition(newPosition) && maze[newrow][newcol] != '+' &&
                    distance[newrow][newcol] > distance[current.row][current.col] + calcularDistancia(current, newPosition)) {
                    distance[newrow][newcol] = distance[current.row][current.col] + calcularDistancia(current, newPosition);
                    pq.push({distance[newrow][newcol], newPosition});
                    parent[newrow][newcol] = current;
                } 
            }
            
        }
        return false;
    }

public:
    Dijkstra(const string& filename){
        ifstream file(filename);
        string line;
        while (getline(file,line)){
            vector<char> row;
            for(char c:line){
                row.push_back(c);
            }
            maze.push_back(row);
        }
        file.close();
    }
    void datastarend();
    void printMazeSolution(const vector<Position>& path) const;
    vector<Position> solutionDijkstra()const{
        vector<Position> pathDijkstra;
        if (caminodijkstra(start,end,pathDijkstra))
        {
            return pathDijkstra;
        }else{
            return {};
        }
        
    }
    
};

void Dijkstra::datastarend(){
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'e') {
                start = Position(i, j);
            } else if (maze[i][j] == 's') {
                end = Position(i, j);
            }
        }
    }
}

void Dijkstra::printMazeSolution(const vector<Position>& path)const{
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (i == start.row && j == start.col && maze[i][j] == 'e') {
                cout << ANSI_COLOR_YELLOW << 'e' << ANSI_COLOR_RESET << ' ';
            }else if (i == end.row && j == end.col && maze[i][j] == 's') {
                cout << ANSI_COLOR_RED << 's' << ANSI_COLOR_RESET << ' ';
            }else if (maze[i][j]=='+')
            {
                cout<<ANSI_COLOR_CELESTE<<'+'<<ANSI_COLOR_RESET<<' ';
            }else{
                bool isPath = false;
                for (const auto& pos : path) {
                    if (i == pos.row && j == pos.col) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << ANSI_COLOR_GREEN << '*' << ANSI_COLOR_RESET << ' ';
                } else if (maze[i][j] == '*') {
                    cout << ANSI_COLOR_ORANGE << '*' << ANSI_COLOR_RESET << ' ';
                } else {
                    cout << maze[i][j] << ' ';
                }
            }
        }
        cout << endl;
    }
}


int main(){
    // DFS mazesolver("maze.txt");
    
    // mazesolver.datastartend();
    // if (mazesolver.solucionDFS())
    // {
    //     cout<<"Camino encontrado con algoritmo DFS: "<<endl;
    //     mazesolver.printMazeSolution();
    //     cout<<endl<<endl;
    // } else {
    //     cout << "No se encontró un camino desde 'e' hasta 's'." << endl;
    // }
    
    // BFS mazesolver2("maze.txt");

    // mazesolver2.datastarend();
    // vector<Position> pathBFS=mazesolver2.solucionBFS();

    // if (!pathBFS.empty())
    // {
    //     cout<<"Camino encontrado con algoritmo BFS: "<<endl;
    //     mazesolver2.printMazeSolution(pathBFS);
    //     cout<<endl<<endl;
    // }else{
    //     cout << "No se encontró un camino desde 'e' hasta 's'." << endl;
    // }
    
    Dijkstra mazesolver3("maze.txt");

    mazesolver3.datastarend();

    vector<Position> pathdijkstra=mazesolver3.solutionDijkstra();

    if (!pathdijkstra.empty()) {
        cout << "Camino encontrado con Dijkstra:" << endl;
        mazesolver3.printMazeSolution(pathdijkstra);
    } else {
        cout << "No se encontró un camino desde 'e' hasta 's'." << endl;
    }
}
