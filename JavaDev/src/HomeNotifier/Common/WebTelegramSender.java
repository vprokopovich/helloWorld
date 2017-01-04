package HomeNotifier.Common;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.fluent.Request;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.NameValuePair;

public class WebTelegramSender
{
	final private String _chatId = "-1001057953718";
	final private String _token = "TODO: Put your secret token here";
	
	public void Send(String str)
	{
		if ((null == str) || (str.equals("")))
		{
			return;
		}
		
		try
		{
			List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>();
			nameValuePairs.add(new BasicNameValuePair("text", str));
			nameValuePairs.add(new BasicNameValuePair("chat_id", _chatId));
	        
			Request.Post("https://api.telegram.org/bot" + _token + "/sendMessage")
			       .body(new UrlEncodedFormEntity(nameValuePairs,"UTF-8"))
			       .execute()
			       .returnContent();
		}
		catch (ClientProtocolException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
