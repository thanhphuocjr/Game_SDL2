
#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>

class Character {
public:
    bool jump = false;
    bool up_pressed = false;
    bool isLeft = true;
    int Vmax_Character = 20;
    int Vjump = -17;
    
    Character() {
        jump = false;
        isLeft = true;
        real_x_position = SCREEN_WIDTH / 2;
        width_ = 55;
        height_ = 75;
        real_y_position = SCREEN_HEIGHT - height_;
        real_x_Vel = 0;
        real_y_Vel = 0;
    }
    
    void move() {
        if(up_pressed && !jump) {
            real_y_Vel = Vjump;
            jump = true;
        }
        if(jump) {
            real_y_Vel += 1; 
        }
        
        real_y_position += real_y_Vel;
        if(real_y_position >= SCREEN_HEIGHT - height_) {
            real_y_position = SCREEN_HEIGHT - height_;
            real_y_Vel = 0;
            jump = false;
        }
        
        real_x_position += real_x_Vel;
        if(real_x_position < 0 || (real_x_position + width_ > SCREEN_WIDTH)) {
            real_x_position -= real_x_Vel;
        }
    }
    
    void Solve_Event(SDL_Event &e) {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_LEFT:
                    isLeft = true;
                    real_x_Vel -= Vmax_Character;
                    break;
                case SDLK_RIGHT:
                    isLeft = false;
                    real_x_Vel += Vmax_Character;
                    break;
                case SDLK_UP:
                    if(!jump) jump = true;
                    up_pressed = true;
                    break;
            }
        } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch(e.key.keysym.sym) {
                case SDLK_LEFT:
                    real_x_Vel += Vmax_Character;
                    break;
                case SDLK_RIGHT:
                    real_x_Vel -= Vmax_Character;
                    break;
                case SDLK_UP:
                    up_pressed = false;
                    break;
            }
        }
    }
    
    void reset() {
        real_x_position = SCREEN_WIDTH / 2;
        real_y_position = SCREEN_HEIGHT - height_;
        real_x_Vel = 0;
        real_y_Vel = 0;
        jump = false;
        up_pressed = false;
    }
    
    int Get_posx() const { return real_x_position; }
    int Get_posy() const { return real_y_position; }
    int Get_velx() const { return real_x_Vel; }
    int Get_vely() const { return real_y_Vel; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    
    void set_velocity_x(int vel) { real_x_Vel = vel; }
    void set_velocity_y(int vel) { real_y_Vel = vel; }
    void set_jump(bool j) { jump = j; }
    void set_up_pressed(bool up) { up_pressed = up; }
    
private:
    int width_;
    int height_;
    int real_x_position;
    int real_y_position;
    int real_x_Vel;
    int real_y_Vel;
};

void test_character_move_left() {
    Character c;
    c.set_velocity_x(-20);
    int initial_x = c.Get_posx();
    c.move();
    assert(c.Get_posx() == initial_x - 20);
    std::cout << "  ✓ Test 2.1: Character::move() - left\n";
}

void test_character_move_right() {
    Character c;
    c.set_velocity_x(20);
    int initial_x = c.Get_posx();
    c.move();
    assert(c.Get_posx() == initial_x + 20);
    std::cout << "  ✓ Test 2.2: Character::move() - right\n";
}

void test_character_jump() {
    Character c;
    c.set_up_pressed(true);
    c.move();
    assert(c.jump == true);
    assert(c.Get_vely() == -16);
    std::cout << "  ✓ Test 2.3: Character::move() - jump\n";
}

void test_character_gravity() {
    Character c;
    c.set_jump(true);
    c.set_velocity_y(-10);
    c.move();
    assert(c.Get_vely() == -9);
    std::cout << "  ✓ Test 2.4: Character::move() - gravity\n";
}

void test_character_ground_collision() {
    Character c;
    c.set_jump(true);
    c.set_velocity_y(10);
    c.move();
    assert(c.Get_posy() == SCREEN_HEIGHT - 75);
    assert(c.jump == false);
    std::cout << "  ✓ Test 2.5: Character::move() - ground\n";
}

void test_character_reset() {
    Character c;
    c.set_velocity_x(20);
    c.move();
    c.reset();
    assert(c.Get_posx() == SCREEN_WIDTH / 2);
    assert(c.Get_velx() == 0);
    std::cout << "  ✓ Test 2.6: Character::reset()\n";
}