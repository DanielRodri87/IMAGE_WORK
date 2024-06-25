from PIL import Image, ImageDraw, ImageFilter
import numpy as np

# Função para encontrar as cores predominantes
def get_dominant_colors(image, k=2):
    small_image = image.resize((50, 50), Image.Resampling.LANCZOS)
    result = small_image.convert('P', palette=Image.Palette.ADAPTIVE, colors=k)
    result = result.convert('RGB')
    palette = result.getcolors(50 * 50)
    palette = sorted(palette, key=lambda t: t[0], reverse=True)
    dominant_colors = [color for count, color in palette[:k]]
    return dominant_colors

# Função para criar um degradê radial
def create_radial_gradient(width, height, start_color, end_color):
    center_x, center_y = width // 2, height // 2
    max_radius = np.sqrt(center_x**2 + center_y**2)
    gradient = Image.new('RGB', (width, height), start_color)
    for y in range(height):
        for x in range(width):
            distance_to_center = np.sqrt((x - center_x)**2 + (y - center_y)**2)
            blend_factor = min(distance_to_center / max_radius, 1)
            r = int(start_color[0] * (1 - blend_factor) + end_color[0] * blend_factor)
            g = int(start_color[1] * (1 - blend_factor) + end_color[1] * blend_factor)
            b = int(start_color[2] * (1 - blend_factor) + end_color[2] * blend_factor)
            gradient.putpixel((x, y), (r, g, b))
    return gradient

# Abrir a imagem original
img = Image.open("image_rgb.png")

# Calcular as cores predominantes
dominant_colors = get_dominant_colors(img)
start_color = dominant_colors[0]
end_color = dominant_colors[1] if len(dominant_colors) > 1 else dominant_colors[0]

# Redimensionar a imagem mantendo a proporção
img.thumbnail((1450, 700), Image.Resampling.LANCZOS)

# Criar um fundo com degradê radial
background = create_radial_gradient(1450, 700, start_color, end_color)

# Calcular a posição para centralizar a imagem redimensionada
x_offset = (1450 - img.width) // 2
y_offset = (700 - img.height) // 2

# Colar a imagem redimensionada no fundo
background.paste(img, (x_offset, y_offset))

# Mostrar a imagem final
background.show()

# Salvar a imagem final se necessário
# background.save("output_image.png")
