/*
Auteur : Orwel
Date de cr�ation : 05/04/2010

R�le : Read file to load data in game

M�thode:
Read                    Lit le fichier, ins�re le UpsFileManager script en coupant les commentaires
ConversionStringFloat       Static
ConversionStringInt         Static

Attribus:
UpsFileManager                    Vecteur de string qui contient le UpsFileManager script
line                    indique la ligne actuelle

Am�lioration:
N/C
*/

#ifndef HEADER_CODE
#define HEADER_CODE

#include<string>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../../../include/odfaeg/Core/utilities.h"
namespace odfaeg {
class UpsFileManager
{
public :
    UpsFileManager(std::string path);
    //~UpsFileManager();
    void read(std::string path);
    void save(std::string path);
    ///Static Method
    static std::vector<int> conversionStringInts(std::string str);
    static std::vector<float> conversionStringFloats (std::string str);
    void Display();

protected :
    std::string getLine();

protected :
    std::vector< std::string > code;
    int line;
};
}
#endif
