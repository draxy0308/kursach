#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ErrorTracker.h"
#include "DataBase.h"

DB::DB(std::string DBName)
    {
        std::ifstream file(DBName);
		if(!file.good()){
			throw server_error(std::string("Wrong DB File Name"), true);
		}
        std::string Pair;
        while(getline(file, Pair)) {
            DataBaseP[Pair.substr(0,Pair.find(sep))] = Pair.substr(Pair.find(sep)+1);
        }
        file.close();
    }

bool DB::IDcheck(std::string login)
    {
        for (std::map<std::string, std::string>::iterator it=DataBaseP.begin(); it!=DataBaseP.end(); ++it) {
            std::cout << it->first << " => " << it->second << '\n';
        }
			if (DataBaseP.count(login) != 1){
				throw server_error(std::string("Invalid ID"), false);}
        return DataBaseP.count(login) == 1;
    }
