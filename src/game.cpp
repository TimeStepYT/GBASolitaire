#include "game.hpp"
#include "global.hpp"
#include "bn_keypad.h"

Game* Game::m_instance = nullptr;

Game* Game::get() {
	if (!m_instance) {
		m_instance = new Game();
	}
	return m_instance;
}

bool addNumberToVector(bn::vector<int, 13>& vec, int content) {
	if (bn::find(vec.begin(), vec.end(), content) == vec.end()) {
		vec.push_back(content);
		return true;
	}
	return false;
}

void Game::initPlayingBoard() {
	int prevColMax = 0;
	int colMax = 0;
	int layer = 0;
	for (int i = 0; i < 28; i++) {
		Type cardType;
		int cardNumber;
		bool leave = false;
		while (!leave) {
			cardType = (Type) rndm.get_int(4);
			cardNumber = rndm.get_int(13) + 1;
			if (addNumberToVector(m_cardsOccupied[cardType], cardNumber))
				leave = true;
		}
		auto newCard = Card::create(cardType, cardNumber);
		newCard->setPositionY(newCard->getPositionY() - 10);

		if (i >= colMax) {
			prevColMax = colMax;
			if (colMax != 0) layer++;
		}
		if (i < 7) {
			colMax = 7;
		}
		else if (i < 13) {
			colMax = 13;
		}
		else if (i < 18) {
			colMax = 18;
		}
		else if (i < 22) {
			colMax = 22;
		}
		else if (i < 25) {
			colMax = 25;
		}
		else if (i < 27) {
			colMax = 27;
		}
		else if (i < 28) {
			colMax = 28;
		}

		int const col = i - (prevColMax - layer);
		newCard->setColumn(col);
		newCard->setLayer(layer);
		if (i == prevColMax) newCard->setFlipped(false);

		m_cards.push_back(newCard);
		bn::core::update();
	}
}

void Game::initDrawingStack() {
	int cardsAdded = 0;
	while (cardsAdded < 24) {
		rndm.update();
		int randomNumber = rndm.get_int(13) + 1;
		Type randomType = (Type) rndm.get_int(4);

		if (m_cardsOnDeck.contains(randomType)) {
			auto allOfType = m_cardsOnDeck[randomType];
			if (bn::find(allOfType.begin(), allOfType.end(), randomNumber) != allOfType.end())
				continue;
		}
		m_cardsOnDeck[randomType].push_back(randomNumber);
		cardsAdded++;
	}
	auto newCard = Card::create();
	newCard->setPosition(-SCREEN_WIDTH / 2 + CARD_WIDTH / 2 + 2, -SCREEN_HEIGHT / 2 + CARD_HEIGHT / 2 + 3);
	drawingCard = newCard;
}

void Game::setupGame() {
	rndm.update();

	initPlayingBoard();
	initDrawingStack();
}

void Game::drawCard() {

}

void Game::gameLoop() {
	bool setUp = false;
	while (true) {
		rndm.update();

		if (bn::keypad::a_pressed() && !setUp) {
			setupGame();
			setUp = true;
		}
		else if (bn::keypad::l_pressed() && setUp) {
			drawCard();
		}

		bn::core::update();
	}
}