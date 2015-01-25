#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json/json.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

void parseJSON(const std::string& document);
 
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = static_cast<char*>(realloc(mem->memory, mem->size + realsize + 1));
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}

int main(void)
{
  CURL *curl;
  CURLcode res;

  struct MemoryStruct chunk;
 
  chunk.memory = static_cast<char*>(malloc(1));  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */ 

  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl)
  {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, "https://heater-control.firebaseio.com/msg-pool.json");
    /* Now specify the POST data */ 
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);

    /* send all data to this function  */ 
  	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  	/* we pass our 'chunk' struct to the callback function */ 
  	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
    {
    	fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
	    /*
	     * Now, our chunk.memory points to a memory block that is chunk.size
	     * bytes big and contains the remote file.
	     *
	     * Do something nice with it!
	     */ 
	 
    	printf("%lu bytes retrieved\n", (long)chunk.size);

    	std::string jsonDocument(chunk.memory, chunk.size);
    	parseJSON(jsonDocument);
  	}
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);

    if(chunk.memory)
    free(chunk.memory);
  }
  curl_global_cleanup();
  return 0;
}


void parseJSON(const std::string& document)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( document, root );
	if ( !parsingSuccessful )
	{
	    // report to the user the failure and their locations in the document.
	    std::cout  << "Failed to parse configuration" << std::endl;
	    return;
	}
	const Json::Value requests = root;
	for (Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ )
	{
			Json::Value key = itr.key();
			Json::Value value = (*itr);

			std::cout<<key.asString() << "   - " << value["action"].asString() << "  " << value["value"].asInt() << std::endl;
    }
}