#ifndef ROBORALLY_BOARD_HPP_
#define ROBORALLY_BOARD_HPP_

#include <string>
#include <unordered_map>
#include <bitset>

namespace RR {

/* Location */

/* this is just coordinates, with a hash function to be able to use an unordered
 * map with locations as keys */

struct Location {

  Location(int l, int c) ;
  Location() {}

  bool operator==(const Location& rhs) const ;

  int line ;
  int column ;

} ;

/* hash function for locations */

struct LocationHash {
  std::size_t operator()(const Location& l) const ;
} ;

/* Robot */

struct Robot {

  /* Robot movements */

  enum struct Move {
    FORWARD_1,
    FORWARD_2,
    FORWARD_3,
    BACKWARD_1,
    TURN_LEFT,
    TURN_RIGHT,
    U_TURN
  } ;
  
  /* Robot status (mostly orientation) */
  
  enum struct Status {
    EAST,
    NORTH,
    WEST,
    SOUTH,
    DEAD
  } ;

  /* A robot contains a location an a status */

  Location location ;
  Status status ;
} ;

bool operator<(const Robot& r1, const Robot& r2);

/* Board */

struct Board {

  /* construction from data in a file */
  /* each line of the file is made of three integers : 
   *   - the line of the tile
   *   - the column of the tile
   *   - the type of the tile (see below)
   */
  Board(const std::string& filename) ;
  
  /* backup */
  void save(const std::string& filename) const ;
  void json(std::ostream& output) const ;

  /* move a robot */

  void play(Robot& robot, Robot::Move m) const ;

  /* all the available tiles */
  enum struct TileType {
    /*  0 */  BELT_E,
    /*  1 */  BELT_N,
    /*  2 */  BELT_W,
    /*  3 */  BELT_S,
    /*  4 */  TURN_SE,
    /*  5 */  TURN_SW,
    /*  6 */  TURN_EN,
    /*  7 */  TURN_WN,
    /*  8 */  TURN_NW,
    /*  9 */  TURN_NE,
    /* 10 */  TURN_WS,
    /* 11 */  TURN_ES,
    /* 12 */  JOIN_S_TO_E, 
    /* 13 */  JOIN_S_TO_W, 
    /* 14 */  JOIN_E_TO_N, 
    /* 15 */  JOIN_W_TO_N, 
    /* 16 */  JOIN_N_TO_E, 
    /* 17 */  JOIN_N_TO_W, 
    /* 18 */  JOIN_W_TO_S, 
    /* 19 */  JOIN_E_TO_S, 
    /* 20 */  JOIN_NS_TO_E, 
    /* 21 */  JOIN_EW_TO_N, 
    /* 22 */  JOIN_NS_TO_W, 
    /* 23 */  JOIN_EW_TO_S, 
    /* 24 */  FAST_BELT_E,
    /* 25 */  FAST_BELT_N,
    /* 26 */  FAST_BELT_W,
    /* 27 */  FAST_BELT_S,
    /* 28 */  FAST_TURN_SE,
    /* 29 */  FAST_TURN_SW,
    /* 30 */  FAST_TURN_EN,
    /* 31 */  FAST_TURN_WN,
    /* 32 */  FAST_TURN_NW,
    /* 33 */  FAST_TURN_NE,
    /* 34 */  FAST_TURN_WS,
    /* 35 */  FAST_TURN_ES,
    /* 36 */  FAST_JOIN_S_TO_E, 
    /* 37 */  FAST_JOIN_S_TO_W, 
    /* 38 */  FAST_JOIN_E_TO_N, 
    /* 39 */  FAST_JOIN_W_TO_N, 
    /* 40 */  FAST_JOIN_N_TO_E, 
    /* 41 */  FAST_JOIN_N_TO_W, 
    /* 42 */  FAST_JOIN_W_TO_S, 
    /* 43 */  FAST_JOIN_E_TO_S, 
    /* 44 */  FAST_JOIN_NS_TO_E, 
    /* 45 */  FAST_JOIN_EW_TO_N, 
    /* 46 */  FAST_JOIN_NS_TO_W, 
    /* 47 */  FAST_JOIN_EW_TO_S, 
    /* 48 */  ROTATE_RIGHT, 
    /* 49 */  ROTATE_LEFT, 
    /* 50 */  NOTHING,
    /* 51 */  NONE 
  } ;

  /* the tiles are stored in a hash table */

  std::unordered_map<Location, TileType, LocationHash> tiles ;
} ;

} //end of namespace RR

#endif
