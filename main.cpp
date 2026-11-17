#include "chess.h"
#include "chess.cpp"

int main(){
    string move;
    cout<<"Welcome to the Chess Game!"<<endl;
    cout<<"\n";
    ChessBoard game;
    game.printBoard();
        do{
        game.WhitePlays();
        game.printBoard();
        game.BlackPlays();
        game.printBoard();
        }while(1);
return 0;
}