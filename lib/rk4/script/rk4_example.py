import rk4
import time
if __name__ == '__main__':
    s = [1, 2, 3, 4, 5, 6]
    ti = 0
    dt = 0.02
    tf = 1000

    rk4.sys_init()
    print("RK4 Example:")
    s = rk4.iterate_range(0.02, 0, 70*60, 8000000, 0, 0, 4900, 0, 0)
    for r in s:
        print(r)
