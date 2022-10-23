cmake_minimum_required(VERSION 3.23)
project(BankAccounts)

set(CMAKE_CXX_STANDARD 23)

add_executable(BankAccounts main.cpp
        account/Account.h account/Account.cpp
        bank/Bank.h bank/Bank.cpp
        operation/Operation.h operation/Operation.cpp
        operator/BankOperator.h operator/BankOperator.cpp
        anaf/AnafAgent.cpp anaf/AnafAgent.h)
