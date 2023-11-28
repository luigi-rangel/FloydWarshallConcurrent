import pandas as pd
import matplotlib.pyplot as plt
import subprocess

solution_path = "./main.exe"
output_path = "output/bin.txt"

num_tests = 4
max_threads = 20
num_attempts = 5

results = {}

for i in range(num_tests):
    results[i] = {}

    for nthreads in range(1, max_threads + 1):
        avg = 0

        for attempt in range(num_attempts):
            subprocess.call([solution_path, str(nthreads), f"input/evaluate-{i}.txt", output_path])

            outputFile = open(output_path, "r")
            line = outputFile.readline()

            avg += int(line[2:])

            outputFile.close()

        results[i][nthreads] = avg / num_attempts

df = pd.DataFrame(results)

size = df.shape[1]
array_sizes = [100, 500, 1000, 2000]

fig, axis = plt.subplots(size // 2, 2)

plt.suptitle("Performance por # de threads")

for i in range(size):
    filtered_df = df[i].transpose()

    plt.subplot(size // 2, 2, i + 1)

    plt.plot(filtered_df.index, filtered_df)
    plt.xlabel("# de threads")
    plt.ylabel("tempo (ms)")
    plt.title(f"grau da entrada: {array_sizes[i]}")

plt.tight_layout()

plt.savefig("./results.jpg")