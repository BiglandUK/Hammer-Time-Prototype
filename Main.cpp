#include <SFML/Graphics.hpp>
#include "Game.h"
int main(int argc, char** argv[]) {
	Game game_;

	while (!game_.GetWindow().IsDone()) {
		game_.Update();
		game_.Render();
		game_.LateUpdate();
	}
	return 0;
}