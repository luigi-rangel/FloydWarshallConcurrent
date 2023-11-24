import networkx as nx
import numpy as np
import random
import os

os.makedirs("input", exist_ok=True)

for i in range(10):
    # num_nodes = np.random.randint(50, 1000)
    # num_edges = num_nodes * np.random.random() * 3

    num_nodes = 10
    num_edges = 15

    fPath = f"input/test-{i}.txt"

    # Gere um grafo aleatório
    G = nx.gnm_random_graph(num_nodes, num_edges)

    # Adicione pesos aleatórios às arestas
    for edge in G.edges():
        weight = random.uniform(0.1, 1.0)  # Peso aleatório entre 0.1 e 1
        G[edge[0]][edge[1]]['weight'] = weight

    nx.write_edgelist(G, fPath)

    # Leia o conteúdo do arquivo
    with open(fPath, "r") as file:
        content = file.read()

    # Adicione o comentário ao início do conteúdo
    content = f"# {num_nodes}\n" + content

    # Reescreva o arquivo com o comentário
    with open(fPath, "w") as file:
        file.write(content)