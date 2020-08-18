#include<bits/stdc++.h>
using namespace std;




class TrieNode
{
  public:
    bool endOfWord;
    unordered_map<char,TrieNode*> children;

    TrieNode()
    {
        endOfWord=false;
    }

    void insert(string word)
    {
        TrieNode *temp=this;
        for(char c:word)
        {
            if(temp->children.find(c)==temp->children.end())
                temp->children[c]=new TrieNode();
            temp=temp->children[c];
        }
        temp->endOfWord=true;
    }

    bool startsWith(string word)
    {
        TrieNode *temp=this;
        for(char c:word)
        {
            if(temp->children.find(c)==temp->children.end())
                return false;
            temp=temp->children[c];
        }
        return true;
    }
};




class Solution
{
public:

    int rows,col;


    void dfs(TrieNode *temp,vector<vector<char>> &board,vector< vector<bool>> &visited ,int i,int j,unordered_set<string> &res,string word)
    {

        if(i<0 || i>=rows || j<0 || j>=col || visited[i][j])
            return;

        word+=board[i][j];

        if(temp->children.find(board[i][j])==temp->children.end())
            return;
        temp=temp->children[board[i][j]];

        if(temp->endOfWord==true  )
        {
            res.insert(word);
        }



        visited[i][j]=true;

        dfs(temp,board,visited,i+1,j,res,word);
        dfs(temp,board,visited,i-1,j,res,word);
        dfs(temp,board,visited,i,j+1,res,word);
        dfs(temp,board,visited,i,j-1,res,word);

        visited[i][j]=false;
    }


    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        TrieNode *Trie=new TrieNode();

        for(string s:words)
        {
           Trie->insert(s);
        }




         rows=board.size();
         col=rows>0? board[0].size():0;

        if(rows==0)
            return {};

        int i,j;
        unordered_set<string> res;
        vector< vector<bool>> visited(rows,vector<bool>(col,false));
        vector<string> ans;

        for(i=0;i<rows;i++)
        {
            for(j=0;j<col;j++)
            {
                    dfs(Trie,board,visited,i,j,res,"");
            }
        }

        for(string s:res)
            ans.push_back(s);

        return ans;

    }
};


void showInstructions()
{
    cout<<endl<<endl;
    cout<<"Instructions"<<endl;
    cout<<"In this game given a 2D Board of characters, we will ask user for the words he/she wants to find ."<<endl;
    cout<<"This program will return all the words of the user that are present in the board ."<<endl;
    cout<<"Also 2 characters are adjacent in the board if they are horizontal or vertical ."<<endl;
}




int main()
{

cout<<"BOGGLE GAME"<<endl;
cout<<"-----------";

showInstructions();

 vector< vector<char> > board;
 board.push_back({'o','a','a','n','a'});
 board.push_back({'e','t','a','e','l'});
 board.push_back({'i','h','k','r','m'});
 board.push_back({'i','e','l','v','s'});
 board.push_back({'j','e','t','c','s'});

 //   we can also modify board


 cout<<endl<<endl;

 for(int i=0;i<board.size();i++)
 {
     for(int j=0;j<board[i].size();j++)
       {
           cout<<board[i][j]<<",";
       }
       cout<<endl;
 }

 cout<<"Enter the number of words you want to search in the board:";
 int num;
 cin>>num;
  vector<string> words(num);
  cout<<endl<<"Enter the words you want to search :";
  string word;
  for(int i=0;i<num;i++)
  {
      cin>>word;
      words.push_back(word);
  }

  vector<string> res;
  Solution s;
  res=s.findWords(board,words);

  int size=res.size();
  if(size==0)
    cout<<endl<<"Sorry no words of your list are present in the board !!!"<<endl;
  else
   {
       cout<<endl<<"The words of your list that are present in the board are:"<<endl;
       for(int i=0;i<size;i++)
         cout<<res[i]<<"  ";
   }





return 0;
}