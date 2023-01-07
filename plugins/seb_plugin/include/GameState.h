/**
 * @file GameState.h
 * Holds Quoridor Game State Information and a GriGraph representation
 * of the board
 *
 * @author sebastian.popa@raptor-technologies.ro
 *
**/

#pragma once

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> // for std::sort
#include <vector>
#include <string>
#include <sstream> // for std::stringstream

#include "IntPair2.h" // for IntPair and point printing support
#include "GridGraph.h" // for GridGraph
#include "Player.h"

class GameState {
public:
    GridGraph graph;
    IntPair myPos;
    IntPair enemyPos;
    qcore::PlayerId myId;

    /* Constructor based on quoridor board game state */
    GameState(std::vector<qcore::PlayerState> players, std::list<qcore::WallState> walls, qcore::PlayerId id);

    /* Generates a default connected board graph */
    void default_board();

    /* Removes graph edges related to input wall */
    void remove_wall_edges(qcore::WallState wall);

    /* Prints the current game graph to stdout*/
    void plot();
};