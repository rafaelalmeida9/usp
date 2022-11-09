public class Ex8{
    public static double f(double x){
        int a = 1;
        int b = -1;
        int c = -13;
        int d = 8;

        return (a*x*x*x + b*x*x + c*x + d);
    }
    
    public static void main(String args[]) throws Exception{

        double a = EntradaTeclado.leDouble();
        double b = EntradaTeclado.leDouble();
        
        double c = (a + b)/2;
        int contador = 0;

        while(Math.abs(a-b) > 0.0000001){
    
            if(f(c) * f(a) < 0){
                b = c;
                c = (a + b)/2;
            }
            else{
                a = c;
                c = (a + b)/2;
            }

            contador++;
        }

        System.out.println("A raiz encontrada no intervalo dado foi: " + c);
        System.out.println("Foram realizadas " + contador + " iterações");
    }
}
