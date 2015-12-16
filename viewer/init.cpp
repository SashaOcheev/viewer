#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <windows.h> 

#include "disp.h"
#include "files.h"
#include "init.h"

using namespace std;
using namespace sf;

void setNextFile(Files &files, Texture &texture, RenderWindow &window, string error_file) {
	if (files.can_get_next) {
		string file_name = files.dir_name;
		file_name.append(files.list[files.number]);
		if (!texture.loadFromFile(file_name))
			texture.loadFromFile(error_file);
		files.can_get_next = false;
		window.setTitle(files.list[files.number]);
	}
}

Vector2i getMove(Mouse_struct &mouse, RenderWindow &window) {
	Vector2i move = { 0, 0 };
	if (mouse.is_clicked) {
		mouse.pos = mouse.new_pos;
		mouse.new_pos = Mouse::getPosition(window);
		move = Vector2i({ mouse.pos.x - mouse.new_pos.x, mouse.pos.y - mouse.new_pos.y });
	}
	if (mouse.is_released) {
		mouse.is_released = false;
		mouse.is_clicked = false;
	}
	return move;
}

void initZoom(Zoom &zoom, int inc, Vector2f &img_center) {
	float t = zoom.modes[zoom.number + inc] / zoom.modes[zoom.number];
	zoom.number += inc;
	img_center.x *= t;
	img_center.y *= t;
	zoom.scale *= t;
	zoom.is_not_scaled = zoom.number == 0;
}

void initNextFile(bool &next_file, float &scale, int &file_number, int inc) {
	file_number += inc;
	scale = 1.f;
	next_file = true;
}

bool isInRect(Vector2i el_coor, Vector2f rect_coor, Vector2i rect_size) {
	return (el_coor.x >= rect_coor.x && el_coor.y >= rect_coor.y &&
		el_coor.x <= rect_coor.x + rect_size.x && el_coor.y <= rect_coor.y + rect_size.y);
}

void setButton(button &but, RenderWindow &window, Vector2f pos_on_display) {
	but.pos = pos_on_display;
	drawButton(window, but.texture, but.start, but.size, but.pos);
}

void setInterface(Interface &intface, RenderWindow &window) {
	Vector2f app_size = Vector2f(window.getSize());
	setButton(intface.left, window, Vector2f({ 0, app_size.y - but_size }));
	setButton(intface.right, window, Vector2f({ float(but_size), app_size.y - but_size }));
	setButton(intface.minus, window, Vector2f({ app_size.x - 2 * but_size, app_size.y - but_size }));
	setButton(intface.plus, window, Vector2f({ app_size.x - but_size, app_size.y - but_size }));
}


void setEvent(RenderWindow &window, Mouse_struct &mouse, Interface &intface, Zoom &zoom, Files &files, Img &img) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Left) {
				mouse.is_clicked = true;
				mouse.pos = mouse.new_pos = Mouse::getPosition(window);
			}
		if (event.type == Event::MouseButtonReleased)
			if (event.key.code == Mouse::Left)
				mouse.is_released = true;
		if (event.type == Event::KeyPressed || mouse.is_released) {
			if ((event.key.code == Keyboard::Add || isInRect(mouse.new_pos, intface.plus.pos, intface.plus.size)) && zoom.number < scale_count - 1)
				initZoom(zoom, 1, img.center);
			else if ((event.key.code == Keyboard::Subtract || isInRect(mouse.new_pos, intface.minus.pos, intface.minus.size)) && zoom.number > 0)
				initZoom(zoom, -1, img.center);
			else if (zoom.is_not_scaled)
				if ((event.key.code == Keyboard::Left || isInRect(mouse.new_pos, intface.left.pos, intface.left.size)) && files.number > 0)
					initNextFile(files.can_get_next, zoom.scale, files.number, -1);
				else if ((event.key.code == Keyboard::Right || isInRect(mouse.new_pos, intface.right.pos, intface.right.size)) && files.number < files.list.size() - 1)
					initNextFile(files.can_get_next, zoom.scale, files.number, 1);
		}
		if (event.type == Event::Closed)
			window.close();
	}
}