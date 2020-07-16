#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "core.h"
#include <GL/glew.h>
#include "Utils/file.h"


class Texture {
	private:
		uint32_t m_id;
		uint32_t m_width;
		uint32_t m_height;
		uint8_t m_channels;
		uint8_t* m_pixels;

		void applyPixels(const uint8_t* pixels);

	public:
		Texture(const char* name, uint8_t channels = 0);
		Texture(uint8_t* pixels, uint32_t width, uint32_t height, uint8_t channels = 4);
		~Texture();

		static Texture* createBlank(uint8_t channels = 4);

		void bind(uint32_t slot = 0);

		void print();
};


#endif
