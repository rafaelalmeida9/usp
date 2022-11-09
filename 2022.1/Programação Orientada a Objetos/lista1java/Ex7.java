public class Ex7{
    public static void main(String args[]) throws Exception{
        float x;
        float max = -999999999;
        float min = 999999999;

        while(true){
            x = (float)EntradaTeclado.leDouble();
            if(x == 0) break;

            max = Math.max(x, max);
            min = Math.min(x, min);
        }

        System.out.println("O maior número da sequência é: " + max);
        System.out.println("O menor número da sequência é: " + min);
    }
}
