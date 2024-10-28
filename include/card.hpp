#pragma once

#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_unordered_map.h"

typedef enum {
	SPADE,
	CLUB,
	HEART,
	DIAMOND,
	NONE
} Type;

class Card {
protected:
	bn::vector<bn::sprite_ptr, 2> m_baseSprites;
	bn::vector<bn::sprite_ptr, 10> m_faceSprites;
	Type m_type;
	int m_number;
	int m_column = 7;
	int m_layer = 0;
	bool m_flipped = true;
public:
	static Card* create(Type, int);
	static Card* create();
	void initFaceSprites();
	void setPosition(bn::fixed, bn::fixed);
	void setPositionX(bn::fixed);
	void setPositionY(bn::fixed);
	void setLayer(int);
	bn::fixed getPositionY();
	bn::fixed getPositionX();
	void setColumn(int);
	void setFlipped(bool);
	bool isBlack();
};