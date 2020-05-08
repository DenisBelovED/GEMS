#include "GameView.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

GameView::GameView()
{
	window = SDL_CreateWindow(
		"GEMS",
		100,
		100,
		WIDTH, HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI
	);

#ifdef _DEBUG
	if (window == nullptr)
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; 
#endif // _DEBUG
	
	render = SDL_CreateRenderer(
		window,
		-1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

#ifdef _DEBUG
	if (render == nullptr)
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
#endif // _DEBUG

	render_queue = new std::queue<std::tuple<size_t, std::shared_ptr<SDL_Rect>>>();

	wchar_t buffer_path[MAX_PATH];
	GetModuleFileName(NULL, buffer_path, MAX_PATH);
	std::wstring path_to_exe(buffer_path);

	auto texture_pack_dir = path_to_exe.substr(0, path_to_exe.rfind('\\')).append(L"\\textures");

	texture_map = new std::map<size_t, SDL_Texture*>();

	for (auto& t_name : std::filesystem::directory_iterator(texture_pack_dir))
	{
		SDL_Texture* texture = IMG_LoadTexture(render, t_name.path().string().c_str());

#ifdef _DEBUG
		if (texture == nullptr)
			std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
#endif // _DEBUG

		(*texture_map)[texture_enum[t_name.path().stem().string()]] = texture;
	}
}

GameView::~GameView()
{
	for (auto& link : *texture_map)
		SDL_DestroyTexture(link.second);
	delete texture_map;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
}

void GameView::draw()
{
	SDL_RenderClear(render);
	while (!render_queue->empty())
	{
		auto tuple = render_queue->front();
		render_queue->pop();
		SDL_RenderCopy(render, get_texture(std::get<0>(tuple)), NULL, &(*(std::get<1>(tuple))));
	}
	SDL_RenderPresent(render);
}

void GameView::add_to_rendering_queue(size_t texture_id, std::shared_ptr<SDL_Rect> dst_rect)
{
	render_queue->push(std::tuple<size_t, std::shared_ptr<SDL_Rect>>(texture_id, dst_rect));
}

SDL_Texture* GameView::get_texture(size_t texture_id)
{
	return (*texture_map)[texture_id];
}
