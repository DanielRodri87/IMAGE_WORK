#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct dimensoes {
    int altura, largura;
} Dimensoes;

typedef struct pixelRGB {
    int red, blue, green;
} PixelRGB;

typedef struct pixelGray {
    int value;
} PixelGray;

typedef struct imageGray {
    Dimensoes dim;
    PixelGray *pixels;
} ImageGray;

typedef struct imageRGB {
    Dimensoes dim;
    PixelRGB *pixels;
} ImageRGB;


int compare(const void *a, const void *b);

void salvar_imagem_arkv(ImageGray *img, FILE *gray_image); // Ok
void salvar_imagem_arkv_rgb(ImageRGB *img, FILE *rgb_image); // Ok
// Funções de criação e liberação
void alocarGray(int altura, int largura, PixelGray **pixel); //Ok
void alocarRGB(int altura, int largura, PixelRGB **pixel); // Ok
ImageGray *create_image_gray(int largura, int altura); // Ok
ImageGray *converter_para_gray(ImageRGB *img, ImageGray *imgray); // OK - com a necessidade de implementar mais funções
void free_image_gray(ImageGray *image); // Rita de Cássia                | Ok

ImageRGB *create_image_rgb(int largura, int altura); // Daniel           | Ok
void free_image_rgb(ImageRGB *image); // Daniel                          | Ok

// Operações para ImageGray
void flip_vertical_gray(ImageGray *image, ImageGray *flipped_image); // Ok
ImageGray *flip_horizontal_gray(ImageGray *image); // Pedro Henrique
ImageGray *transpose_gray(const ImageGray *image); // Rita

// Operações para ImageRGB
void flip_vertical_rgb(ImageRGB *image, ImageRGB *flipped_image); // Daniel
ImageRGB *flip_horizontal_rgb(const ImageRGB *image); // Pedro Henrique
ImageRGB *transpose_rgb(const ImageRGB *image); // Rita

// Manipulação por pixel para ImageGray
ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height);
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);

// Manipulação por pixel para ImageRGB
ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height);
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);


void printPixelColor(int lin, int col, ImageRGB *img); // Daniel           | Ok
void printImageColor(ImageRGB *img); // Rita                               | Ok
void ler_imagem_arkv(FILE *arq, ImageRGB *img); // Daniel                  | Ok

#endif // IMAGE_H