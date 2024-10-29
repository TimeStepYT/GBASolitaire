#include "bn_core.h"
#include "bn_regular_bg_item.h"
#include "bn_bg_palettes.h"
#include "game.hpp"

int main() {
	bn::core::init();
	const bn::color tableGreen = bn::color(0, 15, 0);
	bn::bg_palettes::set_transparent_color(tableGreen);

	Game::get()->gameLoop();
	return 0;
}