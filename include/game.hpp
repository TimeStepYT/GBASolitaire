#pragma once

#include "bn_core.h"
#include "bn_vector.h"
#include "bn_unordered_map.h"
#include "bn_random.h"
#include "card.hpp"

class Game {
protected:
	static Game* m_instance;
public:
	bn::vector<Card*, 52> m_cards;
	bn::unordered_map<Type, bn::vector<int, 13>, 4> m_cardsOccupied;
	bn::vector<Card*, 19> m_cardsOnCol[7];
	bn::random m_rndm;

	static Game* get();
	void initPlayingBoard();
	void setupGame();
	void gameLoop();
};