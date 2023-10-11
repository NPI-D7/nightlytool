#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
#include <filesystem>

#include "json.hpp"

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

std::string ver = "1.2.0";

void GenFile(AppData appd)
{
  nlohmann::json js;
  std::ifstream ifs(appd.fname, std::ios::in);
  if(ifs.is_open()) {
    ifs >> js;
    ifs.close();
  }
  js[appd.Tag]["name"] = appd.appname;
  js[appd.Tag]["desc"] = appd.desc;
  js[appd.Tag]["Version"] = appd.Tag;
  js[appd.Tag]["commit_tag"] = appd.committag;
  js[appd.Tag]["Author"] = appd.Author;

  std::string _3dsx = "https://github.com/" + appd.Devname + "/" + appd.Repo + "/releases/download/" + appd.Tag + "/" + appd.appname + ".3dsx";
  std::string cia = "https://github.com/" + appd.Devname + "/" + appd.Repo + "/releases/download/" + appd.Tag + "/" + appd.appname + ".cia";

  js[appd.Tag]["3dsx"] =   _3dsx;
  js[appd.Tag]["cia"] =   cia;
  
  std::ofstream ofs(appd.fname, std::ios::out);
  if(ofs.is_open()) {
    ofs << js.dump(3);
    ofs.close();
  }
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
    "db/" + std::string(argv[1]) + ".json",
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
  nlohmann::json js;
  std::ifstream ifs("db.json", std::ios::in);
  if(ifs.is_open()) {
    ifs >> js;
    ifs.close();
  }
  js["info"]["repository"] = appd.Repo;
  js["info"]["user"] = appd.Devname;

  js[appd.appname]["Name"] = appd.appname;
  js[appd.appname]["data"] = dllink;
  std::ofstream ofs("db.json", std::ios::out);
  if(ofs.is_open()) {
    ofs << js.dump(3);
    ofs.close();
  }
  return 0;
}
