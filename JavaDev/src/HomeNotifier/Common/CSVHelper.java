package HomeNotifier.Common;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.jsoup.nodes.Element;

import HomeNotifier.AFP.AFPCar;

public class CSVHelper
{
	public ArrayList<String[]> Read(String csvFile)
	{
		ArrayList<String[]> retVal = new ArrayList<String[]>();
		
		String line = "";
        String cvsSplitBy = ";";

        BufferedReader br = null;
        try
        {
        	br = new BufferedReader(new FileReader(csvFile));
            while ((line = br.readLine()) != null)
            {
                String[] parsedLine = line.split(cvsSplitBy);
                retVal.add(parsedLine);
            }
        }
        catch (IOException e)
        {
        	// TODO Write log with error
        	e.printStackTrace();
        }
        
        return retVal;
	}

	public void Write(String csvFile, ArrayList<AFPCar> cars)
	{
		FileWriter fw = null;
		try
		{
			fw = new FileWriter(csvFile);
			
			Iterator<AFPCar> iterator = cars.iterator();
			while (iterator.hasNext())
			{
				AFPCar elCarFromTheList = (AFPCar) iterator.next();
				fw.write(elCarFromTheList.ToCSVString() + "\n");
			}
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try
		{
			fw.close();
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
