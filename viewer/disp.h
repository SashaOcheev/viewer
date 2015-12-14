using namespace sf;
using namespace std;

const int but_size = 50;
const int but_count = 4;
const float min_app_size = 500;

const int scale_count = 8;

const string but_file = "images/buttons2.png";

struct button {
	Texture texture;
	Vector2i start;
	Vector2i size;
	Vector2f pos;
};

struct Zoom {
float modes[scale_count] = { 1, 1.5, 2, 2.5, 3, 4, 6, 8 };
int number = 0;
bool is_not_scaled = true;
float scale = 1.f;
};

struct Img {
	Vector2f center;
	Texture texture;
};

Texture getTexture(std::string name);

struct Interface {
	button left = { getTexture(but_file), Vector2i({ 0, 0 }), Vector2i({ but_size, but_size }), Vector2f({ 0, 0 }) };
	button right = { getTexture(but_file), Vector2i({ but_size, 0 }), Vector2i({ but_size, but_size }), Vector2f({ 0, 0 }) };
	button minus = { getTexture(but_file), Vector2i({ but_size * 2, 0 }), Vector2i({ but_size, but_size }), Vector2f({ 0, 0 }) };
	button plus = { getTexture(but_file), Vector2i({ but_size * 3, 0 }), Vector2i({ but_size, but_size }), Vector2f({ 0, 0 }) };
};

void drawButton(RenderWindow &app, Texture txtr, Vector2i img_start, Vector2i img_size, Vector2f app_pos);
int drawImage(Texture &txtr, RenderWindow &app, bool is_not_scale, float &scale, Vector2i move, Vector2f &img_center);