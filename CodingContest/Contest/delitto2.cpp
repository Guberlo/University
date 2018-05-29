#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void azzeraMatrice(int[][3]);
void stampaMatrice(int[][3]);
int getWinner(int board[][3]);

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	string line;
	int mat[3][3];
	while (getline(input,line)) {
		//Inizio di un nuovo TASK
		istringstream iss(line);
		int N;
		N=0;
		iss >> N;
		azzeraMatrice(mat);
		int turno=0;
		int punteggio_B = 0;
		int punteggio_C = 0;
		int risultato = 0;
		while (!iss.eof()) {
			string mossa;
			iss >> mossa;

			int x=0, y=0;
			x = (int)mossa.at(1) - 48;
			y = (int)mossa.at(3) - 48;

			if (turno%2==0) // Turno Brancata
				mat[x][y] = 1;
			else // Turno Carcannazzu
				mat[x][y] = 2;

			turno++;
			risultato = getWinner(mat);
			if (risultato == 1) {
				punteggio_B++;
				turno = 0;
				azzeraMatrice(mat);
				risultato = 0;
			}
			if (risultato == 2) {
					punteggio_C++;
					turno = 0;
					azzeraMatrice(mat);
					risultato = 0;

			}
			else if (turno >= 9) {
				turno = 0;
				azzeraMatrice(mat);
				risultato = 0;
			}
		}
		output << punteggio_B <<" " << punteggio_C << endl;

	}

}



void azzeraMatrice(int mat[][3]) {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			mat[i][j] = 0;
		}
	}
}

int getWinner(int board[][3])
  {
  	int rows = 3;
  	int columns = 3;
    int k = 0;
    int h = 0;
    // Verifico se il tris � presente in una riga
    for(int i=0; i<rows; i++)
    {
        for (int j=0; j<columns ; j++)
        {
          if(board[i][j]== 1)
          {
            k++;
            if(k==3){ return 1; }
          }
          else
          {
             if(board[i][j] == 2)
             {
                h++;
                if(h==3){ return 2; }
             }
          }
        }
        k=0;
        h=0;
    }
    // Verifico se il tris � presente in una colonna
    for(int i=0; i<columns; i++)
    {
        for (int j=0; j<rows ; j++)
        {
          if(board[j][i]== 1)
          {
            k++;
            if(k==3){ return 1; }
          }
          else
          {
             if(board[j][i] == 2)
             {
                h++;
                if(h==3){ return 2; }
             }
          }
        }
        k=0;
        h=0;
    }

    // Verifico se il tris � presente in una diagonale
    for(int i=0; i<rows; i++)
    {
        int j = i;
        if(board[i][j]== 1)
        {
            k++;
            if(k==3){ return 1; }
        }
        else
        {
           if(board[i][j] == 2)
           {
              h++;
              if(h==3){ return 2; }
           }
        }
    }
    k=0;
    h=0;
    int j = 2;
    for(int i=0; i<rows; i++)
    {
        if(board[i][j] == 1)
        {
            k++;
            if(k==3){ return 1; }
        }
        else
        {
           if(board[i][j] == 2)
           {
              h++;
              if(h==3){ return 2; }
           }
        }
        j--;
    }
    return 0 ;
  }

void stampaMatrice(int mat[][3]) {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}


}
