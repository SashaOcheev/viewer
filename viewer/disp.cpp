#include <SFML/Graphics.hpp>
#include "disp.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace sf;

Texture getTexture(std::string name) {
	Texture but_texture;
	but_texture.loadFromFile(name);
	return but_texture;
}

float getScale(Vector2f img_size, Vector2f app_size) {
	if (img_size.x > app_size.x || img_size.y > app_size.y) {
		Vector2f ratio = { app_size.x / img_size.x, app_size.y / img_size.y };
		return (ratio.x < ratio.y) ? ratio.x : ratio.y;
	}
	return 1.f;
}

float checkExtremeCenter(float center, float app_size, float img_size, float scale) {
	float temp1 = app_size / 2;
	center = (center < temp1) ? temp1 : center;
	float temp2 = img_size * scale - temp1;
	center = (center > temp2) ? temp2 : center;
	return center;
}

float getExtremeCenter(float img_center, float app_size, float img_size, float scale) {
	if (img_size * scale > app_size)
		return checkExtremeCenter(img_center, app_size, img_size, scale);
	else
		return scale * img_size / 2;
}

int drawImage(Texture &texture, RenderWindow& app, bool is_not_scale, float &scale, Vector2i move, Vector2f &img_center) {

	Vector2f app_size = Vector2f(app.getSize());
	Vector2f img_size = Vector2f(texture.getSize());
	if (app_size.x < min_app_size)
		app_size.x = min_app_size;
	if (app_size.y < min_app_size)
		app_size.y = min_app_size;
	app.setSize(Vector2u(app_size));

	Sprite sprite;
	sprite.setTexture(texture);

	if (is_not_scale)
		scale = getScale(img_size, app_size);

	sprite.scale(scale, scale);

	img_center.x += move.x;
	img_center.y += move.y;

	img_center.x = getExtremeCenter(img_center.x, app_size.x, img_size.x, scale);
	img_center.y = getExtremeCenter(img_center.y, app_size.y, img_size.y, scale);

	FloatRect rect = { Vector2f({ 0, 0 }), app_size };
	View view(rect);
	view.setCenter(img_center);
	app.setView(view);

	sprite.setPosition(0, 0);

	app.draw(sprite);

	return 0;
}

void drawButton(RenderWindow &app, Texture txtr, Vector2i img_start, Vector2i img_size, Vector2f app_pos) {
	Sprite sprt;
	sprt.setTexture(txtr);
	sprt.setTextureRect(IntRect(img_start, img_size));

	View view(FloatRect(0.f, 0.f, float(app.getSize().x), float(app.getSize().y)));
	app.setView(view);

	sprt.setPosition(app_pos);

	app.draw(sprt);
}