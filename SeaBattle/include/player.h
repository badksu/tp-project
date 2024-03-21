#include <iostream>
#include <vector>

#include "field.h"

class Player {
  static constexpr size_t kShipsCount[5]{0, 4, 3, 2, 1};

  std::string name;
  OwnField ownField;
  OpponentsField opponentsField;

   public:
  void initSelf(size_t playerNum);
  Ship initShip(size_t size, size_t num);
  Field* getOwnField();
  void setOpponentsField(Field* field);

  void checkOwnField();
  void checkOpponentsField();

  bool shoot();
  bool makeMove();
  size_t getAliveShips();
  std::string getName();
};