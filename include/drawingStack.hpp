#pragma once

#include "bn_core.h"
#include "card.hpp"

class DrawingStack {
protected:
	static DrawingStack* m_instance;
public:
	bn::optional<Card*> m_drawingCard;
	bn::vector<bn::unordered_map<Type, int, 1>, 52> m_cardsOnDeck;

	static DrawingStack* get();
	void drawCard();
	void initDrawingStack();
};