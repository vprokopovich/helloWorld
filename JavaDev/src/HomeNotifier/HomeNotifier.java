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

		AFPEventProvider providerOdessaAll = new AFPEventProvider(AFPClient.Mark.Any, AFPClient.Region.Odessa, "carsOdessaAny.csv");
		String odessaResult = providerOdessaAll.Poll();
		
		AFPEventProvider providerUkraineToyota = new AFPEventProvider(AFPClient.Mark.Toyota, AFPClient.Region.Any, "carsUkraineToyota.csv");
		String toyotaResult = providerUkraineToyota.Poll();
		
		AFPEventProvider providerOdessaHonda = new AFPEventProvider(AFPClient.Mark.Honda, AFPClient.Region.Odessa, "carsOdessaHonda.csv");
		String hondaResult = providerOdessaHonda.Poll();
		
		AFPEventProvider providerOdessaHyundai = new AFPEventProvider(AFPClient.Mark.Hyundai, AFPClient.Region.Odessa, "carsOdessaHyundai.csv");
		String hyundaiResult = providerOdessaHyundai.Poll();
		
		WebTelegramSender ws = new WebTelegramSender();
		if (odessaResult != null)
		{
			ws.Send(odessaResult);
		}
		if (toyotaResult != null)
		{
			ws.Send(toyotaResult);
		}
		if (hondaResult != null)
		{
			ws.Send(hondaResult);
		}
		if (hyundaiResult != null)
		{
			ws.Send(hyundaiResult);
		}
	}
}
