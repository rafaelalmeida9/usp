import java.util.Arrays;
class Placar{
    private int score = 0;
    private String[] scoreMark = {"","(1)","(2)","(3)","(4)","(5)","(6)","(7)","(8)","(9)","(10)"};
    private boolean[] disponivel = {true,true,true,true,true,true,true,true,true,true,true};

    public void add(int posicao, int[] dados){
        if(!disponivel[posicao]) return;
        int pontuacaoObtida = 0;

        if(posicao >= 1 && posicao <= 6){
            for(int i = 0; i < dados.length; i++){
                if(dados[i] == posicao) pontuacaoObtida += posicao;
            }
        }
        else if(posicao == 7){
            Arrays.sort(dados);
            if(dados[0] == dados[1] && dados[1] != dados[2] && dados[2] == dados[3] && dados[3] == dados[4]){
                pontuacaoObtida += 15;
            }
            else if(dados[0] == dados[1] && dados[1] == dados[2] && dados[2] != dados[3] && dados[3] == dados[4]){
                pontuacaoObtida += 15;
            }
        }
        else if(posicao == 8){
            Arrays.sort(dados);
            boolean ehSequencia = true;
            for(int i = 1; i < dados.length;i++){
                if(dados[i] != dados[i-1] + 1){
                    ehSequencia = false;
                }
            }
            if(ehSequencia) pontuacaoObtida += 20;
        }
        else if(posicao == 9){
            Arrays.sort(dados);
            if(dados[0] == dados[1] && dados[1] == dados[2] && dados[2] == dados[3]){
                pontuacaoObtida += 30;
            }
            else if(dados[1] == dados[2] && dados[2] == dados[3] && dados[3] == dados[4]){
                pontuacaoObtida += 30;
            }
        }
        else if(posicao == 10){
            if(dados[0] == dados[1] && dados[1] == dados[2] && dados[2] == dados[3] && dados[3] == dados[4]){
                pontuacaoObtida += 40;
            }
        }
        
        if(posicao == 10){
            if(pontuacaoObtida == 0){
                scoreMark[posicao] = String.format("%3d ",pontuacaoObtida);
            }
            else{
                scoreMark[posicao] = String.format("%4d",pontuacaoObtida);
            }
        }
        else if(pontuacaoObtida >= 10){
            scoreMark[posicao] = String.format("%3d",pontuacaoObtida);
        }
        else{
            scoreMark[posicao] = String.format("%2d ",pontuacaoObtida);
        }
        score += pontuacaoObtida;
        disponivel[posicao] = false;
    }

    public int getScore(){
        return this.score;
    }

    @Override
    public String toString(){
        String tmp = "";
        tmp += "  " + scoreMark[1] + " |    " + scoreMark[7] + "   | " + scoreMark[4] + '\n';
        tmp += "------------------------\n";
        tmp += "  " + scoreMark[2] + " |    " + scoreMark[8] + "   | " + scoreMark[5] + '\n';
        tmp += "------------------------\n";
        tmp += "  " + scoreMark[3] + " |    " + scoreMark[9] + "   | " + scoreMark[6] + '\n';
        tmp += "------------------------\n";
        tmp += "      |   " + scoreMark[10] + "   |\n";
        tmp += "      +----------+";

        return tmp;
    }
}