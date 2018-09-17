#include "game.h"
#include <unordered_map>
#include <string>
#include <sstream>

template <>
struct std::hash<pair<int, int> > {
public:
        size_t operator()(pair<int, int> x) const throw() {
            //  size_t h = hash<int>()(x.first) ^ hash<int>()(x.second);//something with x   
            size_t h = (10+x.first)*101 + x.second;
             return h;
        }
};

class MoveTables{
    public:
    unordered_map<pair<int,int>,vector<pair<int,int> > > vertical_up_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > vertical_down_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_right_up_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_right_down_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_left_up_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_left_down_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > vertical_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_right_map;
    unordered_map<pair<int,int>,vector<pair<int,int> > > diag_left_map;
    unordered_map<pair<int,int>,pair<int,int> > ours_to_axes;
    unordered_map<pair<int,int>,pair<int,int> > axes_to_ours;

    MoveTables(int BoardSize){
        int i = 0, j = 0;
        int ax_x = 0, ax_y = 0;
        ours_to_axes.insert(make_pair(make_pair(i,j),make_pair(ax_x,ax_y)));
        axes_to_ours.insert(make_pair(make_pair(ax_x,ax_y),make_pair(i,j)));        
        int div;
        int flag;
        for(i=1;i<=BoardSize;i++){
            ax_y += 1;
            for(j=0;j<6*i;j++){
                flag = 0;
                if(ax_x==0 && (ax_y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(ax_x==0 && (ax_y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(ax_x==(-1*BoardSize) && (ax_y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(ax_x==(BoardSize) && (ax_y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(ax_x==(-1*BoardSize) && (ax_y==0) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(ax_x==(BoardSize) && (ax_y==0) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    flag = 1;
                if(!(flag==1)){
                    ours_to_axes.insert(make_pair(make_pair(i,j),make_pair(ax_x,ax_y)));
                    axes_to_ours.insert(make_pair(make_pair(ax_x,ax_y),make_pair(i,j)));        
                }
                div = j/i;
                if(div==0){
                    ax_x+=1;
                }
                else if(div==1){
                    ax_y-=1;
                }
                else if(div==2){
                    ax_x-=1;
                    ax_y-=1;
                }
                else if(div==3){
                    ax_x-=1;
                }
                else if(div==4){
                    ax_y+=1;
                }
                else if(div==5){
                    ax_x+=1;
                    ax_y+=1;;
                }
            }
        }
        for(i=0;i<=BoardSize;i++){
            if(i==0){

                continue;
            }
            for(j=0;j<6*i;j++){
                pair<int,int> in_ax = ours_to_axes[make_pair(i,j)];
                ax_x = in_ax.first;
                ax_y = in_ax.second;
                int t1,t2,t3;
                
                int x,y;
                vector<pair<int,int> > vert_up;
                vector<pair<int,int> > vert_down;
                vector<pair<int,int> > vert;
                vector<pair<int,int> > diag_right_up;
                vector<pair<int,int> > diag_right_down;
                vector<pair<int,int> > diag_right;
                vector<pair<int,int> > diag_left_up;
                vector<pair<int,int> > diag_left_down;
                vector<pair<int,int> > diag_left;
                x = ax_x;
                for(y=ax_y+1;y<=BoardSize;y++)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;       
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;  
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    vert_up.push_back(nxt_vert);
                }
                int ll=ax_y;
                for(y=ax_y-1;y>=-1*BoardSize;y--)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    ll = y;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    vert_down.push_back(nxt_vert);
                }
                for(y=ll;y<=BoardSize;y++)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    vert_up.push_back(nxt_vert);
                }
                int x_up,x_down;
                x = ax_x+1;
                y = ax_y;
                x_up = ax_x;
                x_down = ax_x;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    x_up = x;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_right_down.push_back(nxt_vert);
                    x++;
                }

                x = ax_x-1;
                y = ax_y;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    x_down = x;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_left_up.push_back(nxt_vert);
                    x--;
                }

                x = x_down;
                y = ax_y;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_left.push_back(nxt_vert);
                    x++;
                }

                int x_lim,y_lim;
                x = ax_x+1;
                y = ax_y+1;
                x_lim = ax_x;
                y_lim = ax_y;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;

                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_right_up.push_back(nxt_vert);
                    x++;
                    y++;
                }

                x = ax_x-1;
                y = ax_y-1;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    x_lim = x;y_lim = y;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_left_down.push_back(nxt_vert);
                    x--;
                    y--;
                }

                x = x_lim;
                y = y_lim;
                while(true)
                {
                    if(axes_to_ours.count(make_pair(x,y))==0)
                        break;
                    if(x==0 && (y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==0 && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(-1*BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    if(x==(BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                        continue;
                    pair<int,int> nxt_vert = axes_to_ours[make_pair(x,y)];
                    diag_right.push_back(nxt_vert);
                    x++;
                    y++;
                }

                vertical_up_map.insert(make_pair(make_pair(i,j),vert_up));
                vertical_down_map.insert(make_pair(make_pair(i,j),vert_down));
                vertical_map.insert(make_pair(make_pair(i,j),vert));

                diag_right_up_map.insert(make_pair(make_pair(i,j),diag_right_up));
                diag_right_down_map.insert(make_pair(make_pair(i,j),diag_right_down));
                diag_right_map.insert(make_pair(make_pair(i,j),diag_right));

                diag_left_up_map.insert(make_pair(make_pair(i,j),diag_left_up));
                diag_left_down_map.insert(make_pair(make_pair(i,j),diag_left_down));
                diag_left_map.insert(make_pair(make_pair(i,j),diag_left));
            }
        }



    }

};

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
        int BoardSize;
        MoveTables* table;
        GameState(){
        }
        GameState(int BoardSize, char OurTurn){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            // BoardSize = 5; // num hexagons
            board.push_back(vector<char>(1,'e'));
            for(i=1;i<=BoardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back('e');
                }
                board.push_back(temp);
            }
            // deal with the six banned squares here?
            
            table = new MoveTables(BoardSize);
            turn = OurTurn;
            RingsRemoved = vector<int>(2,0);
        }

        GameState(GameState* oth){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            BoardSize = oth->BoardSize; // num hexagons
            board.push_back(vector<char>(1,oth->board[0][0]));
            for(i=1;i<=BoardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back(oth->board[i][j]);
                }
                board.push_back(temp);
            }
            // deal with the six banned squares here?
            
            turn = oth->turn;
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
                    if(board[i][j]=='g'){
                        bPegs+=1;
                    }
                    else if(board[i][j]=='p'){
                        oPegs+=1;
                    }
                    else if(board[i][j]=='b'){
                        bRings+=1;
                    }
                    else if(board[i][j]=='o'){
                        oRings+=1;
                    }
                    else{}
                }
            }
            score += (bPegs - oPegs);
            score += 0.5*(bRings - oRings);
            score += 5*(RingsRemoved[0] - RingsRemoved[1]);
        }

        vector<pair<int,int> > vertical_up(int x,int y)
        {
            vector<pair<int,int> > res = table->vertical_up_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > vertical_down(int x,int y)
        {
            vector<pair<int,int> > res = table->vertical_down_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_right_up(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_right_up_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_right_down(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_right_down_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_left_up(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_left_up_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_left_down(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_left_down_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > vertical(int x,int y)
        {
            vector<pair<int,int> > res = table->vertical_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_right(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_right_map[make_pair(x,y)];
            return res;
        }

        vector<pair<int,int> > diag_left(int x,int y)
        {
            vector<pair<int,int> > res = table->diag_left_map[make_pair(x,y)];
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
            for(i=0;i<BoardSize;i++)
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
                                                    if(turn=='b'){
                                                        RingsRemoved[0]+=1;
                                                    }
                                                    else if(turn == 'o'){
                                                        RingsRemoved[1]+=1;
                                                    }
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
                                                    if(turn=='b'){
                                                        RingsRemoved[0]+=1;
                                                    }
                                                    else if(turn == 'o'){
                                                        RingsRemoved[1]+=1;
                                                    }
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
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

vector<pair<int,int> > getline(pair<int,int> st,pair<int,int> end,GameState* S)
{
    vector<pair<int,int> > res;
    pair<int,int> st_ax = S->table->ours_to_axes[st];
    pair<int,int> en_ax = S->table->ours_to_axes[st];
    int x1,y1,x2,y2;
    x1 = st_ax.first; y1 = st_ax.second;
    x2 = en_ax.first; y2 = en_ax.second;

    if(x1==x2&&y2==(y1+4))
    {
        int i;
        for(i=0;i<5;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1,y1+i)]);
        }
    }
    else if(x1==x2&&y2==(y1-4))
    {
        int i;
        for(i=4;i>=0;i--)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1,y2+i)]);
        }
    } 
    else if(y1==y2&&x2==(x1+4))
    {
        int i;
        for(i=0;i<5;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1+i,y2)]);
        }
    } 
    else if(y1==y2&&x2==(x1-4))
    {
        int i;
        for(i=4;i>=0;i--)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x2+i,y2)]);
        }
    } 
    else if(x2==(x1+4)&&y2==(y1+4))
    {
        int i;
        for(i=0;i<5;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1+i,y1+i)]);
        }
    }
    else
    {
        int i;
        for(i=0;i<5;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x2+i,y2+i)]);
        }
    }
    return res;
}

void mov(string s,GameState* S)
{
    vector<string> v;
    split(s.c_str(),v,' ');
    if(v[0]=="P")
    {
        int x,y;
        x = atoi(v[1].c_str());
        y = atoi(v[2].c_str());
        S->board[x][y] = S->turn;
    }
    else
    {
        if(v.size()==6)
        {
            int x1,y1,x2,y2;
            x1 = atoi(v[1].c_str());
            y1 = atoi(v[2].c_str());
            x2 = atoi(v[4].c_str());
            y2 = atoi(v[5].c_str());
            S->board[x2][y2] = S->turn;
            S->board[x1][y1] = 'e';
        }
        else
        {
            int x1,y1,x2,y2;
            x1 = atoi(v[1].c_str());
            y1 = atoi(v[2].c_str());
            x2 = atoi(v[4].c_str());
            y2 = atoi(v[5].c_str());
            S->board[x2][y2] = S->turn;
            S->board[x1][y1] = 'e';

            int xs,ys,xe,ye,rx,ry;
            xs = atoi(v[7].c_str());
            ys = atoi(v[8].c_str());
            xe = atoi(v[10].c_str());
            ye = atoi(v[11].c_str());
            rx = atoi(v[13].c_str());
            ry = atoi(v[14].c_str());

            S->board[rx][ry] = 'e';

            vector<pair<int,int> > rempos = getline(make_pair(xs,ys),make_pair(xe,ye),S);

            int i;
            for(i=0;i<rempos.size();i++)
            {
                int x,y;
                x = rempos[i].first;
                y = rempos[i].second;
                S->board[x][y] = 'e';
            }
        }
    }
    if(S->turn=='b')
        S->turn = 'o';
    else
        S->turn = 'b';
}
