#include "game.h"


class GameState {
    private:


    public:
        vector<vector<char> > board; // blue ring is b orange ring is o 
                                    // blue peg is g  orange peg is p
                                    // empty is e 
        char turn; // 'b' and  'o'
        vector<int> rings;
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
            rings = vector<int>(2,0);
        }
        float evaluateHeuristic(){

        }
        vector<GameState> getValidMoves(){

        }
};
