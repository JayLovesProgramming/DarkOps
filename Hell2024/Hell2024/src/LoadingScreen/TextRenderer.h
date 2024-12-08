#pragma once
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "HellCommon.hpp"

class TextRenderer_INITIAL
{
private:
    unsigned char* ttf_buffer = nullptr;
    unsigned char* temp_bitmap = nullptr;
    stbtt_bakedchar* cdata = nullptr;
    GLuint font_texture = 0;

    const int bitmap_width = 512;
    const int bitmap_height = 512;

public:
    TextRenderer_INITIAL(const std::string& fontPath)
    {
        // Read font file
        FILE* fontFile = nullptr;
        errno_t err = fopen_s(&fontFile, fontPath.c_str(), "rb");
        if (err != 0 || !fontFile)
        {
            std::cerr << "Failed to open font file: " << fontPath << std::endl;
            return;
        }

        // Get file size
        fseek(fontFile, 0, SEEK_END);
        long fileSize = ftell(fontFile);
        fseek(fontFile, 0, SEEK_SET);

        // Allocate buffer
        ttf_buffer = new unsigned char[fileSize];
        fread(ttf_buffer, 1, fileSize, fontFile);
        fclose(fontFile);

        // Prepare bitmap for baked characters
        temp_bitmap = new unsigned char[bitmap_width * bitmap_height];
        cdata = new stbtt_bakedchar[96]; // ASCII characters

        // Bake font characters
        stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, bitmap_width, bitmap_height, 32, 96, cdata);

        // Create OpenGL texture
        glGenTextures(1, &font_texture);
        glBindTexture(GL_TEXTURE_2D, font_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitmap_width, bitmap_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void RenderText(const std::string& text, float x, float y, float scale = 1.0f, const float* color = nullptr)
    {
        //if (!font_texture) return;

        // Default to white if no color specified
        float defaultColor[3] = { 1.0f, 1.0f, 1.0f };
        if (!color) color = defaultColor;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, font_texture);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor3f(color[0], color[1], color[2]);

        glBegin(GL_QUADS);
        float xpos = x;
        float ypos = y;

        for (char c : text)
        {
            if (c < 32 || c > 128) continue;

            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, bitmap_width, bitmap_height, c - 32, &xpos, &ypos, &q, 1);

            glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0 * scale, q.y1 * scale);
            glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1 * scale, q.y1 * scale);
            glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1 * scale, q.y0 * scale);
            glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0 * scale, q.y0 * scale);
        }

        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }

    ~TextRenderer_INITIAL()
    {
        delete[] ttf_buffer;
        delete[] temp_bitmap;
        delete[] cdata;

        if (font_texture) 
        {
            glDeleteTextures(1, &font_texture);
        }
    }
};

//// Modify InitLoadingScreen to use the new text renderer
//void InitLoadingScreen()
//{
//    // ... (existing initialization code)
//
//    // Create text renderer
//    TextRenderer textRenderer("path/to/your/font.ttf");
//
//    while (!glfwWindowShouldClose(loadingWindow) && !finishedLoading)
//    {
//        // ... (existing drawing code)
//
//        // Render text next to the GIF
//        float textColor[] = { 1.0f, 1.0f, 1.0f }; // White color
//        textRenderer.RenderText("Loading...", 0.6f, -0.9f, 0.5f, textColor);
//
//        // ... (rest of the existing loop code)
//    }
//
//    // ... (rest of the existing function)
//}