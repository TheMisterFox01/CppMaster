#include <string>
#include <vector>
#include <Windows.h>

#include "plugin_loader.h"

void getFilesList(std::string filePath, std::string extension, std::vector<std::string>& returnFileName)
{
  WIN32_FIND_DATA fileInfo;
  HANDLE hFind;
  std::string fullPath = filePath + extension;
  hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
  if (hFind != INVALID_HANDLE_VALUE) {
    returnFileName.push_back(filePath + fileInfo.cFileName);
    while (FindNextFile(hFind, &fileInfo) != 0) {
      returnFileName.push_back(filePath + fileInfo.cFileName);
    }
  }
}

void plugin_loader::load_unary(HMODULE lib)
{
  unary_loader u_loader = (unary_loader)GetProcAddress(lib, "RetriveUnary");
  if (u_loader == NULL)
  {
    return;
  }
  unary_table tu = u_loader();
  dll_unary_table.insert(tu.begin(), tu.end());
}

void plugin_loader::load_binary(HMODULE lib)
{
  binary_loader b_loader = (binary_loader)GetProcAddress(lib, "RetriveBinary");
  if (b_loader == NULL)
  {
    return;
  }
  binary_table tb = b_loader();
  dll_binary_table.insert(tb.begin(), tb.end());
}


plugin_loader::plugin_loader(std::string path)
{
  std::vector<std::string> DLLs;
  getFilesList(path, "*.dll", DLLs);

  for (auto& dll : DLLs)
  {
    HMODULE lib = LoadLibraryA(dll.c_str());
    load_unary(lib);
    load_binary(lib);
    to_free.push_back(lib);
  }
}

plugin_loader::~plugin_loader()
{
  for (auto& dll : to_free)
  {
    FreeLibrary(dll);
  }
}
