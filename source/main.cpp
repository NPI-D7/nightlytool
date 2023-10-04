#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
#include <filesystem>

#include "ini.h"

struct AppData
{
  std::string fname;
  std::string appname;
  std::string Devname;
  std::string Repo;
  std::string Tag;
  std::string committag;
  std::string desc= "No Description";
  std::string Author = "None";
};
std::string ver = "1.1.0";

void GenFile(AppData appd)
{
  mINI::INIFile file(appd.fname);
  mINI::INIStructure ini;

  file.read(ini);
  ini[appd.Tag]["name"] = appd.appname;
  ini[appd.Tag]["desc"] = appd.desc;
  ini[appd.Tag]["Version"] = appd.Tag;
  ini[appd.Tag]["commit_tag"] = appd.committag;
  ini[appd.Tag]["Author"] = appd.Author;

  std::string _3dsx = "https://github.com/" + appd.Devname + "/" + appd.Repo + "/releases/download/" + appd.Tag + "/" + appd.appname + ".3dsx";
  std::string cia = "https://github.com/" + appd.Devname + "/" + appd.Repo + "/releases/download/" + appd.Tag + "/" + appd.appname + ".cia";

  ini[appd.Tag]["3dsx"] =   _3dsx;
  ini[appd.Tag]["cia"] =   cia;
  
  file.write(ini);
}
int main(int argc, char* argv[]) {  
  if(argc < 8) {
    std::cout << "Version: " << ver << std::endl;
		std::cout << "usage: nightlytool AppName RepoUser Repo Tag Commit_Hash Desc Author" << std::endl;
		return 1;
	}
  if(!std::filesystem::is_directory("db"))
    std::filesystem::create_directory("db");
  AppData appd = {
    "db/" + std::string(argv[1]) + ".ini",
    argv[1],
    argv[2],
    argv[3],
    argv[4],
    argv[5],
    argv[6],
    argv[7]
  };

  GenFile(appd);
  //generate database
  std::string dbname = "db.ini";
  std::string dllink = "https://github.com/" + appd.Devname + "/" + appd.Repo + "/raw/master/" + appd.fname;
  mINI::INIFile dbfile(dbname); 
  mINI::INIStructure database;
  dbfile.read(database);
  database["info"]["repository"] = appd.Repo;
  database["info"]["user"] = appd.Devname;

  database[appd.appname]["Name"] = appd.appname;
  database[appd.appname]["data"] = dllink;
  dbfile.write(database);
  return 0;
}
