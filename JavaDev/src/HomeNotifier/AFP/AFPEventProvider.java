package HomeNotifier.AFP;

import java.util.ArrayList;
import java.util.Iterator;

import HomeNotifier.Common.CSVHelper;
import HomeNotifier.Common.IEventProvider;

public class AFPEventProvider implements IEventProvider
{
	private String				_filename = "";
	private AFPClient.Mark 		_mark = AFPClient.Mark.Undefined;
	private AFPClient.Region 	_region = AFPClient.Region.Undefined;
	
	public AFPEventProvider(AFPClient.Mark mark, AFPClient.Region region, String filename)
	{
		this._mark = mark;
		this._region = region;
		this._filename = filename;
	}
	
	@Override
	public void Poll()
	{
		ArrayList<AFPCar> carsFromWeb = new ArrayList<AFPCar>();
		ArrayList<AFPCar> carsFromFile = new ArrayList<AFPCar>();
		ArrayList<AFPCar> newCars = new ArrayList<AFPCar>();
		
		// Step 1. Getting list of cars from Website
		AFPClient afp = new AFPClient();
		String sListPage = afp.GetWebPage(_mark, _region);
		AFPParserListPage parser = new AFPParserListPage();
		
		carsFromWeb = parser.Parse(sListPage);
		
		// Step 2. Getting list of cars stored on the filesystem
		CSVHelper csvHelper = new CSVHelper();
		ArrayList<String[]> csvLines = csvHelper.Read(_filename);
		
		if (!csvLines.isEmpty())
		{
			Iterator<String[]> iterator = csvLines.iterator();
			while (iterator.hasNext())
			{
				String[] line = (String[]) iterator.next();
				if (line.length == 0) continue;
				
				try
				{
					AFPCar carFromFile = new AFPCar();
					carFromFile.ParseFromCSV(line);
					carsFromFile.add(carFromFile);
				}
				catch (Exception e)
				{
					// TODO Write log with error
					e.printStackTrace();
				}
				
			}
		}
		
		// Searching for items from list carsFromWeb that do not exist in carsFromFile
		// Performing very slow full search. Let the computer work!!! :)
		// Filling up newCars
		
		if (carsFromFile.isEmpty())
		{
			newCars = carsFromWeb;
		}
		else
		{
			Iterator<AFPCar> iteratorWeb  = carsFromWeb.iterator();
			while (iteratorWeb.hasNext())
			{
				AFPCar carFromWeb = (AFPCar) iteratorWeb.next();
				
				Iterator<AFPCar> iteratorFile = carsFromFile.iterator();
				boolean found = false;
				while (iteratorFile.hasNext())
				{
					AFPCar carFromFile = (AFPCar) iteratorFile.next();
					
					if (carFromFile._url.equals(carFromWeb._url))
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					newCars.add(carFromWeb);
				}
			}
		}
		
		// Writing new cars to file
		if (!newCars.isEmpty())
		{
			csvHelper.Write(_filename, newCars);
		}
		
		System.out.println("New cars added: " + newCars.size());
	}

}
