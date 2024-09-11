import tkinter as tk
import json
import os
import subprocess

# Dados para páginas
page_name = {0: "Iniciar câmera\n(sempre comece por aqui)", 1 : "Gerar uma esfera", 2 : "Gerar um plano", 3 : "Gerar uma malha de triângulos", 4 : "Transformar um objeto", 5 : "Gerar uma fonte de luz", 6: "Gerar um cilíndro"}
object_name = {1 : "sphere", 2 : "plane", 3: "mesh", 4 : "transf", 5 : "light", 6: "cylinder"}
data_pages = [
    ["origin", "target", "up", "cor", "height", "length", "distance",  "ambient color"],
    ["center", "radius", "sp_color", "kd", "ks", "ka", "kr", "kt", "nrugo"],
    ["plane_origin", "plane_normal", "plane_cor", "kd", "ks", "ka", "kr", "kt", "nrugo"],
    ["total_triangles", "total_vertex", "list_vertex", "list_index", "mesh_color", "kd", "ks", "ka", "kr", "kt", "nrugo"],
    ["objetc_name", "object_index", "rotate? eixo, ang", "matrix_line_1", "matrix_line_2", "matrix_line_3", "matrix_line_4"],
    ["light origin", "light intensity"],
    ["base", "axis", "radius", "height", "cor", "kd", "ks", "ka", "kr", "kt", "nrugo"]
]

def compile_and_run():

    if os.path.exists("input.txt"):
        with open("input.txt", "r") as file:
            existing_lines = file.readlines()
    else:
        existing_lines = []

    with open("input.txt", "w") as file:
        file.writelines(existing_lines)
        file.write("generate\n")

    # Compilar main.cpp em um executável chamado "render"
    compile_process = subprocess.run(["g++", "main.cpp", "-o", "render"], capture_output=True, text=True)
    run_process = subprocess.run(["./render.exe"], stdin=open("input.txt", "r"), stdout=open("output.ppm", "w"))
    
    #fecha e limpa o input
    on_closing()

def clear_input_file():
    with open("input.txt", "w") as file:
        file.write("")

def write_on_input(append=False):
    global object_name

    current_data = {}
    for entry in entries[current_page]:
        current_data[entry["label"].cget("text")] = entry["entry"].get()

    # Append to input.txt
    if os.path.exists("input.txt") and append:
        with open("input.txt", "r") as file:
            existing_lines = file.readlines()
    else:
        existing_lines = []

    with open("input.txt", "w") as file:
        file.writelines(existing_lines)

        if current_page != 0:
            file.write(f"{object_name[current_page]}\n")

        for value in current_data.values():
            file.write(f"{value}\n")

def save_current_json(append=False):
    current_data = {}
    for entry in entries[current_page]:
        current_data[entry["label"].cget("text")] = entry["entry"].get()

    # Append to data.json
    if os.path.exists("data.json") and append:
        with open("data.json", "r") as file:
            existing_data = json.load(file)
        existing_data.update(current_data)
        data_to_save = existing_data
    else:
        data_to_save = current_data

    with open("data.json", "w") as file:
        json.dump(data_to_save, file)

def write_to_file():
    for i in range(len(data_pages)):
        show_page(i)
        save_current_json(append=True)
    compile_and_run()

def on_closing():
    for i in range(len(data_pages)):
        show_page(i)
        save_current_json(append=True)
    clear_input_file()
    root.destroy()

def load_data():
    if os.path.exists("data.json"):
        with open("data.json", "r") as file:
            data = json.load(file)
            return data
    return {}

def create_entries(labels, data):
    entries = []
    for label in labels:
        lbl = tk.Label(root, text=label)
        entry = tk.Entry(root)
        #entry.insert(0, data.get(label, ""))
        entries.append({"label": lbl, "entry": entry})
    return entries

def show_menu():
    global page_name

    # Limpar widgets da página anterior
    for widget in root.winfo_children():
        widget.grid_forget()

    menu_label = tk.Label(root, text="Menu", font=('Helvetica', 16, 'bold'))
    menu_label.grid(row=0, column=0, pady=10, columnspan=2)

    # Botões do menu
    for i, page in enumerate(data_pages):
        button = tk.Button(root, text=f"{page_name[i]}", command=lambda i=i: show_page(i))
        button.grid(row=i+1, column=0, padx=5, pady=5)

    save_button.grid(row=len(data_pages) + 1, column=0, pady=20)

def show_page(page_index):
    global current_page
    current_page = page_index

    # Limpar widgets da página anterior
    for widget in root.winfo_children():
        widget.grid_forget()

    page_entries = entries[page_index]
    for i, entry in enumerate(page_entries):
        entry["label"].grid(row=i, column=0, padx=5, pady=5, sticky='w')
        entry["entry"].grid(row=i, column=1, padx=5, pady=5, sticky='we')

    back_to_menu_button.grid(row=len(page_entries) + 1, column=1, pady=10)
    back_to_menu_button_no_save.grid(row=len(page_entries) + 1, column=0, pady=10)

def back_to_menu():
    write_on_input(append=True)
    show_menu()

def back_to_menu_no_save():
    show_menu()

# Inicialização
root = tk.Tk()
root.title("Data Writer")
current_page = 0

# Carregar dados
data = load_data()

# Criar entradas
entries = []
for page in data_pages:
    page_entries = create_entries(page, data)
    entries.append(page_entries)

# Botões
save_button = tk.Button(root, text="Salvar no Arquivo", command=write_to_file)
back_to_menu_button = tk.Button(root, text="Salvar", command=back_to_menu)
back_to_menu_button_no_save = tk.Button(root, text="Cancelar", command=back_to_menu_no_save)

# Mostrar o menu inicial
show_menu()

# Eventos
root.protocol("WM_DELETE_WINDOW", on_closing)

# Loop principal
root.mainloop()
