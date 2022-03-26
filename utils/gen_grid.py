from dataclasses import dataclass


@dataclass
class LineSet:
    x_min_bot: float
    x_min_top: float

    y_min: float
    y_max: float

    del_x: float


def generate_grid(m: int = 6e6, n: int = 4.5e6):

    line_set_1 = LineSet(x_min_bot=0, x_min_top=5, y_min=0, y_max=8, del_x=4.5)
    line_set_2 = LineSet(x_min_bot=1.5, x_min_top=-10, y_min=0, y_max=8, del_x=6)

    with open(f"grid_m_{m}-n_{n}.txt", "w") as inFile:
        inFile.write(f"{m+n}\n")

        for i in range(m):
            x = [
                line_set_1.x_min_bot + i * line_set_1.del_x,
                line_set_1.x_min_top + i * line_set_1.del_x,
            ]
            y = [line_set_1.y_min, line_set_1.y_max]

            inFile.write(f"{x[0]} {y[0]} {x[1]} {y[1]}\n")

        for i in range(n):
            x = [
                line_set_2.x_min_bot + i * line_set_2.del_x,
                line_set_2.x_min_top + i * line_set_2.del_x,
            ]
            y = [line_set_2.y_min, line_set_2.y_max]

            inFile.write(f"{x[0]} {y[0]} {x[1]} {y[1]}\n")

        inFile.close()


if __name__ == "__main__":
    generate_grid()
