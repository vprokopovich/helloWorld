package HomeNotifier;

import HomeNotifier.AFP.*;
import HomeNotifier.Common.WebTelegramSender;

public class HomeNotifier
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// TODO: !! add .ini files parser
		// TODO: !! add support of command line options

		AFPEventProvider providerOdessaAll = new AFPEventProvider(AFPClient.Mark.Any, AFPClient.Region.Odessa, "e:\\carsOdessaAny.csv");
		String odessaResult = providerOdessaAll.Poll();
		
		AFPEventProvider providerUkraineToyota = new AFPEventProvider(AFPClient.Mark.Toyota, AFPClient.Region.Any, "e:\\carsUkraineToyota.csv");
		String toyotaResult = providerUkraineToyota.Poll();
		
		WebTelegramSender ws = new WebTelegramSender();
		if (odessaResult != null)
		{
			ws.Send(odessaResult);
		}
		if (toyotaResult != null)
		{
			ws.Send(toyotaResult);
		}
	}
}
