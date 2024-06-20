import tkinter as tk
from tkinter import filedialog
from image_utils import txt_from_image_gray

def select_image():
    root = tk.Tk()
    root.withdraw()  # Esconder a janela principal
    file_path = filedialog.askopenfilename(
        title="Selecione uma imagem",
        filetypes=[("Image Files", "*.png *.jpg *.jpeg *.bmp *.gif")]
    )
    
    if file_path:
        output_path = "utils/input_image_example_RGB.txt"
        txt_from_image_gray(file_path, output_path, gray=False)
        print(f"Imagem selecionada: {file_path}")
        print(f"Arquivo de texto salvo em: {output_path}")
    else:
        print("Nenhuma imagem selecionada.")
    
    return file_path

if __name__ == "__main__":
    select_image()
