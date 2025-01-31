#pragma once

#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_unordered_map.h"

typedef enum { 										// The types of cards
	SPADE,
	CLUB,
	HEART,
	DIAMOND,
	NONE
} Type;

class Card {										// Everything about cards
protected:
	bn::vector<bn::sprite_ptr, 2> m_baseSprites;	// The two sprites that make up the background of a card
	bn::vector<bn::sprite_ptr, 10> m_faceSprites;	// The sprites that go on top of a card
	Type m_type;									// The type on a card
	int m_number;									// The number on a card
	int m_column = 7;								// The column a card is in
	int m_layer = 0;								// The layer a card is on
	bool m_flipped = true;							// If a card is flipped so you can't see what's on it
	bool m_visible = true;							// If a card is visible
	bn::fixed m_hiddenX = 0;						// X value intended to store the card's position while hidden
	bn::fixed m_hiddenY = 0;						// Y value intended to store the card's position while hidden
public:
	// Creates a card with the given type and number
	static Card* create(Type, int);

	// Creates a card with nothing on it
	static Card* create();

	// Creates the background of a card
	void createBackground();

	// Sets up the sprites on a card			
	void initFaceSprites();

	// Sets the position of a card using an X and Y value
	void setPosition(bn::fixed, bn::fixed);

	// Sets the X position of a card
	void setPositionX(bn::fixed);
	
	// Sets the Y position of a card					
	void setPositionY(bn::fixed);

	// Sets the layer a card is on
	void setLayer(int);

	// Returns the Y position of a card
	bn::fixed getPositionY();

	// Returns the X position of a card
	bn::fixed getPositionX();

	// Sets the column a card is on
	void setColumn(int);

	// Sets if a card is flipped (true if you don't want to see the contents)
	void setFlipped(bool);

	// Returns if a card is spade or clubs
	bool isBlack();

	// Sets the visibility of a card
	void setVisible(bool);

	// Returns if a card is visible
	bool getVisible();
};