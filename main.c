#include <stdio.h>
#include "image.h"

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb);
void aplicar_blur_rgb(ImageRGB *imrgb);
void aplicar_clahe_rgb(ImageRGB *imrgb);
void aplicar_transpose_rgb(ImageRGB *imrgb);
void aplicar_flip_vertical_rgb(ImageRGB *imrgb);
void aplicar_flip_horizontal_rgb(ImageRGB *imrgb);
void aplicar_transpose_gray(ImageGray *imgray);
void aplicar_clahe_gray(ImageGray *imgray);
void aplicar_blur_gray(ImageGray *imgray);
void aplicar_flip_vertical_gray(ImageGray *imgray);

int main() {
    FILE *arq = fopen("utils/input_image_example_RGB.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    system("pause");
    ImageRGB imrgb;
    criar_imagem_rgb(arq, &imrgb);

    aplicar_blur_rgb(&imrgb);
    aplicar_clahe_rgb(&imrgb);
    aplicar_transpose_rgb(&imrgb);
    aplicar_flip_vertical_rgb(&imrgb);
    aplicar_flip_horizontal_rgb(&imrgb);

    system("pause");

    ImageGray imgray;
    converter_para_gray(&imrgb, &imgray);

    FILE *GrayExample;
    GrayExample = fopen("utils/example_GRAY.txt", "w");
    salvar_imagem_arkv(&imgray, GrayExample);

    GrayExample = fopen("utils/example_GRAY.txt", "r");
    ler_imagem_arkv(GrayExample, &imrgb);
    printImageColor(&imrgb);
    printf("\n\n\n");


    aplicar_transpose_gray(&imgray);
    aplicar_clahe_gray(&imgray);
    aplicar_blur_gray(&imgray);
    aplicar_flip_vertical_gray(&imgray);
    system("pause");

    return 0;
}

void criar_imagem_rgb(FILE *arq, ImageRGB *imrgb) {
    ler_imagem_arkv(arq, imrgb);
    printImageColor(imrgb);
    printf("\n\n\n");
}

void aplicar_blur_rgb(ImageRGB *imrgb) {
    ImageRGB blur_rgb;
    blur_rgb.dim.altura = imrgb->dim.altura;
    blur_rgb.dim.largura = imrgb->dim.largura;
    alocarRGB(blur_rgb.dim.altura, blur_rgb.dim.largura, &(blur_rgb.pixels));

    blur_rgb = *median_blur_rgb(imrgb, 15);

    FILE *RGBBlur = fopen("utils/blur_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&blur_rgb, RGBBlur);
    
    RGBBlur = fopen("utils/blur_rgb.txt", "r");
    ImageRGB img_saida_blur_rgb;
    ler_imagem_arkv(RGBBlur, &img_saida_blur_rgb);
    printImageColor(&img_saida_blur_rgb);
    printf("\n\n\n");
}

void aplicar_clahe_rgb(ImageRGB *imrgb) {
    ImageRGB clahe_rgb_img;
    clahe_rgb_img.dim.altura = imrgb->dim.altura;
    clahe_rgb_img.dim.largura = imrgb->dim.largura;
    alocarRGB(clahe_rgb_img.dim.altura, clahe_rgb_img.dim.largura, &(clahe_rgb_img.pixels));

    clahe_rgb_img = *clahe_rgb(imrgb, 256, 40);

    FILE *RGBClahe = fopen("utils/clahe_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&clahe_rgb_img, RGBClahe);
    
    RGBClahe = fopen("utils/clahe_rgb.txt", "r");
    ImageRGB img_saida_clahe_rgb;
    ler_imagem_arkv(RGBClahe, &img_saida_clahe_rgb);
    printImageColor(&img_saida_clahe_rgb);
    printf("\n\n\n");
}

void aplicar_transpose_rgb(ImageRGB *imrgb) {
    ImageRGB transpose_rgb_var;
    transpose_rgb_var.dim.altura = imrgb->dim.altura;
    transpose_rgb_var.dim.largura = imrgb->dim.largura;
    alocarRGB(transpose_rgb_var.dim.altura, transpose_rgb_var.dim.largura, &(transpose_rgb_var.pixels));

    transpose_rgb(imrgb, &transpose_rgb_var);

    FILE *transporgb = fopen("utils/transpose_rgb.txt", "w");
    salvar_imagem_arkv_rgb(&transpose_rgb_var, transporgb);
    
    transporgb = fopen("utils/transpose_rgb.txt", "r");
    ImageRGB img_saida_transpose_rgb;
    ler_imagem_arkv(transporgb, &img_saida_transpose_rgb);
    printImageColor(&img_saida_transpose_rgb);
    printf("\n\n\n");
}

void aplicar_flip_vertical_rgb(ImageRGB *imrgb) {
    ImageRGB flip_rgb_vertical;
    flip_rgb_vertical.dim.altura = imrgb->dim.altura;
    flip_rgb_vertical.dim.largura = imrgb->dim.largura;
    alocarRGB(flip_rgb_vertical.dim.altura, flip_rgb_vertical.dim.largura, &(flip_rgb_vertical.pixels));

    flip_vertical_rgb(imrgb, &flip_rgb_vertical);

    FILE *RGBFlip = fopen("utils/flip_rgb_vertical.txt", "w");
    salvar_imagem_arkv_rgb(&flip_rgb_vertical, RGBFlip);
    
    RGBFlip = fopen("utils/flip_rgb_vertical.txt", "r");
    ImageRGB flip_rgb_vertical_saida;
    ler_imagem_arkv(RGBFlip, &flip_rgb_vertical_saida);
    printImageColor(&flip_rgb_vertical_saida);
    printf("\n\n\n");
}

void aplicar_flip_horizontal_rgb(ImageRGB *imrgb) {
    ImageRGB flip_rgb_horizontal;
    flip_rgb_horizontal.dim.altura = imrgb->dim.altura;
    flip_rgb_horizontal.dim.largura = imrgb->dim.largura;
    alocarRGB(flip_rgb_horizontal.dim.altura, flip_rgb_horizontal.dim.largura, &(flip_rgb_horizontal.pixels));

    flip_horizontal_rgb(imrgb, &flip_rgb_horizontal);

    FILE *RGBFlipHorizontal = fopen("utils/flip_rgb_horizontal.txt", "w");
    salvar_imagem_arkv_rgb(&flip_rgb_horizontal, RGBFlipHorizontal);
    
    RGBFlipHorizontal = fopen("utils/flip_rgb_horizontal.txt", "r");
    ImageRGB flip_rgb_horizontal_saida;
    ler_imagem_arkv(RGBFlipHorizontal, &flip_rgb_horizontal_saida);
    printImageColor(&flip_rgb_horizontal_saida);
    printf("\n\n\n");
}

void aplicar_transpose_gray(ImageGray *imgray) {
    ImageGray transpose_gray_var;
    transpose_gray_var.dim.altura = imgray->dim.altura;
    transpose_gray_var.dim.largura = imgray->dim.largura;
    alocarGray(transpose_gray_var.dim.altura, transpose_gray_var.dim.largura, &(transpose_gray_var.pixels));

    transpose_gray(imgray, &transpose_gray_var);

    FILE *transpogray = fopen("utils/transpose_gray.txt", "w");
    salvar_imagem_arkv(&transpose_gray_var, transpogray);
    
    transpogray = fopen("utils/transpose_gray.txt", "r");
    ImageRGB transpose_gray_saida;
    ler_imagem_arkv(transpogray, &transpose_gray_saida);
    printImageColor(&transpose_gray_saida);
    printf("\n\n\n");
}

void aplicar_clahe_gray(ImageGray *imgray) {
    ImageGray clahe_gray_saida;
    clahe_gray_saida.dim.altura = imgray->dim.altura;
    clahe_gray_saida.dim.largura = imgray->dim.largura;
    alocarGray(clahe_gray_saida.dim.altura, clahe_gray_saida.dim.largura, &(clahe_gray_saida.pixels));

    clahe_gray_saida = *clahe_gray(imgray, 256, 90);

    FILE *GrayClahe = fopen("utils/clahe_gray.txt", "w");
    salvar_imagem_arkv(&clahe_gray_saida, GrayClahe);
    
    GrayClahe = fopen("utils/clahe_gray.txt", "r");
    ImageRGB img_clahe_gray_saida;
    ler_imagem_arkv(GrayClahe, &img_clahe_gray_saida);
    printImageColor(&img_clahe_gray_saida);
    printf("\n\n\n");
}

void aplicar_blur_gray(ImageGray *imgray) {
    ImageGray blur_gray;
    blur_gray.dim.altura = imgray->dim.altura;
    blur_gray.dim.largura = imgray->dim.largura;
    alocarGray(blur_gray.dim.altura, blur_gray.dim.largura, &(blur_gray.pixels));

    blur_gray = *median_blur_gray(imgray, 15);

    FILE *GrayBlur = fopen("utils/blur_gray.txt", "w");
    salvar_imagem_arkv(&blur_gray, GrayBlur);
    
    GrayBlur = fopen("utils/blur_gray.txt", "r");
    ImageRGB img_blur_gray_saida;
    ler_imagem_arkv(GrayBlur, &img_blur_gray_saida);
    printImageColor(&img_blur_gray_saida);
    printf("\n\n\n");
}

void aplicar_flip_vertical_gray(ImageGray *imgray) {
    ImageGray flip_gray_vertical;
    flip_gray_vertical.dim.altura = imgray->dim.altura;
    flip_gray_vertical.dim.largura = imgray->dim.largura;
    alocarGray(flip_gray_vertical.dim.altura, flip_gray_vertical.dim.largura, &(flip_gray_vertical.pixels));

    flip_vertical_gray(imgray, &flip_gray_vertical);

    FILE *GrayFlipVertical = fopen("utils/flip_gray_vertical.txt", "w");
    salvar_imagem_arkv(&flip_gray_vertical, GrayFlipVertical);
    
    GrayFlipVertical = fopen("utils/flip_gray_vertical.txt", "r");
    ImageRGB img_flip_gray_vertical_saida;
    ler_imagem_arkv(GrayFlipVertical, &img_flip_gray_vertical_saida);
    printImageColor(&img_flip_gray_vertical_saida);
    printf("\n\n\n");
}
