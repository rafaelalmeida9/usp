package streams;

import java.io.File;
import java.util.Scanner;

import model.MachineData;

public class MachineDataConverterInputStream {
    private Scanner streamScanner;
    private File stream;
    private final String pathPrefix = "../inputFiles/";

    public MachineDataConverterInputStream(String fileName) {
        try {
            stream = new File(pathPrefix + fileName);
            streamScanner = new Scanner(stream);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private int getStreamMetadata() {
        int metadata = streamScanner.nextInt();
        streamScanner.nextLine();
        return metadata;
    } 

    private String getStreamContent() {
        String content = "";
        
        while (streamScanner.hasNextLine()) {
            String line = streamScanner.nextLine();
            content = content + line + System.lineSeparator();
        }

        return content;
    }

    public MachineData streamDataToMachineData() {
        int streamMetadata = getStreamMetadata();
        String streamContent = getStreamContent();
        
        return new MachineData(streamContent, streamMetadata);
    }
}
