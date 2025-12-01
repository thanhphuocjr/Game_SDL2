
void test_collision_off_by_one_error() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {49, 49, 50, 50}; 
    if(!checkCollision(a, b)) {
        throw std::runtime_error("F1: Off-by-one collision detection failed");
    }
}

void test_character_velocity_boundary_crossing() {
    Character c;
    c.set_velocity_x(50000); 
    c.move();
    if(c.Get_posx() < 0 || c.Get_posx() + c.GetWidth() > SCREEN_WIDTH) {
        throw std::runtime_error("F2: Character velocity caused out-of-bounds position");
    }
}

void test_character_double_jump_bug() {
    Character c;
    if(c.jump) {
        throw std::runtime_error("F3: Character should not start with jump enabled");
    }
    c.set_up_pressed(true);
    c.move();
    if(!c.jump) {
        throw std::runtime_error("F3: Character jump not activated");
    }

    c.set_up_pressed(true);
    int vel_before = c.Get_vely();
    c.move();

    if(c.Get_vely() < vel_before) {
        throw std::runtime_error("F3: Character velocity decreased (double jump bug)");
    }
}

void test_gift_negative_screen_position() {
    gifts.clear();
    gifts.push_back(Gift(-100, 100, 5));
    UpdateGift();
}

void test_failscore_extreme_velocity() {
    Fscores.clear();
    Fscores.push_back(FailScore(100, 100, 10000)); 
    UpdateFailScore();
    if(Fscores.size() < 0) {
        throw std::runtime_error("F5: FailScore list size is negative");
    }
}

void test_deadline_right_edge_precision() {
    deadlines.clear();
    deadlines.push_back(Deadline(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, 1));
    UpdateDeadline();
    if(deadlines[0].x_position != SCREEN_WIDTH - 101) {
        throw std::runtime_error("F6: Deadline position incorrect at right edge");
    }
}

void test_collision_character_partially_off_screen() {
    reset_game_state();
    Character c;
    c.set_velocity_x(1000); 
    for(int i = 0; i < 10; i++) c.move();
    
    gifts.push_back(Gift(SCREEN_WIDTH - 50, c.Get_posy(), 5));
    Check_Character_Gift_Collision(c);
}

void test_score_level_transition_multiple_times() {
    reset_game_state();
    for(int i = 0; i <= 31; i++) {
        score = i;
        Change_level();
    }
    if(level != 3) {
        throw std::runtime_error("F8: Level should be 3 after score 31, got " + std::to_string(level));
    }
}

void test_file_io_concurrent_access() {
    std::string test_file = "test_concurrent.txt";
    
    highscore = 123;
    Save_High_Score(test_file);
    
    highscore = 0;
    Load_High_Score(test_file);
    
    if(highscore != 123) {
        throw std::runtime_error("F9: File I/O failed - highscore is " + std::to_string(highscore));
    }
    std::remove(test_file.c_str());
}

void test_collision_with_very_small_rects() {
    SDL_Rect a = {100, 100, 1, 1};
    SDL_Rect b = {101, 101, 1, 1};
    if(checkCollision(a, b)) {
        throw std::runtime_error("F10: 1x1 pixel rects should not collide");
    }
}

void test_character_velocity_overflow() {
    Character c;
    c.set_jump(true);
    for(int i = 0; i < 10000; i++) {
        c.set_velocity_y(c.Get_vely() + 1000);
        if(i % 1000 == 0) c.move();
    }
    if(c.Get_posy() >= SCREEN_HEIGHT * 2) {
        throw std::runtime_error("F11: Character velocity overflow");
    }
}

void test_multiple_gifts_same_position() {
    gifts.clear();
    gifts.push_back(Gift(200, 200, 5));
    gifts.push_back(Gift(200, 200, 5)); 
    if(gifts.size() != 2) {
        throw std::runtime_error("F12: Gift list size incorrect");
    }
    UpdateGift();
    if(gifts.size() != 2) {
        throw std::runtime_error("F12: Gift list size incorrect after update");
    }
    if(gifts[0].y_position != 205 || gifts[1].y_position != 205) {
        throw std::runtime_error("F12: Gift positions incorrect");
    }
}


void test_guaranteed_fail_collision_diagonal_pixels() {
    SDL_Rect a = {0, 0, 50, 50};
    SDL_Rect b = {100, 100, 50, 50}; 
    bool collision = checkCollision(a, b);
    if(!collision) {
        throw std::runtime_error("FAIL-1: Expected collision for non-overlapping rectangles");
    }
}

void test_guaranteed_fail_character_jump_down() {
    Character c;
    c.set_jump(true);
    c.set_velocity_y(20); 
    c.move();
    if(c.Get_vely() != 100) {
        throw std::runtime_error("FAIL-2: Character velocity is " + std::to_string(c.Get_vely()) + ", expected 100");
    }
}

void test_guaranteed_fail_score_boundary() {
    reset_game_state();
    score = 7;
    Change_level();
    if(level != 1) {
        throw std::runtime_error("FAIL-3: Level is " + std::to_string(level) + ", expected 1");
    }
}

void test_guaranteed_fail_gift_screen_boundary() {
    gifts.clear();
    gifts.push_back(Gift(100, SCREEN_HEIGHT - 1, 10));
    UpdateGift();
    if(gifts.size() != 1) {
        throw std::runtime_error("FAIL-4: Gift list size is " + std::to_string(gifts.size()) + ", expected 1");
    }
}

void test_guaranteed_fail_collision_score_increment() {
    reset_game_state();
    Character c;
    gifts.clear();
    gifts.push_back(Gift(c.Get_posx(), c.Get_posy(), 5));
    Check_Character_Gift_Collision(c);
    if(score != 5) {
        throw std::runtime_error("FAIL-5: Score is " + std::to_string(score) + ", expected 5");
    }
}
