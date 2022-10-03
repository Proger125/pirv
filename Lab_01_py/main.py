import matplotlib.pyplot as plt

if __name__ == '__main__':
    f = open("output.txt", "r")
    block_sizes = [1, 10, 50, 100, 500]
    for i in range(4):
        matrix_size = int(f.readline())
        cons_values = []
        par1_values = []
        par2_values = []
        for j in range(5):
            line = f.readline()
            tokens = line.split(' ')
            cons_values.append(int(tokens[1]))
            par1_values.append(int(tokens[2]))
            par2_values.append(int(tokens[3]))
        plt.xlabel('Block size')
        plt.ylabel('Time')
        plots = [plt.plot(block_sizes, cons_values, label="Последовательный алгоритм")[0],
                 plt.plot(block_sizes, par1_values, label="Параллельный алгоритм 1 цикл")[0],
                 plt.plot(block_sizes, par2_values, label="Параллельный алгоритм 2 цикл")[0]]
        plt.legend(handles=plots)

        plt.show()
