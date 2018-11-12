#include "game_t.h"

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
    float f = 1/0;
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

vector<pair<int,int> > getline_ours_gen(pair<int,int> st,pair<int,int> end,GameState* S)
{
    vector<pair<int,int> > res;
    pair<int,int> st_ax = S->table->ours_to_axes[st];
    pair<int,int> en_ax = S->table->ours_to_axes[end];
    int x1,y1,x2,y2;
    x1 = st_ax.first; y1 = st_ax.second;
    x2 = en_ax.first; y2 = en_ax.second;
    int bs = S->BoardSize;
    if(x1==x2)
    {
        if(y2>y1)
        {
            int i;
            for(i=y1;i<=y2;i++)
            {
                res.push_back(S->table->axes_to_ours[make_pair(x1,i)]);
            }
        }
        else
        {
            int i;
            for(i=y1;i>=y2;i--)
            {
                res.push_back(S->table->axes_to_ours[make_pair(x1,i)]);
            }
        }
    }
    else if(y1==y2)
    {
        if(x2>x1)
        {
            int i;
            for(i=x1;i<=x2;i++)
            {
                res.push_back(S->table->axes_to_ours[make_pair(i,y1)]);
            }
        }
        else
        {
            int i;
            for(i=x1;i>=x2;i--)
            {
                res.push_back(S->table->axes_to_ours[make_pair(i,y1)]);
            }
        }
    } 
    else
    {
        if(y2>y1)
        {
            int diff = y2 - y1;
            int i;
            for(i=0;i<=diff;i++)
            {
                res.push_back(S->table->axes_to_ours[make_pair(x1+i,y1+i)]);
            }
        }
        else
        {
            int diff = y1 - y2;
            int i;
            for(i=diff;i>=0;i--)
            {
                res.push_back(S->table->axes_to_ours[make_pair(x2+i,y2+i)]);
            }
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
    else
    {
        int cur = 0;

        while(v[cur]=="RS")
        {
            int xs,ys,xe,ye,rx,ry;
            xs = atoi(v[cur + 1].c_str());
            ys = atoi(v[cur + 2].c_str());
            xe = atoi(v[cur + 4].c_str());
            ye = atoi(v[cur + 5].c_str());
            rx = atoi(v[cur + 7].c_str());
            ry = atoi(v[cur + 8].c_str());

            S->board[rx][ry] = 'e';

            vector<pair<int,int> > rempos = getline_ours_gen(make_pair(xs,ys),make_pair(xe,ye),S);

            int i;
            for(i=0;i<rempos.size();i++)
            {
                int x,y;
                x = rempos[i].first;
                y = rempos[i].second;
                S->board[x][y] = 'e';
            }
            //added
            if(S->turn=='b')
                S->RingsRemoved[0]+=1;
            else
                S->RingsRemoved[1]+=1;

            cur = cur + 9;
        }

        int x1,y1,x2,y2;
        x1 = atoi(v[cur + 1].c_str());
        y1 = atoi(v[cur+ 2].c_str());
        x2 = atoi(v[cur + 4].c_str());
        y2 = atoi(v[cur + 5].c_str());
        S->board[x2][y2] = S->turn;
        if(S->turn=='b')
            S->board[x1][y1] = 'g';
        else
            S->board[x1][y1] = 'p';
        
        vector<pair<int,int> > rempos = getline_ours_gen(make_pair(x1,y1),make_pair(x2,y2),S);

            int i;
            for(i=1;(i+1)<rempos.size();i++)
            {
                int x,y;
                x = rempos[i].first;
                y = rempos[i].second;
                if(S->board[x][y] == 'g')
                    S->board[x][y] = 'p';
                else if(S->board[x][y] == 'p')
                    S->board[x][y] = 'g';
            }
        
        cur = cur + 6;

        while(true)
        {
            if(cur>=v.size())
                break;

            int xs,ys,xe,ye,rx,ry;
            xs = atoi(v[cur + 1].c_str());
            ys = atoi(v[cur + 2].c_str());
            xe = atoi(v[cur + 4].c_str());
            ye = atoi(v[cur + 5].c_str());
            rx = atoi(v[cur + 7].c_str());
            ry = atoi(v[cur + 8].c_str());

            S->board[rx][ry] = 'e';

            vector<pair<int,int> > rempos = getline_ours_gen(make_pair(xs,ys),make_pair(xe,ye),S);

            int i;
            for(i=0;i<rempos.size();i++)
            {
                int x,y;
                x = rempos[i].first;
                y = rempos[i].second;
                S->board[x][y] = 'e';
            }
            //added
            if(S->turn=='b')
                S->RingsRemoved[0]+=1;
            else
                S->RingsRemoved[1]+=1;

            cur = cur + 9;
        }

    }
    if(S->turn=='b')
        S->turn = 'o';
    else
        S->turn = 'b';
}

vector<pair<pair<int,int>,pair<int,int> > > get_comp(GameState S,char tok)
{
   vector<pair<pair<int,int>,pair<int,int> > > res;
   vector<pair<int,int> > vert,d_right,d_left;
   vert = S.table->vertical_gen;
   d_right = S.table->diag_right_gen;
   d_left = S.table->diag_left_gen;
   int i,j,k;
   for(i=0;i<vert.size();i++)
   {
       int x,y ;
       x = vert[i].first;
       y = vert[i].second;
       vector<pair<int,int> > ret = S.table->vertical_map[make_pair(x,y)];
       for(k=0;k<ret.size();k++)
       {
           bool fivepres = true;
           for(int ii = k;ii < (k+S.NumRingsToRemove);ii++) // This for loop checks all elements 
           {
               if (ii>=ret.size())
               {
                fivepres = false;
                break;
               }
               int xi,yi;
               xi = ret[ii].first;
               yi = ret[ii].second;
               if(S.board[xi][yi]!=tok)
               {
                   fivepres = false;
                   break;
               }
           }
           if(fivepres)
                res.push_back(make_pair(ret[k],ret[k+S.NumRingsToRemove-1]));

       }

   }

   for(i=0;i<d_right.size();i++)
   {
       int x,y ;
       x = d_right[i].first;
       y = d_right[i].second;
       vector<pair<int,int> > ret = S.table->diag_right_map[make_pair(x,y)];
       for(k=0;k<ret.size();k++)
       {
           bool fivepres = true;
           for(int ii = k;ii < (k+S.NumRingsToRemove);ii++) // This for loop checks all elements 
           {
               if (ii>=ret.size())
               {
                fivepres = false;
                break;
               }
               int xi,yi;
               xi = ret[ii].first;
               yi = ret[ii].second;
               if(S.board[xi][yi]!=tok)
               {
                   fivepres = false;
                   break;
               }
           }
           if(fivepres)
                res.push_back(make_pair(ret[k],ret[k+S.NumRingsToRemove-1]));

       }

   }


   for(i=0;i<d_left.size();i++)
   {
       int x,y ;
       x = d_left[i].first;
       y = d_left[i].second;
       vector<pair<int,int> > ret = S.table->diag_left_map[make_pair(x,y)];
       for(k=0;k<ret.size();k++)
       {
           bool fivepres = true;
           for(int ii = k;ii < (k+S.NumRingsToRemove);ii++) // This for loop checks all elements 
           {
               if (ii>=ret.size())
               {
                fivepres = false;
                break;
               }
               int xi,yi;
               xi = ret[ii].first;
               yi = ret[ii].second;
               if(S.board[xi][yi]!=tok)
               {
                   fivepres = false;
                   break;
               }
           }
           if(fivepres)
                res.push_back(make_pair(ret[k],ret[k+S.NumRingsToRemove-1]));

       }

   }
   return res; 
}  

void cleaner_in(GameState s, vector<GameState> &topush)
{
    // vector<GameState> res;
    char mytok;
    if (s.turn=='b')
        mytok = 'g';
    else
        mytok = 'p';
    
    vector<pair<pair<int,int>,pair<int,int> > > line_pos;
    line_pos = get_comp(s,mytok);
    if(line_pos.size()==0)
        topush.push_back(s);
    else
    {
        int i,j,k;
        vector<pair<int,int> > ringpos;

        if(s.board[0][0]==s.turn)
            ringpos.push_back(make_pair(0,0));
        for(i=1;i<=s.BoardSize;i++)
        {
            for(j=0;j<6*i;j++)
            {
                if(s.board[i][j]==s.turn)
                {
                    ringpos.push_back(make_pair(i,j));
                }
            }
        }

        for(i=0;i<line_pos.size();i++)
        {
            for(j=0;j<ringpos.size();j++)
            {
                GameState *temp = new GameState(&s);
                temp->LastMove.beg_remr.push_back(ringpos[j]);
                temp->LastMove.beg_rem_first.push_back(line_pos[i].first);
                temp->LastMove.beg_rem_last.push_back(line_pos[i].second);

                vector<pair<int,int> > rempos = getline_ours_gen(line_pos[i].first,line_pos[i].second,temp);

                temp->board[ringpos[j].first][ringpos[j].second] = 'e';

                for(k=0;k<rempos.size();k++)
                {
                    temp->board[rempos[k].first][rempos[k].second] = 'e';
                }

                if(temp->turn=='b')
                    temp->RingsRemoved[0]+=1;
                else
                    temp->RingsRemoved[1]+=1;

                cleaner_in(*temp,topush);
                delete(temp);
                // for(k=0;k<recurse.size();k++)
                //     res.push_back(recurse[k]);

            }
        }

    }
    // return res;
}

void cleaner_out(GameState s, vector<GameState> &topush)
{
    // vector<GameState> res;
    char mytok;
    if (s.turn=='b')
        mytok = 'g';
    else
        mytok = 'p';
    
    vector<pair<pair<int,int>,pair<int,int> > > line_pos;
    line_pos = get_comp(s,mytok);
    if(line_pos.size()==0){
        topush.push_back(s);
	}
    else
    {
        int i,j,k;
        vector<pair<int,int> > ringpos;

        if(s.board[0][0]==s.turn)
            ringpos.push_back(make_pair(0,0));
        for(i=1;i<=s.BoardSize;i++)
        {
            for(j=0;j<6*i;j++)
            {
                if(s.board[i][j]==s.turn)
                {
                    ringpos.push_back(make_pair(i,j));
                }
            }
        }

        for(i=0;i<line_pos.size();i++)
        {
            for(j=0;j<ringpos.size();j++)
            {
                GameState *temp = new GameState(&s);
                temp->LastMove.end_remr.push_back(ringpos[j]);
                temp->LastMove.end_rem_first.push_back(line_pos[i].first);
                temp->LastMove.end_rem_last.push_back(line_pos[i].second);

                vector<pair<int,int> > rempos = getline_ours_gen(line_pos[i].first,line_pos[i].second,temp);

                temp->board[ringpos[j].first][ringpos[j].second] = 'e';

                for(k=0;k<rempos.size();k++)
                {
                    temp->board[rempos[k].first][rempos[k].second] = 'e';
                }
                if(temp->turn=='b')
                    temp->RingsRemoved[0]+=1;
                else
                    temp->RingsRemoved[1]+=1;
                cleaner_out(*temp, topush);
                delete(temp);
                // for(k=0;k<recurse.size();k++)
                //     topush.push_back(recurse[k]);

            }
        }

    }
    // return res;
}

bool GetStartMoves( GameState s, vector<GameState> &topush){
	int i,j;
	int oRings=0,bRings=0;
	if((s.RingsRemoved[0]!=0) || (s.RingsRemoved[1]!=0 )){
		return false;	
	}
	for(i=0;i<s.board.size();i++){
		for(j=0;j<s.board[i].size();j++){
			if(s.board[i][j]=='b'){
				bRings+=1;
			}
			else if(s.board[i][j]=='o'){
				oRings+=1;
			}
		}
	}
	if((bRings==s.RingsInit) && (oRings==s.RingsInit)){
		return false;
	}
	for(i=0;i<s.board.size();i++){
		for(j=0;j<s.board[i].size();j++){
			if(s.board[i][j]=='e'){
                int x,y;
                pair<int,int> other_coord = (s.table)->ours_to_axes[make_pair(i,j)];
                x = other_coord.first;
                y = other_coord.second;

                if(x==0 && (y==s.BoardSize) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;
                if(x==0 && (y==(-1*s.BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;
                if(x==(-1*s.BoardSize) && (y==(-1*s.BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;
                if(x==(s.BoardSize) && (y==(s.BoardSize)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;
                if(x==(-1*s.BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;
                if(x==(s.BoardSize) && (y==(0)) )         // 0,bsz  0,-bsz bsz,0 -bsz,0 bsz,bsz -bsz,-bsz
                    continue;

				GameState another = GameState(s);
				another.LastMove.RingPlaced = make_pair(i,j);
				another.LastMove.movecolour = s.turn;
				another.board[i][j] = s.turn;
				if(another.turn=='b'){
					another.turn ='o';
				}
				else{
					another.turn ='b';
				}
				topush.push_back(another);
			}
			else if((s.board[i][j]!='o')&&(s.board[i][j]!='b')){
				cout<<"error";
			}
		}
	}
    return true;
}
void FinalGetValidMoves(GameState s, vector<GameState> &topush){
    // s.LastMove = new Move('a',make_pair(-1,-1), make_pair(-1,-1));
    s.LastMove = Move();
    if(GetStartMoves(s, topush)){
		return;
	}   
    
    vector<GameState> FirstCleaned;
    cleaner_in(s, FirstCleaned);
    vector<GameState> Middle;
    int i;
    for(i=0;i<FirstCleaned.size();i++){
        FirstCleaned[i].GetValidMoves(Middle);
        // Middle.reserve(Middle.size()+ MiddleValid.size());
        // Middle.insert(Middle.end(),MiddleValid.begin(),MiddleValid.end());
    }
    vector<GameState> Output;
    for(i=0;i<Middle.size();i++){
        cleaner_out(Middle[i],Output);
        // Output.reserve(Output.size()+ OutputValid.size());
        // Output.insert(Output.end(),OutputValid.begin(),OutputValid.end());
    }
    for(i=0;i<Output.size();i++){
        if(Output[i].turn=='b')
            Output[i].turn ='o';
        else
            Output[i].turn ='b';
    }
    for(i=0;i<Output.size();i++){
        topush.push_back(Output[i]);
    }
    // return Output;
}

