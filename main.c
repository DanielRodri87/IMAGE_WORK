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

    system("pause");

    ler_imagem_arkv(arq, &imrgb);
    printImageColor(&imrgb);
    
    converter_para_gray(&imrgb, &imgray);

    FILE *GrayExample;
    GrayExample = fopen("utils/example_GRAY.txt", "w");
    salvar_imagem_arkv(&imgray, GrayExample);

    GrayExample = fopen("utils/example_GRAY.txt", "r");
    ler_imagem_arkv(GrayExample, &imrgb);
    printImageColor(&imrgb);

    free_image_gray(&imgray);
    free_image_rgb(&imrgb);

    return 0;
}
