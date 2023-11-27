import pandas as pd
import matplotlib.pyplot as plt
import subprocess
import time

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

        results[i][nthreads] = avg / num_attempts

df = pd.DataFrame(results)

filtered_df = df.transpose().mean()

plt.bar(filtered_df.index, filtered_df)
plt.savefig()