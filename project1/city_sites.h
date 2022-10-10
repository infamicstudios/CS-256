//By Duncan McFarlane on 10/4/22 for PDX.EDU CS163
// Revised 10/5/22 
// I have realized after writing this that it would be much better 
// to refactor my structs into classes but due to time constraints I can't do this

#include <cstdint>
#include <map>

struct site {
  char * name; // Name of the site 
  unsigned int visitTime_mins; // The time consumed by visiting in Minutes
  unsigned int costDollars; // Cost in dollars of visiting the Site
  bool reservationsRequired; // If Reservations are required
  bool swimsuitRequired; // If a swimsuit is required
  bool hasBeenVisited; // If the site has been visited in the past
};


struct Site_node {
  site * Site;
  Site_node * next; // Pointer to next site 
};


struct City_node {
  char * name; // Name of the site
  unsigned int numsites; //Number of sites
  City_node * next; // linked list next pointer
  Site_node * head; // Head pointer to list of Sites
};


class CS_Trip_Planning {

  public:
    CS_Trip_Planning();
   ~CS_Trip_Planning();
  
  /// @brief Add a city 
  /// @param name The name of the city to add
  /// @return True if sucessful 
  bool Add_City(char name[]);
  bool removeCity(char CityName[]); // Remove a city

  bool Add_Site_To_City(char CityName[], struct site * aSite); // NEEDS WORK
  bool removeSiteFromCity(char CityName[], char siteName[]); // Remove a city

  void displayCities();
  void displayCitySites(char CityName[]); // Display all the sites in all cities
  bool displayCitiesSites(char CityName[]); // Display all the sites in a city
  void SiteSearch(char SiteName[]); // Display every site with a particular name or type
  void SiteSearch(int constMax, int CostMin); // Display every city with a particular type of Site


  private:
    
    City_node * head; // City head node
    /// @brief This is temporary and will get better implemented later
    /// @param headNode Head node of the city linked list
    void printDetails();
    void printDetails(City_node * aCity);
    void printDetails(site * aSite);

    City_node * traverseForCityName(char * CityName[]);
    Site_node * traverseForSiteName(Site_node * head, char * SiteName[]);
    //Pop an element of the linked list in place (IE delete a city or site)
    template <typename T> bool PopInPlace(T* llhead, T* aNode);
    //Traverse a linked list for a name
    //template <typename T> bool PopDuplicates(T* aNode, char * duplicateName = 0);
    //template <typename T> bool CheckDuplicates(T* aNode,  char * duplicateName = 0);
    
};