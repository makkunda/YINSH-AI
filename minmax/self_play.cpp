#include <algorithm>
#include <fstream>
#include "game.h"
#include <string>
#include <sys/stat.h>

using namespace std;

string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    string str(length,0);
    generate_n( str.begin(), length, randchar );
    // cout<<str<<endl;
    return str;
}

int play_game_and_write(int BoardSize, int  TIME_GIVEN, int MODE, string directory){
    // mode = 1 -> random vs random adv heuristic 
    // mode = 2 -> 4 depth vs random adv heuristic 
    // mode = 3 -> 4 depth vs 4 depth adv heuristic 
    // int player, BoardSize, TIME_GIVEN;
    time_t now = time(0);
    // srand(time(0));
    cout<<"Seed is "<<now<<endl;
    srand(now);
    BoardSize = 5;
    TIME_GIVEN = 200;
    char turn;
    turn = 'b';
    ofstream GameFile;
    GameFile.open (directory+"/"+"game-"+random_string(15));
    double elapsed_seconds = 0;
    MoveTables*  FullTable;
    FullTable = new MoveTables(BoardSize);
    GameState CurrentState(BoardSize, 'b', FullTable);

    int MAX_DEPTH = 2;    
    int num_moves_we_played = 1;
    while(true){
        // play own move
        // cerr<<endl;
        int i = 0, j = 0;
        // if(num_moves_we_played>35){
        //     MAX_DEPTH = 4; // 35 mins! with 6
        // }
        if(num_moves_we_played>10){
            MAX_DEPTH = 4;
        }
        else{
            MAX_DEPTH = 2;
        }
        time_t start = time(0);
        GameState NewState;
        if (MODE==1){
            if(turn == 'b'){
                NewState = RandomPlayer(CurrentState, turn);
            }
            else{
                NewState = RandomPlayer(CurrentState, turn);
            }
        }
        else if(MODE==2){
            if(turn == 'b'){
                NewState = AlphaBetaPlayer(CurrentState, turn, MAX_DEPTH);
            }
            else{
                NewState = RandomPlayer(CurrentState, turn);
            }
        }
        else if(MODE==3){
            if(turn == 'b'){
                NewState = AlphaBetaPlayer(CurrentState, turn, MAX_DEPTH);
            }
            else{
                NewState = AlphaBetaPlayer(CurrentState, turn, MAX_DEPTH);
            }
        }
        else{
            cout<<"Wrong mode"<<endl;
            return -1;
        }
        elapsed_seconds += difftime( time(0), start);

        num_moves_we_played++;
        stringstream MoveOut;
        // MoveOut<< turn <<" ";
        int cur_ring;
        if(turn=='b'){
            cur_ring = CurrentState.RingsRemoved[0];
		}
        else{
            cur_ring = CurrentState.RingsRemoved[1];
		}
        int all_done = false;
        if(NewState.LastMove.RingPlaced != make_pair(-1,-1)){
			MoveOut << "P " << NewState.LastMove.RingPlaced.first<<" "<<NewState.LastMove.RingPlaced.second;			
		}
        else{
			for(i=0;i<NewState.LastMove.beg_remr.size();i++){
				cur_ring ++;
                //correct printing here
				MoveOut << "RS " << NewState.LastMove.beg_rem_first[i].first<<" "<<NewState.LastMove.beg_rem_first[i].second;
				MoveOut << " RE " << NewState.LastMove.beg_rem_last[i].first<<" "<<NewState.LastMove.beg_rem_last[i].second;
                if(cur_ring>=3){
                    MoveOut << " X " << NewState.LastMove.beg_remr[i].first<<" "<<NewState.LastMove.beg_remr[i].second;
					all_done = true;
					break;
				}
                MoveOut << " X " << NewState.LastMove.beg_remr[i].first<<" "<<NewState.LastMove.beg_remr[i].second<<" ";
			}
            if(all_done){ //break out of while
                MoveOut <<"\n";
                GameFile<<MoveOut.str();
                // cout<<MoveOut.str();
				break;
            }
			MoveOut << "S " << NewState.LastMove.init.first<<" "<<NewState.LastMove.init.second;
			MoveOut << " M " << NewState.LastMove.finl.first<<" "<<NewState.LastMove.finl.second;
			for(i=0;i<NewState.LastMove.end_remr.size();i++){
				cur_ring ++;
				MoveOut << " RS " << NewState.LastMove.end_rem_first[i].first<<" "<<NewState.LastMove.end_rem_first[i].second;
				MoveOut << " RE " << NewState.LastMove.end_rem_last[i].first<<" "<<NewState.LastMove.end_rem_last[i].second;
				MoveOut << " X " << NewState.LastMove.end_remr[i].first<<" "<<NewState.LastMove.end_remr[i].second;
                if(cur_ring>=3){
					all_done = true;
					break;
				}
			}
            if(all_done){ //break out of while
                MoveOut <<"\n";
                GameFile<<MoveOut.str();
                // cout<<MoveOut.str();
				break;
            }
		}
        MoveOut <<"\n";
        GameFile<<MoveOut.str();
        // cout<<MoveOut.str();
        CurrentState = NewState;
        if(turn=='b'){
			turn = 'o';
		}
		else{
			turn = 'b';
		}
    }
    GameFile.close();
    delete(FullTable);
    return 0;
}

int main(int argc, char** argv){
    if(argc!=4){    
        cout<<"wrong number of args, usage ./execute dir num_games mode";
    }
    else{
        if (mkdir(argv[1], S_IRWXU) == -1 && (errno != EEXIST)){
            if( errno == EEXIST ) {
                cout << "Directory already exists"<<endl;
                return -1;
            } else {
                cout << "Other error in directory creation"<<endl;
                return -1;
            }
        }
        else{
            int num_games = atoi(argv[2]);
            int mode = atoi(argv[3]);
            int i = 0;
            string dir(argv[1]);
            for(i=1;i<=num_games;i++){
                play_game_and_write(5,300,mode,dir);
                if(i*20==0){
                    cout<<"Played "<< i <<" games"<<endl;
                }
            }
        }
    }
    return 0;
}