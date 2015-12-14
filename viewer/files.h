using namespace std;

const string error_file = "images/error.png";

struct Files {
	vector <string> list;
	vector <string> formats = { "jpg", "bmp", "png" };
	string dir_name = "D:/images/";
	int number = 0;
	bool can_get_next = true;
};

void getFormFilesList(Files &files);