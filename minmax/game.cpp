#include "game.h"

class Move{
    public:
    char movecolour;
    pair<int,int> init;
    pair<int,int> finl;
    pair<int,int> remr;
    pair<int,int> reml_first;
    pair<int,int> reml_last;
    Move(char mv,pair<int,int> init_in,pair<int,int> finl_in)
    {
        movecolour = mv;
        init = make_pair(init_in.first,init_in.second);
        finl = make_pair(finl_in.first,finl_in.second);
        remr = make_pair(-1,-1);
        reml_first = make_pair(-1,-1);
        reml_last = make_pair(-1,-1);
    }
};

class GameState {
    private:


    public:
        vector<vector<char> > board; // blue ring is b orange ring is o 
                                    // blue peg is g  orange peg is p
                                    // empty is e 
        char turn; // 'b' and  'o'
        vector<int> RingsRemoved; // rings by blue is zeroth element and rings by orange is first
        Move*  LastMove;//move which led to this state;
        int boardSize;
        GameState(){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            boardSize = 5; // num hexagons
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

        GameState(GameState* oth){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            boardSize = oth->boardSize; // num hexagons
            board.push_back(vector<char>(1,oth->board[0][0]));
            for(i=1;i<=boardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back(oth->board[i][j]);
                }
                board.push_back(temp);
            }
            // deal with the six banned squares here?
            
            turn = oth->turn;
            rings = vector<int>(2,0);
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

        vector<pair<int,int> > vertical_up(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > vertical_down(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_right_up(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_right_down(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_left_up(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_left_down(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > vertical(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_right(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }

        vector<pair<int,int> > diag_left(int x,int y)
        {
            vector<pair<int,int> > res;
            return res;
        }
        


        vector<GameState> GetValidMoves(){
            vector<GameState> res;
            int i,j,k;
            char opp;
            char mytok,opptok;
            if(turn=='b')
            {
                opp='o';
                mytok='g';
                opptok='p';
            }
            else
            {
                opp='b';
                mytok='p';
                opptok='g';
            }
            vector<pair<int,int> > ringpos;
            if(board[0][0]==turn)
                ringpos.push_back(make_pair(0,0));
            for(i=0;i<boardSize;i++)
            {
                for(j=0;j<6*i;j++)
                {
                    if(board[i][j]==turn)
                    {
                        ringpos.push_back(make_pair(i,j));
                    }
                }
            }
            for(i=0;i<ringpos.size();i++)
            {
                int x,y;
                x = ringpos[i].first;
                y = ringpos[i].second;

                vector<vector<pair<int,int> > >pos;
                pos.push_back(vertical_up(x,y));
                pos.push_back(vertical_down(x,y));
                pos.push_back(diag_left_down(x,y));
                pos.push_back(diag_right_up(x,y));
                pos.push_back(diag_left_up(x,y));
                pos.push_back(diag_right_down(x,y));

                for(j=0;j<6;j++)
                {
                    bool vismark=false;
                    for(k=0;k<pos[i].size();k++)
                    {
                        int xi,yi;
                        xi=pos[i][k].first;
                        yi=pos[i][k].second;
                        if(board[xi][yi]==opp || board[xi][yi]==turn)
                            break;
                        if(board[xi][yi]==mytok || board[xi][yi]==opptok )
                        {
                            vismark = true;
                        }
                        else
                        {
                            GameState temp = new GameState(this);     
                            if(turn=='b')
                                temp.turn ='o';
                            else
                                temp.turn ='b';
                            temp.board[xi][yi] = turn;
                            temp.board[x][y] = mytok;
                            temp.LastMove = new Move(turn,make_pair(x,y),make_pair(xi,yi));
                            int kp;
                            for(kp=0;kp<k;kp++)
                            {
                                int xk,yk;
                                xk=pos[i][kp].first;
                                yk=pos[i][kp].second;
                                if(temp.board[xk][yk]==mytok)
                                    temp.board[xk][yk]=opptok;
                                else if(temp.board[xk][yk]==opptok)
                                    temp.board[xk][yk]=mytok;
                            }
                            bool ring_rem=false;

                            for(kp=0;kp<k;kp++)
                            {
                                int xk,yk;
                                xk=pos[i][kp].first;
                                yk=pos[i][kp].second;

                                vector<vector<pair<int,int> > >alllines;
                                if(j==0 || j==1)
                                {
                                    alllines.push_back(diag_right(xk,yk));
                                    alllines.push_back(diag_left(xk,yk));
                                }
                                else if(j==2 || j==3)
                                {
                                    alllines.push_back(vertical(xk,yk));
                                    alllines.push_back(diag_left(xk,yk));
                                }
                                else if(j==0 || j==1)
                                {
                                    alllines.push_back(diag_right(xk,yk));
                                    alllines.push_back(vertical(xk,yk));
                                }

                                for (int jp=0;jp<2;jp++)
                                {
                                    for(int ii=0;ii<alllines[jp].size();ii++)
                                    {
                                        if(ii>(alllines[jp].size()-5))
                                            break;
                                        bool linep = true;
                                        for(int jj=ii;jj<(ii+5);jj++)
                                        {
                                            int xx,yy;
                                            xx = alllines[jp][jj].first;
                                            yy = alllines[jp][jj].second;
                                            if(temp.board[xx][yy]!=mytok)
                                                {
                                                    linep = false;
                                                    break;
                                                }
                                        }
                                        if(linep)
                                            {
                                                ring_rem = true;
                                                for(int iii=0;iii<ringpos.size();iii++)
                                                {
                                                    int rx,ry;
                                                    if(iii==i)
                                                        {
                                                            rx = xi;
                                                            ry = yi;
                                                        }
                                                    else
                                                    {
                                                        rx = ringpos[iii].first;
                                                        ry = ringpos[iii].second;
                                                    }

                                                    GameState to_push = new GameState(temp);
                                                    for(int jj=ii;jj<(ii+5);jj++)
                                                    {
                                                        int xxx = alllines[jp][jj].first;
                                                        int yyy = alllines[jp][jj].second;
                                                        to_push.board[xxx][yyy]='e';
                                                    }
                                                    to_push.board[rx][ry]='e';

                                                    to_push.LastMove->remr.first = rx;
                                                    to_push.LastMove->remr.second = ry;

                                                    to_push.LastMove->reml_first.first = alllines[jp][ii].first;
                                                    to_push.LastMove->reml_first.second = alllines[jp][ii].second;

                                                    to_push.LastMove->reml_last.first = alllines[jp][ii+4].first;
                                                    to_push.LastMove->reml_last.second = alllines[jp][ii+4].second;

                                                    res.push_back(to_push);
                                                }
                                            }
                                    }
                                }

                            }

                            vector<vector<pair<int,int> > >alllines;
                            if(j==0 || j==1)
                            {
                                alllines.push_back(vertical(xi,yi));
                            }
                            else if(j==2 || j==3)
                            {
                                alllines.push_back(diag_right(xi,yi));
                                
                            }
                            else if(j==0 || j==1)
                            {
                                alllines.push_back(diag_left(xi,yi));
                            }

                            for (int jp=0;jp<1;jp++)
                                {
                                    for(int ii=0;ii<alllines[jp].size();ii++)
                                    {
                                        if(ii>(alllines[jp].size()-5))
                                            break;
                                        bool linep = true;
                                        for(int jj=ii;jj<(ii+5);jj++)
                                        {
                                            int xx,yy;
                                            xx = alllines[jp][jj].first;
                                            yy = alllines[jp][jj].second;
                                            if(temp.board[xx][yy]!=mytok)
                                                {
                                                    linep = false;
                                                    break;
                                                }
                                        }
                                        if(linep)
                                            {
                                                ring_rem = true;
                                                for(int iii=0;iii<ringpos.size();iii++)
                                                {
                                                    int rx,ry;
                                                    if(iii==i)
                                                        {
                                                            rx = xi;
                                                            ry = yi;
                                                        }
                                                    else
                                                    {
                                                        rx = ringpos[iii].first;
                                                        ry = ringpos[iii].second;
                                                    }

                                                    GameState to_push = new GameState(temp);
                                                    for(int jj=ii;jj<(ii+5);jj++)
                                                    {
                                                        int xxx = alllines[jp][jj].first;
                                                        int yyy = alllines[jp][jj].second;
                                                        to_push.board[xxx][yyy]='e';
                                                    }
                                                    to_push.board[rx][ry]='e';

                                                    to_push.LastMove->remr.first = rx;
                                                    to_push.LastMove->remr.second = ry;

                                                    to_push.LastMove->reml_first.first = alllines[jp][ii].first;
                                                    to_push.LastMove->reml_first.second = alllines[jp][ii].second;

                                                    to_push.LastMove->reml_last.first = alllines[jp][ii+4].first;
                                                    to_push.LastMove->reml_last.second = alllines[jp][ii+4].second;

                                                    res.push_back(to_push);
                                                }
                                            }
                                    }
                                }

                            if(!ring_rem)
                                res.push_back(temp);
                            if(vismark)
                                break;
                        }
                        
                        
                    }
                }
            }
            return res;
        }
};


