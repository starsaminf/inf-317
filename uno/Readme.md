SISD (Simple instrucción) es una arquitectura de procesador secuencial y la CPU procesa
una sola instrucción de un programa; así mismo, opera en un solo conjunto de datos.
Esto significa que cada instrucción se completa antes de que se ejecute la siguiente.

SIMD (Datos Múltiples) es una arquitectura de procesador que permite que una sola
instrucción se ejecute en múltiples conjuntos de datos simultáneamente.


MISD (Instrucción múltiple de Datos Individuales) es una arquitectura de procesador
que permite que múltiples instrucciones se ejecuten en un solo conjunto de datos con
desventajas.

MIMD (Instrucción múltiple de Datos múltiples) es una arquitectura de procesador que
permite que múltiples instrucciones se ejecuten en múltiples conjuntos de datos
simultáneamente, lo que proporciona una mayor capacidad de procesamiento para
aplicaciones que requieren un alto nivel de paralelismo.

Openmp .- usa MIMD y el SIMD

    MPI (Message Passing Interface): utiliza una arquitectura MIMD (Multiple
    Instruction Multiple Data) para el procesamiento paralelo en sistemas de memoria
    distribuida. MPI permite la comunicación entre procesos y la coordinación de la
    ejecución en sistemas distribuidos y se utiliza comúnmente en aplicaciones de
    simulación y modelado

    Multiprocessing: utiliza una arquitectura MIMD (Multiple Instruction Multiple
    Data) para el procesamiento paralelo en sistemas de memoria compartida (SMP) y
    distribuida. La biblioteca multiprocessing de Python permite la creación de procesos
    que pueden ejecutarse en paralelo en diferentes núcleos o incluso en diferentes
    máquinas, lo que permite una mayor velocidad de procesamiento y escalabilidad.

Threads(NET): utiliza una arquitectura SISD (Single Instruction Single Data) o MIMD
(Multiple Instruction Multiple Data) dependiendo de la implementación. Los hilos son
subprocesos de ejecución que pueden ser programados para ejecutarse en paralelo
en diferentes núcleos de procesamiento. Los hilos también pueden ser
implementados en sistemas de memoria compartida (SMP) o distribuida. Los hilos
se utilizan comúnmente en aplicaciones que requieren una alta concurrencia, como
servidores web o aplicaciones de bases de datos.


