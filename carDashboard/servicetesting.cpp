#include<gtest/gtest.h>
#include<../ServiceFolder/serviceconnection.h>


class servicetestingclass : public ::testing::Test {
protected:
    serviceConnection* sptr;

    // Constructor
    servicetestingclass() {
        sptr = new serviceConnection();
    }

    // Destructor
    ~servicetestingclass() override {
        delete sptr;
    }
};

// Define your test cases here using TEST_F macro
TEST_F(servicetestingclass, SetUsernameGetUsername) {
    bool val=sptr->setusername("shardul");
    EXPECT_EQ(1,val);
    // Test logic goes here
}

