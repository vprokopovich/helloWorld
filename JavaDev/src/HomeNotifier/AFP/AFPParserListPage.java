package HomeNotifier.AFP;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class AFPParserListPage
{
	public ArrayList<AFPCar> Parse(String html)
	{
		ArrayList<AFPCar> retVal = new ArrayList<AFPCar>();
		
		Document doc = Jsoup.parse(html);
		Elements carItems = doc.select("span.show_info"); // a with href
		
		for (Iterator<Element> iterator = carItems.iterator(); iterator.hasNext();)
		{
			Element elCarFromTheList = (Element) iterator.next();
			AFPCar parsedCar = ParseCarFromList(elCarFromTheList);
			if (null != parsedCar)
			{
				retVal.add(parsedCar);
			}
		}
		
		return retVal;
	}
	
	private AFPCar ParseCarFromList(Element el)
	{
		AFPCar retVal = null;
		
		String parsedUrl	= null;
		String parsedDate	= null;
		String parsedYear	= null;
		String parsedHeader = null;
		String parsedPrice	= null;
		String parsedMain	= null;
		
		// Not yet implemented
		//String parsedCity			= null;
		//String parsedEngine		= null;
		//String parsedKilometers	= null;
		
		// This list contains mapping between values that need to be parsed and 
		// List<Pair<String,String>> pairList = new ArrayList<Pair<String,String>>();
		
		Elements carUrl = el.select("a[href]");
		if (carUrl.size() > 0)
		{
			Element e = carUrl.get(0);
			parsedUrl = e.attr("href");
		}
		
		Elements carDate = el.select("span.show_date");
		if (carDate.size() > 0)
		{
			Element e = carDate.get(0);
			parsedDate = e.text();
		}
		
		Elements carYear = el.select("span.show_year");
		if (carYear.size() > 0)
		{
			Element e = carYear.get(0);
			parsedYear = e.text();
		}
		
		Elements carHeader = el.select("span.show_header");
		if (carHeader.size() > 0)
		{
			Element e = carHeader.get(0);
			parsedHeader = e.text();
		}
		
		Elements carPrice = el.select("span.show_price");
		if (carPrice.size() > 0)
		{
			Element e = carPrice.get(0);
			parsedPrice = e.text();
		}
		
		Elements carMain = el.select("span.show_main");
		if (carMain.size() > 0)
		{
			Element e = carMain.get(0);
			parsedMain = e.text();
		}
		
		if (null != parsedDate   && 
			null != parsedYear   && 
			null != parsedHeader && 
			null != parsedPrice  && 
			null != parsedMain)
		{
			retVal = new AFPCar();
			retVal._url		= parsedUrl;
			retVal._date	= parsedDate;
			retVal._year	= parsedYear;
			retVal._header	= parsedHeader;
			retVal._price	= parsedPrice;
			retVal._main	= parsedMain;
		}
		
		return retVal;
	}
}
