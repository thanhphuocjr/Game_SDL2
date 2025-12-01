
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <SDL2/SDL.h>

class Gift {
public:
    int x_position, y_position, y_Vel;
    Gift(int x, int y, int vel) : x_position(x), y_position(y), y_Vel(vel) {}
};

class FailScore {
public:
    int x_position, y_position, y_Vel;
    FailScore(int x, int y, int vel) : x_position(x), y_position(y), y_Vel(vel) {}
};

class Deadline {
public:
    int x_position, y_position, x_Vel;
    Deadline(int x, int y, int vel) : x_position(x), y_position(y), x_Vel(vel) {}
};

std::vector<Gift> gifts;
std::vector<FailScore> Fscores;
std::vector<Deadline> deadlines;

void AddGift() {
    int x = rand() % (SCREEN_WIDTH - GIFT_WIDTH);
    int y = 0;
    int vel = rand() % 5 + 3;
    Gift newGift(x, y, vel);
    gifts.push_back(newGift);
}

void UpdateGift() {
    for(int i = 0; i < (int)gifts.size(); i++) {
        gifts[i].y_position += gifts[i].y_Vel;
        if(gifts[i].y_position > SCREEN_HEIGHT) {
            gifts.erase(gifts.begin() + i);
            i--;
        }
    }
}

void AddFailScore() {
    int x = rand() % (SCREEN_WIDTH - FAIL_WIDTH);
    int y = 0;
    int vel = rand() % 5 + 5;
    FailScore newFail(x, y, vel);
    Fscores.push_back(newFail);
}

void UpdateFailScore() {
    for(int i = 0; i < (int)Fscores.size(); i++) {
        Fscores[i].y_position += Fscores[i].y_Vel;
        if(Fscores[i].y_position > SCREEN_HEIGHT) {
            Fscores.erase(Fscores.begin() + i);
            i--;
        }
    }
}

void AddDeadline() {
    int x = SCREEN_WIDTH - DEADLINE_WIDTH;
    int y = SCREEN_HEIGHT - DEADLINE_HEIGHT;
    int vel = 2;
    Deadline newDeadline(x, y, vel);
    deadlines.push_back(newDeadline);
}

void UpdateDeadline() {
    for(int i = 0; i < (int)deadlines.size(); i++) {
        deadlines[i].x_position -= deadlines[i].x_Vel;
        if(deadlines[i].x_position < 0) {
            deadlines.erase(deadlines.begin() + i);
            i--;
        }
    }
}

void test_add_gift() {
    gifts.clear();
    AddGift();
    assert(gifts.size() == 1);
    assert(gifts[0].y_position == 0);
    std::cout << "  ✓ Test 3.1: AddGift()\n";
}

void test_update_gift() {
    gifts.clear();
    gifts.push_back(Gift(100, 100, 5));
    UpdateGift();
    assert(gifts[0].y_position == 105);
    std::cout << "  ✓ Test 3.2: UpdateGift()\n";
}

void test_gift_off_screen() {
    gifts.clear();
    gifts.push_back(Gift(100, SCREEN_HEIGHT + 10, 5));
    UpdateGift();
    assert(gifts.size() == 0);
    std::cout << "  ✓ Test 3.3: UpdateGift() - off screen\n";
}

void test_add_failscore() {
    Fscores.clear();
    AddFailScore();
    assert(Fscores.size() == 1);
    assert(Fscores[0].y_position == 0);
    std::cout << "  ✓ Test 3.4: AddFailScore()\n";
}

void test_update_failscore() {
    Fscores.clear();
    Fscores.push_back(FailScore(200, 150, 7));
    UpdateFailScore();
    assert(Fscores[0].y_position == 157);
    std::cout << "  ✓ Test 3.5: UpdateFailScore()\n";
}

void test_failscore_off_screen() {
    Fscores.clear();
    Fscores.push_back(FailScore(200, SCREEN_HEIGHT + 20, 7));
    UpdateFailScore();
    assert(Fscores.size() == 0);
    std::cout << "  ✓ Test 3.6: UpdateFailScore() - off screen\n";
}

void test_add_deadline() {
    deadlines.clear();
    AddDeadline();
    assert(deadlines.size() == 1);
    assert(deadlines[0].x_position == SCREEN_WIDTH - DEADLINE_WIDTH);
    std::cout << "  ✓ Test 3.7: AddDeadline()\n";
}

void test_update_deadline() {
    deadlines.clear();
    deadlines.push_back(Deadline(500, SCREEN_HEIGHT - DEADLINE_HEIGHT, 4));
    UpdateDeadline();
    assert(deadlines[0].x_position == 496);
    std::cout << "  ✓ Test 3.8: UpdateDeadline()\n";
}

void test_deadline_off_screen() {
    deadlines.clear();
    deadlines.push_back(Deadline(-10, SCREEN_HEIGHT - DEADLINE_HEIGHT, 2));
    UpdateDeadline();
    assert(deadlines.size() == 0);
    std::cout << "  ✓ Test 3.9: UpdateDeadline() - off screen\n";
}
void test_gift_zero_velocity() {
    gifts.clear();
    gifts.push_back(Gift(100, 100, 0));
    UpdateGift();
    assert(gifts[0].y_position == 100); 
    std::cout << "  ✓ Test 3.10: Gift with zero velocity\n";
}

void test_gift_negative_velocity() {
    gifts.clear();
    gifts.push_back(Gift(100, 100, -5));
    UpdateGift();
    assert(gifts[0].y_position == 95);
    std::cout << "  ✓ Test 3.11: Gift with negative velocity\n";
}

void test_failscore_at_screen_bottom_boundary() {
    Fscores.clear();
    Fscores.push_back(FailScore(100, SCREEN_HEIGHT, 5));
    UpdateFailScore();
    assert(Fscores.size() == 0);
    std::cout << "  ✓ Test 3.12: FailScore at bottom boundary\n";
}

void test_failscore_just_before_boundary() {
    Fscores.clear();
    Fscores.push_back(FailScore(100, SCREEN_HEIGHT - 6, 5)); 
    UpdateFailScore();
    assert(Fscores.size() == 1); 
    assert(Fscores[0].y_position == SCREEN_HEIGHT - 1);
    std::cout << "  ✓ Test 3.13: FailScore just before boundary\n";
}

void test_deadline_at_left_boundary() {
    deadlines.clear();
    deadlines.push_back(Deadline(0, SCREEN_HEIGHT - DEADLINE_HEIGHT, 2));
    UpdateDeadline();
    assert(deadlines.size() == 0);
    std::cout << "  ✓ Test 3.14: Deadline at left boundary\n";
}

void test_deadline_just_before_left_boundary() {
    deadlines.clear();
    deadlines.push_back(Deadline(1, SCREEN_HEIGHT - DEADLINE_HEIGHT, 1));
    UpdateDeadline();
    assert(deadlines.size() == 1); 
    assert(deadlines[0].x_position == 0);
    std::cout << "  ✓ Test 3.15: Deadline just before left boundary\n";
}

void test_multiple_gifts_mixed() {
    gifts.clear();
    gifts.push_back(Gift(100, 100, 5));
    gifts.push_back(Gift(200, SCREEN_HEIGHT + 10, 5));
    gifts.push_back(Gift(300, 150, 3));
    UpdateGift();
    assert(gifts.size() == 2);
    std::cout << "  ✓ Test 3.16: Multiple gifts with mixed states\n";
}

void test_high_velocity_gift() {
    gifts.clear();
    gifts.push_back(Gift(100, SCREEN_HEIGHT - 100, 500));
    UpdateGift();
    assert(gifts.size() == 0); 
    std::cout << "  ✓ Test 3.17: Gift with high velocity\n";
}
