/*
 * Eviatar Natan
 * 307851808
 */
/*
 * Player.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: eviatar
 */

#include "Player.h"
#include <iostream>

Player::Player() {
  disks_num_ = 2;
  my_turn_ = false;
  symbol_ = ' ';
  other_symbol_ = ' ';
}
Player::~Player() {
  // TODO Auto-generated destructor stub
}

