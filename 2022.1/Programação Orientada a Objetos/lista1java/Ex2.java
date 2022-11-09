public class Ex2{
    public static void main(String args[]){

        double a;
        double b;
        double c;

        try {
            a = EntradaTeclado.leDouble();
            b = EntradaTeclado.leDouble();
            c = EntradaTeclado.leDouble();
           } catch (Exception e) {
            System.out.println("Isso não é um número, digite outro valor");
            return;
           }

        double delta = b*b - 4*a*c;

        if(delta < 0){
            System.out.println("Delta negativo, não existem raízes reais");
            return;
        }

        double x1 = (-1*b + Math.sqrt(delta))/(2*a);
        double x2 = (-1*b - Math.sqrt(delta))/(2*a);

        System.out.println("a raiz x1 vale: " + x1 + " e a raiz x2 vale: " + x2);
    }
}