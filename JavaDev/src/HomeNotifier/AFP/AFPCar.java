package HomeNotifier.AFP;

public class AFPCar
{
	// TODO: parse to real types
	// TODO: make private and provide getters
	public String _year;
	public String _engine;
	public String _kilometers;
	public String _transmission;
	public String _city;
	public String _url;
	public String _date;
	public String _header;
	public String _price;
	public String _main;
	
	public String ToString()
	{
		// TODO: implement full serialization to string
		String retVal = _date + ";" + _year + ";" + _header + ";" + _price + ";" + _url + ";";
		
		return retVal;
	}
}
