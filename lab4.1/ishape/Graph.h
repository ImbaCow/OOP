#pragma once
class Graph
{
public:
	void InitFromFile(const std::string & file_name);
	void FillFromFile();
	void Info();

private:
	struct City {
		bool isMain = false;
	};
	struct Road {
		unsigned CityId;
		unsigned RoadLen;
	};
	std::vector<City> m_cities;
};

