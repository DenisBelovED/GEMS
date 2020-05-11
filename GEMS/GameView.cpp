#include "GameView.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

GameView::GameView()
{
	int st = TTF_Init();

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
	auto font_dir = path_to_exe.substr(0, path_to_exe.rfind('\\')).append(L"\\fonts");

	texture_map = new std::map<size_t, SDL_Texture*>();

	for (auto& f_name : std::filesystem::directory_iterator(font_dir))
	{
		font = TTF_OpenFont(f_name.path().string().c_str(), FONT_SIZE);

#ifdef _DEBUG
		if (font == nullptr)
			std::cout << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
#endif // _DEBUG
	}

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
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	TTF_Quit();
}

void GameView::clear_render()
{
	SDL_RenderClear(render);
}

void GameView::rendering_all()
{
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

void GameView::rendering_score(int score)
{
	std::string s("Score: ");
	s.append(std::to_string(score));

	SDL_Color c;
	c.a = 255;
	c.r = 255;
	c.g = 104;
	c.b = 0;

	SDL_Rect r;
	r.x = SCORE_X;
	r.y = SCORE_Y;
	r.w = SCORE_W;
	r.h = SCORE_H;

	SDL_Surface* f_s = TTF_RenderText_Blended(font, s.c_str(), c);
	SDL_Texture* f_t = SDL_CreateTextureFromSurface(render, f_s);

	SDL_FreeSurface(f_s);
	SDL_RenderCopy(render, f_t, NULL, &r);
	SDL_RenderPresent(render);
	SDL_DestroyTexture(f_t);
}
