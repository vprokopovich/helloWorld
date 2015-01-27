#include "FirebaseClient.h"
#include <CTrace.h>
#include <cstring>
#include "Exceptions.h"
#include <curl/curl.h>

FirebaseClient::FirebaseClient(const std::string& baseUrl)
: mBaseUrl(baseUrl)
{
    curl_global_init(CURL_GLOBAL_ALL);
}

FirebaseClient::~FirebaseClient()
{
    curl_global_cleanup();
}

std::string FirebaseClient::GetRequestsJsonString()
{
    std::string retVal;
    CURLcode res;
    
    CURL* curl = curl_easy_init();
    if (curl)
    {
        MemoryStruct chunk;

        curl_easy_setopt(curl, CURLOPT_URL, GetMsgPoolUrl());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FirebaseClient::WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            throw CurlException(curl_easy_strerror(res));
        }
        else
        {
            TRC_DEBUG("%lu bytes retrieved", static_cast<size_t>(chunk.size));
            retVal = std::string(chunk.pMemory, chunk.size);
        }

        curl_easy_cleanup(curl);
    }

    return retVal;
}

size_t FirebaseClient::WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct* pMem = (struct MemoryStruct *)userp;

    pMem->pMemory = static_cast<char*>(realloc(pMem->pMemory, pMem->size + realsize + 1));
    if(pMem->pMemory == NULL)
    {
        /* out of memory! */ 
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    memcpy(&(pMem->pMemory[pMem->size]), contents, realsize);
    pMem->size += realsize;
    pMem->pMemory[pMem->size] = 0;
    return realsize;
}

const char* FirebaseClient::GetMsgPoolUrl() const
{
    std::string url = mBaseUrl + "msg-pool.json";
    return url.c_str();
}