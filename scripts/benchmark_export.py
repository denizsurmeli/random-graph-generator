import pandas as pd
import matplotlib.pyplot as plt


def export_graph(in_path, out_path):
    df = pd.read_csv(in_path)
    df = df.sort_values("input_size")
    df.plot(x="input_size", y=["HH", "PM", "SA"], kind="bar")
    plt.savefig(out_path)
