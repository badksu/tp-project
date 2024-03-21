#include <iostream>
#include <set>

enum class ShipState { ALIVE, DAMAGED, DESTROYED };
enum class ShipDirection { VERTICAL, HORIZONTAL };

struct Position {
  size_t row;
  size_t column;

  bool operator<(const Position& other) const;
  Position operator+(size_t num);
};

std::istream& operator>>(std::istream& in, Position& pos);

class Ship {
  size_t size;
  Position headPosition;
  std::set<Position> cells;
  ShipDirection direction;
  ShipState state;

   public:
  Ship(size_t size, Position headPosition, bool isVertical);

  size_t getRow() const;
  size_t getColumn() const;
  size_t getSize() const;
  bool isVertical() const;
  void destroyCell(Position pos);
  bool isDestroyed() const;
  bool isDamaged() const;
};

Ship buildShip(size_t size, size_t num);