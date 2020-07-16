#include "texture.h"


void Texture::applyPixels(const uint8_t* pixels) {
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, (m_channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, pixels);
}

Texture::Texture(const char* name, uint8_t channels): m_channels(channels) {
	m_pixels = readPNG(name, &m_width, &m_height, &m_channels);
	applyPixels(m_pixels);
}

Texture::Texture(uint8_t* pixels, uint32_t width, uint32_t height, uint8_t channels): m_width(width), m_height(height), m_channels(channels), m_pixels(pixels) {
	applyPixels(m_pixels);
}

Texture::~Texture() {
	delete[] m_pixels;
	glDeleteTextures(1, &m_id);
}

Texture* Texture::createBlank(uint8_t channels) {
	uint8_t full = (uint8_t)255;
	uint8_t* pixel = new uint8_t[4] {full, full, full, full};
	return new Texture(pixel, 1, 1, channels);
}

void Texture::bind(uint32_t slot) {
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::print() {
	APP_DEBUG(m_width, "/", m_height, "/", m_channels);
	for (uint32_t y = 0 ; y < m_height ; y+=2) {
		for (uint32_t x = 0 ; x < m_width ; x++) {
			std::cout << "\x1B[48;2";
			for (int doubleLine = 0 ; doubleLine < 2 ; doubleLine++) {
				for (uint8_t z = 0 ; z < 3 ; z++) {
					if (z < m_channels && y+doubleLine < m_height) {
						std::cout << ";" << (m_pixels[((y+doubleLine)*m_width+x)*m_channels+z]&255);
					} else {
						std::cout << ";" << 0;
					}
				}
				if (doubleLine == 0) {
					std::cout << ";38;2";
				}
			}
			std::cout << "m▄\x1B[0m";
		}
		std::cout << std::endl;
	}
}
