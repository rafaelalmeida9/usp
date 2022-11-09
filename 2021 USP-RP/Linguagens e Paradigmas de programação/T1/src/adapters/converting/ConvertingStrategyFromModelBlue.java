package adapters.converting;

public class ConvertingStrategyFromModelBlue implements ConvertingStrategy{
    @Override
    public String convertContent(String contentToConvert){
        String convertedContent = contentToConvert.toLowerCase();
        return convertedContent;
    }
}