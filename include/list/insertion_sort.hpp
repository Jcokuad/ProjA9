#pragma once

#include <iostream>

namespace dsac::list {

template <typename List>
void insertion_sort(List& data) {  //linked list insertion sort
    if (data.size() > 1) {   //else no need to sort 
        auto boundary{--data.end()};//last element 
        while (boundary != data.begin()) { 
            auto newest{boundary}; 
            --newest;// before boundary 
            auto walk{boundary}; //look entry >= newest (or end) 
            while (walk != data.end() && *walk < *newest) 
                ++walk; 
            if (walk == boundary) { // newest is correct 
                --boundary; // include in boundary 
            } else { //re-insert newest element before walk 
                data.insert(walk, *newest); 
                data.erase(newest); // remove from original position 
            } 
        } 
    }
}

}  // namespace dsac::list
