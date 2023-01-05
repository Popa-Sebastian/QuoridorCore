
/**
 * @file GraphSearchCommon.h
 * University of Illinois CS 400, MOOC 3, Week 3: Graph Search
 *
 * @author Eric Huber
 *
**/

// We use the pragma once directive to ensure that this header won't
// be included multiple times per compilation unit by mistake.
#pragma once

#include <string> // for std::string
#include <vector> // for std::vector
#include <list>
#include <queue>
#include <utility> // for std::pair
#include <unordered_map> // for std::unordered_map

// For simple test randomization:
// (This is the old way of doing randomization, as it was done in C and in
//  earlier C++ versions. C++11 introduced more advanced random number
//  generators in the standard library, with better statistical properties,
//  but it's beyond the scope of this course.)
#include <cstdlib> // for srand(), rand()
#include <ctime> // for time()

// We're going to need to specify how to hash a pair of integers,
// because the standard library doesn't support this natively.
// This defines IntPair and IntPairPair, as well as std::hash support.
#include "IntPair2.h"

// The simple GridGraph class for 2D grid diagrams, where points must have
// integer coordinates, and edges may only connect two points that are one
// space apart. This implements a very simple version of an "adjacency list"
// graph data structure using std::unordered_map.
#include "GridGraph.h"

// This function is defined in GraphSearch.cpp
std::list<IntPair> graphBFS(const IntPair& start, const IntPair& goal, const GridGraph& graph);
