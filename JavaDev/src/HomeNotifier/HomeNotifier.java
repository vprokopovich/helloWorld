package HomeNotifier;

import HomeNotifier.AFP.AFPEventProvider;

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

		AFPEventProvider provider = new AFPEventProvider();
		provider.Poll();
		
		
		// System.out.println(sListPage);
	}
}
