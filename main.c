#include <stdio.h>
#include "image.h"

int main() {
    FILE *arq;
    arq = fopen("utils/input_image_example_RGB.txt", "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    ImageGray *imgray;
    ImageRGB *imrgb;

    ler_imagem_arkv(arq, imrgb);
    
    printImageColor(imrgb);
    
    // imgray = converter_para_gray(imrgb, imgray);
    
    // printImageGray(imgray);

    free_image_gray(imgray);
    free_image_rgb(imrgb);

    return 0;
}
