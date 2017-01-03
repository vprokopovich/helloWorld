package HomeNotifier.AFP;

import java.io.IOException;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class AFPClient
{
	public enum Mark
	{
		Undefined(-1),
		Any(0),
		Toyota(116),
		Mazda(76),
		Honda(53),
		Hyundai(56),
		Kia(62),
		Mitsubishi(83),
		Skoda(105);
		
		Mark(int value) {this._value = value;}
		String ToString()
		{
			if ((_value == Any._value) || (_value == Undefined._value)) return "";
			return Integer.toString(_value);
		}
		private int _value;
	}
	public enum Region
	{
		Undefined(-1),
		Any(0),
		Odessa(81),
		Kyiv(76),
		Chernigov(90),
		Nikolaev(80);
		
		Region(int value) {this._value = value;}
		String ToString()
		{
			if ((_value == Any._value) || (_value == Undefined._value)) return "";
			return Integer.toString(_value);
		}
		private int _value;
	}
	
	public String GetWebPage(Mark mark, Region region)
	{
		String retVal = "";
		CloseableHttpClient httpclient = HttpClients.createDefault();
        
		try
		{
            HttpGet httpGet = new HttpGet(GenerateUrl(mark, region));	// originally was: "http://httpbin.org/get"
            
            // Create a custom response handler
            ResponseHandler<String> responseHandler = new ResponseHandler<String>()
            {
                @Override
                public String handleResponse(HttpResponse response) throws ClientProtocolException, IOException
                {
                    int status = response.getStatusLine().getStatusCode();
                    if (status >= 200 && status < 300)
                    {
                        HttpEntity entity = response.getEntity();
                        
                        //String encoding = entity.getContentEncoding().getValue();
                        //encoding = encoding == null ? "UTF-8" : encoding;

                        return entity != null ? EntityUtils.toString(entity, "UTF-8") : null;
                    }
                    else
                    {
                        throw new ClientProtocolException("Unexpected response status: " + status);
                    }
                }
            };
            
            retVal = httpclient.execute(httpGet, responseHandler);
        }
		catch (ClientProtocolException e)
		{
			// TODO Write log with error
			e.printStackTrace();
		}
		catch (IOException e)
		{
			// TODO Write log with error
			e.printStackTrace();
		}
        finally
        {
            try
            {
				httpclient.close();
			}
            catch (IOException e)
            {
				// TODO Write log with error
				e.printStackTrace();
			}
        }
		
		return retVal;
	}

	// Some helpers
	private final String _baseUrl = "http://www.afp.com.ua/sale/?rub=1&model=&yearfrom=&yearto=&pricefrom=&priceto=&moneyid=93";
	private String GenerateUrl(Mark mark, Region region)
	{
		// Adding following things to base url: &region=81&mark=116
		final String retVal = _baseUrl 
		                    + "&region=" + region.ToString()
		                    + "&mark=" + mark.ToString();
		return retVal;
	}
}
