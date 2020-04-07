#include<iostream>
#include<random>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<time.h>
#define ll long long int
//#define DEBUG
#define rep(number) for(int i=0;i < number;i++)
using namespace std;
int game() {

  random_device rnd;
  vector<int> card_yama(52, 0), card_my, card_enemy;
  rep(52) {
    card_yama[i] = i + 1;
  }
  rep(2) {
    int a = rnd() % card_yama.size();
    card_my.push_back(card_yama[a]);
    card_yama.erase(card_yama.begin() + a);
  }
  rep(2) {
    int a = rnd() % card_yama.size();
    card_enemy.push_back(card_yama[a]);
    card_yama.erase(card_yama.begin() + a);
  }

#ifdef DEBUG
  rep(card_my.size()) {
    cout << card_my[i] << endl;
  }
  rep(card_enemy.size()) {
    cout << card_enemy[i] << endl;
  }
#endif

  int a,enemy_point,my_point;
  bool tr, gameend = false, my_tr, enemy_tr, dontmove = false;
  string input;
  while (true) {
    /////自分の判定/////
    a = 0;
    dontmove = false;
    tr = false;
    rep(card_my.size()) {
      if (card_my[i]%13 == 11 || card_my[i] % 13 == 12 || ((card_my[i]-1) % 13)+1 == 13) {
        a += 10;
      }
      else {
        a += card_my[i]%13;
      }
      if (card_my[i] % 13 == 1) {
        tr = true;
      }
    }
    if (a >= 21) {
      if (a == 21) {
        cout << "BlackJack!!" << endl;
        cout << "You win!!" << endl;
        return 1;
      }
      else {
        cout << "Your card has exceeded 21!" << endl;
        cout << "Your card total :" << a << endl;
        cout << "You lose.." << endl;
        return 2;
      }
    }
    if (tr && a + 10 == 21) {
      cout << "BlackJack!!" << endl;
      cout << "You win!!" << endl;
      return 1;
    }
    my_point = a;
    my_tr = tr;
    /////自分の判定\\\\\

    /////敵の判定/////
    a = 0;
    tr = false;
    rep(card_enemy.size()) {
      if (card_enemy[i] == 11 || card_enemy[i] == 12 || ((card_enemy[i] - 1) % 13) + 1 == 13) {
        a += 10;
      }
      else {
        a += card_enemy[i]%13;
      }
      if (card_enemy[i] % 13 == 1) {
        tr = true;
      }
    }
    if (a >= 21) {
      if (a == 21) {
        cout << "BlackJack!!" << endl;
        cout << "You lose.." << endl;
        return 2;
      }
      else {
        cout << "You Win!" << endl;
        return 1;
      }
    }
    if (tr && a + 10 == 21) {
      cout << "BlackJack!!" << endl;
      cout << "Dealers cards:" << endl;
      rep(card_enemy.size()) {
        cout << ((card_enemy[i] - 1) % 13) + 1 << " ";
      }
      cout << endl;
      cout << "You lose.." << endl;
      return 2;
    }
    enemy_point = a;
    enemy_tr = tr;
    /////敵の判定\\\\\

    /////マイターン/////
    RP:
    cout << "There are your cards." << endl;
    rep(card_my.size()) {
      cout << ((card_my[i] - 1) % 13) + 1 << " ";
    }
    cout << endl;
    cout << "Do you want Hit?([y]or[n]) :";
    cin >> input;
    if (input == "y") {
      a = rnd() % card_yama.size();
      card_my.push_back(card_yama[a]);
      card_yama.erase(card_yama.begin() + a);
    }
    else if (input == "n") {
      if (gameend) {
        cout << "You and the dealer have chosen a stand." << endl;
        if (my_tr && my_point + 10 <= 21)my_point += 10;
        if (enemy_tr && enemy_point + 10 <= 21)enemy_point += 10;
        if (my_point > enemy_point) {

          cout << "You win!!" << endl;
          cout << "There are cards." << endl;
          cout << "My cards:" << endl;
          rep(card_my.size()) {
            cout << ((card_my[i] - 1) % 13) + 1 << " ";
          }
          cout << endl;
          cout << "Enemy cards:" << endl;
          rep(card_enemy.size()) {
            cout << ((card_enemy[i] - 1) % 13) + 1 << " ";
          }
          return 1;
        }
        else if (my_point < enemy_point) {

          cout << "You lose.." << endl;
          cout << "There are cards." << endl;
          cout << "My cards:" << endl;
          rep(card_my.size()) {
            cout << ((card_my[i] - 1) % 13) + 1 << " ";
          }
          cout << endl;
          cout << "Enemy cards:" << endl;
          rep(card_enemy.size()) {
            cout << ((card_enemy[i] - 1) % 13) + 1 << " ";
          }
          return 2;
        }
        else {

          cout << "Draw!" << endl;
          cout << "There are cards." << endl;
          cout << "My cards:" << endl;
          rep(card_my.size()) {
            cout << ((card_my[i] - 1) % 13) + 1 << " ";
          }
          cout << endl;
          cout << "Enemy cards:" << endl;
          rep(card_enemy.size()) {
            cout << ((card_enemy[i] - 1) % 13) + 1 << " ";
          }
          return 3;
        }

      }
    }
    else if (input == "d") {
      dontmove = true;
      cout << "There are cards." << endl;
      cout << "My cards:" << endl;
      rep(card_my.size()) {
        cout << ((card_my[i] - 1) % 13) + 1 << " ";
      }
      cout << endl;
      cout << "Enemy cards:" << endl;
      rep(card_enemy.size()) {
        cout << ((card_enemy[i] - 1) % 13) + 1 << " ";
      }
      cout << endl;
    }
    else
    {
      cout << "Wrong input!!" << endl;
      cout << "Please type [y]or[n]" << endl;
      goto RP;
    }
    /////マイターン\\\\\

    /////敵ターン/////
    if (dontmove)continue;
    if (enemy_point >= 17) {//ディーラーは17点以上だとスタンドしなければならない

      gameend = true;
      cout << "Dealer chose stand" << endl;

    }
    else {//ディーラーは16点以上だとヒットしなければならない

      cout << "Dealer chose Hit" << endl;

      a = rnd() % card_yama.size();
      card_enemy.push_back(card_yama[a]);
      card_yama.erase(card_yama.begin() + a);

    }
  }
  return 0;
}
int main(){
  
  string input;

  cout << "Copyright 2019 NULL_CT All Rights Reserved." << endl;
  cout << " ____  _        _    ____ _  __      _   _    ____ _  __" << endl;
  cout << "| __ )| |      / \\  / ___| |/ /     | | / \\  / ___| |/ /" << endl;
  cout << "|  _ \\| |     / _ \\| |   | ' /   _  | |/ _ \\| |   | ' / " << endl;
  cout << "| |_) | |___ / ___ \\ |___| . \\  | |_| / ___ \\ |___| . \\ " << endl;
  cout << "|____/|_____/_/   \\_\\____|_|\\_\\  \\___/_/   \\_\\____|_|\\_\\ " << endl;
  /*
  
 ____  _        _    ____ _  __      _   _    ____ _  __
| __ )| |      / \  / ___| |/ /     | | / \  / ___| |/ /
|  _ \| |     / _ \| |   | ' /   _  | |/ _ \| |   | ' / 
| |_) | |___ / ___ \ |___| . \  | |_| / ___ \ |___| . \ 
|____/|_____/_/   \_\____|_|\_\  \___/_/   \_\____|_|\_\

  
  */
  while (true) {
    game();
    cout << endl;
    cout << "One more?([y]or[n]) :";
    cin >> input;
    if (input == "y") {
      continue;
    }
    else if (input == "n") {
      cout << "Thank you for playing!!" << endl;
      return 0;
    }
  }
}
