#include <gtest/gtest.h>
#include "PoliticalSys.h"
#include "algorithm"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Leader_Democretic.h"
#include "social_denocrat.h"
#include "Leader_republic.h"
#include "social_republic.h"
#include "Republican_Party.h"
#include "Democratic_Party.h"
#include "Exception.h"
#include <limits>

using namespace std;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
1) addPolitician()
   * Adding a Republicans successfully
   * Adding a Democrat successfully
   * If user enters an number/ID not specified
   * large ID / powers
   * special characters in names
   * User enters a negative number
   * Duplicate IDs
   * The party name is already in the list
   * Party name is invalid
   * Party name is blank (ex: "")
2) add_pol_with_params()
   * Successfully added a Democrat leader
   * Successfully added a Republican leader
   * Adding a social Democrat
   * Adding a social Republican

*/

/*
ctor
c ctor
return pow
name
pol party
change party
set pow
get location
*/

class PoliticalSysTest : public ::testing::Test
{
    protected:
        std::stringstream _stream;
        PoliticalSys* _politicalSys;

    void SetUp () override
    {
        std:cin.rdbuf(_stream.rdbuf());
        _politicalSys = new PoliticalSys();

    }
    
    void TearDown () override
    {
        std:cin.rdbuf(NULL);
        delete _politicalSys;
        _politicalSys = NULL;
    }
};

TEST_F(PoliticalSysTest, PrintParties)
{
    _politicalSys->add_pol_with_params("Bob", "Smith", 1, "D", "L", 100);
    _politicalSys->add_pol_with_params("Joe", "Smith", 2, "R", "L", 100);
    _politicalSys->add_party_with_params("Democratic Party", "D");
    _politicalSys->add_party_with_params("Republican Party", "R");
    ::testing::internal::CaptureStdout();
    _politicalSys->printParties();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    expected = "----Parties----\nDemocrat Party: Democratic Party, chairman:None, Size:1\n\tDemocratic Person:Bob Smith, Id:1, Power:100, Type:L, Chairman: None\nRepublican Party: Republican Party, chairman:None, Size:1\n\tRepublican Person:Joe Smith, Id:2, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, PrintParties_Empty)
{
    ::testing::internal::CaptureStdout();
    _politicalSys->printParties();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, D_BiggestParty)
{
    _politicalSys->add_pol_with_params("Bob", "Smith", 1, "D", "L", 100);
    _politicalSys->add_party_with_params("Democratic Party", "D");
    _politicalSys->add_party_with_params("Republican Party", "R");

    // found on stack overflow: https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest
    // tests every output and shows what's supposed to be outputted
    ::testing::internal::CaptureStdout();
    _politicalSys->BiggestParty();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    expected = "----Biggest Party----\n[Democratic Party,1]\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, R_BiggestParty)
{
    _politicalSys->add_pol_with_params("Joe", "Smith", 1, "R", "L", 100);
    _politicalSys->add_party_with_params("Democratic Party", "D");
    _politicalSys->add_party_with_params("Republican Party", "R");

    // tests every output and shows what's supposed to be outputted
    ::testing::internal::CaptureStdout();
    _politicalSys->BiggestParty();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    expected = "----Biggest Party----\n[Republican Party,1]\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, BiggestParty_Empty)
{
    // tests every output and shows what's supposed to be outputted
    ::testing::internal::CaptureStdout();
    _politicalSys->BiggestParty();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

// TEST FAILS - when parties are equal, it always returns the Republican Party
TEST_F(PoliticalSysTest, EQ_BiggestParty_R1st)
{
    _politicalSys->add_pol_with_params("Joe", "Smith", 2, "R", "L", 100);
    _politicalSys->add_pol_with_params("Bob", "Smith", 1, "D", "L", 100);
    _politicalSys->add_party_with_params("Republican Party", "R");
    _politicalSys->add_party_with_params("Democratic Party", "D");

    // tests every output and shows what's supposed to be outputted
    ::testing::internal::CaptureStdout();
    _politicalSys->BiggestParty();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    // expected = " ----Biggest Party----\n-[Republican Party,1]\n\n+[Democratic Party,1]\n";
    expected = "----Biggest Party----\n[Republican Party,1]\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

// TEST FAILS - when parties are equal, it always returns the Republican Party
TEST_F(PoliticalSysTest, EQ_BiggestParty_D1st)
{
    _politicalSys->add_pol_with_params("Bob", "Smith", 1, "D", "L", 100);
    _politicalSys->add_pol_with_params("Joe", "Smith", 2, "R", "L", 100);
    _politicalSys->add_party_with_params("Democratic Party", "D");
    _politicalSys->add_party_with_params("Republican Party", "R");

    // tests every output and shows what's supposed to be outputted
    ::testing::internal::CaptureStdout();
    _politicalSys->BiggestParty();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;
    // expected = " ----Biggest Party----\n-[Republican Party,1]\n\n+[Democratic Party,1]\n";
    expected = "----Biggest Party----\n[Republican Party,1]\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, PrintPoliticians)
{
    _politicalSys->add_pol_with_params("Bob", "Smith", 1, "D", "L", 100);
    _politicalSys->add_pol_with_params("Joe", "Smith", 2, "R", "L", 100);
    _politicalSys->add_party_with_params("Democratic Party", "D");
    _politicalSys->add_party_with_params("Republican Party", "R");
    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:1, Power:100, Type:L, Chairman: None\nRepublican Person:Joe Smith, Id:2, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());

}

TEST_F(PoliticalSysTest, PrintPoliticians_Empty)
{
    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());

}

TEST_F(PoliticalSysTest, Elections_Empty)
{
    ::testing::internal::CaptureStdout();
    _politicalSys->elections();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

// Able to override cin
// Found using google test example: https://github.com/google/googletest/issues/2385
TEST_F(PoliticalSysTest, CinTest)
{
    _stream << "5\n10\nabc\n";
    int num;
    int num2;
    std::string word;
    std::cin >> num;
    std::cin >> num2;
    std::cin >> word;

    ASSERT_EQ(num, 5);
    ASSERT_EQ(num2, 10);
    ASSERT_STREQ(word.c_str(), "abc");
}

TEST_F(PoliticalSysTest, addPolIdValid)
{
    _stream << "Bob\n" << "Smith\n" << "1\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:1, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolIdNotValid)
{
    // throw exception on negative id, must accept the valid id
    _stream << "Bob\n" << "Smith\n" << "-1\n";
    // starts over, expecting name, id, power, etc
    _stream << "Bob\n" << "Smith\n" << "1\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:1, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolIdMaxInt)
{
    std::stringstream id;
    id << INT_MAX;
    _stream << "Bob\n" << "Smith\n" << id.str() << "\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:" + id.str() + ", Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolId0)
{
    _stream << "Bob\n" << "Smith\n" << "0\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolIdSame)
{
    // fail on duplicate id number
    _stream << "Bob\n" << "Smith\n" << "0\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    _stream << "Bri\n" << "Smith\n" << "0\n";
        // starts over, expecting name, id, power, etc
    _stream << "Bri\n" << "Smith\n" << "1\n" << "99\n" << "D\n" << "S\n";
    _politicalSys->addPolitician();


    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:100, Type:L, Chairman: None\nDemocratic Person:Bri Smith, Id:1, Power:99, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolPowNegative)
{
    // fail on duplicate id number
    _stream << "Bob\n" << "Smith\n" << "0\n" << "-1\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();


    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:100, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolPow0)
{
    // fail on duplicate id number
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();


    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolPowMaxInt)
{
    std::stringstream pow;
    pow << INT_MAX;
    _stream << "Bob\n" << "Smith\n" << "1\n" << pow.str() << "\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:1, Power:" + pow.str() + ", Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartySwitchRole)
{
    // fail on bad party
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "L\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyF)
{
    // fail on bad party, invalid entry
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "F\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyE)
{
    // fail on bad party, invalid entry
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "E\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyFullNameD)
{
    // fail on bad party, spelled out party instead of giving one letter (D)
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "Democrat\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyFullNameR)
{
    // fail on bad party
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "Republican\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyLowerCaseR)
{
    // fail on bad party
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "r\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongPartyLowerCaseD)
{
    // fail on bad party
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "d\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

// TEST FAILS
// TEST_F(PoliticalSysTest, addPolWrongPartySpaceBeforeD)
// {
//     // fail on bad party
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << " D\n";
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
//     _politicalSys->addPolitician();

//     ::testing::internal::CaptureStdout();
//     _politicalSys->printPoliticians();
//     std::string line = ::testing::internal::GetCapturedStdout();
//     std::string expected;

//     expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
//     ASSERT_STREQ(line.c_str(), expected.c_str());
// }

// TEST FAILS
// TEST_F(PoliticalSysTest, addPolWrongPartySpaceAfterD)
// {
//     // fail on bad party
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D \n";
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
//     _politicalSys->addPolitician();

//     ::testing::internal::CaptureStdout();
//     _politicalSys->printPoliticians();
//     std::string line = ::testing::internal::GetCapturedStdout();
//     std::string expected;

//     expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
//     ASSERT_STREQ(line.c_str(), expected.c_str());
// }

// TEST FAILS
// TEST_F(PoliticalSysTest, addPolWrongPartySpaceBeforeR)
// {
//     // fail on bad party
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << " R\n";
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "L\n";
//     _politicalSys->addPolitician();

//     ::testing::internal::CaptureStdout();
//     _politicalSys->printPoliticians();
//     std::string line = ::testing::internal::GetCapturedStdout();
//     std::string expected;

//     expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
//     ASSERT_STREQ(line.c_str(), expected.c_str());
// }

// TESTS FAILS
// TEST_F(PoliticalSysTest, addPolWrongPartySpaceAfterR)
// {
//     // fail on bad party
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R \n";
//     _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "L\n";
//     _politicalSys->addPolitician();

//     ::testing::internal::CaptureStdout();
//     _politicalSys->printPoliticians();
//     std::string line = ::testing::internal::GetCapturedStdout();
//     std::string expected;

//     expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
//     ASSERT_STREQ(line.c_str(), expected.c_str());
// }

TEST_F(PoliticalSysTest, addPolWrongRollFullNameL)
{
    // fail on bad party, spelled out party instead of giving one letter (D)
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "Leader\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleS)
{
    // fail on bad role, put T instead of S)
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "T\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "S\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleL)
{
    // fail on bad role, put K instead of L
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "K\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleFullNameS)
{
    // fail on bad role, put Social instead of S
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "Social\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "S\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleLowerCaseL)
{
    // fail on bad role, put lower case L
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "l\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleLowerCaseS)
{
    // fail on bad role, put lower case S
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "s\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "R\n" << "S\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nRepublican Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleSpaceBeforeL)
{
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << " L\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleSpaceAfterL)
{
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L \n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:L, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleSpaceBeforeS)
{
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << " S\n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "S\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, addPolWrongRoleSpaceAfterS)
{
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "S \n";
    _stream << "Bob\n" << "Smith\n" << "0\n" << "0\n" << "D\n" << "S\n";
    _politicalSys->addPolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

// TEST_F(PoliticalSysTest, AddPartyValidID)
// {
//     // _politicalSys->addParty();
//     _politicalSys->add_party_with_params("Democratic Party", "D");

//     _stream << "Democratic Party\n";
//     _politicalSys->removeParty();
//     ::testing::internal::CaptureStdout();
//     _politicalSys->printParties();
//     std::string line = ::testing::internal::GetCapturedStdout();
//     std::string expected;

//     expected = "----Politicians----\nDemocratic Person:Bob Smith, Id:0, Power:0, Type:S, Chairman: None\n";
//     ASSERT_STREQ(line.c_str(), expected.c_str());
// }

TEST_F(PoliticalSysTest, RemovePolValidID)
{
    _stream << "Bob\n" << "Smith\n" << "1\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();
    _stream << "1\n";
    _politicalSys->removePolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, RemovePolIDNotFound)
{
    _stream << "Bob\n" << "Smith\n" << "1\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();
    _stream << "0\n";
    _stream << "1\n";
    _politicalSys->removePolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, RemovePolInvalidID)
{
    _stream << "Bob\n" << "Smith\n" << "1\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();
    _stream << "-1\n";
    _stream << "1\n";
    _politicalSys->removePolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, RemovePolEmpty)
{
    _stream << "0\n";
    _politicalSys->removePolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

TEST_F(PoliticalSysTest, RemovePolMaxInt)
{
    std::stringstream id;
    id << INT_MAX;
    _stream << "Bob\n" << "Smith\n" << id.str() << "\n" << "100\n" << "D\n" << "L\n";
    _politicalSys->addPolitician();

    _stream << id.str() << "\n";
    _politicalSys->removePolitician();

    ::testing::internal::CaptureStdout();
    _politicalSys->printPoliticians();
    std::string line = ::testing::internal::GetCapturedStdout();
    std::string expected;

    expected = "";
    ASSERT_STREQ(line.c_str(), expected.c_str());
}

/*
add pol
    X valid id
    X invalid id [ERROR]
    X id of 0
    X max int id
    X 2 pols with same id [ERROR]
    X pow < 0 [ERROR]
    X pow = 0
    X pow max int
    X anything other than a D or R [ERROR] X2
        X switching party and role
        X spelling out "Democrat"
        X spelling out "Republican"
        X lower case d
        X lower case r
        X adding a space at the end of d
        X adding a space at the end of d
        X adding a space at in front of d
        X adding a space at in front of r
    (19)
    X anything other than S or L [ERROR] X2
        X spelling out "Leader"
        X spelling out "Social"
        X lower case l
        X lower case s
        X adding a space at the end of s
        X adding a space at the end of s
        X adding a space at in front of l
        X adding a space at in front of l
    (29)
add party
remove party
    X valid id
    (30)
    invalid id [ERROR]
    remove empty party [ERROR] (DNE)
    spell it out fully
        R
        D
    lowercase
        r
        d
    remove when there's only 1 other party
    remove when there's 2 parties (pols moved to other party)

remove pol
    X valid id
    invalid id [ERROR]
        X negative id [ERROR]
        X id of 0
        X max int id
    X remove empty pol [ERROR] (does not exist) [ERROR]
    (35)

elections
    only 1 party
    2 parties
    [done] 0 parties
    0 pols
    equal power
*/
