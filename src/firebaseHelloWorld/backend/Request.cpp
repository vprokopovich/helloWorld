#include "Request.h"
#include <CTrace.h>

RequestSetTemperature::RequestSetTemperature(const std::string& id, const std::uint32_t temperature)
: mId(id)
, mTemperature(temperature)
{
	TRC_DEBUG("RequestSetTemperature(%d) id='%s'", mTemperature, mId.c_str());
}

RequestSetTemperature::~RequestSetTemperature()
{
	TRC_DEBUG("~RequestSetTemperature");
}

void RequestSetTemperature::Process()
{
	TRC_DEBUG("RequestSetTemperature::Process()");
}

const std::string& RequestSetTemperature::GetId()
{
	return mId;
}

RequestDummy::RequestDummy(const std::string& id)
: mId(id)
{
    TRC_DEBUG("RequestDummy() id='%s'", mId.c_str());
}

RequestDummy::~RequestDummy()
{
	TRC_DEBUG("~RequestDummy");
}

void RequestDummy::Process()
{
	TRC_DEBUG("RequestDummy::Process()");
}

const std::string& RequestDummy::GetId()
{
	return mId;
}