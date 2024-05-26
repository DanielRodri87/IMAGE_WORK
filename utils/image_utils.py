from PIL import Image

def txt_from_image_gray(image_path, output_path, gray=True):
    img = Image.open(image_path)

    if gray:
        img = img.convert('L')
    
    largura, altura = img.size
    pixels = list(img.getdata())
    
    with open(output_path, 'w') as file:
        file.write(f"{largura}\n")
        file.write(f"{altura}\n")
        for y in range(altura):
            for x in range(largura):
                pixel = str(pixels[y * largura + x]).replace(",", "").replace("(", "").replace(")", "")
                file.write(f"{pixel},")
            file.write("\n")

def image_gray_from_txt(txt_path, output_path):
    with open(txt_path, 'r') as file:
        lines = file.readlines()

        largura = int(lines[0].strip())
        altura = int(lines[1].strip())

        nova_imagem = Image.new('L', (largura, altura))

        for y in range(altura):
            for x in range(largura):
                gray_value = int(lines[2 + y].split(',')[x].strip())
                nova_imagem.putpixel((x, y), gray_value)

        # Salva a imagem resultante
        nova_imagem.save(output_path)


def image_rgb_from_txt(txt_path, output_path):
    with open(txt_path, 'r') as file:
        lines = file.readlines()

        largura = int(lines[0].strip())
        altura = int(lines[1].strip())

        nova_imagem = Image.new('RGB', (largura, altura))

        for y in range(altura):
            for x in range(largura):
                pixel = tuple(map(int, lines[2 + y].split(',')[x].strip().split()))
                nova_imagem.putpixel((x, y), pixel)

        # Salva a imagem resultante
        nova_imagem.save(output_path)
