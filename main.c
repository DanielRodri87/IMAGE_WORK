#include <stdio.h>
#include "image.h"

int main() {
    FILE *arq;
    arq = fopen("utils/input_image_example_RGB.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    ImageGray imgray;
    ImageRGB imrgb;
    ImageGray flip_gray_vertical;
    ImageRGB flip_rgb_vertical;

    system("pause");

    ler_imagem_arkv(arq, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");

// #################################### INICIO - flip_vertical_RGB ###########################################
    
    // Inicializa flip_rgb_vertical
    flip_rgb_vertical.dim.altura = imrgb.dim.altura;
    flip_rgb_vertical.dim.largura = imrgb.dim.largura;
    alocarRGB(flip_rgb_vertical.dim.altura, flip_rgb_vertical.dim.largura, &(flip_rgb_vertical.pixels));

    // Chama a função ajustada
    flip_vertical_rgb(&imrgb, &flip_rgb_vertical);

    FILE *RGBFlip;
    RGBFlip = fopen("utils/flip_rgb_vertical.txt", "w");
    salvar_imagem_arkv_rgb(&flip_rgb_vertical, RGBFlip);

    RGBFlip = fopen("utils/flip_rgb_vertical.txt", "r");
    ler_imagem_arkv(RGBFlip, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");  

// #################################### FIM - flip_vertical_RGB ###########################################

    converter_para_gray(&imrgb, &imgray);

    FILE *GrayExample;
    GrayExample = fopen("utils/example_GRAY.txt", "w");
    salvar_imagem_arkv(&imgray, GrayExample);

    GrayExample = fopen("utils/example_GRAY.txt", "r");
    ler_imagem_arkv(GrayExample, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");



// #################################### INICIO - flip_vertical_gray ###########################################

    // Inicializa flip_gray_vertical
    flip_gray_vertical.dim.altura = imgray.dim.altura;
    flip_gray_vertical.dim.largura = imgray.dim.largura;
    alocarGray(flip_gray_vertical.dim.altura, flip_gray_vertical.dim.largura, &(flip_gray_vertical.pixels));

    // Chama a função ajustada
    flip_vertical_gray(&imgray, &flip_gray_vertical);

    FILE *GrayFlip;
    GrayFlip = fopen("utils/flip_gray_vertical.txt", "w");
    salvar_imagem_arkv(&flip_gray_vertical, GrayFlip);

    GrayFlip = fopen("utils/flip_gray_vertical.txt", "r");
    ler_imagem_arkv(GrayFlip, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");

// #################################### FIM - flip_vertical_gray ###########################################

    free_image_rgb(&flip_rgb_vertical);
    free_image_gray(&imgray);
    free_image_rgb(&imrgb);
    free_image_gray(&flip_gray_vertical);

    return 0;
}
