#pragma once
#define SAVER DataSaver::Instance()
class DataSaver
{
private:
	DataSaver() = default;
	DataSaver(const DataSaver& s) = delete;
	DataSaver& operator=(const DataSaver& val) = delete;
public:
	static DataSaver& Instance() {
		static DataSaver instance;
		return instance;
	}
	void SaveData();
	void LoadData();
};

