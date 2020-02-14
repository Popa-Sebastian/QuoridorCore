#include "PluginManager.h"
#include "GameController.h"

#include "ConsoleApp.h"
#include "ConsolePlayer.h"

#include <iostream>
#include <iomanip>

typedef const qcli::ConsoleApp::CliArgs& qarg;

qcore::GameController GC;

void PrintAsciiGameBoard()
{
   qcore::BoardMap map;
   GC.getBoardState()->createBoardMap(map, 0);

   std::cout << "\n";

   for (int i = 0; i < qcore::BOARD_SIZE; ++i)
   {
      std::cout << std::setfill(' ') << std::setw(6) << i;
   }

   std::cout << "\n   0 \u2554";

   for (int i = 0; i < qcore::BOARD_SIZE * 6 - 1; ++i)
   {
      std::cout << "\u2550";
   }

   std::cout << "\u2557\n";

   for (int i = 0; i < qcore::BOARD_MAP_SIZE; ++i)
   {
      if (i & 1)
      {
         std::cout << std::setfill(' ') << std::setw(4) << (i / 2) + 1 << " \u2551 ";
      }
      else
      {
         std::cout << "     \u2551 ";
      }

      for (int j = 0; j < qcore::BOARD_MAP_SIZE; ++j)
      {
         switch (map(i, j))
         {
            case 0:
               std::cout << "   ";
               break;
            case qcore::BoardMap::VertivalWall:
               std::cout << " \u2502 ";
               break;
            case qcore::BoardMap::HorizontalWall:
               std::cout << "\u2500\u2500\u2500";
               break;
            case qcore::BoardMap::Pawn0:
               std::cout << " 0 ";
               break;
            case qcore::BoardMap::Pawn1:
               std::cout << " 1 ";
               break;
            case qcore::BoardMap::Pawn2:
               std::cout << " 2 ";
               break;
            case qcore::BoardMap::Pawn3:
               std::cout << " 3 ";
               break;
            default:
               std::cout << " " << map(i, j) << " ";
               break;
         }
      }

      std::cout << " \u2551\n";
   }

   std::cout << "     \u255A";

   for (int i = 0; i < qcore::BOARD_SIZE * 6 - 1; ++i)
   {
      std::cout << "\u2550";
   }

   std::cout << "\u255D\n\n";
}

void RunCommand_Move(qarg args)
{
   std::string dirStr = args.getValue("<direction>");
   qcore::Direction direction = qcore::Direction::Up;

   if (dirStr == "up" or dirStr == "u")
   {
      direction = qcore::Direction::Up;
   }
   else if(dirStr == "down" or dirStr == "d")
   {
      direction = qcore::Direction::Down;
   }
   else if(dirStr == "left" or dirStr == "l")
   {
      direction = qcore::Direction::Left;
   }
   else if(dirStr == "right" or dirStr == "r")
   {
      direction = qcore::Direction::Right;
   }
   else
   {
      std::cout << "Invalid direction '" << dirStr << "'\n";
      return;
   }

   GC.moveCurrentPlayer(direction);
}

void RunCommand_Wall(qarg args)
{
   uint8_t x = std::stoi(args.getValue("<x>"));
   uint8_t y = std::stoi(args.getValue("<y>"));
   std::string orStr = args.getValue("<orientation>");
   qcore::Orientation orientation;

   if (orStr == "v")
   {
      orientation = qcore::Orientation::Vertical;
   }
   else if(orStr == "h")
   {
      orientation = qcore::Orientation::Horizontal;
   }
   else
   {
      std::cout << "Invalid orientation '" << orStr << "'\n";
      return;
   }

   GC.placeWallForCurrentPlayer(qcore::Position(x, y), orientation);
}

int main(int argc, char *argv[])
{
   qcore::PluginManager::RegisterPlugin<qcli::ConsolePlayer>("qcli::ConsolePlayer");

   // Initialize a local game with 2 players
   GC.initLocalGame(4);

   // Print board at every change
   GC.getBoardState()->registerStateChange(PrintAsciiGameBoard);

   // Setup console application menu
   qcli::ConsoleApp app;

   app.addCommand([](qarg){ PrintAsciiGameBoard(); }, "board", "Game Setup")
      .setSummary("Prints the current state of the board.");

   app.addCommand([](qarg){ for (auto& p : qcore::PluginManager::GetPluginList()) std::cout << "   " << p << "\n"; }, "plugins", "Game Setup")
      .setSummary("Lists all available plugins.");

   app.addCommand([](qarg a){ GC.addPlayer(a.getValue("<plugin>"), a.getValue("<player-name>")); }, "add player <plugin> <player-name>", "Game Setup")
      .setSummary("Adds a new player to the current game.")
      .setDescription("EXAMPLE:\n   add player qplugin::DummyPlayer P1\n   add player qcli::ConsolePlayer P2");

   app.addCommand([](qarg){ GC.start(); }, "start", "Game Setup")
      .setSummary("Starts the game.");

   app.addCommand([](qarg){ GC.initLocalGame(2); }, "reset", "Game Setup")
      .setSummary("Resets the current game.");

   app.addCommand(RunCommand_Move, "move <direction>", "Player Actions")
      .setSummary("Moves the current player in the specified direction (up, down, left, right)");

   app.addCommand([](qarg a){ GC.moveCurrentPlayer(qcore::Position(std::stoi(a.getValue("<x>")), std::stoi(a.getValue("<y>")))); }, "moveto <x> <y>", "Player Actions")
      .setSummary("Moves the current player to the specified position (x, y)");

   app.addCommand(RunCommand_Wall, "wall <x> <y> <orientation>", "Player Actions")
      .setSummary("Places a wall at position (x, y) with the specified orientation (v, h) ");

   // Run application
   return app.execute(argc, argv);
}