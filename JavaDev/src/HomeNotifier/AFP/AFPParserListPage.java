package HomeNotifier.AFP;

import java.util.ArrayList;

public class AFPParserListPage
{
	public ArrayList<AFPCar> Parse(String html)
	{
		ArrayList<AFPCar> retVal = new ArrayList<AFPCar>();
		
		// TODO: implement real parsing of this page
		
		for (int i=0; i < 10; i++)
		{
			AFPCar testItem = new AFPCar();
			testItem._city = "DummyCity_" + i;
			testItem._date = "DummyDate_" + i;
			testItem._engine = "DummyEngine_" + i;
			testItem._kilometers = "DummyKilometers_" + i;
			
			retVal.add(testItem);
		}
		
		return retVal;
	}
}
