#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
user definition*/

struct user
{
  char name[20];
  int games = 0;
  int wins = 0;
  int losses = 0;
  int draws = 0;
  int points = 0;
};

  
/*----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
primary function prototypes*/

void Start();
void PVP();
void PVC();
void Ranking();

/*----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
secondary function prototypes*/

void Print_();
bool IsNumber(string str);
void Player_Names(user &player1, user &player2);
void Print_();
void Player1(user player1, string base[6][6], string board[4][7][7]);
void Player2(user player2, string base[6][6], string board[4][7][7]);
void PVP_Result(int status, user &player1, user &player2, string board[4][7][7]); 
int  Check_Finish(string base[6][6]);
void Default_Base(string base [6][6]);
void Default_Board(string board[4][7][7]);
void Base_To_Board(string base[6][6], string board[4][7][7]);
void Print_Board(string board[4][7][7]);
void Computer(string base[6][6], string board[4][7][7]);
void Player(user player, string base[6][6], string board[4][7][7]);
int  Check_Finish(string base[6][6]);
void PVC_Result(int status, user &player, string board[4][7][7]);
void Move(user player, char character, string base[6][6], string board[4][7][7]);
void Rotation(user player, char characterr, string base[6][6], string board[4][7][7]);
void PrintMove(user player, char character, int row, int col, string base[6][6], string board[4][7][7]);
void PrintRotate(user player, char character, int section, string base[6][6], string board[4][7][7]);
void Select_Coor(int row, int col, string board[4][7][7]);
bool Check_Coor(int number);
void Select_Section(int section, string board[4][7][7]);
bool Check_Section(int section);
void Clockwise(int section, string base[6][6]);
void C_Clockwise(int section, string base[6][6]);
void Computer_Move(string base[6][6], string board[4][7][7]);
void Computer_Rotate(string base[6][6], string board[4][7][7]);
int  check_count(int count1, int count2);
int  BaseToBoardCoor(int coordinate);
void Write_To_File(user &player);
void Build_File();
int  Player_Count();
void Read_File(user * players, int player_count);
int  Check_Repeat(user player, user * players, int player_count);
void Update_File(user * players, int player_count);
void app(user player);
void Sort_players(user * players, int player_count);
void Print_Table(user * players, int player_count);

/*----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
primary function definitions*/

int main()
{
  Start();
}

void Start()
{
  string str;
  int num;

  system("cls");

  while(1)
  {
      Print_();
      cout << "Enter 1, 2, 3 or 4" << endl;
      Print_();
      cout << "1-Player VS Player" << endl;
      cout << "2-Player VS Computer" << endl;
      cout << "3-Ranking Table" << endl;
      cout << "4-Exit" << endl;
      Print_();

      getline(cin, str);
      if(str == "")
      {
        system("cls");
        continue;
      }

      if(IsNumber(str))
      {
        num = stoi(str);
        if(num == 1 || num == 2 || num == 3 || num == 4)
        {
          break;
        }

        else
        {
          system("cls");
          Print_();
          cout << "please enter an integer between 1 and 4." << endl;
        }
      }

      else
      {
        system("cls");
        Print_();
        cout << "please enter an integer." << endl;
      }
  }

  system("cls");

  if(num == 1)
  {
    PVP();
  }

  else if(num == 2)
  {
    PVC();
  }

  else if(num == 3)
  {
    Ranking();
  }

  else
  {
    Print_();
    cout << "Have A Good Day!" << endl;
    Print_();
    return;
  }
}

void PVP()
{
  string board[4][7][7];
  string base[6][6];
  user player1, player2;
  int status;

  Player_Names(player1, player2);

  system("cls");

  Default_Board(board);

  Default_Base(base);

  Base_To_Board(base, board);

  do
  {
    Player1(player1, base, board);

    if(Check_Finish(base) != 0)
      break;
      
    Player2(player2, base, board);

  } while (Check_Finish(base) == 0);
  

  status = Check_Finish(base);

  PVP_Result(status, player1, player2, board);   

  Write_To_File(player1);
  Write_To_File(player2); 

  cout << "Return To The Starting Menu? Press \'y\' For Yes And \'n\' For No:" << endl;

  string action;
  do
  {
    getline(cin, action);
  } while (action != "y" && action != "Y" && action != "n" && action != "N");
   
  if(action == "y" || action == "y")
    Start();

  else if(action == "n" || action =="N")
  {
    Print_();
    cout << "Have A Good Day!" << endl;
    Print_();
  }
}

void PVC()
{
  string base[6][6];
  string board[4][7][7];
  int  status;
  user player;
  string str;

  do
  {
      system("cls");
      cout << "Player name: " << endl;
      getline(cin, str);
  } while (str == "");
  


  for(int i = 0; i < str.length(); i++)
  {
      player.name[i] = str[i];
  }

  for(int i = str.length(); i < 20; i++)
  {
      player.name[i] = '\0';
  }

  Default_Base(base);
  Default_Board(board);
  Base_To_Board(base, board);
  
  string turn;
  do
  {
    system("cls");
    cout << "Which Player Do You Want To Be? enter \'1\' For First And \'2\' For Second." << endl;
    getline(cin, turn);
  }while(turn != "1" && turn != "2");
  
  system("cls");


  if(turn == "1")
  {
    do
    {
      Player(player, base, board);
      if(Check_Finish(base) != 0)
        break;

      Computer(base, board);  
    } while (Check_Finish(base) == 0);
  }


  else if(turn == "2")
  {
    do
    {
      Computer(base, board);
      if(Check_Finish(base) != 0)
        break;

      Player(player, base, board);  
    } while (Check_Finish(base) == 0);
  }

  status = Check_Finish(base);

  PVC_Result(status, player, board);

  Write_To_File(player);

  cout << "Return To The Starting Menu? Press \'y\' For Yes And \'n\' For No:" << endl;

  string action;
  do
  {
    getline(cin, action);
  } while (action != "y" && action != "Y" && action != "n" && action != "N");
   
  if(action == "y" || action == "y")
    Start();

  else if(action == "n" || action =="N")
  {
    Print_();
    cout << "Have A Good Day!" << endl;
    Print_();
  } 
}

void Ranking()
{
    Build_File();
    int player_count = Player_Count();

    if(player_count == 0)
    {
        cout << "No Information Available. Press The Enter Button To Return To Main Menu." << endl;

        char action;

            do
            {
                action = getch();
                if(action == '\r')
                    break;
            } while (1);

        Start();
    }

    user * players = new user[player_count];
    Read_File(players, player_count);

    Sort_players(players, player_count);
    Print_Table(players, player_count);
        
    delete[] players;

    cout << endl << endl;

    cout << "Press The Enter Button To Return To Main Menu" << endl;

    char action;

        do
        {
            action = getch();
            if(action == '\r')
                break;
        } while (1);

    Start();

}

/*----------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------
secondary function definitions*/

//getting player names

bool IsNumber(string str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(isdigit(str[i]) == false)
        {
            return false;
        }
    }
    return true;
}

void Player_Names(user &player1, user &player2)
{
    string str;
    do
    {
      system("cls");
      cout << "First Player's name: " << endl;
      getline(cin, str);
    } while (str == "");
    

    int n = str.length();

    for(int i = 0; i < n; i++)
    {
        player1.name[i] = str[i];
    }
    
    for(int i = n; i < 20; i++)
    {
        player1.name[i] = '\0';
    }


    do
    {
      system("cls");
      cout << "Second Player's name: " << endl;
      getline(cin, str);
    } while (str == "");

    n = str.length();
    for(int i = 0; i < n; i++)
    {
        player2.name[i] = str[i];
    }
    
    for(int i = n; i < 20; i++)
    {
        player2.name[i] = '\0';
    }

    system("cls");
}

//playing a turn

void Player1(user player1, string base[6][6], string board[4][7][7])
{
  Move(player1, 'X', base, board);
  Rotation(player1, 'X', base, board);
}

void Player2(user player2, string base[6][6], string board[4][7][7])
{
  Move(player2, 'O', base, board);
  Rotation(player2, 'O', base, board);
}

void Computer(string base[6][6], string board[4][7][7])
{
  Computer_Move(base, board);
  Computer_Rotate(base, board);
}

void Player(user player, string base[6][6], string board[4][7][7])
{
  Move(player, 'X', base, board);
  Rotation(player, 'X', base, board);
}

void Move(user player, char character, string base[6][6], string board[4][7][7])
{
  int row = 0, col = 0;

  Select_Coor(row, col, board);
  cout << player.name << "\' Turn, As " << character << ". Select A Square And Press The Enter button To Place The letter There." << endl;
  Print_Board(board);

  do
  {
    char action = getch(), confirm;
    string s_character(1, character);

    if(action == 'w' || action == 'W')
    {
      row--;
      if(Check_Coor(row))
      {
        PrintMove(player, character, row, col, base, board);
      }

      else
        row++;
    }


    else if(action == 'd' || action == 'D')
    {
      col++;
      if(Check_Coor(col))
      {
        PrintMove(player, character, row, col, base, board);
      }

      else
        col--;
    }


    else if(action == 's' || action == 'S')
    {
      row++;
      if(Check_Coor(row))
      {
        PrintMove(player, character, row, col, base, board);
      }

      else
        row--;
    }


    else if(action == 'a' || action == 'A')
    {
      col--;
      if(Check_Coor(col))
      {
        PrintMove(player, character, row, col, base, board);
      }

      else
        col++;
    }

    else if(action == '\r')
    {
      if(base[row][col] == " ")
      {
        base[row][col] = s_character;
        Base_To_Board(base, board);
        system("cls");
        cout << "Confirm Move: Press enter To Confirm Or \'n\' To Undo." << endl;
        Default_Board(board);
        Print_Board(board);

        do
        {
          confirm = getch();

          if(confirm == '\r')
            break;

          else if(confirm == 'n' || confirm == 'N')
          {
            base[row][col] = " ";
            Base_To_Board(base, board);
            PrintMove(player, character, row, col, base, board);
            break;
          }

        } while (1);
        

      }

      else
        continue;
      
      if(confirm == '\r')
          break;   
    }
  } while (1);

  system("cls");
  Base_To_Board(base, board);
}

void Rotation(user player, char character, string base[6][6], string board[4][7][7])
{
  cout << player.name << "\'s Turn As " << character << ". Select A Section. ";
  cout << "then Press \'r\' To Rotate It Clockwise Or \'l\' To Rotate It Counter Clockwise." << endl;
  int section = 0;

  Select_Section(section, board);
  Print_Board(board);

  do
  {
    char action = getch(), confirm;

    if(action == 'w' || action == 'W')
    {
      section -= 2;
      if(Check_Section(section))
      {
        PrintRotate(player, character, section, base, board);
      }

      else
        section += 2;
    }



    if(action == 's' || action == 's')
    {
      section += 2;
      if(Check_Section(section))
      {
        PrintRotate(player, character, section, base, board);
      }

      else
        section -= 2;
    }



    if(action == 'd' || action == 'D')
    {
      section++;
      if(Check_Section(section))
      {
        PrintRotate(player, character, section, base, board);
      }

      else
        section--;
    }



    if(action == 'a' || action == 'A')
    {
      section--;
      if(Check_Section(section))
      {
        PrintRotate(player, character, section, base, board);
      }

      else
        section++;
    }



    if(action == 'l' || action == 'L')
    {
      system("cls");
      C_Clockwise(section, base);
      Base_To_Board(base, board);
      cout << "Confirm Move: Press enter To Confirm Or \'n\' To Undo." << endl;
      Default_Board(board);
      Print_Board(board);

        do
        {
          confirm = getch();

          if(confirm == '\r')
            break;

          else if(confirm == 'n' || confirm == 'N')
          {
            Clockwise(section, base);
            Base_To_Board(base, board);
            PrintRotate(player, character, section, base, board);
            break;
          }
        } while (1); 
    }



    if(action == 'r' || action == 'R')
    {
      system("cls");
      Clockwise(section, base);
      Base_To_Board(base, board);
      cout << "Confirm Move: Press enter To Confirm Or \'n\' To Undo." << endl;
      Default_Board(board);
      Print_Board(board);

        do
        {
          confirm = getch();

          if(confirm == '\r')
            break;

          else if(confirm == 'n' || confirm == 'N')
          {
            C_Clockwise(section, base);
            Base_To_Board(base, board);
            PrintRotate(player, character, section, base, board);
            break;
          }
        } while (1);

    }

    if(confirm == '\r')
      break;

  } while (1);
  

  system("cls");
  Base_To_Board(base, board);
}

void PrintMove(user player, char character, int row, int col, string base[6][6], string board[4][7][7])
{
  system("cls");
  cout << player.name << "\' Turn, As " << character << ". Select A Square And Press The Enter button To Place The letter There." << endl;
  Default_Board(board);
  Select_Coor(row, col, board);
  Print_Board(board);
}

void PrintRotate(user player, char character, int section, string base[6][6], string board[4][7][7])
{
  system("cls");
  cout << player.name << "\'s Turn As " << character << ". Select A Section. ";
  cout << "then Press \'r\' To Rotate It Clockwise Or \'l\' To Rotate It Counter Clockwise." << endl;
  Default_Board(board);
  Select_Section(section, board);
  Print_Board(board);
}

void Computer_Move(string base[6][6], string board[4][7][7])
{
  srand(time(NULL));

  int row, col;

  do
  {
    row = rand() % 6;
    col = rand() % 6;
  } while (base[row][col] != " ");

  base[row][col] = "O";
  Select_Coor(row, col, board);
  Base_To_Board(base, board);
  cout << "The Computer Selected The Square in Row " << row + 1;
  cout << " And Column " << col + 1 << "." << endl; 
}

void Computer_Rotate(string base[6][6], string board[4][7][7])
{

  srand(time(NULL));  
  int section = rand() % 4;
  int rotate = rand() % 2;

  Select_Section(section, board);

  cout << "And It Rotates The Section " << section + 1;
  if(rotate == 0)
  {
    char enter;
    cout << " Clockwise. Press Enter To Continue" << endl;
    Print_Board(board);
    do
    {
      enter = getch();  
    } while (enter != '\r');
    
    Clockwise(section, base);
    Base_To_Board(base, board);
    Default_Board(board);
  }

  else
  {
    char enter;
    cout << " Counter Clockwise. Press Enter To Continue" << endl;
    Print_Board(board);
    do
    {
      enter = getch();  
    } while (enter != '\r');
    
    C_Clockwise(section, base);
    Base_To_Board(base, board);
    Default_Board(board);
  }

  system("cls");
}

//finding & showing the result

int Check_Finish(string base[6][6])
{
  //function prototypes
  int  Check_Hor(string base[6][6], string character);
  int  Check_Ver(string base[6][6], string character);
  int  Check_Diag(string base[6][6], string character);
  bool Full(string base[6][6]);

  int hor1 = Check_Hor(base, "X");
  int hor2 = Check_Hor(base, "O");

  int ver1 = Check_Ver(base, "X");
  int ver2 = Check_Ver(base, "O");

  int diag1 = Check_Diag(base, "X");
  int diag2 = Check_Diag(base, "O");

  if((hor1 == 1 || ver1 == 1 || diag1 == 1) && (hor2 == 0 && ver2 == 0 && diag2 == 0))
  {
    return 1;
  }

  else if((hor2 == 1 || ver2 == 1 || diag2 == 1) && (hor1 == 0 && ver1 == 0 && diag1 == 0))
  {
    return 2;
  }

  else if((hor1 == 1 || ver1 == 1 || diag1 == 1) && (hor2 == 1 || ver2 == 1 || diag2 == 1))
  {
    return 3;
  }

  else if(Full(base))
  {
    return 3;
  }

  return 0;
}

int Check_Hor(string base[6][6], string character)
{
  int count = 0;

  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(base[i][j] == base[i][j + 1] && base[i][j] == character)
      {
        count++;
      }
    }
    if(count == 4)
    {
      return 1;
    }

    count = 0;
  }


  for(int i = 0; i < 6; i++)
  {
    for(int j = 1; j < 5; j++)
    {
      if(base[i][j] == base[i][j + 1] && base[i][j] == character)
      {
        count++;
      }
    }

    if(count == 4)
    {
      return 1;
    }

    count = 0;
  }

  return 0;
}

int Check_Ver(string base[6][6], string character)
{

  int count = 0, a;

    for(int j = 0; j < 6; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            if(base[i][j] == base[i + 1][j] && base[i][j] == character)
                count++;
        }

        if(count == 4)
        {
          return 1;
        }
        count = 0;            
    }


    for(int j = 0; j < 6; j++)
    {
        for(int i = 1; i < 5; i++)
        {
            if(base[i][j] == base[i + 1][j] && base[i][j] == character)
                count++;
        }

        if(count == 4)
        {
          return 1;
        }
        count = 0;           
    }

    return 0;
}

int Check_Diag(string base[6][6], string character)
{
    int count = 0;

    for(int i = 0; i < 4; i++)
    {
        if(base[i][i] == base[i + 1][i + 1] && base[i][i] == character)
            count++;   
    }    

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 1; i < 5; i++)
    {
        if(base[i][i] == base[i + 1][i + 1] && base[i][i] == character)
            count++; 
    }         

    if(count == 4)
    {
      return 1;
    }



    count = 0;    

    for(int i = 1; i < 5; i++)
    {
        if(base[i][i - 1] == base[i + 1][i] && base[i][i - 1] == character)
            count++;
    }   

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 0; i < 4; i++)
    {
        if(base[i][i + 1] == base[i + 1][i + 2] && base[i][i + 1] == character)
            count++;
    }        

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 0; i < 4; i++)
    {
        if(base[i][5 - i] == base[i + 1][4 - i] && base[i][5 - i] == character)
            count++;  
    }   

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 1; i < 5; i++)
    {
        if(base[i][5 - i] == base[i + 1][4 - i] && base[i][5 - i] == character)
            count++;    
    }    

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 0; i < 4; i++)
    {
        if(base[i][4 - i] == base[i + 1][3 - i] && base[i][4 - i] == character)
            count++;  
    }    

    if(count == 4)
    {
      return 1;
    }



    count = 0;

    for(int i = 1; i < 5; i++)
    {
        if(base[i][6 - i] == base[i + 1][5 - i] && base[i][6 - i] == character)
            count++;   
    }    

    if(count == 4)
    {
      return 1;
    }

    return 0;  
}

bool Full(string base[6][6])
{
  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 6; j++)
    {
      if(base[i][j] == " ")
        return false;
    }
  }

  return true;
}

void PVP_Result(int status, user &player1, user &player2, string board[4][7][7])
{
  if(status == 1)
  {
    Print_();
    cout << player1.name << " Won! " << endl;
    Print_Board(board);
    Print_();

    player1.games++;
    player2.games++;
    player1.wins++;
    player2.losses++;
    player1.points += 3;
  }


  else if(status == 2)
  {
    Print_();
    cout << player2.name << " Won! " << endl;
    Print_Board(board);
    Print_();

    player1.games++;
    player2.games++;
    player2.wins++;
    player1.losses++;
    player2.points += 3;
  }


  else if(status == 3)
  {
    Print_();
    cout << player1.name << " and " << player2.name << " drew! " << endl;
    Print_Board(board); 
    Print_();

    player1.games++;
    player2.games++;
    player1.points++;
    player2.points++;
    player1.draws++;
    player2.draws++;
  }
}

void PVC_Result(int status, user &player, string board[4][7][7])
{
  if(status == 1)
  {
    Print_();
    cout << player.name << " Won, Well Done! " << endl;
    Print_Board(board);
    Print_();

    player.games++;
    player.wins++;
    player.points += 3;
  }


  else if(status == 2)
  {
    Print_();
    cout << player.name << " Lost, Better Luck Next Time!" << endl;
    Print_Board(board);
    Print_();   
    player.games++;
    player.losses++;
  }


  else if(status == 3)
  {
    Print_();
    cout << player.name << " Drew, GG!" << endl;
    Print_Board(board);
    Print_();
    player.games++;
    player.draws++;
    player.points++;
  }
}


//changing the base and the board

void Default_Base(string base [6][6])
{
  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 6; j++)
    {
      base[i][j] = " ";
    }
  }
}

void Default_Board(string board[4][7][7])
{
    for(int section = 0; section < 4; section++)
    {
        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(i == 0 && j == 0)
                    board[section][i][j] = "\u250F";

                else if(i == 0 && j == 6)
                    board[section][i][j] = "\u2513";  

                else if(i == 0 && (j == 2 || j == 4))
                    board[section][i][j] = "\u2533";   

                else if((i == 2 || i == 4) && j == 0)
                    board[section][i][j] = "\u2523";

                else if((i == 2 || i == 4) && j == 6)
                    board[section][i][j] = "\u252B";

                else if(i == 6 && j == 0)
                    board[section][i][j] = "\u2517";

                else if(i == 6 && j == 6)
                    board[section][i][j] = "\u251B"; 

                else if(i == 6 && (j == 2 || j == 4))
                    board[section][i][j] = "\u253B";      

                else if((i == 2 || i == 4) && (j == 2 || j == 4))
                    board[section][i][j] = "\u254B";

                else if(i % 2 == 0 && j % 2 == 1)
                    board[section][i][j] = "\u2501";         

                else if(i % 2 == 1 && j % 2 == 0)
                    board[section][i][j] = "\u2503";            
            }
        }
    }
}

void Base_To_Board(string base[6][6], string board[4][7][7])
{
    int section = 0;

    for(int board_row = 1, base_row = 0; board_row < 7, base_row < 3; board_row += 2, base_row++)
    {
        for(int board_col = 1, base_col = 0; board_col < 7, base_col < 3; board_col += 2, base_col++)
        {
            board[section][board_row][board_col] = base[base_row][base_col];
        }
    }

    section++;

    for(int board_row = 1, base_row = 0; board_row < 7, base_row < 3; board_row += 2, base_row++)
    {
        for(int board_col = 1, base_col = 3; board_col < 7, base_col < 6; board_col += 2, base_col++)
        {
            board[section][board_row][board_col] = base[base_row][base_col];
        }
    }

    section++;

    for(int board_row = 1, base_row = 3; board_row < 7, base_row < 6; board_row += 2, base_row++)
    {
        for(int board_col = 1, base_col = 0; board_col < 7, base_col < 3; board_col += 2, base_col++)
        {
            board[section][board_row][board_col] = base[base_row][base_col];
        }
    }

    section++;

    for(int board_row = 1, base_row = 3; board_row < 7, base_row < 6; board_row += 2, base_row++)
    {
        for(int board_col = 1, base_col = 3; board_col < 7, base_col < 6; board_col += 2, base_col++)
        {
            board[section][board_row][board_col] = base[base_row][base_col];
        }
    }
}

void Print_Board(string board[4][7][7])
{
    for(int section = 0; section < 4; section += 2)
    {
        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                cout << board[section][i][j];
            }

            for(int j = 0; j < 7; j++)
            {
                cout << board[section + 1][i][j];
            }
            cout << endl;;
        }
    }
}

void Select_Coor(int base_row, int base_col, string board[4][7][7])
{
  int section, section_row, section_col;

    if(base_row < 3)
    {
        if(base_col < 3)
            section = 0;

        else
            section = 1;    
    }

    else
    {
        if(base_col < 3)
            section = 2;

        else
            section = 3;    
    }


    section_row = BaseToBoardCoor(base_row);
    section_col = BaseToBoardCoor(base_col);

    board[section][section_row - 1][section_col - 1] = "\u2554";
    board[section][section_row - 1][section_col] = "\u2550";   
    board[section][section_row - 1][section_col + 1] = "\u2557";

    board[section][section_row][section_col - 1] = "\u2551";
    board[section][section_row][section_col + 1] = "\u2551";

    board[section][section_row + 1][section_col - 1] = "\u255A";
    board[section][section_row + 1][section_col] = "\u2550";
    board[section][section_row + 1][section_col + 1] = "\u255D";
}

bool Check_Coor(int number)
{
  if(number < 0 || number > 5)
    return false;

  return true;
}

void Select_Section(int section, string board[4][7][7])
{
    if(section < 0 || section > 3)
      return;

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(i == 0 && j == 0)
                board[section][i][j] = "\u2554";

            else if(i == 0 && j == 6)
                board[section][i][j] = "\u2557";

            else if(i == 6 && j == 0)
                board[section][i][j] = "\u255A";

            else if(i == 6 && j == 6)
                board[section][i][j] = "\u255D";

            else if((i != 0 && i != 6) && (j == 0 || j == 6))
                board[section][i][j] = "\u2551";

            else if((i == 0 || i == 6) && (j != 0 && j != 6))
                board[section][i][j] = "\u2550";                    
        }
    }
}

bool Check_Section(int section)
{
    if(section < 0 || section > 3)
      return false;

    return true;
}

void Clockwise(int section, string base[6][6])
{
    string temp1[3][3];
    string temp2[3][3];

//initialization

    if(section == 0)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 1)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 2)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 3)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

//rotation

    for(int i1 = 0, j2 = 2; i1 < 3, j2 > -1; i1++, j2--)
    {
      for(int j1 = 0, i2 = 0; j1 < 3, i2 < 3; j1++, i2++)
      {
        temp2[i2][j2] = temp1[i1][j1];
      }
    }

//changing base

    if(section == 0)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 1)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 2)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 3)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }
}

void C_Clockwise(int section, string base[6][6])
{
    string temp1[3][3];
    string temp2[3][3];

//initialization

    if(section == 0)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 1)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 2)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

    else if(section == 3)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                temp1[temp_row][temp_col] = base[base_row][base_col];
            }
        }
    }

//rotation

  for(int i1 = 0, j2 = 0; i1 < 3, j2 < 3; i1++, j2++)
  {
    for(int j1 = 0, i2 = 2; j1 < 3, i2 > -1; j1++, i2--)
    {
      temp2[i2][j2] = temp1[i1][j1];
    }
  }
    

//changing base

    if(section == 0)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 1)
    {
        for(int temp_row = 0, base_row = 0; temp_row < 3, base_row < 3; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 2)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 0; temp_col < 3, base_col < 3; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

    else if(section == 3)
    {
        for(int temp_row = 0, base_row = 3; temp_row < 3, base_row < 6; temp_row++, base_row++)
        {
            for(int temp_col = 0, base_col = 3; temp_col < 3, base_col < 6; temp_col++, base_col++)
            {
                base[base_row][base_col] = temp2[temp_row][temp_col];
            }
        }
    }

}

int BaseToBoardCoor(int coordinate)
{
    int result;

    if(coordinate == 0)
        result = 1;

    else if(coordinate == 1)
        result = 3;

    else if(coordinate == 2)
        result = 5;

    else if(coordinate == 3)
        result = 1;

    else if(coordinate == 4)
        result = 3;

    else if(coordinate == 5)
        result = 5;

    return result;
}

//storing player information in a file

void Write_To_File(user &player)
{
    Build_File();

    int player_count = Player_Count();
    
    user * players = new user [player_count];

    Read_File(players, player_count);

    int index = Check_Repeat(player, players, player_count);

    if(index >= 0)
    {
        players[index].games += player.games;
        players[index].wins += player.wins;
        players[index].losses += player.losses;
        players[index].draws += player.draws;
        players[index].points += player.points;
        Update_File(players, player_count);
    }
    
    else
    {
        app(player);
    }

    delete [] players;
}

void Build_File() 
{
    ifstream iFile("data.dat" , ios :: binary); // iFile = File in
    
    if(!iFile) 
    {
        iFile.close();
        ofstream oFile("data.dat" , ios :: binary); // oFile = File out

        if(!oFile) 
        {
            system("cls");
            cout << "Error: Could Not Open The File. Press Enter To Return To Main Menu." << endl;
            char action;
            do
            {
                action = getch();
                if(action == '\r')
                    break;
            } while (1);

            Start();   
        }

        oFile.close();
    }

    iFile.close();
}

int  Player_Count()
{
    int i = 0;
    char c;

    ifstream iFile("data.dat" , ios :: binary); // iFile = File in
    
    if(!iFile) 
    {
        cout << "Error: Could Not Open The File. Press Enter To Return To Main Menu." << endl;
        char action;
        do
        {
            action = getch();
            if(action == '\r')
                break;
        } while (1);

        Start();
    }

    while(1) 
    {
        iFile.get(c);
        if(iFile.eof()) 
        {
            break;
        }
        i++;
    }

    iFile.close();
    i /= sizeof(user);
    return i;
}

void Read_File(user * players, int player_count)
{
    ifstream iFile("data.dat" , ios :: binary); // iFile = File in
    
    if(!iFile) 
    {
        cout << "Error: Could Not Open The File. Press Enter To Return To Main Menu." << endl;
        char action;
        do
        {
            action = getch();
            if(action == '\r')
                break;
        } while (1);

        Start();
    }    
    
    int j = 0;
    while(j != player_count) 
    {
        iFile.read((char *)&players[j], sizeof(user));
        j++;
    }
    iFile.close();
}

int  Check_Repeat(user player, user * players, int player_count)
{
    for(int i = 0; i < player_count; i++)
    {
        if(strcmp(player.name, players[i].name) == 0)
        {
            return i;
        }
    }

    return -1;
}

void Update_File(user * players, int player_count) 
{
    ofstream oFile("data.dat", ios::binary | ios::out);

    if(!oFile) 
    {
        cout << "Error: Could Not Open The File. Press Enter To Return To Main Menu." << endl;
        char action;
        do
        {
            action = getch();
            if(action == '\r')
                break;
        } while (1);

        Start();   
    }

    for(int i = 0; i < player_count; i++) 
    {
        oFile.write((char*)&players[i], sizeof(user));
    }
    oFile.close();
}

void app(user player)
{
    ofstream oFile("data.dat" , ios::binary | ios::app); // OFile = output file
    
    if(!oFile)
     {
        cout << "Error: Could Not Open The File. Press Enter To Return To Main Menu." << endl;
        char action;
        do
        {
            action = getch();
            if(action == '\r')
                break;
        } while (1);

        Start();
    }  
    oFile.write((char*)& player, sizeof(user));
    oFile.close();
}

void Sort_players(user * players, int player_count)
{
    for(int i = 0; i < player_count - 1; i++)
    {
        for(int j = 0; j < player_count - i - 1; j++)
        {
            if(players[j].points < players[j + 1].points)
            {
                user temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }

            else if(players[j].points == players[j + 1].points)
            {
                if(players[j].wins < players[j + 1].wins)
                {
                    user temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }

                else if(players[j].wins == players[j + 1].wins)
                {
                    if(players[j].games > players[j + 1].games)
                    {
                        user temp = players[j];
                        players[j] = players[j + 1];
                        players[j + 1] = temp;
                    }
                }
            }
        }
    }
}

void Print_Table(user * players, int player_count)
{
    cout << setw(21) << left << "Name" << setw(12) << left << "Games" << setw(8) << left << "Wins"
         << setw(8)  << left << "Losses" << setw(8)  << left <<  "Draws" << setw(8) << left << "Points" << endl;

    Print_();     

    for(int i = 0; i < player_count; i++)
    {
        cout << setw(21) << left << players[i].name <<  setw(12) << left << players[i].games << setw(8) << left << players[i].wins 
             << setw(8)  << left << players[i].losses << setw(8)  << left << players[i].draws << setw(8) << left << players[i].points << endl;

        Print_();      
    }     
}

//printing dashes

void Print_()
{
  for(int i = 0; i < 100; i++)
  {
     cout << "-";
  }
  cout << endl;
}
