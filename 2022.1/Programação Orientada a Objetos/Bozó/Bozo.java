public class Bozo {
    public static void main(String[] args) throws Exception{
        RolaDados rolaDados = new RolaDados(5);
        Placar placar = new Placar();

        for(int i = 0; i < 10; i++){
            if(i == 0) System.out.println("Pressione enter para iniciar o jogo");
            else System.out.println("Pressione enter para ir ao próximo round");
            String entrada = EntradaTeclado.leString();

            System.out.printf("RODADA %d\n",i+1);

            int[] dados = rolaDados.rolar();
            System.out.println(rolaDados.toString());
            
            System.out.println("Digite os dados que deseja rolar:");
            entrada = EntradaTeclado.leString();
            dados = rolaDados.rolar(entrada);
            System.out.println(rolaDados.toString());

            System.out.println("Digite os dados que deseja rolar:");
            entrada = EntradaTeclado.leString();
            dados = rolaDados.rolar(entrada);
            System.out.println(rolaDados.toString());

            System.out.println("PLACAR ATUAL");
            System.out.println(placar.toString());

            System.out.println("Digite a posição que você quer ocupar");
            int posicao = EntradaTeclado.leInt();
            placar.add(posicao, dados);

            System.out.println("NOVO PLACAR");
            System.out.println(placar.toString());
            System.out.printf("Score atual: %d\n\n",placar.getScore());
        }

        System.out.printf("FIM DO JOGO\nPontuação final: %d\n",placar.getScore());
    }
}