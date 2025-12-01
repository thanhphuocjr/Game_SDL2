#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int GIFT_WIDTH = 50;
const int GIFT_HEIGHT = 50;
const int FAIL_WIDTH = 50;
const int FAIL_HEIGHT = 50;
const int DEADLINE_WIDTH = 100;
const int DEADLINE_HEIGHT = 50;

int score = 0;
int highscore = 0;
int level = 1;
bool youlose = false;

#include "T01_checkCollision.cpp"
#include "T02_checkLogicCharacter.cpp"
#include "T03_checkLogicGameObjects.cpp"
#include "T04_checkLogicCollisionWithObjects.cpp"
#include "T05_checkLogicScoreAndLevel.cpp"

void run_all_tests() {
    srand(time(0));
    
    std::cout << "\n";
    std::cout << "================================================================\n";
    std::cout << "           RUNNING COMPLETE UNIT TEST SUITE\n";
    std::cout << "================================================================\n\n";

    std::cout << "Test Suite 1: LOGIC VA CHAM (Collision Detection)\n";
    std::cout << "------------------------------------------------\n";
    test_collision_no_overlap();
    test_collision_complete_overlap();
    test_collision_partial_overlap();
    test_collision_edge_touching();
    test_collision_above();
    test_collision_below();
    test_collision_left();
    test_collision_right();
    test_collision_identical_rects();
    test_collision_corner_overlap();
    std::cout << "\n";
    

    std::cout << "Test Suite 2: LOGIC NHAN VAT (Character Logic)\n";
    std::cout << "------------------------------------------------\n";
    test_character_move_left();
    test_character_move_right();
    test_character_jump();
    test_character_gravity();
    test_character_ground_collision();
    test_character_reset();
    std::cout << "\n";
    

    std::cout << "Test Suite 3: LOGIC GAME OBJECTS\n";
    std::cout << "------------------------------------------------\n";
    test_add_gift();
    test_update_gift();
    test_gift_off_screen();
    test_add_failscore();
    test_update_failscore();
    test_failscore_off_screen();
    test_add_deadline();
    test_update_deadline();
    test_deadline_off_screen();
    std::cout << "\n";
    
    std::cout << "Test Suite 4: LOGIC COLLISION VOI VAT\n";
    std::cout << "------------------------------------------------\n";
    test_gift_collision_score();
    test_gift_no_collision();
    test_failscore_collision_gameover();
    test_failscore_no_collision();
    test_deadline_jump_over();
    test_deadline_collision_fail();
    test_deadline_passed();
    std::cout << "\n";
    
    std::cout << "Test Suite 5: LOGIC DIEM VA LEVEL\n";
    std::cout << "------------------------------------------------\n";
    test_change_level_7();
    test_change_level_14();
    test_change_level_31();
    test_level_stays_1();
    test_save_high_score();
    test_load_high_score();
    test_save_load_cycle();
    std::cout << "\n";
    
    std::cout << "================================================================\n";
    std::cout << "           ALL 35 TESTS PASSED SUCCESSFULLY! ✓\n";
    std::cout << "================================================================\n\n";
}

int main() {
    try {
        run_all_tests();
        return 0;
    } catch (const std::exception& e) {
        std::cout << "\n✗ Test failed: " << e.what() << "\n";
        return 1;
    }
}