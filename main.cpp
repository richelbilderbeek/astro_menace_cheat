#include <algorithm>
#include <iterator>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <algorithm>
#include <iterator>
#include <fstream>

//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void save_container(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<typename Container::value_type>(f,"\n"));
}

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool is_regular_file(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> to_vector(const std::string& filename)
{
  assert(is_regular_file(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  for (int i=0; !in.eof(); ++i)
  {
    std::string s;
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

int find_function_definition_first_line(
  const std::string& function_name,
  const std::vector<std::string>& text
)
{
  const int sz = text.size();
  const std::string hit{"int " + function_name + "(int"};
  for (int i{0}; i != sz; ++i)
  {
    if (text[i].substr(0, hit.size()) == hit)
    {
      if (text[i].find(';') != std::string::npos) continue;
      return i;
    }
  }
  assert(!"Should not get here");
  return -1;
}

int find_function_definition_last_line(
  const std::string& function_name,
  const std::vector<std::string>& text
)
{
  const int sz = text.size();
  const std::string hit{"}"};
  const int start_index{find_function_definition_first_line(function_name, text)};
  for (int i{start_index}; i != sz; ++i)
  {
    if (text[i].substr(0, hit.size()) == hit)
    {
      return i;
    }
  }
  assert(!"Should not get here");
  return -1;
}

/// Simplify a function
std::vector<std::string> simplify_function(
  const std::string& function_name,
  std::vector<std::string> text
)
{
/*
int GetSystemCost(int Num)
{
    [...]

    return 0;
}
*/

  assert(find_function_definition_first_line(function_name, text) != -1);
  assert(find_function_definition_last_line(function_name, text) != -1);
  const int start_index{find_function_definition_first_line(function_name, text)};
  text[start_index] = "int " + function_name + "(int)";
  const int from{start_index + 2};
  const int end_index{find_function_definition_last_line(function_name, text)};
  const int to{end_index - 1};
  assert(from < to);
  assert(from < end_index);
  assert(to < end_index);

  for (int i{from}; i!=to; ++i)
  {
    text[i] = "";
  }
  text[to] = "return 0;";
  return text;
}

void patch_file(
  const std::filesystem::path& filename,
  const std::string& function_name
)
{
  const auto text{to_vector(filename)};
  const auto new_text{simplify_function(function_name, text)};
  save_container(new_text, filename);
}

int main(int argc, char* argv[])
{
  std::filesystem::path workshop_path{"../AstroMenaceCheat/astromenace/src/menu/menu_workshop_workshop.cpp"};
  std::filesystem::path shipyard_path{"../AstroMenaceCheat/astromenace/src/menu/menu_workshop_shipyard.cpp"};
  std::filesystem::path weaponry_path{"../AstroMenaceCheat/astromenace/src/menu/menu_workshop_weaponry.cpp"};
  const std::string workshop_function_name{"GetSystemCost"};
  const std::string shipyard_function_name{"GetWorkshopShipCost"};
  const std::string weaponry_function_name{"GetWeaponBaseCost"};
  if (argc == 4)
  {
    workshop_path = std::string(argv[1]);
    shipyard_path = std::string(argv[2]);
    weaponry_path = std::string(argv[3]);
  }
  patch_file(workshop_path, workshop_function_name);
  patch_file(shipyard_path, shipyard_function_name);
  patch_file(weaponry_path, weaponry_function_name);
}
