package adapters.converting;

public class ConvertingStrategyFromModelGreen implements ConvertingStrategy{
    @Override
    public String convertContent(String contentToConvert){
        String convertedContent = "";
        String[] splittedContentToConvert = contentToConvert.split(" ");
        for(String elem : splittedContentToConvert) {
        String asciiRepresentaion = parseBinaryToChar(elem);
        convertedContent += asciiRepresentaion;
        }
        return convertedContent;
    }
    /**
     * Converte o número binário em caractere ascii
     * @param binary
     * @return String in ascii form
     */

    public String parseBinaryToChar(String binary){
        int asciiNumber = 0;    //forma decimal a ser somada dos algarismos binários
        int powIndex = 7;   //valor do algarismo significativo do binário
        
        for(int i = 0; i < binary.length(); i++,powIndex--){
            if(binary.charAt(i) == '1')
                asciiNumber += Math.pow(2,powIndex);
        }

        char binaryConverted = (char) asciiNumber;

        return Character.toString(binaryConverted);
    }
}