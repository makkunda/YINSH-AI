#include "game.h"


size_t split_ours(const string &txt, vector<string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

vector<pair<int,int> > getline_ours(pair<int,int> st,pair<int,int> end,GameState* S)
{
    vector<pair<int,int> > res;
    pair<int,int> st_ax = S->table->ours_to_axes[st];
    pair<int,int> en_ax = S->table->ours_to_axes[st];
    int x1,y1,x2,y2;
    x1 = st_ax.first; y1 = st_ax.second;
    x2 = en_ax.first; y2 = en_ax.second;
    int bs = S->BoardSize;
    if(x1==x2&&y2==(y1+bs-1))
    {
        int i;
        for(i=0;i<bs;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1,y1+i)]);
        }
    }
    else if(x1==x2&&y2==(y1-bs+1))
    {
        int i;
        for(i=(bs-1);i>=0;i--)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1,y2+i)]);
        }
    } 
    else if(y1==y2&&x2==(x1+(bs-1)))
    {
        int i;
        for(i=0;i<bs;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1+i,y2)]);
        }
    } 
    else if(y1==y2&&x2==(x1-(bs-1)))
    {
        int i;
        for(i=(bs-1);i>=0;i--)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x2+i,y2)]);
        }
    } 
    else if(x2==(x1+(bs-1))&&y2==(y1+(bs-1)))
    {
        int i;
        for(i=0;i<bs;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x1+i,y1+i)]);
        }
    }
    else
    {
        int i;
        for(i=0;i<bs;i++)
        {
            res.push_back(S->table->axes_to_ours[make_pair(x2+i,y2+i)]);
        }
    }
    return res;
}

void ExecuteMove(GameState* S,string s)
{
    vector<string> v;
    split_ours(s.c_str(),v,' ');
    if(v[0]=="P")
    {
        int x,y;
        x = atoi(v[1].c_str());
        y = atoi(v[2].c_str());
        S->board[x][y] = S->turn;
    }
    else if(v[0]=="S")
    {
        if(v.size()==6)
        {
            int x1,y1,x2,y2;
            x1 = atoi(v[1].c_str());
            y1 = atoi(v[2].c_str());
            x2 = atoi(v[4].c_str());
            y2 = atoi(v[5].c_str());
            S->board[x2][y2] = S->turn;
            if(S->turn=='b')
                S->board[x1][y1] = 'g';
            else
                S->board[x1][y1] = 'p';
        }
        else
        {
            int x1,y1,x2,y2;
            x1 = atoi(v[1].c_str());
            y1 = atoi(v[2].c_str());
            x2 = atoi(v[4].c_str());
            y2 = atoi(v[5].c_str());
            S->board[x2][y2] = S->turn;
            if(S->turn=='b')
                S->board[x1][y1] = 'g';
            else
                S->board[x1][y1] = 'p';

            int xs,ys,xe,ye,rx,ry;
            xs = atoi(v[7].c_str());
            ys = atoi(v[8].c_str());
            xe = atoi(v[10].c_str());
            ye = atoi(v[11].c_str());
            rx = atoi(v[13].c_str());
            ry = atoi(v[14].c_str());

            S->board[rx][ry] = 'e';

            vector<pair<int,int> > rempos = getline_ours(make_pair(xs,ys),make_pair(xe,ye),S);

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
    else
    {
        int xs,ys,xe,ye,rx,ry;
        xs = atoi(v[1].c_str());
        ys = atoi(v[2].c_str());
        xe = atoi(v[4].c_str());
        ye = atoi(v[5].c_str());
        rx = atoi(v[7].c_str());
        ry = atoi(v[8].c_str());

        S->board[rx][ry] = 'e';

        vector<pair<int,int> > rempos = getline_ours(make_pair(xs,ys),make_pair(xe,ye),S);

        int i;
        for(i=0;i<rempos.size();i++)
        {
            int x,y;
            x = rempos[i].first;
            y = rempos[i].second;
            S->board[x][y] = 'e';
        }

        int x1,y1,x2,y2;
        x1 = atoi(v[10].c_str());
        y1 = atoi(v[11].c_str());
        x2 = atoi(v[13].c_str());
        y2 = atoi(v[14].c_str());
        S->board[x2][y2] = S->turn;
        if(S->turn=='b')
            S->board[x1][y1] = 'g';
        else
            S->board[x1][y1] = 'p';
    }
    if(S->turn=='b')
        S->turn = 'o';
    else
        S->turn = 'b';
}

vector<GameState> FinalGetValidMoves(GameState s){
    vector<GameState> FirstCleaned = cleaner_in(s);
    vector<GameState> Middle;
    int i;
    for(i=0;i<FirstCleaned.size();i++){
        vector<GameState> MiddleValid = FirstCleaned[i].GetValidMoves();
        Middle.reserve(Middle.size()+ MiddleValid.size());
        Middle.insert(Middle.end(),MiddleValid.begin(),MiddleValid.end());
    }
    vector<GameState> Output;
    for(i=0;i<Middle.size();i++){
        vector<GameState> OutputValid = cleaner_out(Middle[i];
        Output.reserve(Output.size()+ OutputValid.size());
        Output.insert(Output.end(),OutputValid.begin(),OutputValid.end());
    }
    return Output;
}

vector<GameState> cleaner_in(GameState s)
{
    vector<GameState> res;
    res.push_back(s);
    return res;
}

vector<GameState> cleaner_out(GameState s)
{
    vector<GameState> res;
    res.push_back(s);
    return res;
}


