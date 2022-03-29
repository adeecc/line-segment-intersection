import imp


import pandas as pd

data = []
f = open("../data/bm_linear.txt")

for line in f.readlines():
    bm_name, wall_time, _, cpu_time, _, num_iter = line.split()
    _, m, n = bm_name.split("/")

    data.append(
        {
            "bm_name": bm_name,
            "wall_time": int(wall_time),
            "cpu_time": int(cpu_time),
            "num_iter": int(num_iter),
            "m": int(m),
            "n": int(n),
            "num_segments": int(m) + int(n),
            "num_intersections": int(m) * int(n),
        }
    )


df = pd.DataFrame(data)
df.head()
df.sort_values(by="num_segments")
df.to_csv("../data/bm_linear.csv", index=False)
