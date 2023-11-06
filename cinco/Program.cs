using System;
using System.Threading;

public class Program
{
    static int limite = 10000 + 2 ;
    static long[] sol = new long[limite + 2];

    private static long SeriePar(int index)
    {
        return index * 2;
    }
    private static long SerieImPar(int index)
    {
        return (index * index) + 1;
    }

    private static void Serie(object state)
    {
        int index = (int)state;
        var resultado = (SerieImPar(index), SeriePar(index));

        sol[index * 2] = resultado.Item1;
        sol[(index * 2) + 1] = resultado.Item2;
    }

    public static void Main()
    {
        CountdownEvent countdown = new CountdownEvent(limite / 2);

        for (int i = 1; i <= limite / 2; i++)
        {
            ThreadPool.QueueUserWorkItem(state =>
            {
                Serie(state);
                countdown.Signal();
            }, i);
        }

        countdown.Wait();

        for (int i = 2; i < limite; i++)
        {
            Console.Write(sol[i] + " ");
        }
    }
}
