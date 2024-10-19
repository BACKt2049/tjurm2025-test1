#include "tests.h"

int my_strlen(char* str) {
    
    int length = 0;
    while (*str != '\0')
    {
        length++;
        str++;
    }
    return length;
}


void my_strcat(char* str_1, char* str_2) {
  
    while (*str_1 != '\0')
    {
        str_1++;
    }
    while (*str_2 != '\0')
    {
        *str_1 = *str_2;
        str_1++;
        str_2++;
    }
    *str_1 = '\0';

}


char* my_strstr(char* s, char* p) {
   
    int p_len = 0; int s_len = 0;
    
    while (p[p_len] != '\0') p_len++;
    while (s[s_len] != '\0')
    {
        int i;
        for (i = 0; i < p_len; i++)
        {
            if (s[s_len + i] != p[i]) { break; }
        }
        if (i == p_len) { return &s[s_len]; }
        s_len++;
    }
    return 0;
}



void rgb2gray(float* in, float* out, int h, int w)
{
  
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int index = (i * w + j) * 3; 
            float gray_value = 0.299f * in[index] + 0.587f * in[index + 1] + 0.114f * in[index + 2];
            out[i * w + j] = gray_value; 
        }
    }

}


void resize(float* in, float* out, int h, int w, int c, float scale) {
    int new_h = (int)(h * scale);
    int new_w = (int)(w * scale);

    for (int i = 0; i < new_h; i++) {
        for (int j = 0; j < new_w; j++) {
            float x = j / scale;
            float y = i / scale;

            int x0 = (int)x;
            int y0 = (int)y;
            int x1 = x0 + 1 < w ? x0 + 1 : x0; 
            int y1 = y0 + 1 < h ? y0 + 1 : y0;

            float dx = x - x0;
            float dy = y - y0;

            for (int k = 0; k < c; k++) {
                float q00 = in[(y0 * w + x0) * c + k];
                float q10 = in[(y0 * w + x1) * c + k];
                float q01 = in[(y1 * w + x0) * c + k];
                float q11 = in[(y1 * w + x1) * c + k];

                float q = (1 - dx) * (1 - dy) * q00 +
                    dx * (1 - dy) * q10 +
                    (1 - dx) * dy * q01 +
                    dx * dy * q11;

                out[(i * new_w + j) * c + k] = q;
            }
        }
    }
}


void hist_eq(float* in, int h, int w)
{
    int histogram[256] = { 0 };

    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int pixel_value = (int)(in[i * w + j]);
            histogram[pixel_value]++;
        }
    }

    
    float cdf[256] = { 0 };
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    
    float cdf_min = cdf[0];
    float scale = 255.0f / (h * w - cdf_min);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int pixel_value = (int)(in[i * w + j]);
            in[i * w + j] = (cdf[pixel_value] - cdf_min) * scale;
        }
    }
}



