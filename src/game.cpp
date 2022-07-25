
/* 
* CHESS!
* A chess game played through the command prompt.
* 
* 
* @author Christopher Hardy
*/

#include <iostream>
#define SIZE 8
using namespace std;

char output[8][8]={{'r','p','0','0','0','0','P','R'},
                  {'n','p','0','0','0','0','P','N'},
                  {'b','p','0','0','0','0','P','B'},
                  {'k','p','0','0','0','0','P','K'},
                  {'q','p','0','0','0','0','P','Q'},
                  {'b','p','0','0','0','0','P','N'},
                  {'n','p','0','0','0','0','P','B'},
                  {'r','p','0','0','0','0','P','R'}};
int id[8][8] = {{1, 6, 0, 0, 0, 0, 6, 1},
                {2, 6, 0, 0, 0, 0, 6, 2},
                {3, 6, 0, 0, 0, 0, 6, 3},
                {4, 6, 0, 0, 0, 0, 6, 4},
                {5, 6, 0, 0, 0, 0, 6, 5},
                {3, 6, 0, 0, 0, 0, 6, 3},
                {2, 6, 0, 0, 0, 0, 6, 2},
                {1, 6, 0, 0, 0, 0, 6, 1}};


class Piece{
public:
  char symbol;
  int pieceid;
  int team;
  Piece(){
    symbol = '0';
    pieceid = 0;
    team = 3;
  }
  Piece(char sy, int id, int tm){
    symbol = sy;
    pieceid = id;
    team = tm;
  }
};
class Space{
public:
  Piece piece;
  Space(){
    piece = Piece();
  }
};
class Board{
public:
  int gameid;
  bool turn = 0;  // Player1 turn = 0, Player2 turn = 1
  bool checkMate;
  Space board[SIZE][SIZE];
  Board(){
    gameid = 0;
  }
  Board(int gid){
    gameid = gid;
    turn = 0;  // Player1 turn = 0, Player2 turn = 1
    checkMate = false;
    for (int x = 0; x < SIZE; x++){
      for (int y = 0; y < SIZE; y++){
        board[x][y].piece.symbol = output[x][y];
        board[x][y].piece.pieceid = id[x][y];
        if( y < 2) board[x][y].piece.team = 0;
        else if( y > 5) board[x][y].piece.team = 1;
        else board[x][y].piece.team = 3;
      }
    }
  }
  Piece getPieceAt(int x, int y){
    return board[x][y].piece;
  }
  void toString(){
    for (int i = SIZE - 1; i >= 0; i--){
      cout << "\n\t" << i + 1 << " - ";
      for (int j = 0; j < SIZE; j++){
        cout << getPieceAt(j, i).symbol << " ";
        //cout << getPieceAt(j, i).team << " ";
        //cout << getPieceAt(j,i).color << " ";
        //cout << getPieceAt(j,i).pieceid << " ";
      }
    }
    cout << "\n \t    | | | | | | | |";
    cout << "\n \t    1 2 3 4 5 6 7 8";
  }
  void move(int sx, int sy, int dx, int dy){
    if(check(sx, sy, dx, dy)){   //TODO: CHECK PIECE MOVE
      Piece temp = board[dx][dy].piece;
      board[dx][dy].piece = board[sx][sy].piece;
      board[sx][sy].piece = Piece('0', 0, 3);
      if(board[dx][dy].piece.pieceid > 0){
        //TODO: ATTACK
      }
    }
  }
  bool checkVertical(int sx, int sy, int dx, int dy){
    if (sy < dy){
      for (int i = sy + 1; i < dy; i++){
        if (getPieceAt(sx, i).pieceid > 0){
          cout << "INVALID MOVE : x = " << sx << ", y = " << i;
          cout << " : " << board[sx][i].piece.symbol << endl;
          return 0;
        }
      }
      return 1;
    }
    else if (sy > dy){
      for (int i = sy - 1; i > dy; i--){
        if (getPieceAt(sx, i).pieceid > 0){
          cout << "INVALID MOVE : x = " << sx << ", y = " << i;
          cout << " : " << board[sx][i].piece.symbol << endl;
          return 0;
        }
      }
      return 1;
    }
    else{ // error catch
      return 0;
    }
    return 1;
  }
  bool checkHorizontal(int sx, int sy, int dx, int dy){
    if (sx < dx){
      for (int i = sx + 1; i < dx; i++){
        if (getPieceAt(i, sy).pieceid > 0){
          cout << "INVALID MOVE : x = " << i << ", y = " << sy;
          cout << " : " << getPieceAt(i, sy).symbol << endl;
          return 0;
        }
      }
      return 1;
    }
    else if (sx > dx){
      for (int i = sx - 1; i > dx; i--){
        if (getPieceAt(i, sy).pieceid > 0){
          cout << "INVALID MOVE : x = " << i << ", y = "<< sy;
          cout << " : " << getPieceAt(i, sy).symbol << endl;
          return 0;
        }
      }
      return 1;
    }
    else{ // error catch
      return 0;
    }
    return 1;
  }
  bool checkDiagnol(int sx, int sy, int dx, int dy){
    int diagx, diagy;
    if(sx < dx) diagx = 1;
    else if(sx > dx) diagx = -1;
    if(sy < dy) diagy = 1;
    else if(sy > dy) diagy = -1;
    for(int i = sx + diagx, j = sy + diagy; i != dx && j != dy; i, j){
      //cout << getPieceAt(i, j).symbol << " ";
      if(getPieceAt(i, j).pieceid != 0){
        cout << "INVALID MOVE : x = " << i << ", y = " << j << " : " << getPieceAt(i, j).symbol << endl;
        return 0;
      }
      i = i + diagx;
      j = j + diagy;
    }
    return 1;
  }
  bool check(int sx, int sy, int dx, int dy){
    bool allowed;
    switch(getPieceAt(sx,sy).pieceid){
      case 1:                                     // ROOK
        if(sx != dx){
          cout << "NOT VERTICAL" << endl;
          allowed = false;
        }
        else{
          allowed = checkVertical(sx,sy,dx,dy);
          if(allowed = true) turn = !turn;
        } 
        break;
      case 2:                                     // KNIGHT
        if(sy - dy == 2 || dy - sy == 2){         //   *    *     * *  * *
          if(sx - dx == 1 || dx - sx == 1){       //   *    *       *  *
            turn = !turn;                         // * *    * *     *  *       
            allowed = true;                           
          }else{
            allowed = false;
          }
        }else if(sx - dx == 2 || dx - sx == 2){  //  * * *  * * *      *  *    
          if(sy - dy == 1 || dy - sy == 1){      //      *  *      * * *  * * *
            turn = !turn;
            allowed = true;                  
          }else{
            allowed = false;
          }
        }else{
          allowed = false;
        }
        if(allowed == false) 
          cout << "INVALID: NOT A KNIGHT MOVE" << endl;
        break;
      case 3:                                   // BISHOP
        if(sx + sy == dx + dy || sx - sy == dx - dy){
          allowed = checkDiagnol(sx,sy,dx,dy);
          if(allowed == true) turn = !turn;
        }
        else{
          cout << "INVALID: NOT A BISHOP MOVE" << endl;
          allowed = false;
        }
        break;
      case 4:                                   // KING
        if(dx - sx == 1 || dx - sx == -1 || dx - sx == 0){
          turn = ! turn;
          allowed = true;
        }else{
          cout << "INVALID: NOT A KING MOVE" << endl;
          allowed = false;
        }
        // return checkMate(sx, sy, dx, dy);
        break;
      case 5:                                   // QUEEN
        if(sx == dx) allowed = checkVertical(sx,sy,dx,dy);
        else if(sy == dy) allowed = checkHorizontal(sx,sy,dx,dy);
        else if(sx + sy == dx + dy || sx - sy == dx - dy) allowed = checkDiagnol(sx,sy,dx,dy);
        else{
           cout << "INVALID: NOT A QUEEN MOVE" << endl;
           allowed = false;
        } 
        allowed = false;
        break;
      case 6:                                   // PAWN
        int vertical;
        if(getPieceAt(sx,sy).team == 0)// Team 0s pawns can only move up
          vertical = 1;
        else if(getPieceAt(sx,sy).team == 1)  // Team 1s pawns can only move down
          vertical = -1;

        if((dx == sx + 1 || dx == sx - 1) && (dy == sy + vertical)){
          if(getPieceAt(dx, dy).symbol == '0'){
            cout << "INVALID: PAWNS MUST ATTACK WHEN MOVING DIAGONALLY" << endl;
            allowed = false;
          }
          else {
            turn = !turn;
            allowed = true;
          }
        }

        else if(dy == sy + vertical && sx == dx && getPieceAt(sx, sy + vertical).pieceid == 0){
          turn = !turn;
          allowed = true;
        }else if(dy == sy + vertical + vertical && sx == dx && getPieceAt(sx, sy + vertical).pieceid == 0){
          turn = !turn;         //DOUBLE PUSH
          allowed = true;
        }
        else{
          cout << "INVALID: NOT A PAWN MOVE" << endl;
          allowed = false;
          break;
        }
    }
    // if(allowed == true) turn = !turn;
    return allowed;
  }
};
class Player{
public:
  string name;
  Board* reference;
  Board board;
  int taken;
  char pieces[20];
  int team;

  static bool turn;
  Player(){
    name = "JOHN";
    team = 0;
    taken = 0;
  }
  Player(string nm, Board* bd, int tm){
    name = nm;
    reference = bd;
    board = *reference;
    team = tm;
    for(int i = 0; i < 20; i++)
      pieces[i] = '0';
    taken = 0;
  }
  bool advance(int sx, int sy, int dx, int dy){
    if((*reference).getPieceAt(sx, sy).team == (*reference).getPieceAt(dx, dy).team){
      cout << "CANT ATTATCK YOURSELF" << endl;
      return false;
    }
    // if((*reference).getPieceAt(sx, sy).team != (*reference).turn){
    //   cout << "NOT YOUR TURN" << endl;m
    //   return 0;
    // }
    if(dx >= 8 || dy >= 8 || dx < 0 || dy < 0){
      cout << "STAY ON THE BOARD" << endl;
      return false;
    }
    // ATTACK
    if((*reference).getPieceAt(dx,dy).pieceid != 0)
      attack(sx,sy,dx,dy);
    // MOVE
    (*reference).move(sx,sy,dx,dy);
    return true;
  }
  void attack(int sx, int sy, int dx, int dy){
    if((*reference).getPieceAt(dx,dy).pieceid == 4)
      (*reference).checkMate = true;
    this->pieces[taken++] = (*reference).getPieceAt(dx,dy).symbol;

  }
  
};
class Game{
  public:
  Board board = Board(3);
  Player player1;
  Player player2;
  Game(){
    player1 = Player("CHRIS",&board, 0);
    player2 = Player("JOHN",&board, 1);
    cout << endl;
    cout << endl;
    while(!board.checkMate){
      for(int i = 0; i < 10; i++) //PIECES TAKEN BY PLAYER 2
        cout << player2.pieces[i] << ", ";
      
      board.toString();   // PRINT BOARD
      cout << endl;
      for(int i = 0; i < 10; i++) //PIECES TAKEN BY PLAYER 1
        cout << player1.pieces[i] << ", ";
      cout << endl;
      cout << endl;
      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;
      cout << endl;
      int sx, sy, dx, dy;
      cout << "ENTER MOVE" << endl;
      cin >> sx >> sy >> dx >> dy;
      if(board.turn == 0)
        player1.advance(sx - 1,sy - 1, dx - 1,dy - 1);
      else if(board.turn == 1)
        player2.advance(sx - 1,sy - 1, dx - 1,dy - 1);

    }
    cout << "PLAYER " << (int)(board.turn)+1 << "WINS" << endl;
  }
};
int main(){
  // Board board = Board(3);
  // Player player1 = Player("CHRIS",board, 0);
  // Player player2 = Player("JOHN",board, 1);
  new Game();
  return 0;
}

/*
* TODO:~SHORT-TERM~
* TODO: 
* TODO:~LONG-TERM~ 
* TODO: Castling
* TODO: King moving in to check
* TODO: Check mate
* TODO: Create a better Interface
* TODO: Undo option
* TODO: 
* TODO: 
* TODO: 
* TODO: 
* TODO: 
* 
* 
* (GO-BACK)TODO: Create an interface / Place Player::pieces[20];
* (GO-BACK)TODO: Better load pieceid systm
* (GO-BACK)TODO: Player::advance()
* (GO-BACK)TODO: checkVertical() function
* (GO-BACK)TODO: checkHorizontal() function
* (GO-BACK)TODO: checkDiagnol() function
* (GO-BACK)TODO: Track attack
* (GO-BACK)TODO: Pawns double push
* (GO-BACK)TODO: Attacking the king to win
* 
* 
* (DONE)TODO: Check move
* (DONE)TODO: Add moves for knight  
* (DONE)TODO: Add moves for queen
* (DONE)TODO: Add moves for king
* (DONE)TODO: Add moves for knight
* (DONE)TODO: Pawn diagonal attack
* (DONE)TODO: Create attack for the rest of the pieces
* (DONE)TODO: Turns
* (DONE)TODO: Boarders
* (DONE)TODO: Prevent self attatck
* 
* 
*/

