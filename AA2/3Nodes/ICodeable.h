#pragma once
#include "../dist/json/json.h"
#include <functional>
#include <map>
class ICodeable {
public:
	typedef std::function<ICodeable* ()> SubClassDecode;
	typedef std::map<std::string, SubClassDecode> DecodeMap;
private:
	static DecodeMap* GetDecodeMap();
public:
	template <typename T, typename = typename std::enable_if<std::is_base_of<ICodeable, T>::value>::type>
	void CodeSubClassType(Json::Value& json) {
		json[GetDecodeKey()] = typeid(T).name();
	}
	static std::string GetDecodeKey();
	static void SaveDecodeMapProcess(std::string className, SubClassDecode decodeProcess);
	template <typename T, typename = typename std::enable_if<std::is_base_of<ICodeable, T>::value>::type>
	static void SaveSecodeMapProcess() {
		SaveDecodeMapProcess(typeid(T).name(), []() {return new T(); });
	}
	virtual Json::Value Code() = 0;
	virtual void Decode(Json::Value json) = 0;
	template <typename T, typename = typename std::enable_if<std::is_base_of<ICodeable, T>::value>::type>
	static T* FromJson(Json::Value json) {
		std::string className = json[GetDecodeKey()].asString();
		SubClassDecode decodeProcess = (*GetDecodeMap())[className];
		ICodeable* codeable = decodeProcess();
		T* codableCasted = dynamic_cast<T*>(codeable);
		codeable->Decode(json);
		return codableCasted;
	}
};