using System;
using System.Threading;

class Program
{
    static double pi = 0.0;

    public static void CalculoPi(int inicio, int fin)
    {
        object locker = new object();
        double sol = 0.0;

        for (int k = inicio; k < fin; k++)
        {
            double term = 1.0 / (2 * k + 1);
            if (k % 2 == 0)
            {
                sol += term;
            }
            else
            {
                sol -= term;
            }
        }

        lock (locker)
        {
            pi += sol;
        }
    }
    public static void Main(string[] args)
    {
        int n = 1000;
        int procesadores = Environment.ProcessorCount;
        int procesadorLimite = n / procesadores;

        Thread[] threads = new Thread[procesadores];

        for (int i = 0; i < procesadores; i++)
        {
            int startTerm = i * procesadorLimite;
            int endTerm = (i + 1) * procesadorLimite;
            threads[i] = new Thread(() => CalculoPi(startTerm, endTerm));
            threads[i].Start();
        }

        foreach (var thread in threads)
        {
            thread.Join();
        }

        pi *= 4.0;

        Console.WriteLine($"Pi = : {pi}");
    }
}
