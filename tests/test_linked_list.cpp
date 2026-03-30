#define CATCH_CONFIG_MAIN
#include <vector>
#include <algorithm>
#include "catch2/catch.hpp"

#include "list/singly_linked.hpp"
#include "list/circularly_linked.hpp"
#include "list/doubly_linked.hpp"

using namespace dsac::list;

TEST_CASE("Check concatenate in SinglyLinkedList that it works correctly with an empty list and a non-empty list") {
    SinglyLinkedList<int> A;
    SinglyLinkedList<int> B;

    B.push_back(5);  // Give list B values and leave list A empty
    B.push_back(10);
    B.push_back(15);

    A.concatenate(B); // Concatenate A and B in list A

    REQUIRE(A.front() == 5);
    REQUIRE(A.back() == 15);
    REQUIRE(A.size() == 3);
    REQUIRE(B.empty()); // List B should be empty

}

TEST_CASE("Check concatenate in SinglyLinkedList that it works correctly with two non empty lists") {
    SinglyLinkedList<int> A, B;

    // Add values to both lists
    A.push_back(200);
    A.push_back(400);

    B.push_back(5);  
    B.push_back(10);
    B.push_back(15);

    B.concatenate(A); // Concatenate A and B in list B

    REQUIRE(B.front() == 5);
    REQUIRE(B.back() == 400);
    REQUIRE(B.size() == 5);
    REQUIRE(A.empty()); // List A should be empty
}

TEST_CASE("Check reverse in SinglyLinkedList that it works correctly") {
    SinglyLinkedList<int> C;

    C.push_back(11);
    C.push_back(12);
    C.push_back(13);

    C.reverse();

    REQUIRE(C.front() == 13);
    REQUIRE(C.back() == 11);
    REQUIRE(C.size() == 3);
}

TEST_CASE("Check splitEven in CircularlyLinkedList that it works correctly") {
    CircularlyLinkedList<int> D, A, B;

    for (int i{1}; i <= 8; i++) {
        D.push_back(i);
    }
    D.splitEven(A, B); // split list D into two even lists in A and B

    REQUIRE(D.empty()); // list D should empty
    REQUIRE(A.front() == 1);
    REQUIRE(A.back() == 4);
    REQUIRE(A.size() == 4);

    REQUIRE(B.front() == 5);
    REQUIRE(B.back() == 8);
    REQUIRE(B.size() == 4);

}

TEST_CASE("Check splitEven in CircularlyLinkedList in small cases") {
    CircularlyLinkedList<int> E, A, B;

    E.push_back(2);
    E.push_back(4);
    
    E.splitEven(A, B); // split list E into two even lists in A and B

    REQUIRE(E.empty()); // list E should empty

    REQUIRE(A.front() == 2);
    REQUIRE(A.size() == 1);

    REQUIRE(B.front() == 4);
    REQUIRE(B.size() == 1);
}

TEST_CASE("Check concatenate in DoublyLinkedList that it works correctly with an empty list and a non-empty list") {
    DoublyLinkedList<int> A, B;

    B.push_back(5);  // Give list B values and leave list A empty
    B.push_back(10);
    B.push_back(15);

    A.concatenate(B); // Concatenate A and B in list A

    REQUIRE(A.front() == 5);
    REQUIRE(A.back() == 15);
    REQUIRE(A.size() == 3);
    REQUIRE(B.empty()); // List B should be empty

    A.pop_front();  // Checking edge case for after concatenate operation
    REQUIRE(A.front() == 10);

    A.pop_back();
    REQUIRE(A.back() == 10);

}

TEST_CASE("Check concatenate in DoublyLinkedList that it works correctly with two non empty lists") {
    DoublyLinkedList<int> A, B;

    // Add values to both lists
    A.push_back(200);
    A.push_back(400);

    B.push_back(5);  
    B.push_back(10);
    B.push_back(15);

    B.concatenate(A); // Concatenate A and B in list B

    REQUIRE(B.front() == 5);
    REQUIRE(B.back() == 400);
    REQUIRE(B.size() == 5);
    REQUIRE(A.empty()); // List A should be empty
}