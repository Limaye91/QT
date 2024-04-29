#include "api.h"
#include "QDebug"
api::api(){
    // Initialize filterd and fluidd
    filterptr = new Filter_details(this);
    fluidptr = new Fluid_details(this);

    QStringList filterNames = {"Cabin Air Filter", "Oil Filter", "Fuel Filter"};
    Filter_details::createAndAddFilterDetails(filterNames, 100);
    QStringList fluidNames = {"Oil Fluid", "Rocket Fluid", "Petrol Fluid"};
    Fluid_details::createAndAddFluidDetails(fluidNames, 100);

}

api::~api()
{
    delete filterptr;
    delete fluidptr;
}

std::vector<Filter_details*> api::getFilterList() {
    return Filter_details::FilterList;
}

std::vector<Fluid_details*> api::getFluidList(){
    return Fluid_details::FluidList;
}
