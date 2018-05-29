#include <iostream>

using namespace std;

class VotingMachine{
public:
  void clear();
  void voteDemo();
  void voteRepub();
  void get_totalVote();

private:
  int total_demo=0;
  int total_repub=0;
};

void VotingMachine::voteDemo(){
  total_demo++;
}

void VotingMachine::voteRepub(){
  total_repub++;
}

void VotingMachine::get_totalVote(){
  if(total_demo>total_repub) cout << "Democratics win with "<<total_demo<<" votes";
  else cout << "Republicans win with "<<total_repub<<" votes";
}

int main(){
  VotingMachine obj;
  cout << "Benvenuto nella VotingMachine!"<<endl;
  cout << "Per votare i Democratici inserisci 1, altrimenti 2"<<endl;
  for(int i=0;i<10;i++){
    int n=0;
    cout << "Inserisci il voto: ";
    cin >> n;
    if(n==1) obj.voteDemo();
    else obj.voteRepub();
  }
  obj.get_totalVote();
  return 0;
}
