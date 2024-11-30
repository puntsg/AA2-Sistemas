#include "ICodeable.h"

ICodeable::DecodeMap* ICodeable::GetDecodeMap()
{
	static DecodeMap* map = new DecodeMap();
	return map;
}

std::string ICodeable::GetDecodeKey()
{
	return "ICodeableType";
}

void ICodeable::SaveDecodeMapProcess(std::string className, SubClassDecode decodeProcess)
{
	ICodeable::GetDecodeMap()->emplace(className, decodeProcess);
}