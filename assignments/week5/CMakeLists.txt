cmake_minimum_required(VERSION 3.16)
project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

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
    tests/UserGTest.cpp
    tests/AccountGTest.cpp
    tests/TransactionGTest.cpp
    tests/TransactionLedgerGTest.cpp
    tests/UserRegistryGTest.cpp
    tests/AccountRegistryGTest.cpp
)

# Main executable
add_executable(banking_system ${MAIN_SOURCES})
target_include_directories(banking_system PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Test executable
add_executable(banking_tests ${TEST_SOURCES} 
    src/entities/User.cpp
    src/entities/Account.cpp
    src/entities/Transaction.cpp
    src/entities/TransactionLedger.cpp
    src/entities/UserRegistry.cpp
    src/entities/AccountRegistry.cpp
    src/roles/AccountHolder.cpp
)

target_include_directories(banking_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(banking_tests 
    GTest::gtest 
    GTest::gmock 
    GTest::gtest_main
)

enable_testing()
add_test(NAME BankingSystemTests COMMAND banking_tests)

target_compile_options(banking_system PRIVATE )
target_compile_options(banking_tests PRIVATE )