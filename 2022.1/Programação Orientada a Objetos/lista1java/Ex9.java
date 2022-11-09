public class Ex9{
    public static double f1(double x){
        int a = 3;
        int b = -2;
        int c = -13;

        return (a*x*x + b*x + c);
    }

    public static double f(double x){
        int a = 1;
        int b = -1;
        int c = -13;
        int d = 8;

        return (a*x*x*x + b*x*x + c*x + d);
    }

    public static void main(String args[]) throws Exception{

        double x0 = EntradaTeclado.leDouble();
        double x1 = x0;
        
        int contador = 0;

        do{
            x0 = x1;
            x1 = x0 - (f(x0)/f1(x0));

            contador++;
        }while(Math.abs(x1 - x0) > 0.0000001);

        System.out.println("A raiz encontrada foi: " + x1);
        System.out.println("Foram realizadas " + contador + " iterações");
    }
}
