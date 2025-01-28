#pragma once

#include "bn_core.h"
#include "bn_vector.h"
#include "bn_unordered_map.h"
#include "bn_random.h"
#include "card.hpp"

class Game {															// Everything about the game
protected:
	static Game* m_instance;
public:
	bn::vector<Card*, 28> m_cards;										// Every card on the playing board
	bn::unordered_map<Type, bn::vector<int, 13>, 4> m_cardsOccupied;	// Every card that has already been chosen from a random assortment, used so no two cards are the same
	bn::vector<Card*, 19> m_cardsOnCol[7];								// The cards for every column
	bn::random m_rndm;													// Everything random

	// Gets the instance of the game
	static Game* get();

	// Sets the playing board up
	void initPlayingBoard();

	// Sets the game up								
	void setupGame();

	// The game loop								
	void gameLoop();

	// Adds a number to a vector if it's not already in it and returns if it was successful
	static bool addNumberToVector(bn::vector<int, 13>&, int);
};