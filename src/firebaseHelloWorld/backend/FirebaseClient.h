#ifndef FIREBASECLIENT_H
#define FIREBASECLIENT_H

#include <string>

class FirebaseClient
{
public:
	FirebaseClient(const std::string& baseUrl);
	~FirebaseClient();

	std::string GetRequestsJsonString();
private:
	// Unimplemented to avoid misusing
	FirebaseClient();

	struct MemoryStruct
	{
		char*  pMemory;
		size_t size;

		MemoryStruct()
		: pMemory(static_cast<char*>(malloc(1)))
		, size(0)
		{
		}

		~MemoryStruct()
		{
			if(pMemory) free(pMemory);
		}
	};

	static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp);
	const char* GetMsgPoolUrl() const;

private:
	std::string mBaseUrl;
};

#endif // FIREBASECLIENT_H