public class Ex1{
    public static void main(String args[]) throws Exception{
        System.out.print("Digite o valor de x: ");
        double x = EntradaTeclado.leDouble();
        System.out.print("Digite o chute inicial: ");
        double x1 = EntradaTeclado.leDouble();
        double x0;

        do{
            x0 = x1;
            x1 = (x0 + x/x0)/2;
        }
        while((Math.abs(x1 - x0)) > 0.00000001);

        System.out.println(x1);
    }
}