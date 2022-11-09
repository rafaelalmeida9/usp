public class Ex5{
    public static void main(String args[]) throws Exception{
        int x = EntradaTeclado.leInt();

        int div = 0;
        int minDiv = 99999999;

        for(int i = 2; i <= x; i++){
            if(x%i == 0){
                div++;
                minDiv = Math.min(minDiv,i);
            }
        }

        if(div == 1){
            System.out.println("O número " + x + " é primo");
        }
        else{
            System.out.println("O número " + x + " não é primo");
            System.out.println("Seu menor divisor é o " + minDiv);
        }
    }
}
