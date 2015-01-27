#include "Request.h"
#include <CTrace.h>

RequestSetTemperature::RequestSetTemperature(const std::string& id, const std::uint32_t temperature)
: mId(id)
, mTemperature(temperature)
{
}

RequestSetTemperature::~RequestSetTemperature()
{
}

void RequestSetTemperature::Process()
{
}

const std::string& RequestSetTemperature::GetId()
{
	return mId;
}

const RequestType RequestSetTemperature::GetType()
{
	return RequestType::SetTemperature;
}

RequestDummy::RequestDummy(const std::string& id)
: mId(id)
{
}

RequestDummy::~RequestDummy()
{
}

void RequestDummy::Process()
{
}

const std::string& RequestDummy::GetId()
{
	return mId;
}

const RequestType RequestDummy::GetType()
{
	return RequestType::DummyRequest;
}