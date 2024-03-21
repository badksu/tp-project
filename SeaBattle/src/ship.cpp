#include <iostream>

#include "player.h"

bool Position::operator<(const Position& other) const {
  return (row == other.row ? column < other.column : row < other.row);
}

Position Position::operator+(size_t num) {
  Position result = *this;
  result.row += num / 10;
  result.column += num % 10;
  return result;
}

std::istream& operator>>(std::istream& in, Position& pos) {
  std::string input;
  in >> input;
  pos.column = static_cast<size_t>(input[0] - 'A');
  pos.row = static_cast<size_t>(input[1] - '1');
  /*
   * later it will be safe of wrong-format input
   */
  return in;
}

Ship::Ship(size_t size, Position headPosition, bool isVertical)
    : size(size),
      headPosition(headPosition),
      direction(
          (isVertical ? ShipDirection::VERTICAL : ShipDirection::HORIZONTAL)),
      state(ShipState::ALIVE) {
  for (size_t i = 0; i < size; ++i) {
    size_t add = i * 10 * isVertical + i * !(isVertical);
    cells.insert(headPosition + add);
  }
}

size_t Ship::getRow() const { return headPosition.row; }

size_t Ship::getColumn() const { return headPosition.column; }

size_t Ship::getSize() const { return size; }

bool Ship::isVertical() const { return (direction == ShipDirection::VERTICAL); }

void Ship::destroyCell(Position pos) {
  cells.erase(cells.find(pos));
  state = (cells.empty() ? ShipState::DESTROYED : ShipState::DAMAGED);
}

bool Ship::isDestroyed() const { return state == ShipState::DESTROYED; }

bool Ship::isDamaged() const { return state == ShipState::DAMAGED; }