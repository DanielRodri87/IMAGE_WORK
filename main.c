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
    ImageGray flip_gray;

    system("pause");

    ler_imagem_arkv(arq, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");

    
    converter_para_gray(&imrgb, &imgray);

    FILE *GrayExample;
    GrayExample = fopen("utils/example_GRAY.txt", "w");
    salvar_imagem_arkv(&imgray, GrayExample);

    GrayExample = fopen("utils/example_GRAY.txt", "r");
    ler_imagem_arkv(GrayExample, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");

    // Inicializa flip_gray
    flip_gray.dim.altura = imgray.dim.altura;
    flip_gray.dim.largura = imgray.dim.largura;
    alocarGray(flip_gray.dim.altura, flip_gray.dim.largura, &(flip_gray.pixels));

    // Chama a função ajustada
    flip_vertical_gray(&imgray, &flip_gray);

    FILE *GrayFlip;
    GrayFlip = fopen("utils/flip_GRAY.txt", "w");
    salvar_imagem_arkv(&flip_gray, GrayFlip);

    GrayFlip = fopen("utils/flip_GRAY.txt", "r");
    ler_imagem_arkv(GrayFlip, &imrgb);
    printImageColor(&imrgb);

    free_image_gray(&imgray);
    free_image_rgb(&imrgb);
    free_image_gray(&flip_gray);

    return 0;
}
