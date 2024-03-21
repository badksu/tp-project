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

bool Position::is_row_char(char row) {
  return '0' <= row && row <= '9';
}
bool Position::is_column_char(char row) {
  return 'A' <= row && row <= 'J';
}

Position::Position(std::string& pos) {
  if (pos.size() != 2 || !is_column_char(pos[0]) || !is_row_char(pos[1])) {
    throw std::invalid_argument("invalid input");
  }
  column = static_cast<int>(pos[0] - 'A');
  row = static_cast<int>(pos[1] - '0');
}

size_t Position::getRow() const { return row; }
size_t Position::getColumn() const { return column; }

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

size_t Ship::getRow() const { return headPosition.getRow(); }

size_t Ship::getColumn() const { return headPosition.getColumn(); }

size_t Ship::getSize() const { return size; }

bool Ship::isVertical() const { return (direction == ShipDirection::VERTICAL); }

void Ship::destroyCell(Position pos) {
  cells.erase(cells.find(pos));
  state = (cells.empty() ? ShipState::DESTROYED : ShipState::DAMAGED);
}

bool Ship::isDestroyed() const { return state == ShipState::DESTROYED; }

bool Ship::isDamaged() const { return state == ShipState::DAMAGED; }