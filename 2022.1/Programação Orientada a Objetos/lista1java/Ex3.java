public class Ex3{
    public static void main(String args[]) throws Exception{
        int x = EntradaTeclado.leInt();

        for(int i = 0; i < x; i++){
            for(int j = i; j < x; j++){
                System.out.print("*");
            }
            System.out.println();
        }
    }
}
