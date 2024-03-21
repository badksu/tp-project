#include <iostream>
#include <set>

enum class ShipState { ALIVE, DAMAGED, DESTROYED };
enum class ShipDirection { VERTICAL, HORIZONTAL };

class Position {
private:
  size_t row;
  size_t column;
  static bool is_row_char(char row);
  static bool is_column_char(char row);
public:

  Position(std::string& pos);
  bool operator<(const Position& other) const;
  Position operator+(size_t num);

  size_t getRow() const;
  size_t getColumn() const;
};

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