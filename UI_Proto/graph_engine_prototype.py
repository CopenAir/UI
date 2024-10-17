""" Graph drawer prototype for P1
    17/10/2024 @ 10:05
    graph_engine_prototype.py

    P1    
"""

import random
import colorama

def main():
    GraphEngine()

class GraphEngine(object):
    def __init__(self):
        colorama.init()
        self.ceiling = 10
        # two lists with 24 random datapoints
        self.list1 = [random.randint(1, self.ceiling) for _ in range(24)]
        self.list2 = [random.randint(1, self.ceiling) for _ in range(24)]

        # calculate the median of each list
        # median1 = calculate_median(list1)
        # median2 = calculate_median(list2)

        self.draw()

        # graph_to_draw = input("Please select a graph to draw(1, 2): ")
    
    def draw(self):
        print("Date: 17/10/2024 | Area: A.C.Meyers Vænge")
        print("Substance: PM2.5")
        print("-----------------------------------------\n\n")
        for i in range(self.ceiling, 0, -1):
            if i < 10:
                print(f' {i}', end="|")
            else:
                print(f'{i}', end="|")
            for j in self.list1:
                if j >= i:
                    if i >= 7:
                        print(colorama.Fore.RED + "///", end=" " + colorama.Style.RESET_ALL)
                    else:
                        print(colorama.Fore.GREEN + "///", end=" " + colorama.Style.RESET_ALL)
                else:
                    print("   ", end=" ")
            print("\n", end="")
        print("  +-----------------------------------------------------------------------------------------------")
        print("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24")


if __name__ == "__main__":
    main()