#include<gtest/gtest.h>
#include"mainwindow.h"
#include"filter_details.h"
#include"fluid_details.h"
#include"api.h"
#include<vector>

using namespace::testing;

class test1 : public ::testing ::Test{
protected:
    test1(){

        filter=new Filter_details();
        fluid = new Fluid_details();
    }
    ~test1(){
        delete filter;
        delete fluid;
    }
    Filter_details *filter;
    Fluid_details *fluid;
};


TEST_F(test1, WhenSetterfunctionIsCalledCheckitwithSetter) {
    // Test the getter and setter methods
    Filter_details* filter1 = new Filter_details("New Filter",2);
    filter1->setCurrentDate(QDate(2023, 4, 29));
    EXPECT_EQ(filter1->getName(), "New Filter");
    EXPECT_EQ(filter1->getStatus(), 2);
    EXPECT_EQ(filter1->getCurrentDate(), QDate(2023, 4, 29));

}

TEST_F(test1, SetStatusTest) {
    // Test the setStatus method
    Filter_details* filter = new Filter_details("Test Filter", 10);
    Filter_details* result = filter->setStatus(7);

    EXPECT_EQ(filter->getStatus(), 3);
    EXPECT_EQ(result, filter);

}

TEST_F(test1, CreateAndAddFilterDetailsTest) {
    // Test the createAndAddFilterDetails method
    QStringList filternames = {"Filter A", "Filter B", "Filter C"};
    int status = 3;

    Filter_details::createAndAddFilterDetails(filternames, status);

    EXPECT_EQ(Filter_details::FilterList.size(), 3);
    for (int i = 0; i < Filter_details::FilterList.size(); ++i) {
        EXPECT_EQ(Filter_details::FilterList[i]->getName(), filternames[i]);
        EXPECT_EQ(Filter_details::FilterList[i]->getStatus(), status);
        EXPECT_EQ(Filter_details::FilterList[i]->getCurrentDate(), QDate::currentDate());
    }

    // Clean up the memory
    for (Filter_details* filter : Filter_details::FilterList) {
        delete filter;
    }
    Filter_details::FilterList.clear();
}


//fluid test

TEST_F(test1, GetterSetterTest) {
    // Test the getter and setter methods
    Fluid_details* fluidptr = new Fluid_details("New Fluid",2);


    fluidptr->setCurrentDate(QDate(2023, 4, 29));

    EXPECT_EQ(fluidptr->getName(), "New Fluid");
    EXPECT_EQ(fluidptr->getStatus(), 2);
    EXPECT_EQ(fluidptr->getCurrentDate(), QDate(2023, 4, 29));

}

TEST_F(test1, WhenSetStatusofFluidisCalledCheckValue) {
    // Test the setStatus method

    Fluid_details* result = new Fluid_details("New Fluid",5);
    result->setStatus(3);
    EXPECT_EQ(result->getStatus(), 2);
    delete result;


}

TEST_F(test1, AddFluidDetailsToListTest) {
    // Test the addFluidDetailsToList method
    Fluid_details* fluid1 = new Fluid_details();
    Fluid_details* fluid2 = new Fluid_details();

    Fluid_details::addFluidDetailsToList(fluid1);
    Fluid_details::addFluidDetailsToList(fluid2);

    EXPECT_EQ(Fluid_details::FluidList.size(), 2);
    EXPECT_EQ(Fluid_details::FluidList[0], fluid1);
    EXPECT_EQ(Fluid_details::FluidList[1], fluid2);


    Fluid_details::FluidList.clear();
}

TEST_F(test1, WhenCreateAndAddFluidDetailsisCalledverifydetails) {
    // Test the createAndAddFluidDetails method
    QStringList fluidnames = {"Fluid A", "Fluid B", "Fluid C"};
    int status = 3;

    Fluid_details::createAndAddFluidDetails(fluidnames, status);

    EXPECT_EQ(Fluid_details::FluidList.size(), 3);
    for (int i = 0; i < Fluid_details::FluidList.size(); ++i) {
        EXPECT_EQ(Fluid_details::FluidList[i]->getName(), fluidnames[i]);
        EXPECT_EQ(Fluid_details::FluidList[i]->getStatus(), status);
        EXPECT_EQ(Fluid_details::FluidList[i]->getCurrentDate(), QDate::currentDate());
    }


    Fluid_details::FluidList.clear();
}

TEST(FilterDetailsSetterTest, SetFilterName) {
    // Arrange
    api apiObject; // Assuming this initializes the Filter_details objects
    std::vector<Filter_details*> filterList = apiObject.getFilterList();
    ASSERT_FALSE(filterList.empty()); // Ensure the filter list is not empty

    Filter_details* filter = filterList.front(); // Assuming only one filter is added
    QString newName = "New Filter Name"; // Use QString instead of std::string

    // Act
    filter->setName(newName);

    // Assert
    ASSERT_EQ(filter->getName(), newName);
}

