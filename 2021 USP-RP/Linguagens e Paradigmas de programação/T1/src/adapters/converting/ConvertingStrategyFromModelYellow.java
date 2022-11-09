package adapters.converting;

public class ConvertingStrategyFromModelYellow implements ConvertingStrategy{
    @Override
    public String convertContent(String contentToConvert){
        String convertedContent = "";
        for(char elem : contentToConvert.toCharArray()) {
        if(elem == '+') {
        convertedContent += " ";
        }
        else if(elem == '/') {
        convertedContent += "\n";
        }
        else {
        convertedContent += elem;
        }
        }
        return convertedContent;
    }
}