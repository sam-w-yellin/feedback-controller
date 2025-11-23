import re
import sys
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) < 2:
        print("usage: python3 plot_sim.py <path/to/sim.log>")
        sys.exit(1)

    path = sys.argv[1]

    temps = []

    with open(path) as f:
        for line in f:
            m = re.search(r"TEMP_C:\s*(\d+)", line)
            if m:
                temps.append(int(m.group(1)))

    steps = list(range(len(temps)))

    plt.plot(steps, temps)
    plt.xlabel("Step")
    plt.ylabel("Temperature (C)")
    plt.title("Controller Simulation")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()
