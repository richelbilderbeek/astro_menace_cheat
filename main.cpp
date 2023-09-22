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
  const int to{find_function_definition_last_line(function_name, text) - 1};
  assert(from < to);

  for (int i{from}; i!=to; ++i)
  {
    text[i] = "";
  }

  return text;
}

// int GetWorkshopShipCost(int Num)
// int GetWeaponBaseCost(int Num)
int main(int argc, char* argv[])
{
  std::string filename{"../AstroMenaceCheat/astromenace/src/menu/menu_workshop_workshop.cpp"};
  if (argc == 4) filename = std::string(argv[1]);
  simplify_file(filename, "GetSystemCost");

  const auto text{to_vector(filename)};
  const auto new_text{simplify_function(text)};
  save_container(new_text, filename);
}
