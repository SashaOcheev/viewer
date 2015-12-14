#include <string>
#include <vector>
#include <windows.h> 
#include "files.h"

using namespace std;

int getFilesList(string mask, vector <string>  &files)
{
	HANDLE h_find;
	WIN32_FIND_DATA find_data;

	// Look for first
	h_find = FindFirstFile(mask.c_str(), &find_data);
	if (h_find != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(find_data.cFileName);
		} while (FindNextFile(h_find, &find_data));
	}

	FindClose(h_find);

	return 0;
}

void getFormFilesList(Files &files) {
	for (int i = 0; i < files.formats.size(); ++i) {
		char dir_temp[] = "";
		string mask = files.dir_name;
		getFilesList(mask.append("*.").append(files.formats[i]), files.list);
	}
}