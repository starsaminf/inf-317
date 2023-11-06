import multiprocessing

def serie_par(index):
    return index * 2

def serie_impar(index):
    return (index * index) + 1  

def serie(index):
    return serie_par(index), serie_impar(index)
 
limite = 10000

procesadores = multiprocessing.cpu_count()
print("Cantidad de procesadores ", procesadores)

pool = multiprocessing.Pool(processes=procesadores)  

argumentos = [(i,) for i in range(limite + 1)]

resultados = pool.starmap(serie, argumentos)     

for x, y in resultados:
    print(str(x) + " " + str(y))

