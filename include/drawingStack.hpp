#pragma once

#include "bn_core.h"
#include "card.hpp"

class DrawingStack { 												// Everything about drawing cards (like picking them up)
protected:
	static DrawingStack* m_instance;
public:
	bn::optional<Card*> m_drawingCard; 								// The card icon that indicates if you can draw another card
	bn::vector<bn::unordered_map<Type, int, 1>, 24> m_cardsOnDeck; 	// The cards you can draw
	bn::vector<Card*, 24> m_drawnCards;								// The cards that were drawn
	int m_drawnAmount = 0; 											// The amount of cards you have drawn

	// Gets the instance of the drawing stack
	static DrawingStack* get();

	// Draws a card from the stack
	void drawCard();

	// Sets the drawing stack up
	void initDrawingStack();

	// Puts all of the drawn cards back into the stack
	void resetDrawingStack();
};