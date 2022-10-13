#include <stdio.h>
#include "city_sites.h"

bool test_AddCity(){
    printf("TEST #1 CITY CREATION\n");
    printf("Description: This test adds 3 citys: Portland, Seattle, New York");
    printf(" and tests displaying them.\n");
    CS_Trip_Planning aJourney = CS_Trip_Planning();
    // Test Adding Cities
    try { 
        aJourney.Add_City((char*)"Portland");
        aJourney.Add_City((char*)"Seattle");
        aJourney.Add_City((char*)"New York");
        aJourney.displayCities(); //TODO:: Figure out how to evaluate this quietly.
        return true;
    }
    catch (int){
        printf("City creation test failed");
        return false;
    }
    
}

bool test_RemoveCity(){
    printf("TEST #2 CITY DELETION\n");
    printf("Description: This test adds 6 citys: Portland, Seattle, New York, San Fransisco,");
    printf(" London, and Chicago And tests deleting Seattle.\n");
    printf("Sucessful Output: Portland, New York, San Fransisco, London Chicago\n");
    CS_Trip_Planning aJourney = CS_Trip_Planning();
    // Test Adding Cities
    try { 
        aJourney.Add_City((char*)"Portland");
        aJourney.Add_City((char*)"Seattle");
        aJourney.Add_City((char*)"New York");
        aJourney.Add_City((char*)"San Fransisco");
        aJourney.Add_City((char*)"London");
        aJourney.Add_City((char*)"Chicago");
        aJourney.removeCity((char*)"Seattle");
        aJourney.displayCities(); //TODO:: Figure out how to evaluate this quietly.
        return true; 
    }
    catch (int){
        printf("City deletion test failed");
        return false;
    }
}

bool test_AddSite(){
    printf("TEST #3 Site Creation\n");
    printf("Description: This test adds a site to the city of New York");
    printf(" And tests adding and displaying sites in a specific city\n");
    printf("Sucessful Output: details about the empire state building\n");
    CS_Trip_Planning aJourney = CS_Trip_Planning();
    // Test Adding Cities
    try {
        aJourney.Add_City((char*)"Portland");
        aJourney.Add_City((char*)"New York");
        aJourney.Add_City((char*)"Seattle");
        //aJourney.Add_City((char*)"Portland"); 
        Site EmpireStateBuilding  = {
        (char*)"Empire State Building", // Name of the site 
        60, // The time consumed by visiting in Minutes
        0,  // Cost in dollars of visiting the Site
        false, // If Reservations are required
        false, // If a swimsuit is required
        false  // If the site has been visited in the past
        };
        aJourney.Add_Site_To_City((char*)"New York", &EmpireStateBuilding);
        aJourney.displayCitiesSites((char*)"New York");
        return true;
    }
    catch (int){
        printf("City Site Creation test failed");
        return false;
    }
}

bool test_RemoveSite(){
    printf("\nTEST #4 Site Removal\n");
    printf("Description: This test adds a site to the city of New York");
    printf(" And then remove it testing adding and removing displaying sites\n");
    printf(" in a specific city. Sucessful Output: Removal of the Empire State building Site\n");

    CS_Trip_Planning aJourney = CS_Trip_Planning();
    // Test Adding Cities
    try {
        aJourney.Add_City((char*)"Portland");
        aJourney.Add_City((char*)"New York");
        aJourney.Add_City((char*)"Seattle");
        //aJourney.Add_City((char*)"Portland"); 
        Site EmpireStateBuilding  = {
        (char*)"Empire State Building", // Name of the site 
        60, // The time consumed by visiting in Minutes
        0, // Cost in dollars of visiting the Site
        false, // If Reservations are required
        false, // If a swimsuit is required
        false // If the site has been visited in the past
        };
        aJourney.Add_Site_To_City((char*)"New York", &EmpireStateBuilding);
        aJourney.displayCitiesSites((char*)"New York");
        aJourney.removeSiteFromCity((char*)"New York", (char*)"Empire State Building");
        aJourney.displayCitiesSites((char*)"New York");
        return true;
    }
    catch (int){
        printf("City Site Creation test failed");
        return false;
    }
}