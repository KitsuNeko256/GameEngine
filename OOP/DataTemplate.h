#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>


template<class T> 
class DataTemplate {
protected:
	std::vector<T> val;
	std::map<std::string, size_t> index;

public:
	const T& operator[](size_t index) const {
		return val[index];
	}
	const T& operator[](const std::string& name) const{
		return index.find(name) == index.end() ? val[0] : val[index.at(name)];
	}

	size_t getIndex(const std::string& name) const {
		return index.find(name) == index.end() ? 0 : index.at(name);
	}
	size_t getSize() const {
		return val.size();
	}
	std::string printNameList() {
		std::string ans;
		for (std::map<std::string, size_t>::iterator it = index.begin(); it != index.end(); ++it)
			ans += it->first + "\n";
		return ans;
	}

	T loadSingleInstance(std::ifstream& fin);
	void loadFromFile(const std::string& fileName) {
		std::ifstream fin(fileName);
		if (fin.good()) {
			size_t IDCounter = getSize();
			while (!fin.eof()) {
				T t = loadSingleInstance(fin);
				val.emplace_back(t);
				index[t.name] = IDCounter++;
			}
		}
		fin.close();
	}
};

/*
ifstream file("input.txt");
if (file.good())
{
	string str;
	file >> str;
	while (getline(file, str))
	{
		if(str == "")
			continue;
		istringstream ss(str);
		std::string input;
		while (ss >> input)
		{
			cout << input << " ";
		}
		cout << endl;
	}
}
*/