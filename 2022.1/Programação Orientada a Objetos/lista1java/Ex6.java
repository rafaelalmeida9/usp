public class Ex6{
    public static void main(String args[]) throws Exception{
        int x = EntradaTeclado.leInt();

        int div;

        for(int i = x-1; i >= 2; i--){
            div = 0;
            for(int j = 1; j <= i; j++){
                if(i%j == 0) div++;
            }

            if(div == 2){
                System.out.println("O primeiro primo menor que " + x + " é: " + i);
                return;
            }
        }
    }
}
