#include "PlayMode.hpp"

//for the GL_ERRORS() macro:
#include "gl_errors.hpp"

//for glm::value_ptr() :
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <fstream>
#include <inttypes.h>

PlayMode::PlayMode() {
	//TODO:
	// you *must* use an asset pipeline of some sort to generate tiles.
	// don't hardcode them like this!
	// or, at least, if you do hardcode them like this,
	//  make yourself a script that spits out the code that you paste in here
	//   and check that script into your repository.

	//Also, *don't* use these tiles in your game:
	// { //use tiles 0-16 as some weird dot pattern thing:
	// 	std::array< uint8_t, 8*8 > distance;
	// 	for (uint32_t y = 0; y < 8; ++y) {
	// 		for (uint32_t x = 0; x < 8; ++x) {
	// 			float d = glm::length(glm::vec2((x + 0.5f) - 4.0f, (y + 0.5f) - 4.0f));
	// 			d /= glm::length(glm::vec2(4.0f, 4.0f));
	// 			distance[x+8*y] = std::max(0,std::min(255,int32_t( 255.0f * d )));
	// 		}
	// 	}
	// 	for (uint32_t index = 0; index < 16; ++index) {
	// 		PPU466::Tile tile;
	// 		uint8_t t = (255 * index) / 16;
	// 		for (uint32_t y = 0; y < 8; ++y) {
	// 			uint8_t bit0 = 0;
	// 			uint8_t bit1 = 0;
	// 			for (uint32_t x = 0; x < 8; ++x) {
	// 				uint8_t d = distance[x+8*y];
	// 				if (d > t) {
	// 					bit0 |= (1 << x);
	// 				} else {
	// 					bit1 |= (1 << x);
	// 				}
	// 			}
	// 			tile.bit0[y] = bit0;
	// 			tile.bit1[y] = bit1;
	// 		}
	// 		ppu.tile_table[index] = tile;
	// 	}
	// }

	//use sprite 32 as a "player":
	std::fstream player_file("tile_txt\\player.txt", std::ios_base::in);
	int player_color_idx;
	player_file >> player_color_idx;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			player_file >> bin1;
			player_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[32].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[32].bit1[i] |= (bin1 << (7 - j));
		}
	}
	std::cout << std::hex << static_cast<int>(ppu.tile_table[32].bit1[0]) << std::endl;
	std::cout << std::hex << static_cast<int>(ppu.tile_table[32].bit0[0]) << std::endl;

	//printf("%" PRIu8 "\n", ppu.tile_table[32].bit1[0]);

	//Define the enemy and friend
	std::fstream enemy_file("tile_txt\\enemy.txt", std::ios_base::in);
	int enemy_color_idx;
	enemy_file >> enemy_color_idx;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			enemy_file >> bin1;
			enemy_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[0].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[0].bit1[i] |= (bin1 << (7 - j));
		}
	}

	std::fstream friend_file("tile_txt\\friend.txt", std::ios_base::in);
	int friend_color_index;
	friend_file >> friend_color_index;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			friend_file >> bin1;
			friend_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[1].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[1].bit1[i] |= (bin1 << (7 - j));
		}
	}

	std::fstream spike_file("tile_txt\\spike.txt", std::ios_base::in);
	int spike_color_index;
	spike_file >> spike_color_index;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			spike_file >> bin1;
			spike_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[2].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[2].bit1[i] |= (bin1 << (7 - j));
		}
	}

	std::fstream brick_file("tile_txt\\brick.txt", std::ios_base::in);
	int brick_color_index;
	brick_file >> brick_color_index;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			brick_file >> bin1;
			brick_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[3].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[3].bit1[i] |= (bin1 << (7 - j));
		}
	}

	std::fstream glitched_file("tile_txt\\glitched_tile.txt", std::ios_base::in);
	int glitched_color_index;
	glitched_file >> glitched_color_index;

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			int bin0, bin1;
			glitched_file >> bin1;
			glitched_file >> bin0;

			// std::cout << i << ", " << j << ": " << bin0 << bin1 << std::endl;
			ppu.tile_table[4].bit0[i] |= (bin0 << (7 - j));
			ppu.tile_table[4].bit1[i] |= (bin1 << (7 - j));
		}
	}

	std::cout << std::hex << static_cast<int>(ppu.tile_table[2].bit1[6]) << std::endl;
	std::cout << std::hex << static_cast<int>(ppu.tile_table[2].bit0[6]) << std::endl;

	//makes the outside of tiles 0-16 solid:
	ppu.palette_table[0] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	};

	//makes the center of tiles 0-16 solid:
	ppu.palette_table[1] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	};

	//used for the player:
	ppu.palette_table[7] = {
		glm::u8vec4(0xff, 0x00, 0x00, 0xff),
		glm::u8vec4(0x00, 0xff, 0x00, 0xff),
		glm::u8vec4(0x00, 0x00, 0xff, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	};

	//used for the misc other sprites:
	ppu.palette_table[6] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
		glm::u8vec4(0xff, 0xff, 0xff, 0xff),
		glm::u8vec4(0xff, 0x00, 0xff, 0xff),
	};

	start_new_game();
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_LEFT) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.downs += 1;
			down.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_LEFT) {
			left.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.pressed = false;
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	using namespace std;

	//slowly rotates through [0,1):
	// (will be used to set background color)
	background_fade += elapsed / 10.0f;
	background_fade -= std::floor(background_fade);

	jump_timer -= elapsed;

	constexpr float PlayerSpeed = 30.0f;
	if (left.pressed) player_at.x -= PlayerSpeed * elapsed;
	if (right.pressed) player_at.x += PlayerSpeed * elapsed;
	
	player_at.y -= PlayerSpeed * elapsed;
	if (up.pressed) {
		if(can_jump && jump_timer <= 0) {
			jumps++;
			jump_timer = 0.1f;
		}
		can_jump = false;
	}
	else {
		can_jump = true;
	}

	if(jump_timer > 0) {
		player_at.y += PlayerSpeed * elapsed * 6;
	}

	if(player_at.y < 0) {
		player_at.y = 0;
	}

	if(player_at.y > 236) {
		player_at.y = 236;
	}

	//Taken from game 0 :)
	for(int i = 1; i < 64; i++) {
		//Only collide with enemies
		if(ppu.sprites[i].index == 1) continue;

		glm::vec2 &obj = glm::vec2(ppu.sprites[0].x, ppu.sprites[0].y);
		glm::vec2 &other = glm::vec2(ppu.sprites[i].x, ppu.sprites[i].y);

		bool hitSomething = false;
		
		//compute area of overlap:
		glm::vec2 min = glm::max(obj, other);
		glm::vec2 max = glm::min(obj + 8.0f, other + 8.0f);

		//if no overlap, no collision:
		if (min.x > max.x || min.y > max.y) continue;

		start_new_game();
	}
	
	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	//background color will be some hsv-like fade:
	ppu.background_color = glm::u8vec4(
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 0.0f / 3.0f) ) ) ))),
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 1.0f / 3.0f) ) ) ))),
		std::min(255,std::max(0,int32_t(255 * 0.5f * (0.5f + std::sin( 2.0f * M_PI * (background_fade + 2.0f / 3.0f) ) ) ))),
		0xff
	);

	//tilemap gets recomputed every frame as some weird plasma thing:
	//NOTE: don't do this in your game! actually make a map or something :-)
	for (uint32_t y = 0; y < PPU466::BackgroundHeight; ++y) {
		for (uint32_t x = 0; x < PPU466::BackgroundWidth; ++x) {
			//TODO: make weird plasma thing
			ppu.background[x+PPU466::BackgroundWidth*y] = 3 | (6 << 8);
		}
	}

	//background scroll:
	ppu.background_position.x = int32_t(-0.5f * player_at.x);
	ppu.background_position.y = int32_t(-0.5f * player_at.y);

	//player sprite:
	ppu.sprites[0].x = int32_t(player_at.x);
	ppu.sprites[0].y = int32_t(player_at.y);
	ppu.sprites[0].index = 32;
	ppu.sprites[0].attributes = 7;

	//some other misc sprites:
	for (uint32_t i = 1; i < 53; ++i) {
		if(ppu.sprites[i].x < 0 || ppu.sprites[i].x > 255 || ppu.sprites[i].y < 0 || ppu.sprites[i].y > 255) {
				ppu.sprites[i].x = int32_t(i * 4);
				ppu.sprites[i].y = int32_t(i%2 == 0? 50 : 200);
		}

		ppu.sprites[i].index = (jumps + i) % 2;
		ppu.sprites[i].attributes = 7;
		//if (i % 2) ppu.sprites[i].attributes |= 0x80; //'behind' bit
	}

	for (uint32_t i = 54; i < 63; ++i) {
		ppu.sprites[i].x = int32_t(ppu.sprites[i].x - 2);
		ppu.sprites[i].y = 0;
		ppu.sprites[i].index = 2;
		ppu.sprites[i].attributes = 6;
		//if (i % 2) ppu.sprites[i].attributes |= 0x80; //'behind' bit
	}

	//--- actually draw ---
	ppu.draw(drawable_size);
}

void PlayMode::start_new_game() {
	using namespace std;
	//std::cout << "Starting new game " << std::endl;
	jumps = 0;
	jump_timer = 0;
	can_jump = true;

	player_at.x = 0;
	player_at.y = 0;

	//Reset all locations
	for (uint32_t i = 1; i < 63; ++i) {
		ppu.sprites[i].x = int32_t(i * 4);
		ppu.sprites[i].y = int32_t(i%2 == 0? 50 : 200);
	}
}