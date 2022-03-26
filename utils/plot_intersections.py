from matplotlib import collections as mc
import matplotlib.pyplot as plt


def parse_segments(handler, n):
    segments = []
    for i in range(n):
        segments.append([float(x) for x in handler.readline().split()])

    segments = [[(seg[0], seg[1]), (seg[2], seg[3])] for seg in segments]

    return segments


def parse_intersections(handler, n):
    intersections = []

    for _ in range(n):
        intersections.append([float(x) for x in handler.readline().split()])

    return intersections


def plot_intersections(output_path):
    result = open(output_path, "r")

    num_segments = int(result.readline())
    segments = parse_segments(result, num_segments)

    num_intersections = int(result.readline())
    intersections = parse_intersections(result, num_intersections)

    result.close()

    lc = mc.LineCollection(segments, linewidths=2)

    fig, ax = plt.subplots(figsize=(14, 14))
    ax.add_collection(lc)
    ax.autoscale()
    ax.margins(0.1)

    for pt in intersections:
        ax.plot(pt[0], pt[1], marker=".", markersize=8, markeredgecolor="black")

    plt.show()


if __name__ == "__main__":
    plot_intersections("../bin/output.txt")
