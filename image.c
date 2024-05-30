#include "image.h"
#include <stdio.h>
#include <stdlib.h>

// funcão que converte a RBG pra Gray (basicamente a mesma coisa, so muda pra se adequar nas definições da nova lista.h)
ImageGray *converter_para_gray(const ImageRGB *img) {
    // faz a alocacao em cinza
    ImageGray *imgray = create_image_gray(img->dim.largura, img->dim.altura);

    // percorre todos os pixels
    for (int i = 0; i < img->dim.altura; i++) {
        for (int j = 0; j < img->dim.largura; j++) {
            // calc indice dos pixels
            int index = i * img->dim.largura + j;
            // media dos canais para converter pra cinza
            int gray = (img->pixels[index].red + img->pixels[index].green + img->pixels[index].blue) / 3;
            //da o valor de cinza ao pixel 
            imgray->pixels[index].value = gray;
        }
    }

    return imgray;
}

// cria a imagemgray, basicamente a mesma coisa tambem 
ImageGray *create_image_gray(int largura, int altura) {
    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image) {
        fprintf(stderr, "Erro ao alocar memoria para imagem em escala de cinza.\n");
        exit(1);
    }
    image->dim.largura = largura;
    image->dim.altura = altura;
    image->pixels = (PixelGray *)malloc(largura * altura * sizeof(PixelGray));
    if (!image->pixels) {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem em escala de cinza.\n");
        free(image);
        exit(1);
    }
    return image;
}


ImageRGB *create_image_rgb(int largura, int altura)
{
    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!image)
    {
        fprintf(stderr, "Erro ao alocar memoria para imagem em RGB.\n");
        exit(1);
    }
    image->dim.largura = largura;
    image->dim.altura = altura;
    image->pixels = (PixelRGB *)malloc(largura * altura * sizeof(PixelRGB));
    if (!image->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem em RGB.\n");
        free(image);
        exit(1);
    }
    return image;
}

void free_image_rgb(ImageRGB *image)
{
    free(image->pixels);
    free(image);
}