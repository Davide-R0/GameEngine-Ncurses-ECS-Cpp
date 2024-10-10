#include "assets.h"
#include <fstream>
#include <filesystem>   //for std::filesystem::path
#include <string>
#include "../core/logger.h"

assets::assets() {
    GTRACE("Assets constructor called");
}

assets::~assets() {
    GTRACE("Assets destructor called");
}

bool assets::addNcTexture(TEXTURE_NAME name, std::filesystem::path path) {
    //GINFO("call add texture");

    //NOTE: Trow an error???
    if (!m_texture[name].empty()) {
        GWARN("Overwriting texture Asset tag %d with the texture in path: %s", name, path.c_str());
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        GERROR("Falied to open Texture Asset with name %d in path: %s", name, path.c_str());
        return false;
    }

    std::string line;

    std::getline(file, line);
    lenLine[name] = line.length();
    nLine[name] = 0;

    do {
        if ((int)line.length() != lenLine[name]) GERROR("Texture Asset with name %d in path: %s have not the right format", name, path.c_str());
        m_texture[name] += line.c_str();
        nLine[name]++;
        //GINFO("Line %d, content %s", nLine[name], line.c_str());
    } while (std::getline(file, line));
    
    //to normalize the numbering convenction
    nLine[name]--;
    lenLine[name]--;

    file.close();

    //GINFO("Number of character per line: %d and number of line: %d content: %s", lenLine[name], nLine[name], m_texture[name].c_str());

    return true;
}
