import networkx as nx

in_file = "./test.in"
outFile = "./test.out"

in_test = nx.floyd_warshall(nx.read_edgelist(in_file), weight='weight')

validator = {a: dict(b) for a, b in in_test.items()}

def load_matrix(input_file):
    matrix = []

    with open(input_file, 'r') as file:
        lines = file.readlines()

        for line in lines:
            # Remove espaços em branco e caracteres especiais
            clean_line = line.strip('{}\n').split()

            # Converte os elementos da linha para inteiros ou float, conforme necessário
            matrix_line = [float(x) for x in clean_line]

            matrix.append(matrix_line)

    return matrix

out_matrix = load_matrix(outFile)

error = False

for i in validator:
    for j in validator[i]:
        if validator[i][j] - out_matrix[int(i)][int(j)] > 1e-6: 
            print(f"erro: {validator[i][j]} != {out_matrix[int(i)][int(j)]}")
            error = True

if not error: print("Algoritmo executado corretamente")