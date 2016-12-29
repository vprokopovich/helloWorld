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
	public String _priceUsd;
	public String _main;
	
	public String ToCSVString()
	{
		// TODO: implement full serialization to string
		String retVal = _date + ";" + _year + ";" + _header + ";" + _priceUsd + ";" + _url + ";" + _main;
		return retVal;
	}
	public void ParseFromCSV(String[] line) throws Exception
	{
		// TODO: implement full parsing from strings here
		if (line.length != 6)
		{
			throw new Exception("Error during parsing CSV line to AFPCar. Number of arguments is not correct");
		}
		_date		= line[0];
		_year		= line[1];
		_header		= line[2];
		_priceUsd	= line[3];
		_url		= line[4];
		_main		= line[5];
	}
}
