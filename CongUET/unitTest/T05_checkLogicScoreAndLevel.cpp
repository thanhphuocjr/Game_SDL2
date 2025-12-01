
#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>

void Change_level() {
    if (score >= 7 && score < 14) {
        level = 2;
        for(int i = 0; i < (int)Fscores.size(); i++) {
            Fscores[i].y_Vel = 7 + (rand() % 5);
        }
        for(int i = 0; i < (int)deadlines.size(); i++) {
            deadlines[i].x_Vel = 4;
        }
    } else if(score >= 14 && score < 21) {
        level = 2;
        for(int i = 0; i < (int)Fscores.size(); i++) {
            Fscores[i].y_Vel = 9 + (rand() % 5);
        }
        for(int i = 0; i < (int)deadlines.size(); i++) {
            deadlines[i].x_Vel = 8;
        }
    } else if (score >= 21 && score <= 30) {
        level = 2;
        for(int i = 0; i < (int)Fscores.size(); i++) {
            Fscores[i].y_Vel = 12 + (rand() % 5);
        }
        for(int i = 0; i < (int)deadlines.size(); i++) {
            deadlines[i].x_Vel = 10;
        }
    } else if(score > 30) {
        level = 3;
        for(int i = 0; i < (int)Fscores.size(); i++) {
            Fscores[i].y_Vel = 20 + (rand() % 5);
        }
        for(int i = 0; i < (int)deadlines.size(); i++) {
            deadlines[i].x_Vel = 15;
        }
    }
}

void Save_High_Score(std::string path) {
    std::ofstream file(path);
    if (!file) {
        std::cerr << "Unable to create/open file for writing\n";
        return;
    }
    file << highscore;
    file.close();
}

void Load_High_Score(std::string path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Unable to open file for reading\n";
        return;
    }
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        ss >> highscore;
    }
    file.close();
}


void test_change_level_7() {
    reset_game_state();
    score = 7;
    Change_level();
    assert(level == 2);
    std::cout << "  ✓ Test 5.1: Change_level() - score 7\n";
}

void test_change_level_14() {
    reset_game_state();
    score = 14;
    Change_level();
    assert(level == 2);
    std::cout << "  ✓ Test 5.2: Change_level() - score 14\n";
}

void test_change_level_31() {
    reset_game_state();
    score = 31;
    Change_level();
    assert(level == 3);
    std::cout << "  ✓ Test 5.3: Change_level() - score 31\n";
}

void test_level_stays_1() {
    reset_game_state();
    score = 5;
    Change_level();
    assert(level == 1);
    std::cout << "  ✓ Test 5.4: Change_level() - stays level 1\n";
}

void test_save_high_score() {
    std::string test_file = "test_score.txt";
    highscore = 100;
    Save_High_Score(test_file);
    
    std::ifstream file(test_file);
    int saved_value = -1;
    file >> saved_value;
    file.close();
    
    assert(saved_value == 100);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.5: Save_High_Score()\n";
}

void test_load_high_score() {
    std::string test_file = "test_score_load.txt";
    std::ofstream file(test_file);
    file << 250;
    file.close();
    
    highscore = 0;
    Load_High_Score(test_file);
    
    assert(highscore == 250);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.6: Load_High_Score()\n";
}

void test_save_load_cycle() {
    std::string test_file = "test_cycle.txt";
    
    highscore = 500;
    Save_High_Score(test_file);
    
    highscore = 0;
    Load_High_Score(test_file);
    
    assert(highscore == 500);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.7: Save & Load cycle\n";
}



void test_change_level_boundary_6() {

    reset_game_state();
    score = 6;
    Change_level();
    assert(level == 1);
    std::cout << "  ✓ Test 5.8: Change_level() - score 6 (boundary)\n";
}

void test_change_level_boundary_13() {

    reset_game_state();
    score = 13;
    Change_level();
    assert(level == 2);
    std::cout << "  ✓ Test 5.9: Change_level() - score 13 (boundary)\n";
}

void test_change_level_boundary_21() {
    reset_game_state();
    score = 21;
    Change_level();
    assert(level == 2);
    std::cout << "  ✓ Test 5.10: Change_level() - score 21 (boundary)\n";
}

void test_change_level_boundary_30() {
    reset_game_state();
    score = 30;
    Change_level();
    assert(level == 2); 
    std::cout << "  ✓ Test 5.11: Change_level() - score 30 (boundary)\n";
}

void test_change_level_score_zero() {
    reset_game_state();
    score = 0;
    Change_level();
    assert(level == 1);
    std::cout << "  ✓ Test 5.12: Change_level() - score 0 (minimum)\n";
}

void test_change_level_score_high() {
    reset_game_state();
    score = 100;
    Change_level();
    assert(level == 3);
    std::cout << "  ✓ Test 5.13: Change_level() - score 100 (high)\n";
}

void test_save_high_score_zero() {
    std::string test_file = "test_zero_score.txt";
    highscore = 0;
    Save_High_Score(test_file);
    
    std::ifstream file(test_file);
    int saved_value = -1;
    file >> saved_value;
    file.close();
    
    assert(saved_value == 0);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.14: Save_High_Score() - zero value\n";
}

void test_save_high_score_large_value() {
    std::string test_file = "test_large_score.txt";
    highscore = 999999;
    Save_High_Score(test_file);
    
    std::ifstream file(test_file);
    int saved_value = -1;
    file >> saved_value;
    file.close();
    
    assert(saved_value == 999999);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.15: Save_High_Score() - large value\n";
}

void test_load_high_score_empty_file() {
    std::string test_file = "test_empty_score.txt";
    std::ofstream file(test_file);
    file << ""; 
    file.close();
    highscore = 100;
    Load_High_Score(test_file);
    assert(highscore == 100);
    std::remove(test_file.c_str());
    std::cout << "  ✓ Test 5.16: Load_High_Score() - empty file\n";
}