#include "GameState.h"

GameState::GameState(std::vector<qcore::PlayerState> players, std::list<qcore::WallState> walls, qcore::PlayerId id)
{
    // Generate default board
    default_board();

    // Update Player Positions
    myId = id;
    myPos = IntPair(players[myId].position.x, players[myId].position.y);

    if (id == 0) {
        enemyPos = IntPair(players[1].position.x, players[1].position.y);
    } else {
        enemyPos = IntPair(players[0].position.x, players[0].position.y);
    }

    std::cout<<"My Pos: " << myPos << std::endl;
    std::cout<<"Enemy Pos: " << enemyPos << std::endl;

    // Remove Edges based on wall placement
    for (auto wall : walls) {
        remove_wall_edges(wall);
    }
}

void GameState::default_board()
{
    /* Construct Horizontal Edges */
    for (int j = 0; j <= 8; j ++) {
        for (int i = 0; i < 8; i++) {
            graph.insertEdge(IntPair(j, i), IntPair(j, i+1));
        }
    }

    /* Construct Vertical Edges */
    for (int j = 0; j <= 8; j ++) {
        for (int i = 0; i < 8; i++) {
            graph.insertEdge(IntPair(i, j), IntPair(i+1, j));
        }
    }
}

void GameState::remove_wall_edges(qcore::WallState wall)
{
    auto wall_x = wall.position.x;
    auto wall_y = wall.position.y;
    if (wall.orientation == qcore::Orientation::Horizontal) {
        // Remove Edges above and to the right of horizontal wall
        graph.removeEdge(IntPair(wall_x, wall_y), IntPair(wall_x-1, wall_y));
        graph.removeEdge(IntPair(wall_x, wall_y+1), IntPair(wall_x-1, wall_y+1));
    } else {
        // Remove Edges to the left and bellow vertical wall
        graph.removeEdge(IntPair(wall_x, wall_y), IntPair(wall_x, wall_y-1));
        graph.removeEdge(IntPair(wall_x+1, wall_y), IntPair(wall_x+1, wall_y-1));
    }
}

void GameState::plot()
{
    graph.plot(std::cout);
}