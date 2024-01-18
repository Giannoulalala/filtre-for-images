#include "Image.h"
#include "Color.h"
#include "ppm.h"

using namespace imaging;

namespace imaging {
	
	Color * Image::getRawDataPtr() {
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const {
		unsigned int thesi = 1*x+width*y;
		if (thesi < width*height) {
			Color pixel;
			pixel.r = buffer[thesi].r;
			pixel.g = buffer[thesi].g;
			pixel.b = buffer[thesi].b;
			return pixel;
		} else {
			Color pixel;
			return pixel;
		}
	}
	
	void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		unsigned int thesi = 1 * x + width*y;
		if (thesi < width*height) {
			Color pixel = value;
			buffer[thesi].r = pixel.r;
			buffer[thesi].g = pixel.g;
			buffer[thesi].b = pixel.b;
		}
	}

	void Image::setData(const Color * & data_ptr) {
		int i = 0;
		int j = 0;

		for (unsigned p = 0; p < width*height; p++) {
			buffer[i].r = data_ptr[j].r;
			buffer[i].g = data_ptr[j].g;
			buffer[i].b = data_ptr[j].b;

			++i;
			++j;
		}
	}

	Image::Image() {
		width = 0;
		height = 0;
		buffer = nullptr;	
	}

	Image::Image(unsigned int width, unsigned int height) {
		this->buffer = new Color[width*height];
		this->width = width;
		this->height = height;		
	}
	
	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
		this->buffer = new Color[width*height];
		this->width = width;
		this->height = height;

		int i = 0;
		int j = 0;

		for (unsigned p = 0; p < width*height; p++) {
			buffer[i].r = data_ptr[j].r;
			buffer[i].g = data_ptr[j].g;
			buffer[i].b = data_ptr[j].b;

			++i;
			++j;
		}
	}

	Image::Image(const Image &src) {
		this->buffer = new Color[src.width*src.height];
		this->width = src.width;
		this->height = src.height;

		int i = 0;
		int j = 0;

		for (unsigned p = 0; p < src.width*src.height; p++) {
			buffer[i].r = src.buffer[j].r;
			buffer[i].g = src.buffer[j].g;
			buffer[i].b = src.buffer[j].b;

			++i;
			++j;
		}
	}
	
	Image::~Image() {
		if (buffer != nullptr) {
			delete[] buffer;
		}
	}
	
	Image & Image::operator = (const Image & right) {
		if (this->width == right.width && this->height == right.height) {
			int i = 0;
			int j = 0;

			for (unsigned p = 0; p < right.width*right.height; p++) {
				buffer[i].r = right.buffer[j].r;
				buffer[i].g = right.buffer[j].g;
				buffer[i].b = right.buffer[j].b;

				++i;
				++j;
			}
		} else {
			delete[] buffer;
			if (right.width > 0 && right.height > 0) {
				this->buffer = new Color[right.width*right.height];
				this->width = right.width;
				this->height = right.height;

				int i = 0;
				int j = 0;

				for (unsigned p = 0; p < right.width*right.height; p++) {
					buffer[i].r = right.buffer[j].r;
					buffer[i].g = right.buffer[j].g;
					buffer[i].b = right.buffer[j].b;

					++i;
					++j;
				}
			}
		}

		return *this;
	}

	bool Image::load(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			int i_width, i_height;
			float * data2 = ReadPPM(filename.c_str(), &i_width, &i_height);

			if (data2 != nullptr) {
				if (width != i_width || height != i_height) {
					delete[] buffer;
					buffer = new Color[i_width*i_height];
				}

				this->width = (unsigned) i_width;
				this->height = (unsigned) i_height;

				int i = 0;
				int j = 0;

				for (int p = 0; p < i_width*i_height ; p++) {
					buffer[i].r = data2[j];
					buffer[i].g = data2[j+1];
					buffer[i].b = data2[j + 2];

					i = i + 1;
					j = j + 3;
				}

				delete[] data2;

				return true;
			}			
		} 
		return false;
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		if (format == "ppm") {
			int i_width = (int)this->width, i_height = (int)this->height;

			float * data2 = new float[3*i_width*i_height];

			int i = 0;
			int j = 0;

			for (int p = 0; p < i_width*i_height; p++) {
				data2[j] = buffer[i].r;
				data2[j + 1] = buffer[i].g;
				data2[j + 2] = buffer[i].b;

				i = i + 1;
				j = j + 3;
			}
			
			bool isokay = WritePPM(data2, i_width, i_height, filename.c_str());

			delete[] data2;

			return isokay;
		}

		return false;
	}

}