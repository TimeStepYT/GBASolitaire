#include "drawingStack.hpp"
#include "global.hpp"
#include "card.hpp"
#include "game.hpp"

DrawingStack* DrawingStack::m_instance = nullptr;

DrawingStack* DrawingStack::get() {
	if (!m_instance) {
		m_instance = new DrawingStack();
	}
	return m_instance;
}

void DrawingStack::drawCard() {
	auto newCard = Card::create();
	newCard->setFlipped(false);
	m_drawnAmount++;
}

void DrawingStack::initDrawingStack() {
	int cardsAdded = 0;
	auto game = Game::get();
	while (cardsAdded < 24) {
		game->m_rndm.update();
		int randomNumber = game->m_rndm.get_int(13) + 1;
		Type randomType = (Type) game->m_rndm.get_int(4);
		int leave = false;
		for (auto card : m_cardsOnDeck) {
			if (card.contains(randomType) && card[randomType] == randomNumber) {
				leave = true;
				break;
			}
		}
		if (leave) continue;
		bn::unordered_map<Type, int, 1> map;
		map[randomType] = randomNumber;
		m_cardsOnDeck.push_back(map);
		cardsAdded++;
	}
	auto drawingCard = Card::create();
	drawingCard->setPosition((-SCREEN_WIDTH + CARD_WIDTH) / 2 + 2, (-SCREEN_HEIGHT + CARD_HEIGHT) / 2 + 3);
	m_drawingCard = drawingCard;
}