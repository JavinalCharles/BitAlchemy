#include <iostream>
#include <string>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_filesystem.h>

int main() {
	char* prefPath = SDL_GetPrefPath("Bit-Labs", "SDL_Files_Test");
	if (prefPath == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	std::string pref(prefPath);

	char* basePath = SDL_GetBasePath();
	if (basePath == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 2;
	}
	std::string base(basePath);

	SDL_free(basePath);
	SDL_free(prefPath);

	std::cout << "Pref Path: " << pref << std::endl;
	std::cout << "Base Path: " << base << std::endl;
}
