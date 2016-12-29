package HomeNotifier.AFP;

import java.util.ArrayList;
import java.util.Iterator;

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
		
		Iterator<Element> iterator = carItems.iterator();
		while (iterator.hasNext())
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
		
		String parsedUrl		= null;
		String parsedDate		= null;
		String parsedYear		= null;
		String parsedHeader		= null;
		String parsedPriceUsd	= null;
		String parsedMain		= null;
		
		// Not yet implemented
		//String parsedCity			= null;
		//String parsedEngine		= null;
		//String parsedKilometers	= null;
		
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
			
			// Year string has following format: "YYYY г.в."
			// Getting only year as a string
			int pos = parsedYear.indexOf(" г.в");
			if (pos >= 0)
			{
				parsedYear = parsedYear.substring(0, pos); 
			}
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
			String parsedPrice = e.text();
			
			// Price string has following format: "XXX XXX грн ( $ Y YYY )"
			// Getting price in hrn and in $ separately
			/*
			int posHrn = parsedPrice.indexOf(" грн");
			if (posHrn >= 0)
			{
				String parsedPriceHrn = parsedPrice.substring(0, posHrn); 
			}
			*/
			
			int posUsd = parsedPrice.indexOf(" $");
			int posSkobka = parsedPrice.indexOf(" )");
			if (posUsd >= 0 && posSkobka >= 0)
			{
				parsedPriceUsd = parsedPrice.substring(posUsd + 2, posSkobka); // magic number '2' is to skip "$ " 
			}
		}
		
		Elements carMain = el.select("span.show_main");
		if (carMain.size() > 0)
		{
			Element e = carMain.get(0);
			parsedMain = e.text();
			parsedMain = parsedMain.replace(';', ',');
		}
		
		if (null != parsedDate   	&& 
			null != parsedYear   	&& 
			null != parsedHeader 	&& 
			null != parsedPriceUsd  && 
			null != parsedMain)
		{
			retVal = new AFPCar();
			retVal._url			= parsedUrl;
			retVal._date		= parsedDate;
			retVal._year		= parsedYear;
			retVal._header		= parsedHeader;
			retVal._priceUsd	= parsedPriceUsd;
			retVal._main		= parsedMain;
		}
		
		return retVal;
	}
}
