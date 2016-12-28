package HomeNotifier;

import java.util.ArrayList;

import HomeNotifier.AFP.AFPCar;
import HomeNotifier.AFP.AFPClient;
import HomeNotifier.AFP.AFPParserListPage;

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
		String sListPage = afp.GetWebPage(AFPClient.Mark.Toyota, AFPClient.Region.Odessa);
		
		AFPParserListPage parser = new AFPParserListPage();
		ArrayList<AFPCar> cars = parser.Parse(sListPage);
		
		System.out.println(sListPage);
	}
}
