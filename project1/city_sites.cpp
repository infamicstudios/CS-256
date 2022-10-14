// By Duncan McFarlane 10/6/22

#include "city_sites.h"
#include <cstring>
#include <cstdint>
#include <stdio.h>

//Blank Destructor
CS_Trip_Planning::CS_Trip_Planning(){
    head = 0;
}

//Destructor... destructs and clears all citys
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

    if(desiredCity == NULL){
        printf("\n%s is not a registered city\n", CityName);
        return false;
    }

    try{
        head = PopInPlace(head, desiredCity);
        return true;
    }
    catch(int){
        printf("\nERROR encountered while trying to remove %s from registered city\n", CityName);
        return false;
    }
}

/// @brief Display all Cities
void CS_Trip_Planning::displayCities(){
    printf("\nHere are all citys:\n");
    printDetails();
}

/// @brief Display all Sites within a city TODO: This displays sites twice for some reason
/// @param Cityname The name of city to display sites for
/// @return true if the city exists and has sites
bool CS_Trip_Planning::displayCitiesSites(char Cityname[]){
    City_node * desiredCity = traverseForCityName(&Cityname);

    if(desiredCity == NULL){
        printf("Error: %s is not a registered city.", Cityname);
        return false;
    } else {

        printf("\nHere are all the sites in %s:\n", Cityname);

        Site_node * tempNode = desiredCity->head;

        //If no sites exist
        if(tempNode == NULL){
            printf("\nError: %s Does not contain any sites\n", Cityname);
            return false;
        }
        while(tempNode == NULL){
            printDetails(tempNode->Sitedata);
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
bool CS_Trip_Planning::Add_Site_To_City(char CityName[], struct Site * sitedata){

    City_node * desiredCity = traverseForCityName(&CityName);
    // Check if City Exists
    if (desiredCity == NULL){
        return false; //TODO: I could make custom error classes or handlers for these.
    }

    //Populate the new site
    Site_node *newSite = new Site_node;
    newSite->Sitedata = sitedata;
    newSite->name = sitedata->name;
    // Add at start of linked list.
    newSite->next = desiredCity->head;
    desiredCity->head = newSite;
    desiredCity->numsites++;
    Sort(desiredCity->head);
    return true;
}


/// @brief
/// @param CityName The name of the city Containing the site
/// @param siteName The name of the site to remove
/// @return
bool CS_Trip_Planning::removeSiteFromCity(char CityName[], char siteName[]){
    City_node * desiredCity = traverseForCityName(&CityName);
    if (desiredCity == NULL)
        return false; //TODO: I could make custom error classes or handlers for these.
    Site_node * desiredSite = traverseForSiteName(desiredCity->head, &siteName);
    if (desiredSite == NULL)
        return false; //TODO: I could make custom error classes or handlers for these.
    // If a user wants to remove a site from a city they probably want to remove all instances of it
    desiredCity->head = PopInPlace(desiredCity->head, desiredSite);
    desiredCity->numsites--;
    return true;
}


////////////////////
/////    Utility Methods
////////////////////


////
// Traverse Methods
///

/* Traverse for City Name traverses the City LLL for a particular city name returning
 * A pointer to the desired one if it exists. If it does not exist then it returns a nullptr.
 * This could be recusive but it's not really necessary and would complicate arguments.
 */
City_node * CS_Trip_Planning::traverseForCityName(char * CityName[]){
    City_node * current = head;
    while(current && strcmp(current->name, *CityName) != 0) {
        current = current->next;
    }
    if(current->next == NULL) {
        printf("\nERROR: The Site named %s does not exist\n", *CityName);
        return 0;
    }
    return current;
}

Site_node * CS_Trip_Planning::traverseForSiteName(Site_node * CitySitesHead, char * SiteName[]){
    Site_node * current = CitySitesHead;
    while(current && strcmp(current->Sitedata->name, *SiteName) != 0) {
        current = current->next;
    }
    if(current->next == NULL) {
        printf("\nERROR: The Site named %s does not exist\n", *SiteName);
        return 0;
    }
    return current;
}

/* I wish I could get this to work but I can't for some reason.
template <typename T> T* traverseForName(T* llhead, char * aName[]){
    T* current = llhead;
    while(current && strcmp(current->name, aName)!=0){
        current = current->next;
    }
    if(current->next == NULL) {
        printf("\nERROR: The Name named %s does not exist\n", *aName);
        return 0;
    }
    return current;
}
*/


////
// End Traverse Methods
///


////
// LLL Management Methods
///

/// @brief Remove a node from a linked list TODO:LOOK INTO IF THIS CAUSES MEMORY LEAKS MIGHT NEED TO DELETE>
/// @tparam T SiteNode or CityNode
/// @param llhead 
/// @param aNode 
/// @return 
template <typename T> T* CS_Trip_Planning::PopInPlace(T* llhead, T* aNode){
    if(llhead == NULL)
        return llhead;

    T* newNextNode = PopInPlace(llhead->next, aNode);

    if(strcmp(llhead->name, aNode->name) == 0){
        return newNextNode;
    } else {
            llhead -> next = newNextNode;
            return llhead;
    }
}
////
// End LLL Management Methods
///

////
// Display Methods
///
void CS_Trip_Planning::printDetails(Site * aSite){
    printf("\nSite Name: %s\n\tSite Visit Time: %u\n", aSite->name, aSite->visitTime_mins);
    printf("\tReservations Needed: %d\n\tSwimsuit Needed: %d\n", aSite->reservationsRequired, aSite->swimsuitRequired);
    printf("\tCost:%u\n\tHas Been Visited: %d", aSite->costDollars, aSite->hasBeenVisited);
}

void CS_Trip_Planning::printDetails(City_node * aCity){
    printf("\nCity Name: %s\n\tNumber of Sites: %u\n", aCity->name, aCity->numsites);

    if (aCity->numsites > 0){
        Site_node * current = aCity->head;
        while(current->next){
            printDetails(current->Sitedata);
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

Site_node * CS_Trip_Planning::MergeSortedSites(Site_node* first, Site_node* second){
    Site_node* result = NULL;

    // Base Cases
	if (first == NULL) 
		return (second); 
	else if (second == NULL) 
		return (first); 

	// recursively merging two lists
	if (first->Sitedata->priority <= second->Sitedata->priority) { 
		result = first; 
		result->next = MergeSortedSites(first->next, second); 
	} 
	else { 
		result = second; 
		result->next = MergeSortedSites(first, second->next); 
	} 
	return result; 
}

// If the size of the list is odd, then extra element goes in the first list.
void CS_Trip_Planning::SplitSitesList(Site_node* source, Site_node** front, Site_node** back) 
{ 
	Site_node* ptr1; 
	Site_node* ptr2; 
	ptr2 = source; 
	ptr1 = source->next; 

	// ptr1 is incrmented twice and ptr2 is icremented once.
	while (ptr1 != NULL) { 
		ptr1 = ptr1->next; 
		if (ptr1 != NULL) { 
			ptr2 = ptr2->next; 
			ptr1 = ptr1->next; 
		} 
	} 

	// ptr2 is at the midpoint.
	*front = source; 
	*back = ptr2->next; 
	ptr2->next = NULL; 
} 

// Merge Sort
void CS_Trip_Planning::Sort(Site_node * headptr) 
{ 
	Site_node* head = headptr; 
	Site_node* ptr1; 
	Site_node* ptr2; 

  // Base Case
	if ((head == NULL) || (head->next == NULL)) { 
		return; 
	} 

	// Splitting list
	SplitSitesList(head, &ptr1, &ptr2); 

	// Recursively sorting two lists.
	Sort(ptr1); 
	Sort(ptr2); 

	// Sorted List.
	headptr = MergeSortedSites(ptr1, ptr2); 
} 

////
// End Display Methods
///


///WORK IN PROGESS CODE


///WORK IN PROGESS CODE


//////////////
// Utility Methods
//////////////