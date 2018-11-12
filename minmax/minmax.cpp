#include "game.h"
#include <algorithm>
// const int MAX_DEPTH = 4;
const float MY_FLOAT_MAX =  numeric_limits<float>::max();
const float MY_FLOAT_MIN =  -numeric_limits<float>::max();

// float MinMaxInternal(GameState state, int depth, bool maximizing, char OriginTurn){
//     if((depth==0) || (state.GameEnded())){
//         return state.EvaluateHeuristicAdvanced(OriginTurn);
//     }
//     else{
//         float value;
//         vector<GameState> NextStates;
//         FinalGetValidMoves(state, NextStates);
//         int i=0;
//         if(maximizing){
//             value = MY_FLOAT_MIN;
//             for(i=0;i<NextStates.size();i++){
//                 value = max(value, MinMaxInternal(NextStates[i], depth-1, false, OriginTurn));
//             }
//             return value;
//         }
//         else{
//             value = MY_FLOAT_MAX;
//             for(i=0;i<NextStates.size();i++){
//                 value = min(value, MinMaxInternal(NextStates[i], depth-1, true, OriginTurn));
//             }
//             return value;
//         }
//     }
// }


// pair<GameState,float> MinMax(GameState state, char OriginTurn){
//     float value, temp;
//     vector<GameState> NextStates;
//     FinalGetValidMoves(state, NextStates);
//     int i=0;
//     GameState BestState;
//     value = MY_FLOAT_MIN;
//     for(i=0;i<NextStates.size();i++){
//         // cout<<i<<endl;
//         temp = max(value, MinMaxInternal(NextStates[i], MAX_DEPTH-1, false, OriginTurn));
//         if(temp>value){
//             value = temp;
//             BestState = GameState(NextStates[i]);
//         }
//     }
//     // cout<<"Exiting"<<endl;
//     return make_pair(BestState,value);
// }


float AlphaBetaInternal(GameState state, int depth, bool maximizing, float alpha, float beta, char OriginTurn){
    if((depth==0) || (state.GameEnded())){
        return state.EvaluateHeuristicAdvanced(OriginTurn);
    }
    else{
        float value;
        vector<GameState> NextStates;
        FinalGetValidMoves(state, NextStates);
		random_shuffle(NextStates.begin(), NextStates.end());
        vector<pair<float,int> > to_sort;
        int i=0;
        for(i=0;i<NextStates.size();i++)
        {
            float heur = NextStates[i].EvaluateHeuristicAdvanced(OriginTurn);
            to_sort.push_back(make_pair(heur,i));
        }
        sort(to_sort.begin(),to_sort.end());
        vector<int> move_order;
        move_order.resize(to_sort.size());
        int j = 0;
        for(int i=to_sort.size();i>0;i--)
        {
            move_order[j] = to_sort[i-1].second;
            j++;
        }
        if(maximizing){
            value = MY_FLOAT_MIN;
            for(i=0;i<NextStates.size();i++){
                value = max(value, AlphaBetaInternal(NextStates[move_order[i]], depth-1, false, alpha, beta, OriginTurn));
                alpha = max(alpha, value);
                if(alpha >= beta){
                    break;
                }
            }
        }
        else{
            reverse(move_order.begin(),move_order.end());
            value = MY_FLOAT_MAX;
            for(i=0;i<NextStates.size();i++){
                value = min(value, AlphaBetaInternal(NextStates[move_order[i]], depth-1, true, alpha, beta, OriginTurn));
                beta = min(beta,value);
                if(alpha >= beta){
                    break;
                }
            }
        }
        NextStates.clear();
        return value;
    }
}

pair<GameState,float> AlphaBeta(GameState state, char OriginTurn, int MAX_DEPTH){
    float value, temp;
    vector<GameState> NextStates;
    FinalGetValidMoves(state, NextStates);
    random_shuffle(NextStates.begin(), NextStates.end());
    vector<pair<float,int> > to_sort;
    int i=0;
    for(i=0;i<NextStates.size();i++)
        {
            float heur = NextStates[i].EvaluateHeuristicAdvanced(OriginTurn);
            to_sort.push_back(make_pair(heur,i));
        }
    sort(to_sort.begin(),to_sort.end());
    vector<int> move_order;
    move_order.resize(to_sort.size());
    int j = 0;
    for(int i=to_sort.size();i>0;i--)
    {
        move_order[j] = to_sort[i-1].second;
        j++;
    }
    GameState BestState;
    value = MY_FLOAT_MIN;
    float alpha = MY_FLOAT_MIN;
    float beta = MY_FLOAT_MAX;
    for(i=0;i<NextStates.size();i++){
        temp = max(value, AlphaBetaInternal(NextStates[move_order[i]], MAX_DEPTH-1, false, alpha, beta, OriginTurn));
        alpha = max(alpha, temp);
        if(alpha > beta){
            cout<<"BIG"<<endl;
            exit(-1);
            // break;
        }
        if(temp>value){
            value = temp;
            BestState = NextStates[move_order[i]];
        }
    }
    NextStates.clear();
    return make_pair(BestState,value);
}

GameState AlphaBetaPlayer(GameState state, char OriginTurn, int MAX_DEPTH){
	return AlphaBeta(state, OriginTurn, MAX_DEPTH).first;
}

GameState RandomPlayer(GameState state, char OriginTurn){
    vector<GameState> NextStates;
    FinalGetValidMoves(state, NextStates);
    random_shuffle(NextStates.begin(), NextStates.end());
    GameState RandomState = NextStates[0];
    NextStates.clear();
    return RandomState;
}


int main(){
    int player, BoardSize, TIME_GIVEN,NumRingsToRemoveIn;
    srand(time(0));
    // srand(6334);

    string recv;
    getline(cin, recv);
    vector<string> vv;
    split_ours(recv.c_str(),vv,' ');
    player = atoi(vv[0].c_str());
    BoardSize = atoi(vv[1].c_str());
    TIME_GIVEN = atoi(vv[2].c_str());
    NumRingsToRemoveIn = atoi(vv[2].c_str());
    // cin>>player;
    player-=1; // to make it zero or one
    // cin>>BoardSize;
    // cin>>time_given;
    char turn;
    if(player==0){
        turn = 'b';
    }
    else{
        turn = 'o';
    }

    double elapsed_seconds = 0;

    MoveTables*  FullTable;
    FullTable = new MoveTables(BoardSize);
    GameState CurrentState(BoardSize,BoardSize,NumRingsToRemoveIn,'b', FullTable);
    // CurrentState.board[0][0] = 'p';
    // CurrentState.board[1][0] = 'p';
    // CurrentState.board[1][1] = 'p';
    // CurrentState.board[1][2] = 'o';
    // CurrentState.board[1][3] = 'p';
    // CurrentState.board[1][4] = 'g';
    // CurrentState.board[1][5] = 'g';
    // CurrentState.board[2][0] = 'b';
    // CurrentState.board[2][1] = 'g';
    // CurrentState.board[2][3] = 'p';
    // CurrentState.board[2][4] = 'p';
    // CurrentState.board[2][7] = 'b';
    // CurrentState.board[2][8] = 'b';
    // CurrentState.board[2][11] = 'g';
    // CurrentState.board[3][1] = 'p';
    // CurrentState.board[3][2] = 'g';
    // CurrentState.board[3][3] = 'g';
    // CurrentState.board[3][4] = 'g';
    // CurrentState.board[3][5] = 'p';
    // CurrentState.board[3][13] = 'o';
    // CurrentState.board[3][14] = 'o';
    // CurrentState.board[3][15] = 'p';
    // CurrentState.board[3][16] = 'g';
    // CurrentState.board[3][17] = 'g';
    // CurrentState.board[4][1] = 'p';
    // CurrentState.board[4][3] = 'g';
    // CurrentState.board[4][5] = 'g';
    // CurrentState.board[4][7] = 'o';
    // CurrentState.board[4][23] = 'b';
    // CurrentState.board[5][1] = 'o';
    // CurrentState.board[5][2] = 'p';
    // CurrentState.board[5][7] = 'b';
    // CurrentState.EvaluateHeuristicAdvanced('b');


    int MAX_DEPTH = 3;
    if(player==1){
        getline(cin, recv);
        ExecuteMove(&CurrentState, recv);
    }
    int MyRingsPlaced = 0;
    while(MyRingsPlaced<BoardSize){
        int hexagon;
        int position;
        while(true){
            hexagon = rand() % (BoardSize+1); // more probability to choose center ones (can tune)
            if(hexagon == 0){
                position = 0;
            }
            else{
                position = rand() % (6*hexagon);
            }
            int x,y;
            pair<int,int> other_coord = FullTable->ours_to_axes[make_pair(hexagon,position)];
            x = other_coord.first;
            y = other_coord.second;

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

            if(CurrentState.board[hexagon][position] == 'e'){
                CurrentState.board[hexagon][position] = turn;
                if(player==0){
                    CurrentState.turn = 'o'; 
                }
                else{
                    CurrentState.turn = 'b'; 
                }
                break;
            }
        }
        cout<<"P "<<hexagon<<" "<<position<<endl;
        getline(cin, recv);
        ExecuteMove(&CurrentState, recv);
        MyRingsPlaced++;
    }
    // pair<GameState,float> result;
    int num_moves_we_played = 1;
    bool fixed_depth = false;
    while(true){
        // play own move
        // cerr<<endl;
        int i = 0, j = 0;
        // cerr<<CurrentState.board[0][0]<<endl;
        // for(i=1;i<=BoardSize;i++){
        //     vector<char> temp;
        //     for(j=0;j<6*i;j++){
        //         cerr<<CurrentState.board[i][j]<<" ";s
        //         // temp.push_back('e');
        //     }
        //     cerr<<endl;
        // }
        // cerr<<endl;
        time_t start = time(0);
        GameState NewState = AlphaBetaPlayer(CurrentState, turn, MAX_DEPTH);
        elapsed_seconds += difftime( time(0), start);
        if(elapsed_seconds>TIME_GIVEN-20){
            MAX_DEPTH = 3;
            fixed_depth = true;
        }

        num_moves_we_played++;
        if(num_moves_we_played%9==0){
            if(!fixed_depth){
                MAX_DEPTH++;
            }
            cerr<<"****************Depth is now "<<MAX_DEPTH<<endl;
        }
        stringstream MoveOut;
        int cur_ring;
        if(turn=='b')
            cur_ring = CurrentState.RingsRemoved[0];
        else
            cur_ring = CurrentState.RingsRemoved[1];
        int all_done = false;
        bool removed_once = false;
        for(i=0;i<NewState.LastMove.beg_remr.size();i++){
            if(cur_ring>=3)
            {
                all_done = true;
                MoveOut <<"\n";
                cout<<MoveOut.str();
                break;
            }
            cur_ring ++;
            if(removed_once){
                MoveOut<<" ";
            }
            MoveOut << "RS " << NewState.LastMove.beg_rem_first[i].first<<" "<<NewState.LastMove.beg_rem_first[i].second;
            MoveOut << " RE " << NewState.LastMove.beg_rem_last[i].first<<" "<<NewState.LastMove.beg_rem_last[i].second;
            MoveOut << " X " << NewState.LastMove.beg_remr[i].first<<" "<<NewState.LastMove.beg_remr[i].second;
            removed_once = true;
        }
        if(all_done)
            break;
        if(removed_once){
            MoveOut<<" ";
        }
        MoveOut << "S " << NewState.LastMove.init.first<<" "<<NewState.LastMove.init.second;
        MoveOut << " M " << NewState.LastMove.finl.first<<" "<<NewState.LastMove.finl.second;
        for(i=0;i<NewState.LastMove.end_remr.size();i++){
            if(cur_ring>=3)
            {
                all_done = true;
                break;
            }
            MoveOut << " RS " << NewState.LastMove.end_rem_first[i].first<<" "<<NewState.LastMove.end_rem_first[i].second;
            MoveOut << " RE " << NewState.LastMove.end_rem_last[i].first<<" "<<NewState.LastMove.end_rem_last[i].second;
            MoveOut << " X " << NewState.LastMove.end_remr[i].first<<" "<<NewState.LastMove.end_remr[i].second;
        }
        MoveOut <<"\n";
        cout<<MoveOut.str();
        if(all_done)
            break;
        CurrentState = NewState;
        //execute opponent move
        getline(cin, recv);
        ExecuteMove(&CurrentState, recv);
        // if(num_moves_we_played==4){
        //     // int k = 4/0;
        //     break;
        // }
    }
    delete(FullTable);
    return 0;
}
