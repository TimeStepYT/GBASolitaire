#include "global.hpp"
#include "card.hpp"
#include "game.hpp"

#include "bn_sprite_builder.h"

#include "bn_sprite_items_card_back.h"
#include "bn_sprite_items_card_back_top.h"
#include "bn_sprite_items_card_base.h"
#include "bn_sprite_items_card_base_top.h"
#include "bn_sprite_items_symbols.h"
#include "bn_sprite_items_numbers.h"

Card* Card::create(Type type, int number) {
	auto ret = new Card();
	ret->m_type = type;
	ret->m_number = number;
	ret->createBackground();
	return ret;
}

Card* Card::create() {
	return Card::create(Type::NONE, 0);
}

void Card::createBackground() {
	m_baseSprites.push_back(bn::sprite_items::card_back_top.create_sprite(0, -17));
	m_baseSprites.push_back(bn::sprite_items::card_back.create_sprite(0, 5));
}

void Card::setLayer(int layer) {
	m_layer = layer;
	setPositionY(getPositionY() + layer * 8);
}

void Card::initFaceSprites() {
	if (m_number == 0 || m_number > 13 || m_type >= (Type) 4) return;

	int offset = isBlack() ? 0 : 13;
	auto numberTile = bn::sprite_items::numbers.tiles_item().create_tiles(m_number - 1 + offset);
	auto symbolTile = bn::sprite_items::symbols.tiles_item().create_tiles(m_type);
	auto numberSprite = bn::sprite_items::numbers.create_sprite(getPositionX() - CARD_WIDTH / 2 + 4 + 1, getPositionY() - CARD_HEIGHT / 2 + 4 + 1);
	auto symbol = bn::sprite_items::symbols.create_sprite(numberSprite.x() + 8, numberSprite.y());
	auto numberSpriteRotated = bn::sprite_items::numbers.create_sprite(getPositionX() + CARD_WIDTH / 2 - 4 - 2, getPositionY() + CARD_HEIGHT / 2 - 4 - 2);
	auto symbolRotated = bn::sprite_items::symbols.create_sprite(numberSpriteRotated.x() - 7, numberSpriteRotated.y() + 1);

	numberSprite.set_tiles(numberTile);
	symbol.set_tiles(symbolTile);
	numberSpriteRotated.set_tiles(numberTile);
	numberSpriteRotated.set_rotation_angle(180);
	symbolRotated.set_tiles(symbolTile);
	symbolRotated.set_vertical_flip(true);

	m_faceSprites.push_back(numberSprite);
	m_faceSprites.push_back(numberSpriteRotated);
	m_faceSprites.push_back(symbol);
	m_faceSprites.push_back(symbolRotated);
}

void Card::setPosition(bn::fixed x, bn::fixed y) {
	bn::fixed deltaX = x - getPositionX();
	bn::fixed deltaY = y - getPositionY();
	m_baseSprites[0].set_position(x, y - 17);
	m_baseSprites[1].set_position(x, y + 5);
	for (bn::sprite_ptr& sprite : m_faceSprites) {
		sprite.set_position(sprite.x() + deltaX, sprite.y() + deltaY);
	}
}

void Card::setPositionX(bn::fixed x) {
	setPosition(x, getPositionY());
}

void Card::setPositionY(bn::fixed y) {
	setPosition(getPositionX(), y);
}

void Card::setColumn(int column) {
	if (column >= 7) return;

	m_column = column;
	auto& stack = Game::get()->m_cardsOnCol[column];
	if (stack.size() != 0) {
		auto& baseSprites = stack[stack.size() - 1]->m_baseSprites;
		if (&baseSprites[1])
			baseSprites.erase(baseSprites.begin() + 1);
	}
	stack.push_back(this);
	setPositionX(2 - SCREEN_WIDTH / 2 + CARD_WIDTH / 2 + column * (CARD_WIDTH + 2));
}

void Card::setFlipped(bool flipped) {
	if (flipped == m_flipped) return;

	m_flipped = flipped;
	if (flipped) {
		m_baseSprites[0].set_tiles_and_palette(bn::sprite_items::card_back_top.tiles_item().create_tiles(0), bn::sprite_items::card_back_top.palette_item().create_palette());
	}
	else {
		m_baseSprites[0].set_tiles_and_palette(bn::sprite_items::card_base_top.tiles_item().create_tiles(0), bn::sprite_items::card_base_top.palette_item().create_palette());
		m_baseSprites[1] = bn::sprite_items::card_base.create_sprite(getPositionX(), getPositionY() + 5);
		initFaceSprites();
	}
}

bn::fixed Card::getPositionX() {
	return m_baseSprites[0].x();
}
bn::fixed Card::getPositionY() {
	return m_baseSprites[0].y() + 17;
}

bool Card::isBlack() {
	return m_type == Type::CLUB || m_type == Type::SPADE;
}

void Card::setVisible(bool visible) {
	m_visible = visible;

	if (visible && m_baseSprites.size() == 0) {
		createBackground();
		initFaceSprites();
		setPosition(m_hiddenX, m_hiddenY);
	}
	else if (!visible && m_baseSprites.size() != 0) {
		m_hiddenX = getPositionX();
		m_hiddenY = getPositionY();
		m_baseSprites.clear();
		m_faceSprites.clear();
	}
}

bool Card::getVisible() {
	return m_visible;
}

void Card::hide() {
	setVisible(false);
}

void Card::show() {
	setVisible(true);
}