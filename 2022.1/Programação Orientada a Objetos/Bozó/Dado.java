public class Dado {

    private int lados;
    private int ladoAtual;

    public Dado(){
        this.lados = 6;
        this.ladoAtual = 1;
    }

    public Dado(int n){
        this.lados = n;
    }

    public int getLado(){
        return this.ladoAtual;
    }

    public int rolar(){
        Random random = new Random();
        this.ladoAtual = random.getIntRand(this.lados) + 1;
        return this.ladoAtual;
    }

    @Override
    public String toString(){
        if(this.ladoAtual == 1){
            return "+-----+|     ||  *  ||     |+-----+";
        }
        else if(this.ladoAtual == 2){
            return "+-----+|  *  ||     ||  *  |+-----+";
        }
        else if(this.ladoAtual == 3){
            return "+-----+|*    ||  *  ||    *|+-----+";
        }
        else if(this.ladoAtual == 4){
            return "+-----+|*   *||     ||*   *|+-----+";
        }
        else if(this.ladoAtual == 5){
            return "+-----+|*   *||  *  ||*   *|+-----+";
        }
        else if(this.ladoAtual == 6){
            return "+-----+|* * *||     ||* * *|+-----+";
        }

        return "a";
    }
}