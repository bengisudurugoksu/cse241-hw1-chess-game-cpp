#include "chess.h"

// Check if the current player's king is in check
bool ChessBoard::Check(int turn){
int krow=0, kcol=0;
if(turn==0){
for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
        if(board[row][col].type==Pieces::Type::King && board[row][col].color==Pieces::Color::Black){
            krow=row;
            kcol=col;
        }
    }
}
board[krow][kcol].type=Pieces::Type::Pawn;
board[krow][kcol].color=Pieces::Color::Black;
bool value=UnderAttack(krow,kcol);

board[krow][kcol].type=Pieces::Type::King;
board[krow][kcol].color=Pieces::Color::Black;
return value;
}


if(turn==1){
for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
        if(board[row][col].type==Pieces::Type::King && board[row][col].color==Pieces::Color::White){
            krow=row;
            kcol=col;
        }
    }
}
board[krow][kcol].type=Pieces::Type::Pawn;
board[krow][kcol].color=Pieces::Color::White;
bool value=UnderAttack(krow,kcol);
board[krow][kcol].type=Pieces::Type::King;
board[krow][kcol].color=Pieces::Color::White;
return value;
}
return true;
}

// Check if the current player is in checkmate
bool ChessBoard::Checkmate(int turn) {
    // Check if the current player's king is in check
    bool inCheck = Check(turn);

    if (!inCheck) {
        // The player is not in check, so it's not a checkmate
        return false;
    }

    // Iterate through all pieces on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].color == static_cast<Pieces::Color>(turn)) {
                // Check legal moves for the current piece
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (LegalMove(col, 8 - row, destCol, 8 - destRow, turn)) {
                            // Simulate the move temporarily
                            Pieces temp = board[destRow][destCol];
                            board[destRow][destCol] = board[row][col];
                            board[row][col] = Pieces();

                            // Check if the king is still in check after the move
                            if (!Check(turn)) {
                                // The player has at least one legal move to get out of check
                                // Undo the temporary move
                                board[row][col] = board[destRow][destCol];
                                board[destRow][destCol] = temp;
                                return false;
                            }

                            // Undo the temporary move
                            board[row][col] = board[destRow][destCol];
                            board[destRow][destCol] = temp;
                        }
                    }
                }
            }
        }
    }

    // If no legal moves found, it's a checkmate
    cout<<"Checkmate";
    return true;
}
// Function to warn the player if their king is under attack
void ChessBoard::CheckWarning(bool value, int turn) {
    if (value) {
        cout << "Your king is under attack! You should play accordingly." << endl;

        // Allow the player to make a move
        if (turn == 1) {
            do {
                (*this).WhitePlays();
                value = (*this).Check(1);
            } while (value);
        } else {
            do {
                (*this).BlackPlays();
                value = (*this).Check(0);
            } while (value);
        }
    }
}

// Function for white player's turn
void ChessBoard::WhitePlays(){
    string move;
    turn=0;
    cout<<"\n";
    cout<<"[White's Turn]"<<endl;
    cout<<"Enter your move(e2e4 e.g.): ";
    cin >> move;
    separateInput(move);
}
// Function for black player's turn
void ChessBoard::BlackPlays(){    
    string move;
    turn=1;
    cout<<"\n";
    cout<<"[Black's Turn]"<<endl;
    cout<<"Enter your move(e2e4 e.g.): ";
    cin >> move;
    separateInput(move);
}
// Check if the current player is in checkmate
double ChessBoard::score(int turn){
double OverallGoodnessScoreBlack=0;
double OverallGoodnessScoreWhite=0;

for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
        switch(board[row][col].color){
            case Pieces::Color::Black:
            switch(board[row][col].type){
                case Pieces::Type::Pawn:
                    OverallGoodnessScoreBlack++;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreBlack=OverallGoodnessScoreBlack-0.5;
                    }
                    break;
                case Pieces::Type::Knight:
                    OverallGoodnessScoreBlack=OverallGoodnessScoreBlack+3;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreBlack=OverallGoodnessScoreBlack-1.5;
                    }
                    break;
                case Pieces::Type::Bishop:
                    OverallGoodnessScoreBlack=OverallGoodnessScoreBlack+3;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreBlack=OverallGoodnessScoreBlack-1.5;
                    }
                    break;
                case Pieces::Type::Rook:
                    OverallGoodnessScoreBlack=OverallGoodnessScoreBlack+5;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreBlack=OverallGoodnessScoreBlack-2.5;
                    }
                    break;
                case Pieces::Type::Queen:
                    OverallGoodnessScoreBlack=OverallGoodnessScoreBlack+9;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreBlack=OverallGoodnessScoreBlack-4.5;
                    }
                    break;
            }
            break;
    case Pieces::Color::White:
            switch(board[row][col].type){
                case Pieces::Type::Pawn:
                    OverallGoodnessScoreWhite++;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreWhite=OverallGoodnessScoreWhite-0.5;
                    }
                    break;
                case Pieces::Type::Knight:
                    OverallGoodnessScoreWhite=OverallGoodnessScoreWhite+3;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreWhite=OverallGoodnessScoreWhite-1.5;
                    }
                    break;
                case Pieces::Type::Bishop:
                    OverallGoodnessScoreWhite=OverallGoodnessScoreWhite+3;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreWhite=OverallGoodnessScoreWhite-1.5;
                    }
                    break;
                case Pieces::Type::Rook:
                    OverallGoodnessScoreWhite=OverallGoodnessScoreWhite+5;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreWhite=OverallGoodnessScoreWhite-2.5;
                    }
                    break;
                case Pieces::Type::Queen:
                    OverallGoodnessScoreWhite=OverallGoodnessScoreWhite+9;
                    if(UnderAttack(row,col)==true){
                        OverallGoodnessScoreWhite=OverallGoodnessScoreWhite-4.5;
                    }
                    break;
            }   
    break;   
}
}
}

if(turn==0){
    return OverallGoodnessScoreWhite;
}
else{
    return OverallGoodnessScoreBlack;
}

}
// Check if a square is under attack by any opponent piece
bool ChessBoard::UnderAttack(int arow, int acol) {
    // Iterate through all pieces on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Skip empty squares and squares with pieces of the same color
            if (board[row][col].type == Pieces::Type::Empty || board[row][col].color == board[arow][acol].color) {
                continue;
            }

            // Check if the current piece can legally move to the target square
            if (LegalMove(col, row+1, acol, arow+1, (board[row][col].color == Pieces::Color::Black) ? 0 : 1)) {
                return true;
            }
        }
    }

    return false;
}

// Function to perform a legal move based on piece type
bool ChessBoard::LegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum, int turn){
    bool value=false;
    switch(board[8-secondnum][firstnum].type){
        case Pieces::Type::Pawn:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            }
            return PawnLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        case Pieces::Type::Bishop:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            } 
            return BishopLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        case Pieces::Type::Knight:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            }
            return KnightLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        case Pieces::Type::King:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            }
            return KingLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        case Pieces::Type::Queen:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            }
            return QueenLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        case Pieces::Type::Rook:
            if((turn==0 && board[8-secondnum][firstnum].color==Pieces::Color::Black) || (turn==1 && board[8-secondnum][firstnum].color==Pieces::Color::White)){
                return false;
            }
            return RookLegalMove(firstnum, secondnum, thirdnum, fourthnum);
        default:
            return false;

    }
}
// Function to check if a legal pawn move
bool ChessBoard::PawnLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum) {
    if ((board[8 - fourthnum][thirdnum].type != Pieces::Type::King) &&
        (board[8 - fourthnum][thirdnum].color != board[8 - secondnum][firstnum].color) &&
        (board[8 - secondnum][firstnum].color == Pieces::Color::White)) {
        if (board[8 - fourthnum][thirdnum].type != Pieces::Type::Empty) {
            if (((8 - secondnum - 1 == 8 - fourthnum) && ((firstnum + 1 == thirdnum) || (firstnum - 1 == thirdnum)))) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if ((8 - secondnum == 6) &&
                (((8 - secondnum - 1) == (8 - fourthnum)) && ((firstnum == thirdnum)) || ((8 - secondnum - 2) == (8 - fourthnum)) && (firstnum == thirdnum))) {
                return 1;
            } else if ((8 - secondnum - 1 == 8 - fourthnum) && (firstnum == thirdnum)) {
                return 1;
            } else {
                return 0;
            }
        }
    } else if ((board[8 - fourthnum][thirdnum].type != Pieces::Type::King) &&
               (board[8 - fourthnum][thirdnum].color != board[8 - secondnum][firstnum].color) &&
               (board[8 - secondnum][firstnum].color == Pieces::Color::Black)) {
        if (board[8 - fourthnum][thirdnum].type != Pieces::Type::Empty) {
            if (((8 - secondnum + 1 == 8 - fourthnum) && ((firstnum + 1 == thirdnum) || (firstnum - 1 == thirdnum)))) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if ((8 - secondnum == 1) &&
                (((8 - secondnum + 1) == (8 - fourthnum)) && (firstnum == thirdnum)) || (((8 - secondnum + 2) == (8 - fourthnum)) && (firstnum == thirdnum))) {
                return 1;
            } else if ((8 - secondnum + 1 == 8 - fourthnum) && (firstnum == thirdnum)) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}

// Function to check if a legal knight move
bool ChessBoard::KnightLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum){
if(board[8-fourthnum][thirdnum].type!=Pieces::Type::King && (board[8-fourthnum][thirdnum].color!=board[8-secondnum][firstnum].color) && (((firstnum+1)==thirdnum && (8-secondnum+2)==(8-fourthnum)) || ((firstnum-1)==thirdnum && (8-secondnum-2)==(8-fourthnum)) || ((firstnum-1)==thirdnum && (8-secondnum+2)==(8-fourthnum)) || ((firstnum+1)==thirdnum && (8-secondnum-2)==(8-fourthnum)) || ((firstnum+2)==thirdnum && (8-secondnum+1)==(8-fourthnum)) || ((firstnum-2)==thirdnum && (8-secondnum+1)==(8-fourthnum)) || ((firstnum+2)==thirdnum && (8-secondnum-1)==(8-fourthnum))|| ((firstnum-2)==thirdnum && (8-secondnum-1)==(8-fourthnum))))
return 1;
else return 0;
    
}
// Function to check if a legal bishop move
bool ChessBoard::BishopLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum){
    if (board[8 - fourthnum][thirdnum].type != Pieces::Type::King &&
        (board[8 - fourthnum][thirdnum].color != board[8 - secondnum][firstnum].color)){
        int i = abs(firstnum - thirdnum);

                if ((((8 - secondnum + i) == (8 - fourthnum)) && ((firstnum + i) == thirdnum)) ||
                    (((8 - secondnum - i) == (8 - fourthnum)) && ((firstnum - i) == thirdnum)) ||
                    (((8 - secondnum + i) == (8 - fourthnum)) && ((firstnum - i) == thirdnum)) ||
                    (((8 - secondnum - i) == (8 - fourthnum)) && ((firstnum + i) == thirdnum))) {
                    int step1 = (thirdnum > firstnum) ? 1 : -1;
                    int step2 = ((8 - fourthnum) > (8 - secondnum)) ? 1 : -1;
                    int k = 1;
                    for (int j = firstnum + step1; j != thirdnum; j += step1) {
                        if (board[8 - secondnum + k * step2][j].type != Pieces::Type::Empty) {
                            return true;
                        }
                        k++;
                    }
                }

                else if(((8-secondnum)>(8-fourthnum)) && (firstnum>thirdnum)){
                    int k=1;
                    for(int j = (8-fourthnum); j<(8-secondnum);j++){
                        if(board[8-secondnum-k][firstnum-k].type==Pieces::Type::Empty){
                            return true;
                        }
                        k++;
                    }
                }
                else if(((8-secondnum)>(8-fourthnum)) && (firstnum<thirdnum)){
                    int k=1;
                    for(int j = (8-fourthnum); j<(8-secondnum);j++){
                        if(board[8-secondnum-k][firstnum+k].type==Pieces::Type::Empty){
                            return true;
                        }
                        k++;
                    }
                }
                else if(((8-secondnum)<(8-fourthnum)) && (firstnum>thirdnum)){
                    int k=1;
                    for(int j = (8-secondnum); j<(8-fourthnum);j++){
                        if(board[8-secondnum+k][firstnum-k].type==Pieces::Type::Empty){
                            return true;
                        }
                        k++;
                    } 
                }                            
            }
        return false;
        }
// Function to check if a legal rook move
bool ChessBoard::RookLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum) {
    if (board[8 - fourthnum][thirdnum].type != Pieces::Type::King &&
        (board[8 - fourthnum][thirdnum].color != board[8 - secondnum][firstnum].color)) {
        if ((8 - fourthnum) == (8 - secondnum) && thirdnum != firstnum) {
            int step = (thirdnum > firstnum) ? 1 : -1;
            for (int i = firstnum + step; i != thirdnum; i += step) {
                if (board[8 - secondnum][i].type != Pieces::Type::Empty) {
                    return 0;  
                }
            }
            return 1; 
        }
        if (thirdnum == firstnum && (8 - fourthnum) != (8 - secondnum)) {
            int step = ((8 - fourthnum) > (8 - secondnum)) ? 1 : -1;
            for (int i = 8 - secondnum + step; i != 8 - fourthnum; i += step) {
                if (board[i][firstnum].type != Pieces::Type::Empty) {
                    return 0;  
                }
            }
            return 1; 
        }
    }
    return 0;
}

// Function to check if a legal queen move
bool ChessBoard::QueenLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum){

return(BishopLegalMove(firstnum, secondnum, thirdnum, fourthnum) || RookLegalMove(firstnum, secondnum, thirdnum, fourthnum));    
}
// Function to check if a legal king move
bool ChessBoard::KingLegalMove(int firstnum, int secondnum, int thirdnum, int fourthnum){
    if (board[8 - fourthnum][thirdnum].type != Pieces::Type::King &&
        (board[8 - fourthnum][thirdnum].color != board[8 - secondnum][firstnum].color)){
            if((((8-secondnum+1)==(8-fourthnum)) && (firstnum==thirdnum)) || (((8-secondnum-1)==(8-fourthnum)) && (firstnum==thirdnum)) || (((8-secondnum)==(8-fourthnum)) && ((firstnum-1)==thirdnum)) || (((8-secondnum)==(8-fourthnum)) && ((firstnum+1)==thirdnum)) || (((8-secondnum+1)==(8-fourthnum)) && ((firstnum+1)==thirdnum)) || (((8-secondnum-1)==(8-fourthnum)) && ((firstnum+1)==thirdnum)) || (((8-secondnum-1)==(8-fourthnum)) && ((firstnum-1)==thirdnum)) || (((8-secondnum+1)==(8-fourthnum)) && ((firstnum-1)==thirdnum))){
                return true;
            }
        }
    return false;
}

// Initialize the chessboard with pieces in their starting positions
void ChessBoard::initializeBoard(){
        Pieces blackPawn;
        blackPawn.type = Pieces::Type::Pawn;
        blackPawn.color = Pieces::Color::Black;
        for (int col = 0; col < 8; ++col) {
        board[1][col] = blackPawn; // Black pawns
        }
        Pieces whitePawn;
        whitePawn.type = Pieces::Type::Pawn;
        whitePawn.color = Pieces::Color::White;
        for (int col = 0; col < 8; ++col) {
        board[6][col] = whitePawn; // White pawns
        }


        board[0][0].type = Pieces::Type::Rook;
        board[0][0].color = Pieces::Color::Black;
        board[0][1].type = Pieces::Type::Knight;
        board[0][1].color = Pieces::Color::Black;
        board[0][2].type = Pieces::Type::Bishop;
        board[0][2].color = Pieces::Color::Black;
        board[0][3].type = Pieces::Type::Queen;
        board[0][3].color = Pieces::Color::Black;
        board[0][4].type = Pieces::Type::King;
        board[0][4].color = Pieces::Color::Black;
        board[0][5].type = Pieces::Type::Bishop;
        board[0][5].color = Pieces::Color::Black;
        board[0][6].type = Pieces::Type::Knight;
        board[0][6].color = Pieces::Color::Black;
        board[0][7].type = Pieces::Type::Rook;
        board[0][7].color = Pieces::Color::Black;

        board[7][0].type = Pieces::Type::Rook;
        board[7][0].color = Pieces::Color::White;
        board[7][1].type = Pieces::Type::Knight;
        board[7][1].color = Pieces::Color::White;
        board[7][2].type = Pieces::Type::Bishop;
        board[7][2].color = Pieces::Color::White;
        board[7][3].type = Pieces::Type::Queen;
        board[7][3].color = Pieces::Color::White;                
        board[7][4].type = Pieces::Type::King;
        board[7][4].color = Pieces::Color::White;
        board[7][5].type = Pieces::Type::Bishop;
        board[7][5].color = Pieces::Color::White;        
        board[7][6].type = Pieces::Type::Knight;
        board[7][6].color = Pieces::Color::White;
        board[7][7].type = Pieces::Type::Rook;
        board[7][7].color = Pieces::Color::White;
        
}
// Function to print the current state of the chessboard
void ChessBoard::printBoard() const {
    int number = 8;
        for (int row = 0; row < 8; ++row) {
            cout<<number<< " " << "|" << " ";
            for (int col = 0; col < 8; ++col) {
                switch (board[row][col].getType()) {
                    case Pieces::Type::Pawn:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "P ";
                        else
                            cout << "p ";
                        break;
                    case Pieces::Type::Knight:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "N ";
                        else
                            cout << "n ";
                        break;
                    case Pieces::Type::Bishop:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "B ";
                        else
                            cout << "b ";
                        break;                
                    case Pieces::Type::Rook:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "R ";
                        else
                            cout << "r ";
                        break;                      
                    case Pieces::Type::King:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "K ";
                        else
                            cout << "k ";
                        break;
                    case Pieces::Type::Queen:
                        if (board[row][col].color == Pieces::Color::White)
                            cout << "Q ";
                        else
                            cout << "q ";
                        break;                                              
                    case Pieces::Type::Empty:
                        if (board[row][col].color == Pieces::Color::Empty)
                            cout << ". ";
                        break;

                }
                cout << " ";
            }
            number--;
            cout << endl;
        }
        cout<<"    "<<"-----------------------"<<endl;
        cout<<"    "<<"a  b  c  d  e  f  g  h"<<endl;

}
// Function to parse and execute the user's move input
void ChessBoard::separateInput(string move){
    char firstChar = move.at(0);
    int secondChar = move.at(1) - '0';
    char thirdChar = move.at(2);
    int fourthChar= move.at(3) - '0';
    //if(secondChar<1 || secondChar>8 || fourthChar<1 || fourthChar>8){
        //if(turn==0){
            //cout<<"Invalid input. Please enter a valid input.";
            //WhitePlays();
        //}
        //else{
            //cout<<"Invalid input. Please enter a valid input.";
            //BlackPlays();
        //}
    //}
    int firstnum,secondnum;
    switch (firstChar){
        case 'a':
        firstnum = 0;
        break;
        case 'b':
        firstnum = 1;
        break;
        case 'c':
        firstnum = 2;
        break;
        case 'd':
        firstnum = 3;
        break;
        case 'e':
        firstnum = 4;
        break;
        case 'f':
        firstnum = 5;
        break;
        case 'g':
        firstnum = 6;
        break;
        case 'h':
        firstnum = 7;
        break;
    }
        //default:
        //cout<<"Invalid input. Please enter a valid input.\n";
        //if(turn==0){
            //WhitePlays();
        //}
        //else{
            //BlackPlays();
        //}
        //break;
    //}

    switch (thirdChar){
        case 'a':
        secondnum = 0;
        break;
        case 'b':
        secondnum = 1;
        break;
        case 'c':
        secondnum = 2;
        break;
        case 'd':
        secondnum = 3;
        break;
        case 'e':
        secondnum = 4;
        break;
        case 'f':
        secondnum = 5;
        break;
        case 'g':
        secondnum = 6;
        break;
        case 'h':
        secondnum = 7;
        //default:
        //cout<<"Invalid input. Please enter a valid input.";
        //if(turn==0){
            //WhitePlays();
        //}
        //else{
            //BlackPlays();
        //}
        //break;
    }  
    if(LegalMove(firstnum,move.at(1) - '0',secondnum,move.at(3) - '0', turn)==1){
    board[8 - fourthChar][secondnum].type = board[8 - secondChar][firstnum].type;
    board[8 - fourthChar][secondnum].color = board[8 - secondChar][firstnum].color;
    board[8 - secondChar][firstnum].type = Pieces::Type::Empty;
    board[8 - secondChar][firstnum].color = Pieces::Color::Empty;
    }
    else{
    cout<<"\n";
    cout<<"Illegal Move.Try Again."<<endl;
    if(turn==1){
        (*this).BlackPlays();
    }
    else{
        (*this).WhitePlays();
    }
    }  
}

