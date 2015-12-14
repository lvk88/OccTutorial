from itertools import islice as islice
import matplotlib.pyplot as plt

def main():
    file = open('basisFunctions.txt')
    basisFunctionGroup = []
    while True:
        nextLines = list(islice(file,3))
        if not nextLines:
            break
        basisFunctionGroup.append(nextLines)

    basisFunctionNumericalGroup = []
    for basisFunction in basisFunctionGroup:
        values = [float(value) for value in basisFunction[1].split()]
        parameters = [float(param) for param in basisFunction[2].split()]
        basisFunctionNumericalGroup.append( (parameters,values) )


    for n,curve in enumerate(basisFunctionNumericalGroup):
        plt.plot(curve[0],curve[1],label=str(n))
    plt.legend(loc='best')
    plt.show()


    #for n, curve in enumerate(basisFunctionsForPlotting):
    #    plt.plot(curve)
    #
    #plt.show()

if __name__ == "__main__":
    main()
