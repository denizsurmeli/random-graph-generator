import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def export_graph(in_path, out_path):
    df = pd.read_csv(in_path)
    columns = ["HH", "PM", "SA"]
    for column in columns:
        df[column] = pd.to_numeric(df[column])
    df = df.sort_values("input_size")
    ax = df.plot.bar(x='input_size')
    ax.set_xticks(np.arange(0, len(df) + 1, len(df) / 10))
    plt.savefig(out_path)
    df.to_csv(in_path)


def export_pair_graphs(in_path):
    OUT_PATH = "../feeds/assets/"
    columns = ["HH", "PM", "SA"]
    pairs = [
        ["HH", "PM"],
        ["HH", "SA"],
        ["PM", "SA"]
    ]
    df = pd.read_csv(in_path)
    df["input_size"] = pd.to_numeric(df["input_size"])
    for column in columns:
        df[column] = pd.to_numeric(df[column])
    df = df.sort_values("input_size")
    for pair in pairs:
        ax = df.plot.bar(x='input_size', y=pair)
        ax.set_xticks(np.arange(0, len(df) + 1, len(df) / 10))
        plt.savefig(OUT_PATH + "".join(pair))
