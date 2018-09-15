#include "game.h"

class Move{

};

class GameState {
    private:


    public:
        vector<vector<char> > board; // blue ring is b orange ring is o 
                                    // blue peg is g  orange peg is p
                                    // empty is e 
        char turn; // 'b' and  'o'
        vector<int> RingsRemoved; // rings by blue is zeroth element and rings by orange is first
        Move  LastMove;//move which led to this state;
        GameState(){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            int boardSize = 5; // num hexagons
            board.push_back(vector<char>(1,'e'));
            for(i=1;i<=boardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back('e');
                }
                board.push_back(temp);
            }
            // deal with the six banned squares here?
            
            turn = 'b';
            RingsRemoved = vector<int>(2,0);
        }
        bool GameEnded(){
            if((RingsRemoved[0]==3) ||  (RingsRemoved[1]==3)){
                return true;
            }
            else{
                return false;
            }
        }
        float EvaluateHeuristic(){
            float score = 0;
            int i,j;
            int bPegs=0,bRings=0,oPegs=0,oRings=0;
            for(i=0;i<board.size();i++){
                for(j=0;j<board[i].size();j++){
                    if(board[i][j]=='g'){bPegs+=1}
                    else if(board[i][j]=='p'){oPegs+=1}
                    else if(board[i][j]=='b'){bRings+=1}
                    else if(board[i][j]=='o'){oRings+=1}
                    else{}
                }
            }
            score += (bPegs - oPegs);
            score += 0.5*(bRings - oRings);
            score += 5*(RingsRemoved[0] - RingsRemoved[1]);
        }
        vector<GameState> GetValidMoves(){

        }
};
