#include "../headers/board.hpp"

#include <fstream>
#include <iostream>
#include <bitset>

namespace RR
{

  /**** Enumerations ****/

  enum struct Direction
  {
    EAST,
    NORTH,
    WEST,
    SOUTH,
    NONE
  };

  enum struct Rotation
  {
    RIGHT,
    LEFT,
    NONE
  };

  /* strongly typed enum manipulation */
  /* https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int */
  template <typename T>
  constexpr auto operator+(T e) noexcept
      -> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
  {
    return static_cast<std::underlying_type_t<T>>(e);
  }

  /**** Location ****/

  Location::Location(int l, int c) : line(l), column(c) {}

  bool Location::operator==(const Location &rhs) const
  {
    return (line == rhs.line) && (column == rhs.column);
  }

  std::size_t LocationHash::operator()(const Location &l) const
  {
    if (sizeof(long long) == 2 * sizeof(int))
    {
      //this supposedly always happens
      long long concat = l.line;
      concat <<= 8 * sizeof(int);
      concat += l.column;
      return std::hash<long long>()(concat);
    }
    else
    {
      //just in case
      std::bitset<16 * sizeof(int)> concat;
      concat |= l.line;
      concat <<= 8 * sizeof(int);
      concat |= l.column;
      return std::hash<std::bitset<16 * sizeof(int)>>()(concat);
    }
  }

  /**** Tile manipulation ****/

  /* Check whether a tile is a fast belt */
  static bool tile_is_fast(
      Board::TileType type)
  {
    return type > Board::TileType::JOIN_EW_TO_S &&
           type < Board::TileType::ROTATE_RIGHT;
  }

  /* Check the direction in which the tiles moves the robot if any */
  static Direction tile_direction(
      Board::TileType type)
  {
    /* rotating tile and regular tiles have no direction */
    if (type > Board::TileType::FAST_JOIN_EW_TO_S)
      return Direction::NONE;

    /* fast belts are ordered the same way as regular belts */
    int base_type = +type % 24;

    /* non rotating belts, enum conversion is straightforward */
    if (base_type < +Board::TileType::TURN_SE)
      return (Direction) + base_type;

    /* conversion table for turns and perpendicular joins */
    static const Direction directions[8] =
        {
            Direction::EAST,
            Direction::WEST,
            Direction::NORTH,
            Direction::NORTH,
            Direction::WEST,
            Direction::EAST,
            Direction::SOUTH,
            Direction::SOUTH};

    /* turns and perpendicular joins */
    if (base_type < +Board::TileType::JOIN_NS_TO_E)
      return directions[(base_type - +Board::TileType::TURN_SE) % 8];

    /* opposite joins, enum conversion is straightforward */
    return (Direction)(base_type - +Board::TileType::JOIN_NS_TO_E);
  }

  static Rotation tile_rotation(
      Board::TileType type,
      Direction direction /* some tiles depend on the incoming direction */
  )
  {
    /* static tiles */
    if (type == Board::TileType::NOTHING)
      return Rotation::NONE;

    /* simple rotating tiles */
    if (type > Board::TileType::FAST_JOIN_EW_TO_S)
      return (Rotation)((+type - +Board::TileType::ROTATE_RIGHT) % 2);

    /* fast belts are ordered the same way as regular belts */
    int base_type = +type % 24;

    /* non rotating belts */
    if (base_type < +Board::TileType::TURN_SE)
      return Rotation::NONE;

    /* simple rotating belts */
    if (base_type < +Board::TileType::JOIN_S_TO_E)
      return (Rotation)((base_type - +Board::TileType::TURN_SE) % 2);

    /* joins depend on the incoming direction */
    if (direction == Direction::NONE)
      return Rotation::NONE;

    /* constraint table for perpendicular joins */
    static const Direction perp_directions[8] =
        {
            Direction::SOUTH,
            Direction::SOUTH,
            Direction::EAST,
            Direction::WEST,
            Direction::NORTH,
            Direction::NORTH,
            Direction::WEST,
            Direction::EAST};

    /* perpendicular joins */
    if (base_type < +Board::TileType::JOIN_NS_TO_E)
    {
      if (direction == perp_directions[base_type - +Board::TileType::JOIN_S_TO_E])
      {
        return (Rotation)(base_type % 2);
      }
      else
      {
        return Rotation::NONE;
      }
    }

    /* opposite joins */
    if ((base_type - +Board::TileType::JOIN_NS_TO_E) % 2 != +direction % 2)
    {
      /* this will be hard to figure in a month */
      /* (five years later) indeed, I'll trust myself on this */
      return (Rotation)((
                            +direction / 2 +
                            +direction % 2 +
                            (base_type - +Board::TileType::JOIN_NS_TO_E) / 2) %
                        2);
    }
    return Rotation::NONE;
  }

  /**** Robot ****/

  std::size_t RobotHash::operator()(const Robot &r) const
  {
    //create a bitset to pack line column and orientation
    std::bitset<16 * sizeof(int) + 8 * sizeof(Robot::Status)> concat;
    //pack the line
    concat |= r.location.line;
    concat <<= 8 * sizeof(int);
    //pack the colum,
    concat |= r.location.column;
    concat <<= 8 * sizeof(Robot::Status);
    //pack the orientation
    concat |= +r.status;
    //hash the bitset using the standard implementation on bitsets
    return std::hash<std::bitset<16 * sizeof(int) + 8 * sizeof(Robot::Status)>>()(concat);
  }

  bool operator!=(const Robot &r1, const Robot &r2)
  {
    return !(r1.location == r2.location) || r1.status != r2.status;
  }

  bool operator==(const Robot &r1, const Robot &r2)
  {
    return r1.location == r2.location && r1.status == r2.status;
  }

  /** String format for status */
  std::string Robot::StatusToString()
  {
    std::string ret;
    switch (status)
    {
    case RR::Robot::Status::EAST:
      ret = "East";
      break;
    case RR::Robot::Status::NORTH:
      ret = "North";
      break;
    case RR::Robot::Status::WEST:
      ret = "West";
      break;
    case RR::Robot::Status::SOUTH:
      ret = "South";
      break;
    case RR::Robot::Status::DEAD:
      ret = "Dead";
      break;
    }
    return ret;
  }

  /** String format for moves */
  std::string MovesToString(Robot::Move move)
  {
    std::string ret;
    switch (move)
    {
    case RR::Robot::Move::BACKWARD_1:
      ret = "1 pas en arrière";
      break;
    case RR::Robot::Move::FORWARD_1:
      ret = "1 pas en avant";
      break;
    case RR::Robot::Move::FORWARD_2:
      ret = "2 pas en avant";
      break;
    case RR::Robot::Move::FORWARD_3:
      ret = "3 pas en avant";
      break;
    case RR::Robot::Move::TURN_LEFT:
      ret = "tourne à gauche";
      break;
    case RR::Robot::Move::TURN_RIGHT:
      ret = "tourne à droite";
      break;
    case RR::Robot::Move::U_TURN:
      ret = "demi-tour";
      break;
    }
    return ret;
  }

  /** Moving **/

  /* move the robot in a direction */
  static void robot_push(
      const Board &board,
      Robot &robot,
      Direction direction)
  {
    /* a dead robot does not move */
    if (robot.status == Robot::Status::DEAD)
      return;

    /* no direction, no chocolate */
    if (direction == Direction::NONE)
      return;

    /* good luck with that */
    /* (five years later) yeah sure */
    robot.location.line += (+direction % 2) * (+direction - 2);
    robot.location.column += ((1 + +direction) % 2) * (1 - +direction);

    /*check that the destination tile exists*/
    if (board.tiles.find(robot.location) == board.tiles.end())
    {
      robot.status = Robot::Status::DEAD;
    }
  }

  /* rotate robot in a direction */
  static void robot_rotate(
      Robot &robot,
      Rotation rotation)
  {
    /* a dead robot does not rotate */
    if (robot.status == Robot::Status::DEAD)
      return;

    /* no rotation, no chocolate */
    if (rotation == Rotation::NONE)
      return;

    /* enum conversion is straightforward */
    if (rotation == Rotation::LEFT)
    {
      robot.status = (Robot::Status)((+robot.status + 1) % 4);
    }
    else
    {
      robot.status = (Robot::Status)((+robot.status + 3) % 4);
    }
  }

  /* apply one board tile to the robot */
  static void robot_apply(
      const Board &board,
      Robot &robot)
  {
    try
    {
      /* find the tile the robot is on, throws if does not exist */
      Board::TileType tile = board.tiles.at(robot.location);

      /* direction of the robot tile */
      Direction dir = tile_direction(tile);

      if (dir == Direction::NONE)
      {
        /* rotate the robot if necessary */
        robot_rotate(robot, tile_rotation(tile, Direction::NONE));
      }

      /* the robot is on a belt, move it */
      robot_push(board, robot, dir);

      /* get the arrival tile, throws if does not exist */
      Board::TileType dest_tile = board.tiles.at(robot.location);

      /* handle the rotation of the destination tile */
      robot_rotate(robot, tile_rotation(dest_tile, (Direction)((+dir + 2) % 4)));
    }
    catch (std::out_of_range &e)
    {
      /* the robot is in the void */
      robot.status = Robot::Status::DEAD;
    }
  }

  /**** Public interface ****/

  /** Construction **/

  Board::Board(
      const std::string &filename)
  {
    /* open board file */
    std::ifstream board_file;
    board_file.exceptions(std::ifstream::badbit);
    board_file.open(filename);

    /* read the board */
    while (true)
    {
      Location spot;
      int type;
      board_file >> spot.line >> spot.column >> type;

      if (!board_file.eof())
      {
        tiles[spot] = (TileType)type;
      }
      else
      {
        break;
      }
    }
  }

  void Board::save(
      const std::string &filename) const
  {
    /* open the file for writing */
    std::ofstream output;
    output.exceptions(std::ofstream::badbit);
    output.open(filename);

    for (std::pair<Location, TileType> tile : tiles)
    {
      output << tile.first.line
             << " " << tile.first.column
             << " " << +tile.second
             << std::endl;
    }
  }

  void Board::json(
      std::ostream &output) const
  {
    /* open the file for writing */
    output << "[";
    bool first = true;
    for (std::pair<Location, TileType> tile : tiles)
    {
      if (!first)
      {
        output << ", ";
      }
      output << "{ "
             << "\"line\" : " << tile.first.line << ","
             << "\"column\" : " << tile.first.column << ","
             << "\"type\" : " << +tile.second
             << " }";
      first = false;
    }
    output << "]";
  }

  /** Robot moving **/

  void Board::play(
      Robot &robot,
      Robot::Move move) const
  {
    /* fast exit for dead robots */
    if (robot.status == Robot::Status::DEAD)
      return;

    /* determine the varying coordinate */
    switch (move)
    {
    case Robot::Move::FORWARD_1:
      robot_push(*this, robot, (Direction)robot.status);
      break;
    case Robot::Move::FORWARD_2:
      robot_push(*this, robot, (Direction)robot.status);
      robot_push(*this, robot, (Direction)robot.status);
      break;
    case Robot::Move::FORWARD_3:
      robot_push(*this, robot, (Direction)robot.status);
      robot_push(*this, robot, (Direction)robot.status);
      robot_push(*this, robot, (Direction)robot.status);
      break;
    case Robot::Move::BACKWARD_1:
      robot_push(*this, robot, (Direction)((+robot.status + 2) % 4));
      break;
    case Robot::Move::TURN_LEFT:
      robot_rotate(robot, Rotation::LEFT);
      break;
    case Robot::Move::TURN_RIGHT:
      robot_rotate(robot, Rotation::RIGHT);
      break;
    case Robot::Move::U_TURN:
      robot_rotate(robot, Rotation::RIGHT);
      robot_rotate(robot, Rotation::RIGHT);
      break;
    }

    try
    {
      /* apply the tile to the robot */
      Board::TileType tile = tiles.at(robot.location);
      robot_apply(*this, robot);
      Board::TileType dest_tile = tiles.at(robot.location);

      /* handle fast belts */
      if (tile_is_fast(tile) && tile_is_fast(dest_tile))
      {
        robot_apply(*this, robot);
      }
    }
    catch (std::out_of_range &e)
    {
      robot.status = Robot::Status::DEAD;
      return;
    }
  }
} //end of namespace RR
