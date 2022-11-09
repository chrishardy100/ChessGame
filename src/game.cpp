
/* 
* CHESS!
* A chess game played through the command prompt.
* 
* 
* @author Christopher Hardy
*/
#include <iostream>
#include <stdlib.h>
#define SIZE 8
using namespace std;

char output[8][8]={{'r','p','0','0','0','0','P','R'},
                  {'n','p','0','0','0','0','P','N'},
                  {'b','p','0','0','0','0','P','B'},
                  {'k','p','0','0','0','0','P','K'},
                  {'q','p','0','0','0','0','P','Q'},
                  {'b','p','0','0','0','0','P','B'},
                  {'n','p','0','0','0','0','P','N'},
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
    symbol = ' ';
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
  bool checkMate, turn = 0;  // Player1 turn = 0, Player2 turn = 1
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
        else board[x][y].piece.team = 2;
      }
    }
  }
  Piece getPieceAt(int x, int y){
    return board[x][y].piece;
  }
  void toString(){
    for (int i = SIZE - 1; i >= 0; i--){
      cout << "\n\t" << i + 1 << ' ' << char(250) << ' ';
      for (int j = 0; j < SIZE; j++){
        cout << getPieceAt(j, i).symbol << " ";
      }
    }
    cout << "\n\t  " << char(250) << " " << char(250) << " " << char(250) << " " << char(250) << " " << char(250) << " " << char(250) << " " << char(250) << " " << char(250) << " " << char(250);
    cout << "\n \t    1 2 3 4 5 6 7 8" << endl;
  }
  void move(int sx, int sy, int dx, int dy){
    Piece temp = board[dx][dy].piece;
    board[dx][dy].piece = board[sx][sy].piece;
    board[sx][sy].piece = Piece('0', 0, 3);
    if(board[dx][dy].piece.pieceid > 0){
        //TODO: ATTACK
      }
    
  }
  bool checkVertical(int sx, int sy, int dx, int dy){
    bool allowed = false;
    int verty;
    if (sy < dy) verty = 1;
    else if (sy > dy) verty = -1;

    for (int i = sy + verty; i != dy; i+=verty){
      if (getPieceAt(dx, i).pieceid > 0){
        cout << "*INVALID MOVE: " << board[sx][i].piece.symbol << " AT x=" << sx+1 << ", y=" << i+1 << endl;
        return false;
      }
    }
    return true;
  }
  bool checkHorizontal(int sx, int sy, int dx, int dy){
    int horzx;
    if (sx < dx) horzx = 1;
    else if (sx > dx) horzx = -1;
      for (int i = sx + horzx; i != dx; i+=horzx){
        if (getPieceAt(i, sy).pieceid > 0){
          cout << "*INVALID MOVE: " << getPieceAt(i, sy).symbol << " AT x=" << i+1 << ", y=" << sy+1 << endl;
          return 0;
        }
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
  bool checkMove(int sx, int sy, int dx, int dy){
    bool allowed = false;
    int vertical, horizontal; // for pawns

    // CHECK TURN
    if(getPieceAt(sx, sy).team != turn){
      cout << " * NOT YOUR TURN *" << endl;
      return 0;
    }
    // CHECK BOARDERS
    if(dx >= 8 || dy >= 8 || dx < 0 || dy < 0){
      cout << "*INVALID MOVE: STAY ON THE BOARD" << endl;
      return false;
    }
    // CHECK SELF ATTACK
    if(getPieceAt(sx, sy).team == getPieceAt(dx, dy).team){
      cout << "*INVALID MOVE: CANT ATTATCK YOURSELF" << endl;
      return false;
    }
    // MOVE SETS
    switch(getPieceAt(sx,sy).pieceid){
      case 1:                                                // ROOK
        if(sx == dx){
          allowed = checkVertical(sx,sy,dx,dy);
        }else if(sy == dy){
          allowed = checkHorizontal(sx, sy, dx, dy);
        }
        else{
          cout << "* INVALID MOVE: ROOK *" << endl;
          return false;
        } 
        if(allowed == true) turn = !turn;
        return allowed;
        break;
      case 2:                                               // KNIGHT
        if(sy - dy == 2 || dy - sy == 2){         //   *    *     * *  * *
          if(sx - dx == 1 || dx - sx == 1){       //   *    *       *  *
            allowed = true;                           
          }else{
            allowed = false;
          }
        }else if(sx - dx == 2 || dx - sx == 2){  //  * * *  * * *      *  *    
          if(sy - dy == 1 || dy - sy == 1){      //      *  *      * * *  * * *
            allowed = true;                  
          }else{
            allowed = false;
          }
        }else{
          allowed = false;
        }
        if(allowed == false) 
          cout << "*INVALID MOVE: KNIGHT" << endl;
        if(allowed == true) turn = !turn;
        return allowed;
        break;
      case 3:                                                   // BISHOP
        if(sx + sy == dx + dy || sx - sy == dx - dy)
          allowed = checkDiagnol(sx,sy,dx,dy);
        else{
          cout << "*INVALID MOVE: BISHOP" << endl;
          allowed = false;
        }
        if(allowed == true) turn = !turn;
        return allowed;
        break;
      case 4:                                                     // KING
        if(dx - sx == 1 || dx - sx == -1 || dx - sx == 0){
          allowed = true;
        }else{
          cout << "*INVALID MOVE: KING" << endl;
          allowed = false;
        }
        if(allowed == true) turn = !turn;
        return allowed;
        // return checkMate(sx, sy, dx, dy);
        break;
      case 5:                                                 // QUEEN
        if(sx == dx) return checkVertical(sx,sy,dx,dy);
        else if(sy == dy) return checkHorizontal(sx,sy,dx,dy);
        else if(sx + sy == dx + dy || sx - sy == dx - dy) return checkDiagnol(sx,sy,dx,dy);
        else{
          cout << "*INVALID MOVE: QUEEN" << endl;
          allowed = false;
        }

        break;
      case 6:                                                 // PAWN DOUBLE PUSH
        // check if moving up or down
        if(getPieceAt(sx,sy).team == 0)
          vertical = 1;
        else if(getPieceAt(sx,sy).team == 1)  
          vertical = -1;
        // check if attacking
        horizontal = dx - sx;
        if((horizontal == 1 || horizontal == -1)){
          if(getPieceAt(dx, dy).pieceid == 0){
            cout << "*INVALID MOVE: PAWN ATTACK" << endl;
            allowed = false;
          }else
            allowed = true;
        } else if((horizontal == 0) && (getPieceAt(dx,dy).pieceid != 0)){
          cout << "*INVALID MOVE: PAWNS MUST ATTACK DIAGONALY" << endl;
          allowed = false;
        } else if(dy == sy + vertical && horizontal == 0 && getPieceAt(sx, sy + vertical).pieceid == 0){
          allowed = true;
        // DOUBLE PUSH
        }else if(dy == sy + vertical + vertical && sx == dx && getPieceAt(sx, sy + vertical).pieceid == 0){
          allowed = true;
        }
        else{
          cout << "*INVALID MOVE: PAWN" << endl;
          allowed = false;
        }
        board[sx][sy].piece.pieceid = 7;
        if(allowed == true) turn = !turn;
        return allowed;
        break;
      case 7:
        // check if moving up or down
        if(getPieceAt(sx,sy).team == 0)
          vertical = 1;
        else if(getPieceAt(sx,sy).team == 1)  
          vertical = -1;
        // check if attacking
        horizontal = dx - sx;
        if((horizontal == 1 || horizontal == -1)){
          if(getPieceAt(dx, dy).pieceid == 0){
            cout << "*INVALID MOVE: PAWN ATTACK" << endl;
            allowed = false;
          }else
            allowed = true;
        } else if((horizontal == 0) && (getPieceAt(dx,dy).pieceid != 0)){
          cout << "*INVALID MOVE: PAWNS MUST ATTACK DIAGONALY" << endl;
          allowed = false;
        } else if(dy == sy + vertical && horizontal == 0 && getPieceAt(sx, sy + vertical).pieceid == 0){
          allowed = true;
        }else{
          cout << "*INVALID MOVE: PAWN" << endl;
          allowed = false;
        }
        board[sx][sy].piece.pieceid = 7;
        if(allowed == true) turn = !turn;
        return allowed;
        break;
    }
    // if(allowed == true) turn = !turn;
    return allowed;
  }
};
class Player{
public:
  int taken, team;
  Board* reference;
  Piece pieces[16];

  Player(){
    team = 3;
    taken = 0;
  }
  Player(Board* bd, int tm){
    reference = bd;
    team = tm;
    for(int i = 0; i < 20; i++)
      pieces[i].symbol = ' ';
    taken = 0;
  }
  bool advance(int sx, int sy, int dx, int dy){
    if((*reference).getPieceAt(dx,dy).pieceid != 0)
      attack(sx,sy,dx,dy);
    // OR JUST MOVE
    else
      (*reference).move(sx,sy,dx,dy);
    return true;
  }
  void attack(int sx, int sy, int dx, int dy){
    this->pieces[taken++] = (*reference).getPieceAt(dx,dy);
    if((*reference).getPieceAt(dx,dy).pieceid == 4)
      (*reference).checkMate = true;
    (*reference).move(sx,sy,dx,dy);

  }
};
class Game{
  public:
  Board board = Board(3);
  Player player0;
  Player player1;
  Game(){
    int sx, sy, dx, dy;
    player0 = Player(&board, 0);
    player1 = Player(&board, 1);
    while(!board.checkMate){
      for(int i = 0; i < 16; i++)           //PIECES TAKEN BY PLAYER 1
        cout << player1.pieces[i].symbol << " ";
      board.toString();                     // PRINT BOARD
      for(int i = 0; i < 16; i++)           //PIECES TAKEN BY PLAYER 0
        cout << player0.pieces[i].symbol << " ";
      cout << endl << "ENTER MOVE" << endl;
      cin >> sx >> sy >> dx >> dy;
      sx -= 1; sy -=1; dx -= 1; dy -= 1;    // MOVES -= 1
      system("CLS");
      if(board.checkMove(sx,sy,dx,dy)){
        if(board.getPieceAt(sx,sy).team == 0)
          player0.advance(sx,sy, dx,dy);
        else if(board.getPieceAt(sx,sy).team == 1)
          player1.advance(sx,sy, dx ,dy );
      }

    }
    cout << "PLAYER " << (int)(board.turn) << "WINS" << endl;
  }
};
int main(){
  // Board board = Board(3);
  // Player player1 = Player("CHRIS",board, 0);
  // Player player2 = Player("JOHN",board, 1);
  system("CLS");

  new Game();
  return 0;
}

