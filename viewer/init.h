using namespace std;
using namespace sf;

struct Mouse_struct {
	Vector2i pos = { 0, 0 };
	Vector2i new_pos = { 0, 0 };
	bool is_clicked = false;
	bool is_released = false;
};

struct Init {
	Img img;
	Mouse_struct mouse;
	Zoom zoom;
	Files files;
	Interface intface;
};

void setNextFile(Files &files, Texture &texture, RenderWindow &window, string error_file);
Vector2i getMove(Mouse_struct &mouse, RenderWindow &window);
void initZoom(Zoom &zoom, int inc, Vector2f &img_center);
void initNextFile(bool &next_file, float &scale, int &file_number, int inc);
bool isInRect(Vector2i el_coor, Vector2f rect_coor, Vector2i rect_size);
void setButton(button &but, RenderWindow &window, Vector2f pos_on_display);
void setInterface(Interface &intface, RenderWindow &window);
void setEvent(RenderWindow &window, Mouse_struct &mouse, Interface &intface, Zoom &zoom, Files &files, Img &img);