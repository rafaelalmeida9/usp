package adapters;

import adapters.converting.*;
import model.MachineData;
import model.MachineDataModel;

/**
 * A MachineDataConverter converts a given MachineData's content to new model
 * it does so by using a converting strategy
 */
public class MachineDataConverter {
    private ConvertingStrategy convertingStrategy;

    /**
     * Given a MachineData object, attempts to return another with content in new model
     * if it is not possible to define a converting strategy, returns the original object
     * @param machineData
     * @return a MachineData in new model
     */
    public MachineData convertMachineDataToNewModel(MachineData machineData) {
        boolean couldDefineStrategy = defineConvertingStrategyByModel(machineData.getMachineDataModel());
        
        if(couldDefineStrategy) {
            String newContent = convertContentByDefinedStrategy(machineData.getMachineContent());
            return new MachineData(newContent);
        }
        
        return machineData;
    }

    /**
     * Defines which strategy is going to be used based on model
     * @param model
     * @return boolean stating if it was possible to determine a strategy
     */
    private boolean defineConvertingStrategyByModel(MachineDataModel model) {
        String modelNumber = model.toString();  //Checa o numero do modelo

        if(modelNumber == "1") {
            convertingStrategy = new ConvertingStrategyFromModelBlue();
            return true;
        }

        if(modelNumber == "2") {
            convertingStrategy = new ConvertingStrategyFromModelGreen();
            return true;
        }

        if(modelNumber == "3") {
            convertingStrategy = new ConvertingStrategyFromModelYellow();
            return true;
        }
        
        System.out.println("There is no strategy for this model");

        return false;
    }

    /**
     * Delegate content convertion to ConvertingStrategy abstraction
     * @param content
     * @return a string containing the converted content
     */
    private String convertContentByDefinedStrategy(String content) {
        String convertedContent = convertingStrategy.convertContent(content);
        return convertedContent;
    }
}
