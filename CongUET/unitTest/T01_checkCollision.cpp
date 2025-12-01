
#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;
    
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;
    
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;
    
    return true;
}

void test_collision_no_overlap() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {100, 100, 50, 50};
    assert(!checkCollision(a, b));
    std::cout << "✓ Test 1: No overlap - PASSED\n";
}

void test_collision_complete_overlap() {
    SDL_Rect a = {0, 0, 100, 100};
    SDL_Rect b = {25, 25, 50, 50};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 2: Complete overlap - PASSED\n";
}

void test_collision_partial_overlap() {
    SDL_Rect a = {0, 0, 60, 60};
    SDL_Rect b = {40, 40, 60, 60};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 3: Partial overlap - PASSED\n";
}

void test_collision_edge_touching() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {50, 0, 50, 50};
    assert(!checkCollision(a, b)); 
    std::cout << "✓ Test 4: Edge touching - PASSED\n";
}

void test_collision_above() {
    SDL_Rect a = {0, 100, 50, 50};
    SDL_Rect b = {0, 0, 50, 50};
    assert(!checkCollision(a, b));
    std::cout << "✓ Test 5: A above B - PASSED\n";
}

void test_collision_below() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {0, 100, 50, 50};
    assert(!checkCollision(a, b));
    std::cout << "✓ Test 6: A below B - PASSED\n";
}

void test_collision_left() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {100, 0, 50, 50};
    assert(!checkCollision(a, b));
    std::cout << "✓ Test 7: A left of B - PASSED\n";
}

void test_collision_right() {
    SDL_Rect a = {100, 0, 50, 50};
    SDL_Rect b = {0, 0, 50, 50};
    assert(!checkCollision(a, b));
    std::cout << "✓ Test 8: A right of B - PASSED\n";
}

void test_collision_identical_rects() {
    SDL_Rect a = {50, 50, 100, 100};
    SDL_Rect b = {50, 50, 100, 100};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 9: Identical rectangles - PASSED\n";
}

void test_collision_corner_overlap() {
    SDL_Rect a = {0, 0, 60, 60};
    SDL_Rect b = {50, 50, 60, 60};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 10: Corner overlap - PASSED\n";
}





void test_collision_zero_width() {
    SDL_Rect a = {0, 0, 0, 50};   
    SDL_Rect b = {0, 0, 50, 50};
    assert(!checkCollision(a, b)); 
    std::cout << "✓ Test 11: Zero width - PASSED\n";
}

void test_collision_zero_height() {
    SDL_Rect a = {0, 0, 50, 0};   
    SDL_Rect b = {0, 0, 50, 50};
    assert(!checkCollision(a, b)); 
    std::cout << "✓ Test 12: Zero height - PASSED\n";
}

void test_collision_negative_position() {
    SDL_Rect a = {-50, -50, 100, 100}; 
    SDL_Rect b = {0, 0, 50, 50};
    assert(checkCollision(a, b)); 
    std::cout << "✓ Test 13: Negative position - PASSED\n";
}

void test_collision_one_pixel_overlap() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {49, 49, 50, 50};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 14: One pixel overlap - PASSED\n";
}

void test_collision_exact_boundary() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {50, 50, 50, 50};
    assert(!checkCollision(a, b)); 
    std::cout << "✓ Test 15: Exact boundary touch - PASSED\n";
}

void test_collision_large_rects() {
    SDL_Rect a = {0, 0, 10000, 10000};  
    SDL_Rect b = {5000, 5000, 1000, 1000};
    assert(checkCollision(a, b));
    std::cout << "✓ Test 16: Large rectangles - PASSED\n";
}