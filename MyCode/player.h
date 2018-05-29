#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
  Player();

  Player(int hp, int atk, int def, int dex);

  ~Player();

  void setAtk();

  void setDef();

  void setHp();

  void setDex();

  int getAtk() const;

  int getDef() const;

  int getHp() const;

  int getDex() const;

  void fight();


private:
  int hp;
  int atk;
  int def;
  int dex;
  int lvl;

};
#endif
