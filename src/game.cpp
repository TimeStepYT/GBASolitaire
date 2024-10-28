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
	for (int i = 0; i < 28; i++) {
		bn::core::update();
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
		if (i < 7) {
			newCard->setColumn(i);
			newCard->setLayer(0);
		}
		else if (i < 13) {
			newCard->setColumn(i - 6);
			newCard->setLayer(1);
		}
		else if (i < 18) {
			newCard->setColumn(i - 11);
			newCard->setLayer(2);
		}
		else if (i < 22) {
			newCard->setColumn(i - 15);
			newCard->setLayer(3);
		}
		else if (i < 25) {
			newCard->setColumn(i - 18);
			newCard->setLayer(4);
		}
		else if (i < 27) {
			newCard->setColumn(i - 20);
			newCard->setLayer(5);
		}
		else if (i < 28) {
			newCard->setColumn(i - 21);
			newCard->setLayer(6);
		}
		m_cards.push_back(newCard);
	}

	for (auto col : m_cardsOnCol) {
		col[col.size() - 1]->setFlipped(false);
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

void Game::startLoop() {
	bool setUp = false;
	while (true) { // game loop
		rndm.update();

		if (bn::keypad::a_pressed() && !setUp) {
			setupGame();
			setUp = true;
		}

		bn::core::update();
	}
}