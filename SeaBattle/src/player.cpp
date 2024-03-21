#include "player.h"

#include <iostream>
#include <vector>

void Player::initSelf(size_t playerNum) {
  std::cout << "Player number " << playerNum << " input your name" << std::endl;
  std::cin >> name;

  ownField.setField(new Field);

  for (size_t size = 1; size < 5; ++size) {
    for (size_t num = 1; num <= kShipsCount[size]; ++num) {
      Ship newShip = initShip(size, num);
      ownField.placeShip(newShip);
    }
  }
}

Ship Player::initShip(size_t size, size_t num) {
  std::cout << "Placing " << num
            << (num == 1   ? "st"
                : num == 2 ? "nd"
                           : "th")
            << " ship of size " << size << std::endl;
  std::cout << "Input direction (1 - vertical, 0 - horizontal)" << std::endl;
  bool direction;
  std::cin >> direction;
  std::cout << "Input position (format - C1)" << std::endl;
  std::string pos;
  std::cin >> pos;
  /*
   * there checking if input pos is correct
   */
  return {size, pos, direction};
}

Field* Player::getOwnField() { return ownField.getField(); }

void Player::setOpponentsField(Field* field) { opponentsField.setField(field); }

void Player::checkOwnField() { ownField.printField(); }

void Player::checkOpponentsField() { opponentsField.printField(); }

bool Player::shoot() {
  std::cout << "Input position for shoot" << std::endl;
  Position pos;
  std::cin >> pos;
  return opponentsField.shootInCell(pos);
}

bool Player::makeMove() {
  std::cout << "Player " << name << " is moving" << std::endl;
  while (true) {
    std::cout << "Input your command" << std::endl;
    std::cout
        << "(0 - check own field, 1 - check opponents field, 2 - make shoot)"
        << std::endl;
    size_t command;
    std::cin >> command;
    if (command == 0) {
      checkOwnField();
    } else if (command == 1) {
      checkOpponentsField();
    } else {
      break;
    }
  }

  return shoot();
}

size_t Player::getAliveShips() { return ownField.getAliveShips(); }

std::string Player::getName() { return name; }