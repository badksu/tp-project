#include <iostream>
#include <vector>

#include "ship.h"

class Field {
  static constexpr size_t kFieldSize = 10;
  std::vector<std::vector<int>> field;
  std::vector<Ship> ships;

   public:
  size_t aliveCount;
  Field();
  void placeShip(const Ship& ship);

  void shootInShip(Position pos);
  void shootInEmptyCell(Position pos);

  bool isCellEmpty(Position pos);
  bool isEmptyCellShot(Position pos);
  bool isShipDestroyed(Position pos);
  bool isShipDamaged(Position pos);
};

class OwnField {
  Field* field = nullptr;

  char cellForPrint(Position pos);

   public:
  void setField(Field* fieldToSet);
  Field* getField();
  void placeShip(const Ship& ship);
  void printField();
  size_t getAliveShips();
};

class OpponentsField {
  Field* field = nullptr;

  char cellForPrint(Position pos);

   public:
  void setField(Field* fieldToSet);
  void printField();
  bool shootInCell(Position pos);
};
