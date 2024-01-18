#include <iostream>
#include <fstream>

using namespace std;

namespace imaging {	
	float * ReadPPM(const char * filename, int * w, int * h) {
		ifstream fis;

		char temp[100];
		int d;

		fis.open(filename, ios::binary);

		bool isokay = fis.is_open();

		if (!isokay) {
			return nullptr;
		}

		fis >> temp;
		fis >> *w;
		fis >> *h;
		fis >> d;
		fis.read(&temp[5],1 );

		if (temp[0] != 'P' || temp[1] != '6' || *w <= 0 || *h <= 0 || d != 255) {
			return nullptr;
		}

		std::cout << temp << " " << *w << " " << *h << " " << d << endl;

		int bytes = 3*(*w)*(*h);

		char * data = new char[bytes];
		float * data2 = new float[bytes];

		fis.read(data, bytes);

		int i = 0;
		int j = 0;

		for (int p = 0; p < bytes; p++) {
			data2[i] = ((float)data[j])/d;
			++i;
			++j;
		}

		delete[] data;

		return data2;
	}
	
	bool WritePPM(const float * data, int w, int h, const char * filename) {
		ofstream fos;
		int d = 255;

		fos.open(filename, ios::binary);
		bool isokay = fos.is_open();

		if (!isokay) {
			return false;
		}

		fos << "P6\n" << w << "\n" << h << "\n255\n";		

		int bytes = 3 * w *h;

		char * data2 = new char[bytes];
		int i = 0;
		int j = 0;

		for (int p = 0; p < bytes; p++) {
			data2[j] = ((char)(data[i]*d));
			++i;
			++j;
		}

		fos.write(data2, bytes);

		return true;
	}

} //namespace imaging