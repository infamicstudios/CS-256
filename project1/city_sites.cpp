// By Duncan McFarlane 10/6/22

#include "city_sites.h"
#include <libc.h>
#include <cstdint>
#include <stdio.h>

//Blank Destructor
CS_Trip_Planning::CS_Trip_Planning(){
    head = 0;
}

//Destructor... deletes
CS_Trip_Planning::~CS_Trip_Planning(){
    City_node *current = head;
    while(current) {
       City_node *next = current->next; 
       delete current;
       current = next;
    }
    head = 0;
}

/// @brief Add a City to head of lll 0(n)
/// @param name The name of the City to add
/// @return True if sucessful 
bool CS_Trip_Planning::Add_City(char *name){
    City_node *newCity = new City_node;
    // TODO Check if a duplicate city exists
    // if failure
    //      return false
    newCity->name = name;
    newCity->numsites = 0;
    newCity->next = head; // Swap and push to front of LLL
    head = newCity;
    return true;
}

/// @brief 
/// @param CityName The name of the City to remove 
/// @return True is sucessful
bool CS_Trip_Planning::removeCity(char CityName[]) {
    City_node * desiredCity = traverseForCityName(&CityName);
    if(desiredCity == 0)
        printf("%s is not a registered city", CityName);
        return false;
    try{
        PopInPlace(head, desiredCity);
        return true;
    }
    catch(int){
        printf("ERROR encountered while trying to remove %s from registered city", CityName);
        return false;
    }
}

/// @brief Display all Cities
void CS_Trip_Planning::displayCities(){
    printf("Here are all citys:\n");
    printDetails();
}

/// @brief Display all Sites within a city
/// @param Cityname The name of city to display sites for
/// @return true if the city exists and has sites
bool CS_Trip_Planning::displayCitiesSites(char Cityname[]){
    City_node * desiredCity = traverseForCityName(&Cityname);

    if(desiredCity == 0){
        printf("Error: %s is not a registered city.", Cityname);
        return false;
    }
    else {
        
        printf("Here are all the sites in %s:\n", Cityname);

        Site_node * tempNode = desiredCity->head;

        //If no sites exist
        if(!tempNode){
            printf("Error: %s Does not contain any sites", Cityname);
            return false;
        }

        while(tempNode){
            printDetails(tempNode->Site);
            tempNode = tempNode->next;
        }
        return true;
    }
}


/// @brief Add a Site to a city NEEDS WORK
/// @param CityName Name of the city to add the Site
/// @param siteName What to name the site
/// @param visitTime How long to visit
/// @param costDollars Cost in $ to visit
/// @param needReservations If Reservations are Required
/// @param needswimsuit If a Swimsuit is required
/// @param beenVisited If it has been visited in the past
/// @return True if sucessful false if unable to add it for whatever reason.
bool CS_Trip_Planning::Add_Site_To_City(char CityName[], struct site * aSite){
    
    City_node * desiredCity = traverseForCityName(&CityName);
    // Check if City Exists
    if (desiredCity == 0){
        return false; //TODO: I could make custom error classes or handlers for these.
    }

    //Populate the new site
    Site_node *newSite = new Site_node;
    newSite->Site = aSite;

    // Add at start of linked list.
    newSite->next = desiredCity->head;
    desiredCity->head = newSite;
    desiredCity->numsites++;
    return true;
}


////////////////////
/////    Utility Methods
////////////////////


////
// Traverse Methods
///


//TODO: It would be great to be able to use a similar template function for 
// searching and returning a node by name. This is not currently possible because site struct contains name
// not site node.

/* Traverse for City Name traverses the City LLL for a particular city name returning 
 * A pointer to the desired one if it exists. If it does not exist then it returns a nullptr.
 * This could be recusive but it's not really necessary and would complicate arguments.
 */
City_node * CS_Trip_Planning::traverseForCityName(char * CityName[]){
    City_node * current = head;
    while(current && strcmp(current->name, *CityName) != 0) {
            current = current->next;
    }
    if(current->next == 0) {
            printf("\nERROR: The city named %s does not exist\n", *CityName);
            return 0;
    }
    return current;     
}

Site_node * CS_Trip_Planning::traverseForSiteName(Site_node * CitySitesHead, char * SiteName[]){
    Site_node * current = CitySitesHead; 
    while(current && strcmp(current->Site->name, *SiteName) != 0) {
        current = current->next;
    } 
    if(current->next == 0) {
        printf("\nERROR: The city named %s does not exist\n", *SiteName);
        return 0;
    }
    return current;
}

////
// End Traverse Methods
///

////
// LLL Management Methods
///

/// @brief Templated Method for removing either a city or a site from their linked lists
/// @tparam T Linked list Node
/// @param llhead Head of that respective linked list
/// @param aNode The node to delete
/// @return the next respective node in the LL.
template <typename T> bool CS_Trip_Planning::PopInPlace(T* llhead, T* aNode){
    
    T* prev = llhead;

    while(prev->next && strcmp(prev->next->name, aNode->name) != 0) 
        prev = prev->next; 

    // Check if node exists
    if(prev->next == 0) 
    { 
        printf("\nGiven node does not exist"); 
        return false; 
    } 

    // Remove node from Linked List 
    prev->next = prev->next->next; 
    // Free memory 
    delete aNode;
    return true; 
} 

////
// End LLL Management Methods
///

////
// Display Methods
///
void CS_Trip_Planning::printDetails(site * aSite){
    printf("\nSite Name: %s\n\tSite Visit Time: %u\n", aSite->name, aSite->visitTime_mins);
    printf("\tReservations Needed: %d\n\tSwimsuit Needed: %d\n", aSite->reservationsRequired, aSite->swimsuitRequired);
    printf("\tCost:%u\n\tHas Been Visited: %d", aSite->costDollars, aSite->hasBeenVisited);
}

void CS_Trip_Planning::printDetails(City_node * aCity){
    printf("\nCity Name: %s\n\tNumber of Sites: %u\n", aCity->name, aCity->numsites);

    if (aCity->numsites > 0){
        Site_node * current = aCity->head;
        while(current){
            printDetails(current->Site);
            current = current->next;
        }
    }
}

void CS_Trip_Planning::printDetails(){
    City_node * current = head;
    while (current){
        printDetails(current);
        current = current->next;
    }
}

////
// End Display Methods
///

/*
///WORK IN PROGESS CODE


bool CS_Trip_Planning::removeSiteFromCity(char * CityName[], char * siteName[]){
    City_node * desiredCity = traverseForCityName(head, &CityName);
    if (!desiredCity)
        return false; //TODO: I could make custom error classes or handlers for these.
    Site_node * desiredSite = traverseForSiteName(desiredCity->head, &siteName);
    // If a user wants to remove a site from a city they probably want to remove all instances of it
    bool res = PopInPlace(desiredSite);
    if(res)
        desiredCity->numsites++;
    return res;
}

//////////////
// Utility Methods
//////////////



//TODO: THIS method is unused right now and needs alot of work. Right now it only picks up the first duplicate.
// Additionally it is unused as it needs to iterate over and not just from the node.
template <typename T> bool CS_Trip_Planning::PopDuplicates(T* aNode, char * duplicateName = 0){
    
    // This is kinda funky but it grabs the first name on the first node.
    if(aNode != 0){
        if (strcmp(duplicateName, aNode->name;)){ 
            return PopInPlace(aNode);
        }
        //Catch the first duplicate name and then pass it along on every iteration.
        if (duplicateName == 0)
            duplicateName = aNode->name;
    }
    return false;
}

template <typename T> bool CS_Trip_Planning::CheckDuplicates(T* aNode, char * duplicateName = 0){
    
    // Grabs the first name on the first node on first iteration.
    if (duplicateName == 0)
        duplicateName = aNode->name;
    if(aNode != 0){
        if (strcmp(duplicateName, aNode->name;)){ 
            return true;
        }
        CheckDuplicates(T* aNode, duplicateName);
    }
    return false;
}
*/
