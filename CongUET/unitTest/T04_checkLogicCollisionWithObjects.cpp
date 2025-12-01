
#include <cassert>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

void Check_Character_Gift_Collision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), 
                              character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)gifts.size(); i++) {
        SDL_Rect giftRect = {gifts[i].x_position, gifts[i].y_position, GIFT_WIDTH, GIFT_HEIGHT};
        if (checkCollision(characterRect, giftRect)) {
            gifts.erase(gifts.begin() + i);
            score++;
            i--;
        }
    }
}

void Check_Character_FailScore_Collision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), 
                              character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)Fscores.size(); i++) {
        SDL_Rect failRect = {Fscores[i].x_position, Fscores[i].y_position, FAIL_WIDTH, FAIL_HEIGHT};
        if (checkCollision(characterRect, failRect)) {
            youlose = true;
        }
    }
}

void CheckCharacter_DeadlineCollision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), 
                              character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)deadlines.size(); i++) {
        SDL_Rect deadlineRect = {deadlines[i].x_position, deadlines[i].y_position, 
                                 DEADLINE_WIDTH, DEADLINE_HEIGHT};
        if(checkCollision(characterRect, deadlineRect)) {
            if(character.Get_vely() > 0) {
                deadlines.erase(deadlines.begin() + i);
                score++;
                i--;
            } else {
                youlose = true;
            }
        } else if(characterRect.x > deadlineRect.x + deadlineRect.w) {
            deadlines.erase(deadlines.begin() + i);
            score++;
            i--;
        }
    }
}

void reset_game_state() {
    score = 0;
    level = 1;
    youlose = false;
    gifts.clear();
    Fscores.clear();
    deadlines.clear();
}

void test_gift_collision_score() {
    reset_game_state();
    Character c;
    gifts.push_back(Gift(c.Get_posx(), c.Get_posy(), 5));
    Check_Character_Gift_Collision(c);
    assert(score == 1);
    assert(gifts.size() == 0);
    std::cout << "  ✓ Test 4.1: Check_Character_Gift_Collision() - score++\n";
}

void test_gift_no_collision() {
    reset_game_state();
    Character c;
    gifts.push_back(Gift(500, 500, 5));
    Check_Character_Gift_Collision(c);
    assert(score == 0);
    assert(gifts.size() == 1);
    std::cout << "  ✓ Test 4.2: Check_Character_Gift_Collision() - no collision\n";
}

void test_failscore_collision_gameover() {
    reset_game_state();
    Character c;
    Fscores.push_back(FailScore(c.Get_posx(), c.Get_posy(), 5));
    Check_Character_FailScore_Collision(c);
    assert(youlose == true);
    std::cout << "  ✓ Test 4.3: Check_Character_FailScore_Collision() - game over\n";
}

void test_failscore_no_collision() {
    reset_game_state();
    Character c;
    Fscores.push_back(FailScore(500, 500, 5));
    Check_Character_FailScore_Collision(c);
    assert(youlose == false);
    std::cout << "  ✓ Test 4.4: Check_Character_FailScore_Collision() - no collision\n";
}

void test_deadline_jump_over() {
    reset_game_state();
    Character c;
    c.set_velocity_y(5); 
    deadlines.push_back(Deadline(c.Get_posx(), c.Get_posy(), 2));
    CheckCharacter_DeadlineCollision(c);
    assert(score == 1);
    assert(deadlines.size() == 0);
    std::cout << "  ✓ Test 4.5: CheckCharacter_DeadlineCollision() - jump over\n";
}

void test_deadline_collision_fail() {
    reset_game_state();
    Character c;
    c.set_velocity_y(-5); 
    deadlines.push_back(Deadline(c.Get_posx(), c.Get_posy(), 2));
    CheckCharacter_DeadlineCollision(c);
    assert(youlose == true);
    std::cout << "  ✓ Test 4.6: CheckCharacter_DeadlineCollision() - game over\n";
}

void test_deadline_passed() {
    reset_game_state();
    Character c;
    deadlines.push_back(Deadline(100, c.Get_posy(), 2)); 
    CheckCharacter_DeadlineCollision(c);
    assert(score == 1);
    std::cout << "  ✓ Test 4.7: CheckCharacter_DeadlineCollision() - passed\n";
}


void test_collision_character_at_screen_edge() {

    reset_game_state();
    Character c;
    c.set_velocity_x(1000); 
    c.move();
    gifts.push_back(Gift(c.Get_posx() - 10, c.Get_posy(), 5));
    Check_Character_Gift_Collision(c);
    assert(score == 1); 
    std::cout << "  ✓ Test 4.8: Character at screen edge collision\n";
}

void test_empty_gift_list() {
    reset_game_state();
    Character c;
    gifts.clear();
    Check_Character_Gift_Collision(c);
    assert(score == 0);
    assert(gifts.size() == 0);
    std::cout << "  ✓ Test 4.9: Collision with empty gift list\n";
}

void test_multiple_gifts_collision() {
    reset_game_state();
    Character c;
    gifts.clear();
    gifts.push_back(Gift(c.Get_posx(), c.Get_posy(), 5));
    gifts.push_back(Gift(c.Get_posx() + 10, c.Get_posy() + 10, 5));
    gifts.push_back(Gift(500, 500, 5));
    Check_Character_Gift_Collision(c);
    assert(score == 2); 
    assert(gifts.size() == 1); 
    std::cout << "  ✓ Test 4.10: Multiple gifts collision\n";
}

void test_deadline_zero_velocity() {
    reset_game_state();
    Character c;
    deadlines.push_back(Deadline(c.Get_posx(), c.Get_posy(), 0));
    deadlines[0].x_Vel = 0;
    CheckCharacter_DeadlineCollision(c);
    assert(youlose == true); 
    std::cout << "  ✓ Test 4.11: Deadline zero velocity collision\n";
}

void test_deadline_horizontal_alignment() {
    reset_game_state();
    Character c;
    deadlines.push_back(Deadline(c.Get_posx(), c.Get_posy(), 2));
    CheckCharacter_DeadlineCollision(c);
    assert(youlose == true);
    std::cout << "  ✓ Test 4.12: Deadline exact horizontal alignment\n";
}

void test_failscore_boundary_velocity() {
    reset_game_state();
    Character c;
    Fscores.push_back(FailScore(c.Get_posx() + 1, c.Get_posy() + 1, 5));
    Check_Character_FailScore_Collision(c);
    std::cout << "  ✓ Test 4.13: FailScore boundary proximity\n";
}