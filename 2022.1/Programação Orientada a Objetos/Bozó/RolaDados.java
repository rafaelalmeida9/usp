public class RolaDados {

    private Dado[] dado = new Dado[20];
    private int maxDados;
    
    public RolaDados(int n){
        maxDados = n;
        for(int i = 0; i < maxDados; i++){
            dado[i] = new Dado();
        }
    }

    public int[] rolar(){
        int[] valor = new int[maxDados];
        for(int i = 0; i < maxDados; i++){
            dado[i].rolar();
            try{
                Thread.sleep(1);
            }
            catch(InterruptedException ex){
                Thread.currentThread().interrupt();
            }
            valor[i] = dado[i].getLado();
        }

        return valor;
    }

    public int[] rolar(boolean[] quais){
        int[] valor = new int[maxDados];
        for(int i = 0; i < maxDados; i++){
            if(quais[i]){
                dado[i].rolar();
                valor[i] = dado[i].getLado();
            }
            else valor[i] = dado[i].getLado();
            try{
                Thread.sleep(1);
            }
            catch(InterruptedException ex){
                Thread.currentThread().interrupt();
            }
        }

        return valor;
    }

    public int[] rolar(String s){
        if(s.length() == 0) s = "-1";
        String[] tokens = s.split(" ");
        boolean[] quais = new boolean[5];
        
        for(int i = 0; i < tokens.length; i++){
            int pos = Integer.parseInt(tokens[i]);
            if(pos >= 1 && pos <= 5){
                quais[pos - 1] = true;
            }
        }

        return rolar(quais);
    }

    @Override
    public String toString(){
        String tmp = "";
        String[] dadoStr = new String[maxDados];
        for(int i = 0; i < maxDados; i++){
            dadoStr[i] = dado[i].toString();
        }

        tmp += "1       2       3       4       5\n";

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < maxDados; j++){
                tmp += dadoStr[j].substring(7*i,7*(i+1)) + " ";
            }
            tmp += '\n';
        }

        return tmp;
    }
}