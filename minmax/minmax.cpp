#include "game.h"

const int MAX_DEPTH = 4;


float MinMaxInternal(GameState state, int depth, bool maximizing){
    if((depth==0) || (state.GameEnded())){
        return state.EvaluateHeuristic();
    }
    else{
        float value;
        vector<GameState> NextStates = state.GetValidMoves();
        int i=0;
        if(maximizing){
            value = numeric_limits<float>::min();
            for(i=0;i<NextStates.size();i++){
                value = max(value, MinMaxInternal(NextStates[i], depth-1, false));
            }
            return value;
        }
        else{
            value = numeric_limits<float>::max();
            for(i=0;i<NextStates.size();i++){
                value = min(value, MinMaxInternal(NextStates[i], depth-1, true));
            }
            return value;
        }
    }
}


pair<GameState,float> MinMax(GameState state){
    float value, temp;
    vector<GameState> NextStates = state.GetValidMoves();
    int i=0;
    GameState BestState;
    value = numeric_limits<float>::min();
    for(i=0;i<NextStates.size();i++){
        temp = max(value, MinMaxInternal(NextStates[i], MAX_DEPTH-1, false));
        if(temp>value){
            value = temp;
            BestState = NextStates[i];
        }
    }
    return make_pair(BestState,value);
}


float AlphaBetaInternal(GameState state, int depth, bool maximizing, float alpha, float beta){
    if((depth==0) || (state.GameEnded())){
        return state.EvaluateHeuristic();
    }
    else{
        float value;
        vector<GameState> NextStates = state.GetValidMoves();
        int i=0;
        if(maximizing){
            value = numeric_limits<float>::min();
            for(i=0;i<NextStates.size();i++){
                value = max(value, AlphaBetaInternal(NextStates[i], depth-1, false, alpha, beta));
                alpha = max(alpha, value);
                if(alpha >= beta){
                    break;
                }
            }
            return value;
        }
        else{
            value = numeric_limits<float>::max();
            for(i=0;i<NextStates.size();i++){
                value = min(value, AlphaBetaInternal(NextStates[i], depth-1, true, alpha, beta));
                beta = min(beta,value);
                if(alpha >= beta){
                    break;
                }
            }
            return value;
        }
    }
}

pair<GameState,float> AlphaBeta(GameState state){
    float value, temp;
    vector<GameState> NextStates = state.GetValidMoves();
    int i=0;
    GameState BestState;
    value = numeric_limits<float>::min();
    for(i=0;i<NextStates.size();i++){
        temp = max(value, AlphaBetaInternal(NextStates[i], MAX_DEPTH-1, false, numeric_limits<float>::min(), numeric_limits<float>::max()));
        if(temp>value){
            value = temp;
            BestState = NextStates[i];
        }
    }
    return make_pair(BestState,value);
}

int main(){
    int player, BoardSize, time_given;
    // srand(time(0));
    string recv;
    getline(cin, recv);
    vector<string> vv;
    split_ours(recv.c_str(),vv,' ');
    player = atoi(vv[0].c_str());
    BoardSize = atoi(vv[1].c_str());
    time_given = atoi(vv[2].c_str());
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
    MoveTables*  FullTable;
    FullTable = new MoveTables(BoardSize);
    GameState CurrentState(BoardSize, turn, FullTable);
    if(player==1){
        getline(cin, recv);
        ExecuteMove(&CurrentState, recv);
    }
    int MyRingsPlaced = 0;
    while(MyRingsPlaced<5){
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
    while(true){
        // play own move
        pair<GameState,float> result = MinMax(CurrentState);
        GameState NewState = result.first;
        stringstream MoveOut;

        MoveOut << "S " << NewState.LastMove->init.first<<" "<<NewState.LastMove->init.second;
        MoveOut << " M" << NewState.LastMove->finl.first<<" "<<NewState.LastMove->finl.second;
        if(NewState.LastMove->remr.first != -1){
            MoveOut << " RS" << NewState.LastMove->reml_first.first<<" "<<NewState.LastMove->reml_first.second;
            MoveOut << " RE" << NewState.LastMove->reml_last.first<<" "<<NewState.LastMove->reml_last.second;
            MoveOut << " X" << NewState.LastMove->remr.first<<" "<<NewState.LastMove->remr.second;
        }
        MoveOut <<"\n";
        cout<<MoveOut.str();

        //execute opponent move
        getline(cin, recv);
        ExecuteMove(&CurrentState, recv);
    }
    return 0;
}