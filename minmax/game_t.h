#ifndef CLASS_H
#define CLASS_H


#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include <ctime>
using namespace std;

template <>
struct std::hash<pair<int, int> > {
public:
        size_t operator()(pair<int, int> x) const throw() {
            //  size_t h = hash<int>()(x.first) ^ hash<int>()(x.second);//something with x   
            size_t h = (17+x.first)*103 + x.second;
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

    vector<pair<int,int> > vertical_gen;
    vector<pair<int,int> > diag_right_gen;
    vector<pair<int,int> > diag_left_gen;
    
    // map<pair<int,int>,vector<pair<int,int> > > vertical_up_map;
    // map<pair<int,int>,vector<pair<int,int> > > vertical_down_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_right_up_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_right_down_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_left_up_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_left_down_map;
    // map<pair<int,int>,vector<pair<int,int> > > vertical_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_right_map;
    // map<pair<int,int>,vector<pair<int,int> > > diag_left_map;
    // map<pair<int,int>,pair<int,int> > ours_to_axes;
    // map<pair<int,int>,pair<int,int> > axes_to_ours;

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
                // flag = 0;
                // if(ax_x==0 && (ax_y==BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(ax_x==0 && (ax_y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(ax_x==(-1*BoardSize) && (ax_y==(-1*BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(ax_x==(BoardSize) && (ax_y==(BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(ax_x==(-1*BoardSize) && (ax_y==0) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(ax_x==(BoardSize) && (ax_y==0) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                //     flag = 1;
                // if(!(flag==1)){
                    ours_to_axes.insert(make_pair(make_pair(i,j),make_pair(ax_x,ax_y)));
                    axes_to_ours.insert(make_pair(make_pair(ax_x,ax_y),make_pair(i,j)));        
                // }
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
            for(j=0;j<=6*i;j++){
                if(j==(6*i))
                {
                    if(i>0)
                        break;
                }
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

                vert_up.push_back(make_pair(i,j));
                vert_down.push_back(make_pair(i,j));

                diag_right_up.push_back(make_pair(i,j));
                diag_right_down.push_back(make_pair(i,j));

                diag_left_up.push_back(make_pair(i,j));
                diag_left_down.push_back(make_pair(i,j));

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
                    vert.push_back(nxt_vert);
                }
                int x_up,x_down;
                x = ax_x;
                y = ax_y;
                x_up = ax_x;
                x_down = ax_x;
                while(true)
                {
                    x++;
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
                }

                x = ax_x;
                y = ax_y;
                while(true)
                {
                    x--;                    
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
                }

                x = x_down-1;
                y = ax_y;
                while(true)
                {
                    x++;                    
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
                }

                int x_lim,y_lim;
                x = ax_x;
                y = ax_y;
                x_lim = ax_x;
                y_lim = ax_y;
                while(true)
                {
                    x++;
                    y++;
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
                }

                x = ax_x;
                y = ax_y;
                while(true)
                {
                    x--;
                    y--;
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
                }

                x = x_lim-1;
                y = y_lim-1;
                while(true)
                {
                    x++;
                    y++;
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

        for(i=-BoardSize+1;i<BoardSize;i++){
            vertical_gen.push_back(axes_to_ours[make_pair(i,0)]);
            diag_right_gen.push_back(axes_to_ours[make_pair(i,0)]);
        }
        vertical_gen.push_back(axes_to_ours[make_pair(-BoardSize,-1)]);
        vertical_gen.push_back(axes_to_ours[make_pair(BoardSize,1)]);
        diag_right_gen.push_back(axes_to_ours[make_pair(BoardSize-1,-1)]);
        diag_right_gen.push_back(axes_to_ours[make_pair(-BoardSize+1,1)]);
        for(i=-BoardSize+1;i<BoardSize;i++){
            diag_left_gen.push_back(axes_to_ours[make_pair(i,i)]);
        }
        diag_left_gen.push_back(axes_to_ours[make_pair(-BoardSize+1,-BoardSize)]);
        diag_left_gen.push_back(axes_to_ours[make_pair(BoardSize-1,BoardSize)]);
        

    }

};

class Move{
    public:
    char movecolour;
    pair<int,int> RingPlaced;
    pair<int,int> init;
    pair<int,int> finl;
    vector<pair<int,int> > beg_remr;
    vector<pair<int,int> > beg_rem_first;
    vector<pair<int,int> > beg_rem_last;
    vector<pair<int,int> > end_remr;
    vector<pair<int,int> > end_rem_first;
    vector<pair<int,int> > end_rem_last;
    Move(){
        movecolour = '0';
        init = make_pair(-1,-1);
        finl = make_pair(-1,-1);
        RingPlaced = make_pair(-1,-1);
        beg_remr = vector<pair<int,int> > ();
        beg_rem_first = vector<pair<int,int> > ();
        beg_rem_last = vector<pair<int,int> > ();
        end_remr = vector<pair<int,int> > ();
        end_rem_first = vector<pair<int,int> > ();
        end_rem_last = vector<pair<int,int> > ();

    }
    // Move(char mv,pair<int,int> init_in,pair<int,int> finl_in)
    // {
    //     movecolour = mv;
    //     init = make_pair(init_in.first,init_in.second);
    //     finl = make_pair(finl_in.first,finl_in.second);
    //     beg_remr = vector<pair<int,int> > ();
    //     beg_rem_first = vector<pair<int,int> > ();
    //     beg_rem_last = vector<pair<int,int> > ();
    //     end_remr = vector<pair<int,int> > ();
    //     end_rem_first = vector<pair<int,int> > ();
    //     end_rem_last = vector<pair<int,int> > ();
    // }
    Move(const Move &oth){
        movecolour = oth.movecolour;
        init = make_pair(oth.init.first,oth.init.second);
        finl = make_pair(oth.finl.first,oth.finl.second);
        RingPlaced = make_pair(oth.RingPlaced.first,oth.RingPlaced.second);
        // remr = make_pair(oth->remr.first,oth->remr.second);
        // reml_first = make_pair(oth->reml_first.first,oth->reml_first.second);
        // reml_last = make_pair(oth->reml_last.first,oth->reml_last.second);
        beg_remr = oth.beg_remr;
        beg_rem_first = oth.beg_rem_first;
        beg_rem_last = oth.beg_rem_last;
        end_remr = oth.end_remr;
        end_rem_first = oth.end_rem_first;
        end_rem_last = oth.end_rem_last;
    }
    Move(const Move* oth){
        if(oth!=NULL){
            movecolour = oth->movecolour;
            init = make_pair(oth->init.first,oth->init.second);
            finl = make_pair(oth->finl.first,oth->finl.second);
            RingPlaced = make_pair(oth->RingPlaced.first,oth->RingPlaced.second);
            // remr = make_pair(oth->remr.first,oth->remr.second);
            // reml_first = make_pair(oth->reml_first.first,oth->reml_first.second);
            // reml_last = make_pair(oth->reml_last.first,oth->reml_last.second);
            beg_remr = oth->beg_remr;
            beg_rem_first = oth->beg_rem_first;
            beg_rem_last = oth->beg_rem_last;
            end_remr = oth->end_remr;
            end_rem_first = oth->end_rem_first;
            end_rem_last = oth->end_rem_last;
        }
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
        Move LastMove;//move which led to this state;
        int BoardSize;
        int RingsInit;
        int NumRingsToRemove;
        MoveTables* table;
        // ~GameState(){
        //     if(LastMove!=NULL){
        //         delete(LastMove);
        //     }
        // }
        GameState(){}
        GameState(int BoardSizeIn,int RingsInitIn,int NumRingsToRemoveIn, char OurTurn, MoveTables* ourtable){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            BoardSize = BoardSizeIn; // num hexagons
            RingsInit = RingsInitIn;
            NumRingsToRemove = NumRingsToRemoveIn;
            board.push_back(vector<char>(1,'e'));
            for(i=1;i<=BoardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back('e');
                }
                board.push_back(temp);
            }
            // deal with the six banned squares here?
            LastMove = NULL;
            table = ourtable;
            turn = OurTurn;
            RingsRemoved = vector<int>(2,0);
        }

        GameState(const GameState &oth){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            BoardSize = oth.BoardSize; // num hexagons
            RingsInit = oth.RingsInit;
            NumRingsToRemove = oth.NumRingsToRemove;
            board.push_back(vector<char>(1,oth.board[0][0]));
            for(i=1;i<=BoardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back(oth.board[i][j]);
                }
                board.push_back(temp);
            }
            // if(!(oth.LastMove==NULL)){
            //     LastMove = new Move(oth.LastMove);
            // }
            // else{
            //     LastMove = NULL;
            // }
            LastMove = Move(&oth.LastMove);
            // deal with the six banned squares here?
            
            turn = oth.turn;
            RingsRemoved = vector<int>(2,0);
            RingsRemoved[0] = oth.RingsRemoved[0];
            RingsRemoved[1] = oth.RingsRemoved[1];
            table = oth.table;
        }
        GameState(const GameState *oth){
            board = vector<vector<char> > ();
            int i = 0, j = 0;
            BoardSize = oth->BoardSize; // num hexagons
            RingsInit = oth->RingsInit;
            NumRingsToRemove = oth->NumRingsToRemove;
            board.push_back(vector<char>(1,oth->board[0][0]));
            for(i=1;i<=BoardSize;i++){
                vector<char> temp;
                for(j=0;j<6*i;j++){
                    temp.push_back(oth->board[i][j]);
                }
                board.push_back(temp);
            }
            // if(!(oth->LastMove==NULL)){
            //     LastMove = new Move(oth->LastMove);
            // }
            // else{
            //     LastMove = NULL;
            // }
            LastMove = Move(&(oth->LastMove));
            // deal with the six banned squares here?
            
            turn = oth->turn;
            RingsRemoved = vector<int>(2,0);
            RingsRemoved[0] = oth->RingsRemoved[0];
            RingsRemoved[1] = oth->RingsRemoved[1];
            table = oth->table;
        }

        bool GameEnded(){
            if((RingsRemoved[0]==3) ||  (RingsRemoved[1]==3)){
                return true;
            }
            else{
                return false;
            }
        }
        // float EvaluateHeuristic(char OriginTurn){
        //     float score = 0;
        //     int i,j;
        //     int bPegs=0,bRings=0,oPegs=0,oRings=0;
        //     for(i=0;i<board.size();i++){
        //         for(j=0;j<board[i].size();j++){
        //             if(board[i][j]=='g'){
        //                 bPegs+=1;
        //             }
        //             else if(board[i][j]=='p'){
        //                 oPegs+=1;
        //             }
        //             else if(board[i][j]=='b'){
        //                 bRings+=1;
        //             }
        //             else if(board[i][j]=='o'){
        //                 oRings+=1;
        //             }
        //             else{}
        //         }
        //     }
        //     score += 3*(bPegs - oPegs);
        //     score += 0.5*(bRings - oRings);
        //     score += 25*(RingsRemoved[0] - RingsRemoved[1]);
        //     if(OriginTurn=='o'){
        //         score = -score;
        //     }
        //     return score;
        // }
        float EvaluateHeuristicAdvanced(char OriginTurn){
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
            vector<pair<int,int> > iter_map;
            int combo_pegs_len;
            char combo_pegs_color = '0';
            vector<int> bCombo(NumRingsToRemove+1,0); // first two elements useless
            vector<int> oCombo(NumRingsToRemove+1,0); // first two elements useless
            bCombo[0] = -1000;
            oCombo[0] = -1000;
            bCombo[1] = -1000;
            oCombo[1] = -1000;
            int bThwart = 0; // means b player has ring just after a combo of more than two of other's pegs
            int oThwart = 0; // these are one sided for now
            for(i=0;i<table->vertical_gen.size();i++){
                iter_map = table->vertical_map[table->vertical_gen[i]];
                combo_pegs_len = 0;
                combo_pegs_color = 'a';
                for(j=0;j<iter_map.size();j++){
                    if((combo_pegs_color=='p')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='b')){
                        bThwart++;
                    }
                    if((combo_pegs_color=='g')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='o')){
                        oThwart++;
                    }
                    if(combo_pegs_color == board[iter_map[j].first][iter_map[j].second]){
                        combo_pegs_len++;
                        if(combo_pegs_len>1){
                            if(combo_pegs_color=='g'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    bCombo[combo_pegs_len]++;
                                }
                            }
                            else if(combo_pegs_color=='p'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    oCombo[combo_pegs_len]++;
                                }
                            }
                        }
                    }
                    else{
                        if(board[iter_map[j].first][iter_map[j].second]=='g'){
                            combo_pegs_color = 'g';
                            combo_pegs_len=1;
                        }
                        else if(board[iter_map[j].first][iter_map[j].second]=='p'){
                            combo_pegs_color = 'p';
                            combo_pegs_len=1;
                        }
                        else{
                            combo_pegs_color = 'a';
                            combo_pegs_len=0;
                        }
                    }
                }
            }
            for(i=0;i<table->diag_left_gen.size();i++){
                iter_map = table->diag_left_map[table->diag_left_gen[i]];
                combo_pegs_len = 0;
                combo_pegs_color = 'a';
                for(j=0;j<iter_map.size();j++){
                    if((combo_pegs_color=='p')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='b')){
                        bThwart++;
                    }
                    if((combo_pegs_color=='g')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='o')){
                        oThwart++;
                    }
                    if(combo_pegs_color == board[iter_map[j].first][iter_map[j].second]){
                        combo_pegs_len++;
                        if(combo_pegs_len>1){
                            if(combo_pegs_color=='g'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    bCombo[combo_pegs_len]++;
                                }
                            }
                            else if(combo_pegs_color=='p'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    oCombo[combo_pegs_len]++;
                                }
                            }
                        }
                    }
                    else{
                        if(board[iter_map[j].first][iter_map[j].second]=='g'){
                            combo_pegs_color = 'g';
                            combo_pegs_len=1;
                        }
                        else if(board[iter_map[j].first][iter_map[j].second]=='p'){
                            combo_pegs_color = 'p';
                            combo_pegs_len=1;
                        }
                        else{
                            combo_pegs_color = 'a';
                            combo_pegs_len=0;
                        }
                    }
                }
            }
            for(i=0;i<table->diag_right_gen.size();i++){
                iter_map = table->diag_right_map[table->diag_right_gen[i]];
                combo_pegs_len = 0;
                combo_pegs_color = 'a';
                for(j=0;j<iter_map.size();j++){
                    if((combo_pegs_color=='p')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='b')){
                        bThwart++;
                    }
                    if((combo_pegs_color=='g')&&(combo_pegs_len>2)&&(board[iter_map[j].first][iter_map[j].second]=='o')){
                        oThwart++;
                    }
                    if(combo_pegs_color == board[iter_map[j].first][iter_map[j].second]){
                        combo_pegs_len++;
                        if(combo_pegs_len>1){
                            if(combo_pegs_color=='g'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    bCombo[combo_pegs_len]++;
                                }
                            }
                            else if(combo_pegs_color=='p'){
                                if(combo_pegs_len<=NumRingsToRemove){
                                    oCombo[combo_pegs_len]++;
                                }
                            }
                        }
                    }
                    else{
                        if(board[iter_map[j].first][iter_map[j].second]=='g'){
                            combo_pegs_color = 'g';
                            combo_pegs_len=1;
                        }
                        else if(board[iter_map[j].first][iter_map[j].second]=='p'){
                            combo_pegs_color = 'p';
                            combo_pegs_len=1;
                        }
                        else{
                            combo_pegs_color = 'a';
                            combo_pegs_len=0;
                        }
                    }
                }
            }
            // score += 2*(bCombo[2]-oCombo[2]);
            score += (bPegs - oPegs);                     
            score += 2*(bCombo[2]-oCombo[2]);
            score += 3*(bCombo[3]-oCombo[3]);            
            score += 4*(bCombo[4]-oCombo[4]);
            if(NumRingsToRemove>5)
                score += 5*(bCombo[5]-oCombo[5]);
            score += 10*(bThwart - oThwart);
            score += 400*(RingsRemoved[0] - RingsRemoved[1]);
            if(OriginTurn=='o'){
                score = -score;
            }
            return score;
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
        


        void GetValidMoves(vector<GameState> &topush){
            // vector<GameState> res;
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
            for(i=1;i<=BoardSize;i++)
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
                    for(k=1;k<pos[j].size();k++)
                    {
                        int xi,yi;
                        xi=pos[j][k].first;
                        yi=pos[j][k].second;
                        if(board[xi][yi]==opp || board[xi][yi]==turn)
                            break;
                        if(board[xi][yi]==mytok || board[xi][yi]==opptok )
                        {
                            vismark = true;
                        }
                        else
                        {
                            GameState* temp = new GameState(*this);     
                            // if(turn=='b')
                            //     temp.turn ='o';
                            // else
                            //     temp.turn ='b';
                            temp->board[xi][yi] = turn;
                            temp->board[x][y] = mytok;
                            temp->LastMove.init = make_pair(x,y);
                            temp->LastMove.finl = make_pair(xi,yi);
                            // temp->LastMove = Move(turn,make_pair(x,y),make_pair(xi,yi));
                            int kp;
                            for(kp=1;kp<k;kp++)
                            {
                                int xk,yk;
                                xk=pos[j][kp].first;
                                yk=pos[j][kp].second;
                                if(temp->board[xk][yk]==mytok)
                                    temp->board[xk][yk]=opptok;
                                else if(temp->board[xk][yk]==opptok)
                                    temp->board[xk][yk]=mytok;
                            }
                            topush.push_back(*temp);
                            delete(temp); // destroy this since above we copy by value
                            if(vismark)
                                break;
                        }
                    }
                }
            }
            // return res;
        }
};


size_t split_ours(const string &txt, vector<string> &strs, char ch);
vector<pair<int,int> > getline_ours(pair<int,int> st,pair<int,int> end,GameState* S);
void ExecuteMove(GameState* S,string s);
void FinalGetValidMoves(GameState s, vector<GameState> &topush);
GameState AlphaBetaPlayer(GameState state, char OriginTurn, int MAX_DEPTH);
GameState RandomPlayer(GameState state, char OriginTurn);

#endif
