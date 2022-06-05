//
// Created by leonard on 26.04.2022.
//

#include "cart.h"

void Cart::clearCart() {
    while (!list.empty()) {
        list.pop_back();
    }
}