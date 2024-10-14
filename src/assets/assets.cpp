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
    
    do {
        //TODO: ricontrollare perchè non funziona il controllo
        //GINFO("line lenght %d, m_texture[].lineLen %d", (int)line.length() , m_texture[name].lenLine);
        //if ((int)line.length() != m_texture[name].lenLine) GERROR("Texture Asset with name %d in path: %s have not the right format", name, path.c_str());
        m_texture[name].push_back(line.c_str());
        //GINFO("Line %d, content %s", nLine[name], line.c_str());
    } while (std::getline(file, line));
    
    //to normalize the numbering convenction
    //m_texture[name].nLine--;
    //m_texture[name].lenLine--;

    file.close();

    //GINFO("Number of character per line: %d and number of line: %d content: %s", lenLine[name], nLine[name], m_texture[name].c_str());

    return true;
}

const std::vector<std::string>* assets::getTexture(TEXTURE_NAME name) const {
    //TODO: add checks
    return &m_texture[name];
}
