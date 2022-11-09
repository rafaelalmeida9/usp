public class Ex4{
    public static void main(String args[]) throws Exception{
        int x = EntradaTeclado.leInt();

        for(int i = 0; i < x; i++){
            for(int j = 0; j < i; j++){
                System.out.print(" ");
            }
            for(int j = i; j < x; j++){
                System.out.print("*");
            }
            System.out.println();
        }
    }
}
