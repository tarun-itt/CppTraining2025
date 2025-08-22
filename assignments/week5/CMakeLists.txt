cmake_minimum_required(VERSION 3.16)
project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


include_directories(inc)

set(MAIN_SOURCES
    src/main.cpp
    src/entities/User.cpp
    src/entities/Account.cpp
    src/entities/Transaction.cpp
    src/entities/TransactionLedger.cpp
    src/entities/UserRegistry.cpp
    src/entities/AccountRegistry.cpp
    src/entities/UserDatabaseManager.cpp
    src/roles/AccountHolder.cpp
    src/roles/Admin.cpp
    src/auth/AuthController.cpp
    src/Bank/Bank.cpp
    src/UI/AccountMenu.cpp
    src/UI/AdminMenu.cpp
    src/UI/LoginMenu.cpp
    src/UI/MenuUtils.cpp
)

set(TEST_SOURCES
    tests/test_User.cpp
    tests/test_Account.cpp
    tests/test_Transaction.cpp
    tests/test_TransactionLedger.cpp
    tests/test_UserRegistry.cpp
    tests/test_AccountRegistry.cpp
)

add_executable(banking_system ${MAIN_SOURCES})

add_executable(banking_tests ${TEST_SOURCES} 
    src/entities/User.cpp
    src/entities/Account.cpp
    src/entities/Transaction.cpp
    src/entities/TransactionLedger.cpp
    src/entities/UserRegistry.cpp
    src/entities/AccountRegistry.cpp
    src/roles/AccountHolder.cpp
)

target_link_libraries(banking_tests 
    GTest::gtest 
    GTest::gmock 
    GTest::gtest_main
)

enable_testing()
add_test(NAME BankingSystemTests COMMAND banking_tests)

target_compile_options(banking_system PRIVATE )
target_compile_options(banking_tests PRIVATE )