package HomeNotifier.Common;

import org.telegram.telegrambots.ApiContext;
import org.telegram.telegrambots.ApiContextInitializer;
import org.telegram.telegrambots.TelegramBotsApi;
import org.telegram.telegrambots.api.methods.BotApiMethod;
import org.telegram.telegrambots.api.methods.send.SendMessage;
import org.telegram.telegrambots.api.objects.Message;
import org.telegram.telegrambots.exceptions.TelegramApiException;
import org.telegram.telegrambots.exceptions.TelegramApiRequestException;
import org.telegram.telegrambots.generics.BotSession;
import org.telegram.telegrambots.generics.Webhook;
import org.telegram.telegrambots.updateshandlers.SentCallback;
import org.telegram.telegrambots.updatesreceivers.DefaultBotSession;
import org.telegram.telegrambots.updatesreceivers.DefaultWebhook;

public class TelegramSender
{
	private TelegramBotsApi    _telegramBotsApi = null;
	private TelegramBotHandler _telegramBotHandler = null;
	private BotSession _session = null;
	public void Init()
	{
		//ApiContextInitializer.init();
		//_session = new DefaultBotSession();
		//_session = ApiContext.getInstance(DefaultBotSession.class);
		ApiContext.register(BotSession.class, DefaultBotSession.class);
		//if (!_session.isRunning())
		{
			
			//ApiContext.registerSingleton(BotSession.class, DefaultBotSession.class);
			//ApiContext.register(Webhook.class, DefaultWebhook.class);
		}
		
		_telegramBotsApi = new TelegramBotsApi();
		_telegramBotHandler = new TelegramBotHandler();
		
	    try
	    {
	    	_telegramBotsApi.registerBot(_telegramBotHandler);
	    }
	    catch (TelegramApiException e)
	    {
	        e.printStackTrace();
	    }
	}
	
	public void SendMessage(String str)
	{
		SendMessage message = new SendMessage() // Create a SendMessage object with mandatory fields
                .setChatId("-1001057953718")
                .setText(str);
		
		try
		{
			//_telegramBotHandler.sendMessage(message);
			class SendCallback implements SentCallback<Message>
			{

				@Override
				public void onError(BotApiMethod<Message> arg0, TelegramApiRequestException arg1) {
					// TODO Auto-generated method stub
					
				}

				@Override
				public void onException(BotApiMethod<Message> arg0, Exception arg1) {
					// TODO Auto-generated method stub
					
				}

				@Override
				public void onResult(BotApiMethod<Message> arg0, Message arg1)
				{
					DefaultBotSession session = ApiContext.getInstance(DefaultBotSession.class);
					if (session.isRunning())
					{
						session.stop();
					}
					
				}
			};
			
			SendCallback cb = new SendCallback();
			_telegramBotHandler.sendMessageAsync(message, cb);
		}
		catch (TelegramApiException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void Finalize()
	{
		System.out.println("Finalize");

		//_session.stop();
	}
}
