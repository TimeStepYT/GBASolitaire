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

void DrawingStack::resetDrawingStack() {
	m_drawnCards[m_drawnCards.size() - 1]->setVisible(false);
	m_drawnCards.clear();
	m_drawingCard.value()->setVisible(true);
	m_drawnAmount = 0;
}

void DrawingStack::drawCard() {
	if (m_drawnAmount > m_cardsOnDeck.size() - 1) {
		resetDrawingStack();
		return;
	}

	auto cardToDraw = m_cardsOnDeck[m_drawnAmount];
	Type type = Type::NONE;
	for (int i = 0; i < 4; i++) {
		if (cardToDraw.contains((Type) i)) {
			type = (Type) i;
		}
	}
	if (type == Type::NONE) return;

	auto* drawingCard = m_drawingCard.value();

	if (m_drawnCards.size() != 0) {
		m_drawnCards[m_drawnCards.size() - 1]->setVisible(false);
	}

	auto* newCard = Card::create(type, cardToDraw[type]);
	newCard->setFlipped(false);
	newCard->setPosition(drawingCard->getPositionX() + CARD_WIDTH + 2, drawingCard->getPositionY());
	m_drawnCards.push_back(newCard);
	m_drawnAmount++;
	
	if (m_drawnAmount > m_cardsOnDeck.size() - 1) {
		drawingCard->setVisible(false);
	}
}

void DrawingStack::initDrawingStack() {
	int cardsAdded = 0;
	auto* game = Game::get();
	while (cardsAdded < 24) {
		game->m_rndm.update();
		auto& cardsOccupied = game->m_cardsOccupied;
		Type cardType = Type::NONE;
		int cardNumber = 0;
		bool leave = false;
		while (!leave) {
			cardType = (Type) game->m_rndm.get_int(4);
			cardNumber = game->m_rndm.get_int(13) + 1;
			if (Game::addNumberToVector(cardsOccupied[cardType], cardNumber))
				leave = true;
		}
		bn::unordered_map<Type, int, 1> map;
		map[cardType] = cardNumber;
		m_cardsOnDeck.push_back(map);
		cardsAdded++;
	}
	auto drawingCard = Card::create();
	drawingCard->setPosition((-SCREEN_WIDTH + CARD_WIDTH) / 2 + 2, (-SCREEN_HEIGHT + CARD_HEIGHT) / 2 + 3);
	m_drawingCard = drawingCard;
}