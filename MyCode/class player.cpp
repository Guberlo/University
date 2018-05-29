#include <iostream>
#include "player.h"

using namespace std;

Player::Player(int hp, int atk, int def, int dex)
{
  this->hp=hp;
  this->atk=atk;
  this->def=def;
  this->dex=dex;
}

void Player::setHp()
{
  cout << "Inserisci HP: ";
  cin >> this->hp;
  cout << endl;
}


void Player::setAtk()
{
  cout << "Inserisci ATK: ";
  cin >> this->atk;
  cout << endl;
}

void Player::setDef()
{
  cout << "Inserisci DEF: ";
  cin >> this->def;
  cout << endl;
}

void Player::setDex()
{
  cout << "Inserisci DEX: ";
  cin >> this->dex;
  cout << endl;
}


int Player::getHp() const
{
  cout << "Hp: " << this->hp << endl;
}

int Player::getAtk() const
{
  cout << "Atk: " << this->atk << endl;
}

int Player::getDef() const
{
  cout << "Def: " << this->def << endl;
}

int Player::getDex() const
{
  cout << "Dex: " << this->dex << endl;
}



Player::Player()
{
  //Empty Constructor//
}

Player::~Player()
{
  //Destructor//
}

int main()
{
  Player p1;
  p1.setHp();
  p1.getHp();

  Player p2(50,30,21,1);
  p2.getHp();
  p2.getAtk();
  p2.getDef();
  p2.getDex();



  return 0;
}
