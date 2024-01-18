#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Image.h"
#include "ppm.h"
 
using namespace std;
using namespace imaging;

int main() {	
	char filename[1000];
	char filename2[1000];
	cout << "File name of the image to load? ";
	cin >> filename;

	cout << "You entered: " << filename << endl;

	Image image;

	bool isokay = image.load(filename, "ppm");
	
	if (!isokay) {
		cout << "load failed " << endl;
		system("pause");
		return 0;
	}

	cout << "Image dimensions are " << image.getWidth() << " x " << image.getHeight() << endl;

	unsigned width = image.getWidth(), height = image.getHeight();

	for (unsigned x = 0; x < width; ++x) {
		for (unsigned y = 0; y < height; ++y) {
			Color buf = image.getPixel(x, y);
			buf.r = 1 - buf.r;
			buf.g = 1 - buf.g;
			buf.b = 1 - buf.b;
			image.setPixel(x, y, buf);
		}
	}

	for (unsigned i = 0; i < strlen(filename); i++) {
		if (filename[i] != '.') {
			filename2[i] = filename[i];
		} else {
			filename2[i] = '_';
			filename2[i+1] = 'n';
			filename2[i + 2] = 'e';
			filename2[i + 3] = 'g';
			filename2[i + 4] = '.';
			filename2[i + 5] = 'p';
			filename2[i + 6] = 'p';
			filename2[i + 7] = 'm';
			filename2[i + 8] = '\0';
			break;
		}
	}

	bool isokay2 = image.save(filename2, "ppm");

	if (!isokay) {
		cout << "save failed " << endl;
		system("pause");
		return 0;
	}

	cout << "No problem " << endl;

	system("pause");

	return 0;

}

