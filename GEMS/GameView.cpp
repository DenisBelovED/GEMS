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

	render_queue = new std::queue<ViewEntity*>();
	field_view = new std::vector<std::vector<ViewEntity*>>(G_HEIGHT);
	for (size_t i = 0; i < G_HEIGHT; i++)
		(*field_view)[i] = std::vector<ViewEntity*>(G_WIDTH);

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
	delete background_view;
	delete restart_view;
	delete score_view;
	for (auto& e : *field_view)
		for (auto& n : e)
			delete n;
	for (auto& link : *texture_map)
		SDL_DestroyTexture(link.second);
	delete texture_map;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
}

void GameView::rendering_all()
{
	SDL_RenderClear(render);
	while (!render_queue->empty())
	{
		for (auto& tuple : *(render_queue->front()->get_ordered_content()))
			SDL_RenderCopy(render, get_texture(std::get<0>(tuple)), NULL, &(*(std::get<1>(tuple))));
		render_queue->pop();
	}
	SDL_RenderPresent(render);
}

void GameView::add_to_rendering_queue(ViewEntity* ve)
{
	render_queue->push(ve);
}

void GameView::rendering_entity(ViewEntity* ve)
{
	for (auto& tuple : *(ve->get_ordered_content()))
		SDL_RenderCopy(render, get_texture(std::get<0>(tuple)), NULL, &(*(std::get<1>(tuple))));
	SDL_RenderPresent(render);
}

SDL_Texture* GameView::get_texture(size_t texture_id)
{
	return (*texture_map)[texture_id];
}
