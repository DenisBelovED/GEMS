#include "GameView.h"
#include <iostream>
GameView::GameView()
{
	wchar_t buffer_path[MAX_PATH];
	GetModuleFileName(NULL, buffer_path, MAX_PATH);
	std::wstring path_to_exe(buffer_path);
	
	auto texture_pack_dir = path_to_exe.substr(0, path_to_exe.rfind('\\')).append(L"\\textures");
	
	texture_map = new std::map<size_t, SDL_Surface*>();
	size_t id_img = 0;

	for (auto& t_name : std::filesystem::directory_iterator(texture_pack_dir))
	{
		id_img++;
		std::wstring ws = t_name.path().native();
		std::string path_to_img(ws.begin(), ws.end());
		(*texture_map)[id_img] = SDL_LoadBMP(path_to_img.c_str());
	}

	window = SDL_CreateWindow(
		"GEMS",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI
	);
	if (window == nullptr)
		throw SDL_GetError();

	render = SDL_CreateRenderer(
		window,
		-1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (render == nullptr)
		throw SDL_GetError();
}

GameView::~GameView()
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
	delete texture_map;
}

void GameView::to_render(SDL_Surface img)
{
	texture = SDL_CreateTextureFromSurface(render, &img);
	SDL_FreeSurface(&img);
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderPresent(render);
	//SDL_Delay(5000);
}
