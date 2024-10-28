#include "bn_core.h"
#include "bn_regular_bg_item.h"
#include "bn_bg_palettes.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "card.hpp"
#include "game.hpp"
#include "global.hpp"

int main() {
	bn::core::init();
	const bn::color tableGreen = bn::color(0, 15, 0);
	bn::bg_palettes::set_transparent_color(tableGreen);

	Game::get()->startLoop();
	return 0;
}