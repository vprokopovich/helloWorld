package HomeNotifier;

import java.util.ArrayList;
import java.util.Iterator;

import org.jsoup.nodes.Element;

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
		
		for (Iterator<AFPCar> iterator = cars.iterator(); iterator.hasNext();)
		{
			AFPCar parsedCar = (AFPCar) iterator.next();
			System.out.println(parsedCar.ToString());
		}
		
		// System.out.println(sListPage);
	}
}
