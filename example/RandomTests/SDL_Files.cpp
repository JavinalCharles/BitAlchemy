#include <iostream>
#include <string>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_filesystem.h>

int main(int argc, char* argv[]) {
	char* prefPath = SDL_GetPrefPath("bit-alchemy", "assets");
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

	char* pref2Path = SDL_GetPrefPath(nullptr, "bit-alchemy");
	if (pref2Path == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}
	std::string pref2(pref2Path);

	SDL_free(basePath);
	SDL_free(prefPath);
	SDL_free(pref2Path);

	std::cout << "Pref Path: " << pref << std::endl;
	std::cout << "Base Path: " << base << std::endl;
	std::cout << "Pref w/o org path: " << pref2 << std::endl;

	return 0;
}
