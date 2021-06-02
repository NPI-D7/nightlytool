#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
#include "ini.h"


int main(int argc, char* argv[]) {  

  std::string Devname;
  std::string Repo;
  std::string fname;
  std::string appname;
  std::string Tag;
  std::string desc= "No Description";
  std::string committag;
  if(argc < 6) {
		printf("usage: nightlytool File.ini AppName RepoUser Repo Tag Commit_Hash Desc\n");
		return 1;
	}

  fname = argv[1];
  appname = argv[2];
  Devname = argv[3];
  Repo = argv[4];
  Tag= argv[5];
  if (argc > 6) desc= argv[7];
  committag= argv[6];

  mINI::INIFile file(fname);
  mINI::INIStructure ini;
  file.read(ini);
  
  std::string _3dsx = "https://github.com/" + Devname + "/" + Repo + "/releases/download/" + Tag + "/" + appname + ".3dsx";
  std::string cia = "https://github.com/" + Devname + "/" + Repo + "/releases/download/" + Tag + "/" + appname + ".cia";

  ini[Tag]["name"] = appname;
  ini[Tag]["desc"] = desc;
  ini[Tag]["Version"] = Tag;
  ini[Tag]["commit_tag"] = committag;
  ini[Tag]["3dsx"] =   _3dsx;
  ini[Tag]["cia"] =   cia;

  file.write(ini);
  return 0;
}