package HomeNotifier;

import HomeNotifier.AFP.AFPClient;

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

		
		AFPClient afp = new AFPClient();
		String sWebpage = afp.GetWebPage(AFPClient.Mark.Toyota, AFPClient.Region.Odessa);
		
		System.out.println(sWebpage);
	}
}
