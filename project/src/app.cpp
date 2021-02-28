#include "../headers/board.hpp"
#include "../headers/httplib.hpp"

#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{

  using namespace httplib;
  using namespace RR;

  // a board file must be provided

  if (argc < 2)
  {
    std::cout << "il faut fournir un fichier plateau" << std::endl;
    return 1;
  }

  // loading the board

  Board b(argv[1]);

  //http server

  Server srv;

  //api for interaction

  srv.Get("/board", [b](const Request &req, Response &res) {
    std::stringstream json;
    b.json(json);
    res.set_content(json.str(), "application/json");
  });
  srv.Get("/move", [b](const Request &req, Response &res) {
    if (!req.has_param("line"))
    {
      res.status = 400;
      res.set_content("un paramètre line doit être présent.", "text/plain");
      return;
    }
    if (!req.has_param("column"))
    {
      res.status = 400;
      res.set_content("un paramètre column doit être présent.", "text/plain");
      return;
    }
    if (!req.has_param("state"))
    {
      res.status = 400;
      res.set_content("un paramètre state doit être présent.", "text/plain");
      return;
    }
    if (!req.has_param("move"))
    {
      res.status = 400;
      res.set_content("un paramètre move doit être présent.", "text/plain");
      return;
    }

    int line;
    {
      std::stringstream ss;
      ss << req.get_param_value("line");
      ss >> line;
    }

    int column;
    {
      std::stringstream ss;
      ss << req.get_param_value("column");
      ss >> column;
    }

    int state;
    {
      std::stringstream ss;
      ss << req.get_param_value("state");
      ss >> state;
    }

    int move;
    {
      std::stringstream ss;
      ss << req.get_param_value("move");
      ss >> move;
    }

    Robot r = {{line, column}, (Robot::Status)state};
    b.play(r, (Robot::Move)move);

    std::stringstream json;
    json << "{"
         << " \"line\" : " << r.location.line
         << ", \"column\" : " << r.location.column
         << ", \"state\" : " << (int)r.status
         << " }";

    res.set_content(json.str(), "application/json");
  });

  //serve appdata folder for static files

  auto ret = srv.set_mount_point("/", "./appdata");
  if (!ret)
  {
    std::cout << "données de l'application introuvables" << std::endl;
    return 2;
  }

  //listen on port 8080

  srv.listen("localhost", 8080);

  return 0;
}
