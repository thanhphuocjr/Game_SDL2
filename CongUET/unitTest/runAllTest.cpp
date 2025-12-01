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


int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;


#include "test_failure_cases.cpp"

void run_all_tests() {
    srand(time(0));
    
    std::cout << "\n";
    std::cout << "================================================================\n";
    std::cout << "           RUNNING COMPLETE UNIT TEST SUITE\n";
    std::cout << "================================================================\n\n";

    std::cout << "Test Suite 1: LOGIC VA CHAM (Collision Detection)\n";
    std::cout << "------------------------------------------------\n";
    try { test_collision_no_overlap(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_complete_overlap(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_partial_overlap(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_edge_touching(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_above(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_below(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_left(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_right(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_identical_rects(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_corner_overlap(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_zero_width(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_zero_height(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_negative_position(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_one_pixel_overlap(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_exact_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_large_rects(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    std::cout << "\n";
    

    std::cout << "Test Suite 2: LOGIC NHAN VAT (Character Logic)\n";
    std::cout << "------------------------------------------------\n";
    try { test_character_move_left(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_move_right(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_jump(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_gravity(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_ground_collision(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_reset(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_velocity_negative(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_velocity_zero(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_jump_false_state(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_at_screen_boundary_left(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_at_screen_boundary_right(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_gravity_accumulation(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_character_position_at_ground(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    std::cout << "\n";
    

    std::cout << "Test Suite 3: LOGIC GAME OBJECTS\n";
    std::cout << "------------------------------------------------\n";
    try { test_add_gift(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_update_gift(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_gift_off_screen(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_add_failscore(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_update_failscore(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_off_screen(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_add_deadline(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_update_deadline(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_off_screen(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_gift_zero_velocity(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_gift_negative_velocity(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_at_screen_bottom_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_just_before_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_at_left_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_just_before_left_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_multiple_gifts_mixed(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_high_velocity_gift(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    std::cout << "\n";
    
    std::cout << "Test Suite 4: LOGIC COLLISION VOI VAT\n";
    std::cout << "------------------------------------------------\n";
    try { test_gift_collision_score(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_gift_no_collision(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_collision_gameover(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_no_collision(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_jump_over(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_collision_fail(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_passed(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_collision_character_at_screen_edge(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_empty_gift_list(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_multiple_gifts_collision(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_zero_velocity(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_deadline_horizontal_alignment(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_failscore_boundary_velocity(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    std::cout << "\n";
    
    std::cout << "Test Suite 5: LOGIC DIEM VA LEVEL\n";
    std::cout << "------------------------------------------------\n";
    try { test_change_level_7(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_14(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_31(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_level_stays_1(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_save_high_score(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_load_high_score(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_save_load_cycle(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_boundary_6(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_boundary_13(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_boundary_21(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_boundary_30(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_score_zero(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_change_level_score_high(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_save_high_score_zero(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_save_high_score_large_value(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    try { test_load_high_score_empty_file(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; }
    std::cout << "\n";
    
    std::cout << "Test Suite 6: FAILURE TEST CASES (Edge Cases & Potential Bugs)\n";
    std::cout << "-------------------------------------------------------------\n";
    try { test_collision_off_by_one_error(); total_tests++; passed_tests++; std::cout << "✓ Test F1: Collision off-by-one diagonal - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F1: Collision off-by-one diagonal - FAILED\n"; }
    try { test_character_velocity_boundary_crossing(); total_tests++; passed_tests++; std::cout << "✓ Test F2: Character huge velocity at boundary - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F2: Character huge velocity at boundary - FAILED\n"; }
    try { test_character_double_jump_bug(); total_tests++; passed_tests++; std::cout << "✓ Test F3: Character double jump vulnerability - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F3: Character double jump vulnerability - FAILED\n"; }
    try { test_gift_negative_screen_position(); total_tests++; passed_tests++; std::cout << "✓ Test F4: Gift negative position - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F4: Gift negative position - FAILED\n"; }
    try { test_failscore_extreme_velocity(); total_tests++; passed_tests++; std::cout << "✓ Test F5: FailScore extreme velocity - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F5: FailScore extreme velocity - FAILED\n"; }
    try { test_deadline_right_edge_precision(); total_tests++; passed_tests++; std::cout << "✓ Test F6: Deadline right edge precision - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F6: Deadline right edge precision - FAILED\n"; }
    try { test_collision_character_partially_off_screen(); total_tests++; passed_tests++; std::cout << "✓ Test F7: Collision at screen edge - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F7: Collision at screen edge - FAILED\n"; }
    try { test_score_level_transition_multiple_times(); total_tests++; passed_tests++; std::cout << "✓ Test F8: Level transition rapid changes - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F8: Level transition rapid changes - FAILED\n"; }
    try { test_file_io_concurrent_access(); total_tests++; passed_tests++; std::cout << "✓ Test F9: File I/O concurrent access - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F9: File I/O concurrent access - FAILED\n"; }
    try { test_collision_with_very_small_rects(); total_tests++; passed_tests++; std::cout << "✓ Test F10: 1x1 pixel rect collision - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F10: 1x1 pixel rect collision - FAILED\n"; }
    try { test_character_velocity_overflow(); total_tests++; passed_tests++; std::cout << "✓ Test F11: Character velocity overflow - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F11: Character velocity overflow - FAILED\n"; }
    try { test_multiple_gifts_same_position(); total_tests++; passed_tests++; std::cout << "✓ Test F12: Multiple gifts same position - PASSED\n"; } catch(...) { total_tests++; failed_tests++; std::cout << "✗ Test F12: Multiple gifts same position - FAILED\n"; }
    std::cout << "\n";
    
    std::cout << "Test Suite 7: GUARANTEED FAILURE TEST CASES\n";
    std::cout << "-------------------------------------------\n";
    try { test_guaranteed_fail_collision_diagonal_pixels(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; std::cout << "FAILED\n"; }
    try { test_guaranteed_fail_character_jump_down(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; std::cout << "FAILED\n"; }
    try { test_guaranteed_fail_score_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; std::cout << "FAILED\n"; }
    try { test_guaranteed_fail_gift_screen_boundary(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; std::cout << "FAILED\n"; }
    try { test_guaranteed_fail_collision_score_increment(); total_tests++; passed_tests++; } catch(...) { total_tests++; failed_tests++; std::cout << "FAILED\n"; }
    std::cout << "\n";
    

    std::cout << "TEST RESULTS SUMMARY\n";
   
    std::cout << "Total Tests:     " << total_tests << "\n";
    std::cout << "Passed Tests:    " << passed_tests << "\n";
    std::cout << "Failed Tests:    " << failed_tests << "\n";
    
    double pass_rate = (total_tests > 0) ? (static_cast<double>(passed_tests) / total_tests * 100.0) : 0;
    double fail_rate = (total_tests > 0) ? (static_cast<double>(failed_tests) / total_tests * 100.0) : 0;
    std::cout << "----------------";
    std::cout << "\nPass Rate: " << pass_rate << "%\n";
    std::cout << "Fail Rate: " << fail_rate << "%\n";
    std::cout << "----------------\n";
    
}

int main() {
    run_all_tests();
    return 0;
}