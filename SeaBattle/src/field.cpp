#include "field.h"

#include <iostream>
#include <vector>

Field::Field():field(kFieldSize, std::vector<int>(kFieldSize, -1)), aliveCount(0) {}

void Field::placeShip(const Ship& ship) {
  bool isVertical = ship.isVertical();
  size_t row = ship.getRow();
  size_t column = ship.getColumn();
  size_t size = ship.getSize();
  size_t rowSize = row + size * isVertical + !(isVertical);
  size_t columnSize = column + size * !(isVertical) + isVertical;

  int shipNum = ships.size();

  for (size_t i = row; i < rowSize; ++i) {
    for (size_t j = column; j < columnSize; ++j) {
      field[i][j] = shipNum;
    }
  }
  ships.push_back(ship);
  ++aliveCount;
}

void Field::shootInShip(Position pos) {
  size_t shipNum = field[pos.row][pos.column];
  ships[shipNum].destroyCell(pos);
  if (ships[shipNum].isDestroyed()) {
    --aliveCount;
  }
}

void Field::shootInEmptyCell(Position pos) { field[pos.row][pos.column] = -2; }

bool Field::isCellEmpty(Position pos) { return field[pos.row][pos.column] < 0; }

bool Field::isEmptyCellShot(Position pos) {
  return field[pos.row][pos.column] == -2;
}

bool Field::isShipDestroyed(Position pos) {
  size_t shipNum = field[pos.row][pos.column];
  return ships[shipNum].isDestroyed();
}

bool Field::isShipDamaged(Position pos) {
  size_t shipNum = field[pos.row][pos.column];
  return ships[shipNum].isDamaged();
}

char OwnField::cellForPrint(Position pos) {
  return (field->isCellEmpty(pos)
              ? (field->isEmptyCellShot(pos) ? '+' : ' ')
              : (field->isShipDestroyed(pos)
                     ? '#'
                     : (field->isShipDestroyed(pos) ? 'X' : 'O')));
}

void OwnField::setField(Field* fieldToSet) { field = fieldToSet; }

Field* OwnField::getField() { return field; }

void OwnField::placeShip(const Ship& ship) { field->placeShip(ship); }

void OwnField::printField() {
  std::cout << "    ";
  for (int i = 0; i < 10; ++i) std::cout << char('A' + i) << "  ";
  std::cout << std::endl;
  for (size_t i = 0; i < 10; ++i) {
    std::cout << i + 1 << (i < 9 ? "  " : " ");
    for (size_t j = 0; j < 10; ++j) {
      std::cout << "[" << cellForPrint({i, j}) << "]";
    }
    std::cout << std::endl;
  }
}

size_t OwnField::getAliveShips() { return field->aliveCount; }

char OpponentsField::cellForPrint(Position pos) {
  return (field->isCellEmpty(pos)
              ? (field->isEmptyCellShot(pos) ? '+' : ' ')
              : (field->isShipDestroyed(pos)
                     ? '#'
                     : (field->isShipDamaged(pos) ? 'X' : ' ')));
}

void OpponentsField::setField(Field* fieldToSet) { field = fieldToSet; }

void OpponentsField::printField() {
  std::cout << "    ";
  for (int i = 0; i < 10; ++i) std::cout << char('A' + i) << "  ";
  std::cout << std::endl;
  for (size_t i = 0; i < 10; ++i) {
    std::cout << i + 1 << (i < 9 ? "  " : " ");
    for (size_t j = 0; j < 10; ++j) {
      std::cout << "[" << cellForPrint({i, j}) << "]";
    }
    std::cout << std::endl;
  }
}

bool OpponentsField::shootInCell(Position pos) {
  if (field->isCellEmpty(pos)) {
    field->shootInEmptyCell(pos);
    std::cout << "Miss" << std::endl;
    return false;
  }
  field->shootInShip(pos);
  std::cout << (field->isShipDestroyed(pos) ? "Destroyed" : "Damaged")
            << std::endl;
  return true;
}