#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>


template<class T> 
class DataTemplate {
protected:
	std::vector<T> val;
	std::map<std::string, uint16_t> index;

public:
	const T& operator[](uint16_t index) const {
		return val[index];
	}
	const T& operator[](const std::string& name) const{
		return val[index[name]];
	}

	uint16_t getIndex(const std::string& name) const {
		return index.find(name) == index.end() ? 0 : index.at(name);
	}
	size_t getSize() const {
		return val.size();
	}

	T loadSingleInstance(std::ifstream& fin);
	void loadFromFile(const std::string& fileName) {
		std::ifstream fin(fileName);
		
		uint16_t IDCounter = getSize();
		while(!fin.eof()) {
			T t = loadSingleInstance(fin);
			val.emplace_back(t);
			index[t.name] = IDCounter;
			++IDCounter;
		}

		fin.close();
	}
};

