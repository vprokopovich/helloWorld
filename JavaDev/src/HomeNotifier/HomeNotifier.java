package HomeNotifier;

import HomeNotifier.AFP.*;

public class HomeNotifier
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// TODO: !! add .ini files parser
		// TODO: !! add support of command line options

		AFPEventProvider providerOdessaAll = new AFPEventProvider(AFPClient.Mark.Any, AFPClient.Region.Odessa, "a:\\carsOdessaAny.csv");
		providerOdessaAll.Poll();
		
		AFPEventProvider providerUkraineToyota = new AFPEventProvider(AFPClient.Mark.Toyota, AFPClient.Region.Any, "a:\\carsUkraineToyota.csv");
		providerUkraineToyota.Poll();
		
		
		// System.out.println(sListPage);
	}
}
