import random

vertices = []
faces = []

center = "0 0 0"
target = "1 0 0"
up = "0 1 0"
color = "144 238 144"
width = "500"
height = "500"
dist = "1"

# Valores padrão para os novos componentes
kd = "0.5"
ks = "0.5"
ka = "0.1"
kr = "0.3"
kt = "0.0"
nrugo = "10"

with open("gourd.obj", "r") as file:
    for line in file:
        parts = line.split()
        if parts[0] == "v": 
            x = str(float(parts[1]))
            y = str(float(parts[2]))
            z = str(float(parts[3]))
            vertices.append([x, y, z])
        elif parts[0] == "f":
            faces.append([int(parts[1]), int(parts[2]), int(parts[3])])
        else:
            print("Deu merda")

with open("meshImage.txt", "w") as file:
    file.write(f"{center}\n{target}\n{up}\n{color}\n{width}\n{height}\n{dist}\n\n")
    for i in range(len(faces)):
        file.write("mesh 1 3 \n")
        for j in range(3):
            for k in range(3):
                file.write(vertices[(faces[i][j])-1][k] + " ")
            file.write("\n")
        R = random.randint(0, 255)
        G = random.randint(0, 255)
        B = random.randint(0, 255)
        file.write(f"0 1 2\n{R} {G} {B}\n")
        # Adiciona os novos componentes
        file.write(f"{kd} {ks} {ka} {kr} {kt} {nrugo}\n\n")
    file.write("generate")
