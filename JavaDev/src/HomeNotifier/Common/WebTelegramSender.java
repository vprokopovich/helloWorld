package HomeNotifier.Common;

import java.io.IOException;

import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.fluent.Form;
import org.apache.http.client.fluent.Request;

public class WebTelegramSender
{
	final private String _chatId = "-1001057953718";
	final private String _token = "TODO: Put your secret token here";
	
	public void Send(String str)
	{
		try
		{
			Request.Post("https://api.telegram.org/bot" + _token + "/sendMessage")
			    .bodyForm(Form.form().add("text", str).add("chat_id",  _chatId).build())
			    .execute().returnContent();
		} catch (ClientProtocolException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
