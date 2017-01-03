package HomeNotifier;

import HomeNotifier.AFP.AFPEventProvider;
import HomeNotifier.Common.TelegramSender;

public class HomeNotifier
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		System.out.println("Hello, World");
		
		// TODO: !! add .ini files parser
		// TODO: !! add .csv files parser
		// TODO: !! add support of command line options
		// TODO: !! add XML parser

		//AFPEventProvider provider = new AFPEventProvider();
		//provider.Poll();
		
		TelegramSender sender = new TelegramSender();
		sender.Init();
		sender.SendMessage("Hello");
		sender.Finalize();
		
		// System.out.println(sListPage);
	}
}
