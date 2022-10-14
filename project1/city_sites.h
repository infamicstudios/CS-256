// By Duncan McFarlane on 10/4/22 for PDX.EDU CS163
// Revised 10/5/22 
// I have realized after writing this that it would be much better 
// to refactor my structs into classes but due to time constraints I can't do this

#include <cstdint>
#include <map>

struct Site {
  char * name; // Name of the site
  unsigned int priority; 
  unsigned int visitTime_mins; // The time consumed by visiting in Minutes
  unsigned int costDollars; // Cost in dollars of visiting the Site
  bool reservationsRequired; // If Reservations are required
  bool swimsuitRequired; // If a swimsuit is required
  bool hasBeenVisited; // If the site has been visited in the past
};

struct Site_node {
  Site * Sitedata;
  char * name; // This is largely an organizational tool for searching and deleting
  Site_node * next; // Pointer to next site 
};

struct City_node {
  char * name; // Name of the site
  unsigned int numsites; //Number of sites
  City_node * next; // linked list next pointer
  Site_node * head; // Head pointer to list of Sites
};

//These overloaded == operators break for some reason. Maybe the compiler is autogenerating these?
/*
bool operator==(const Site& site1, const Site& site2)
{
    return !strcmp(site1.name, site2.name)                           && 
            site1.visitTime_mins == site2.visitTime_mins             &&
            site1.costDollars == site2.costDollars                   &&
            site1.reservationsRequired == site2.reservationsRequired &&
            site1.swimsuitRequired == site2.swimsuitRequired         &&
            site1.hasBeenVisited == site2.hasBeenVisited;
}*/

/*
bool operator==(const Site_node& site1, const Site_node& site2)
{
    return site1.Sitedata == site2.Sitedata;
}
*/

/*
bool operator==(const City_node& City1, const City_node& City2)
{
  return !strcmp(City1.name, City2.name)                       && 
      City1.numsites == City2.numsites;
}
*/


class CS_Trip_Planning {

  public:
    CS_Trip_Planning();
   ~CS_Trip_Planning();
  
    /// @brief Add a city 
    /// @param name The name of the city to add
    /// @return True if sucessful 
    bool Add_City(char name[]);
    
    /// @brief Remove a city 
    /// @param CityName The name of the city to remove 
    /// @return true of city was sucesfully removed
    bool removeCity(char CityName[]);

    /// @brief Add a sity to a particular city. NOTES: NEEDS WORK SEEMS TO SEG FAULT
    /// @param CityName The name of the city to add the site
    /// @param aSite Prefilled Site Struct containing Site data 
    /// @return True if sucesfully added
    bool Add_Site_To_City(char CityName[], struct Site * aSite);
    bool Add_Site_To_City(char CityName[], struct Site * aSite, unsigned int Priority);

    /// @brief Remove a Site from a city
    /// @param CityName The name of the city containing Site
    /// @param siteName The name of the site to remove.
    /// @return True if succesffully located and removed. 
    bool removeSiteFromCity(char CityName[], char siteName[]); // Remove a city

    /// @brief Displays recursively all the cities, their sites and site data.
    void displayCities();

    /// @brief Recursively display all sites in a specific city
    /// @param CityName The name of the City to display data on 
    bool displayCitiesSites(char CityName[]); // Display all the sites in a city

    bool displaySitesWithName(char sitename[]);

    /// @brief Search for a specific type of site by site name across all cities
    /// @param SiteName The name of the site to search for ("zoo", "concert") etc.
    void SiteSearch(char SiteName[]); // Display every site with a particular name or type

    /// @brief Search for a specific type of site by site cost across all cities
    /// @param constMax the max cost for search range
    /// @param CostMin the min cost for search range
    void SiteSearch(int constMax, int CostMin); // Display every city with a particular type of Site

  private:
    /// @brief Head of City Linked list
    City_node * head; 

    /// @brief Print recursively details about cities and respective sites.
    void printDetails();

    /// @brief Print City details and recursively print every Site.
    /// @param aCity City to Display details on.
    void printDetails(City_node * aCity);

    /// @brief Print details about a specific site
    /// @param aSite Site to print details on.
    void printDetails(Site * aSite);

    /// @brief Traverse linearly for a specific City name in the city LL
    /// @param CityName City to search for
    /// @return Pointer to the city search for or NULL if nonexistant
    City_node * traverseForCityName(char * CityName[]);

    /// @brief Traverse linearly for a speicifc Site in a city.
    /// @param head The head of the sites on that city node
    /// @param SiteName name of the site to search for
    /// @return Pointer to desired site else null
    Site_node * traverseForSiteName(Site_node * head, char * SiteName[]);

    //Pop an element of the linked list in place (IE delete a city or site)
    //template <typename T> T* traverseForName(T* llhead, char * aName[]);

    /// @brief Remove a Site or City from their Linked lists
    /// @tparam T SiteNode or CityNode
    /// @param llhead Head of the Linked List
    /// @param aNode Node to remove from the linked list
    /// @return Head to the new linked list.
    template <typename T> T* PopInPlace(T* llhead, T* aNode);

    Site_node * MergeSortedSites(Site_node* first, Site_node* second);
    void SplitSitesList(Site_node* source, Site_node** front, Site_node** back);
    void Sort(Site_node * headptr);

    //Traverse a linked list for a name
    //template <typename T> bool PopDuplicates(T* aNode, char * duplicateName = 0);
    //template <typename T> bool CheckDuplicates(T* aNode,  char * duplicateName = 0);
};