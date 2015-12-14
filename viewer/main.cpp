#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h> 

#include "files.h"
#include "disp.h"
#include "init.h"

using namespace sf;
using namespace std;

int main() {

	Init init;
	getFormFilesList(init.files);
	RenderWindow window(VideoMode(600, 600), "view");

	while (window.isOpen()) {
		setEvent(window, init.mouse, init.intface, init.zoom, init.files, init.img);

		window.clear();

		setNextFile(init.files, init.img.texture, window, error_file);
		drawImage(init.img.texture, window, init.zoom.is_not_scaled, init.zoom.scale, getMove(init.mouse, window), init.img.center);
		setInterface(init.intface, window);

		window.display();

	}
	return 0;
}