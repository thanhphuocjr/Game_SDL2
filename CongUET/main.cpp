#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include<SDL2_mixer/SDL_mixer.h>
#include<SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include<vector>
#include<cstdlib>
#include <ctime>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Qua trinh choi game

bool youlose=false;
bool space=false;

//Show Score
int score=0;
int highscore=0;
int times=0;

//Fonts
TTF_Font *gFont=NULL;
TTF_Font *gFont_ChangeLevel=NULL;
TTF_Font *gFont_GameOver = NULL;
TTF_Font *gFont_Toturial=NULL;
TTF_Font *gFont_Record=NULL;
TTF_Font *gFont_Menu_m=NULL;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

//Gift information
const int timefamegift=100;
int  timegift=0;

const int timefameFail=100;
int  timeFail=0;
///Dealine information
///
const int timefamedeadline=200;
int deadlinetime=0;

//Fonts

bool loadFont() {
    gFont = TTF_OpenFont("fontsText/OrangeJuice/juice.ttf", 32);
    if (gFont == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    
    gFont_GameOver = TTF_OpenFont("fontsText/The Score.otf", 50);
    if (gFont_GameOver == NULL) {
        cout << "Failed to load font_GameOver! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    gFont_Toturial = TTF_OpenFont("fontsText/Toturial_Font/Font.ttf", 60);
    if (gFont_Toturial == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    gFont = TTF_OpenFont("fontsText/OrangeJuice/juice.ttf", 32);
    if (gFont == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    
    
    return true;
}
void closeFont() {
    // Đóng font
    TTF_CloseFont(gFont);
    gFont = NULL;
    
    TTF_CloseFont(gFont_GameOver);
    gFont_GameOver = NULL;
    
    TTF_CloseFont(gFont_Toturial);
    gFont_Toturial = NULL;
    
    TTF_CloseFont(gFont_Record);
    gFont_Record = NULL;
    
    TTF_CloseFont(gFont_Menu_m);
    gFont_Menu_m = NULL;
}

///
///
///MUSIC
///
///
Mix_Music* gBackgroundMusic = NULL;
Mix_Music *gBackgroundMusic_Menu=NULL;

Mix_Chunk* gCollisionSound_Character_Gift = NULL;
Mix_Chunk* gLoseGame=NULL;
Mix_Chunk* gTutorial_Menu=NULL;
Mix_Chunk* gWingame=NULL;
Mix_Chunk* gChoice=NULL;
bool initAudio()
{
    bool success = true;

    // Khởi tạo SDL_mixer
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

void playBackgroundMusic_Menu()
{
    Mix_PlayMusic(gBackgroundMusic_Menu, -1);
}
void playBackgroundMusic()
{
    Mix_PlayMusic(gBackgroundMusic, -1);
}
void stopBackgroundMusic() {
    Mix_HaltMusic();
}

void playCollisionSound_Character_Gift() {
    Mix_PlayChannel(-1, gCollisionSound_Character_Gift, 0); // -1 để sử dụng kênh âm thanh đầu tiên có sẵn, 0 để phát một lần duy nhất
}
void playLoseGame_Music(){
    Mix_PlayChannel(-1, gLoseGame, 0);
}
void playWinGame(){
    Mix_PlayChannel(-1, gWingame, 0);
}
void playChoice(){
    Mix_PlayChannel(-1, gChoice, 0);
}

///
///
///
class LoadTexture
{
public:
    LoadTexture();
    ~LoadTexture();
    bool LoadImage(string path);
    void free();
    void render(int x, int y, SDL_RendererFlip flip=SDL_FLIP_NONE,SDL_Rect *clip = NULL);
    //
    int GetWidth();
    int GetHeight();
    void setRealWidth (int x){realWidth=x;}
    void setRealHeight (int y){realHeight=y;}
    private:
    SDL_Texture *realTexture;
    int realWidth;
    int realHeight;
    
};
LoadTexture gBackGround;
LoadTexture gCharacter;
LoadTexture gGift;
LoadTexture gDeadline;
LoadTexture gFail;
LoadTexture gGameOver;
LoadTexture gStartGame;
LoadTexture gHighScore;
LoadTexture gBack;
LoadTexture gToturial;
LoadTexture gToturial_text;
LoadTexture gMenuBackGround;
LoadTexture gUeter;
LoadTexture gShowResultBang;
LoadTexture gContinue;
LoadTexture gRecord;
LoadTexture gYouFail;
///
///
///
LoadTexture::LoadTexture()
{
    realTexture=NULL;
    realWidth=0;
    realHeight=0;
}

LoadTexture::~LoadTexture(){
    free();
}

bool LoadTexture::LoadImage(string path)
{
    free();
    SDL_Texture * tempTexture=NULL;
    SDL_Surface *LoadSurface=IMG_Load(path.c_str());
    if( LoadSurface == NULL )
    {
        cout<<"Khong the load Surface trong Ham LoadTexture::LoadImage "<<path.c_str()<<SDL_GetError();
    }
    else
    {
        tempTexture=SDL_CreateTextureFromSurface(gRenderer, LoadSurface);
        if( tempTexture == NULL )
        {
          cout<<"Khong the load tempTexture trong LoadTexture::LoadImage" <<path.c_str()<< SDL_GetError();
        }
        else
        {
            //Get image dimensions
            realWidth = LoadSurface->w;
            realHeight = LoadSurface->h;
        }
        SDL_FreeSurface( LoadSurface );
    }
    realTexture=tempTexture;
    return realTexture!=NULL;
}
//
void LoadTexture::free()
{
    if( realTexture != NULL )
    {
        SDL_DestroyTexture( realTexture );
        realTexture = NULL;
        realWidth = 0;
        realHeight = 0;
    }
}

void LoadTexture::render(int x, int y,SDL_RendererFlip flip,SDL_Rect *clip)
{
    SDL_Rect renderQuad={x,y,realWidth,realHeight};
    SDL_RenderCopyEx(gRenderer, realTexture, clip, &renderQuad, 0, NULL, flip);
}

int LoadTexture::GetWidth()
{
    return realWidth;
}

int LoadTexture::GetHeight()
{
    return realHeight;
}
///
///
///CHARACTER
///
///
///
class Character
{
public:
    bool jump=false;
    bool up_pressed=false;
    bool isLeft;
    int Vmax_Character=20;
    int Vjump=-17;
    Character();
    void Solve_Event(SDL_Event &event);
    void move();
    void render();
    int Get_posx() const{return real_x_position;}
    int Get_posy() const{return real_y_position;}
    int Get_velx() const{return real_x_Vel;}
    int Get_vely() const{return real_y_Vel;}
    int GetWidth()const {return width_;}
    int GetHeight() const {return height_;}
    SDL_Rect clips[3][8];
    void reset();
private:
    int width_;
    int height_;
    Uint32 lastFrame;
    pair<int,int> current_clip_;
    
    int real_x_position;
    int real_y_position;
    int real_x_Vel;
    int real_y_Vel;
};
Character::Character()
{
    jump=false;
    isLeft=true;
    real_x_position=SCREEN_WIDTH /2;
    width_= 55;
    height_=75;
    for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 8; ++j) {
                clips[i][j].x = j * 128;
                clips[i][j].y = i * 128;
                clips[i][j].w = 128;
                clips[i][j].h = 128;
            }
       }
    real_y_position=SCREEN_HEIGHT-height_;
    real_x_Vel=0;
    real_y_Vel=0;
    current_clip_=make_pair(0, 0);
}


void Character::Solve_Event(SDL_Event &e){
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                isLeft=true;
               real_x_Vel -= Vmax_Character;
                break;
            case SDLK_RIGHT:
                isLeft=false;
                real_x_Vel+= Vmax_Character;
                break;
            case SDLK_UP:
                if (!jump) {
                jump = true;
                }
                 up_pressed=true;
                break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                real_x_Vel += Vmax_Character;
                break;
            case SDLK_RIGHT: 
                real_x_Vel -= Vmax_Character;
                break;
            case SDLK_UP:
                up_pressed=false;
                break;
        }
    }
}
void Character::move()
{
    if( up_pressed && !jump ){
        real_y_Vel = Vjump;
        jump=true;
    }
    if (jump) {
        
        real_y_Vel += 1;
    }
  
    if(SDL_GetTicks()-lastFrame>60){
        current_clip_.second =(current_clip_.second+1)%8;
        lastFrame=SDL_GetTicks();
    }
    real_y_position += real_y_Vel;
    if (real_y_position >=SCREEN_HEIGHT - height_) {
        real_y_position = SCREEN_HEIGHT - height_;
        real_y_Vel = 0;
        jump=false;
    }
    
    
    //Xử lý x: di chuyển theo chiều ngang
    real_x_position += real_x_Vel;
    if(real_x_Vel)
    {
        if(jump) 
        {
            current_clip_.first=1;
        }else 
        {
            current_clip_.first=2;
        }
    }else
    {
        current_clip_.first=0;
    }
    if(real_x_position < 0 || (real_x_position + width_> SCREEN_WIDTH))
    {
        real_x_position -= real_x_Vel;
    }
}

void Character::render()
{
    if(!isLeft){
        gCharacter.render(real_x_position-(gCharacter.GetWidth()-width_)/2,
                          real_y_position-(gCharacter.GetHeight()-height_),
                          SDL_FLIP_NONE,&clips[current_clip_.first][current_clip_.second]);
    }
    else
    {
        gCharacter.render(real_x_position-(gCharacter.GetWidth()-width_)/2,
                          real_y_position-(gCharacter.GetHeight()-height_),
                          SDL_FLIP_HORIZONTAL,
                          &clips[current_clip_.first][current_clip_.second]);
    }
}
void Character::reset(){
    real_x_position=gBackGround.GetWidth()/2;
    real_y_position=gBackGround.GetHeight()-height_;
}
///
///FailScore
class FailScore{
public:
    int x_position;
    int y_position;
    int y_Vel;
    FailScore(int x, int y, int y_Vel):x_position(x),y_position(y),y_Vel(y_Vel){};
};
vector<FailScore> Fscores;
///
///
///Gift
///
class Gift{
public:
    int x_position;
    int y_position;
    int y_Vel;
    Gift(int x, int y, int y_Vel):x_position(x),y_position(y),y_Vel(y_Vel){};
    
};
vector<Gift> gifts;

void AddFailScore()
{
    int x;
    while(true){
        bool isOverlap = false;
        x=rand() % SCREEN_WIDTH-gFail.GetWidth();
        for(const auto& gift: gifts){
            if (abs(gift.x_position - x) < gGift.GetWidth()){
                
                isOverlap =true;
                break;
            }
        }
        if(!isOverlap) break;
    }
    int y=0;
    
    int vel=rand()%5+5;
    FailScore newFail(x,y,vel);
    Fscores.push_back(newFail);
    timegift=0;
}

void UpdateFailScore()
{
    for(int i=0; i<Fscores.size();i++){
        Fscores[i].y_position += Fscores[i].y_Vel;
        if(Fscores[i].y_position>SCREEN_HEIGHT){
            Fscores.erase(Fscores.begin()+i);
            i--;
        }
    }
    for(const auto Score: Fscores){
        gFail.render(Score.x_position,Score.y_position);
    }
}

void AddGift()
{
    int x;
    while(true){
        bool isOverlap = false;
        x=rand() % (SCREEN_WIDTH-gGift.GetWidth());
        for(const auto& fscore: Fscores){
            if (abs(fscore.x_position - x) < gFail.GetWidth()){
                
                isOverlap =true;
                break;
            }
        }
        if(!isOverlap) break;
    }
    int y=0;
    int vel=rand()%5+3;
    Gift newGift(x,y,vel);
    gifts.push_back(newGift);
   timegift=0;
}

void UpdateGift()
{
    for(int i=0; i<gifts.size();i++){
        gifts[i].y_position += gifts[i].y_Vel;
        if(gifts[i].y_position>SCREEN_HEIGHT){
            gifts.erase(gifts.begin()+i);
            i--;
        }
    }
    for(const auto Gift: gifts){
        gGift.render(Gift.x_position,Gift.y_position);
    }
}

///
///
///FAIL_SCORE
///
///
///Deadline
class Deadline{
public:
    int x_position;
    int y_position;
    int x_Vel;
    Deadline(int x, int y, int vel): x_position(x), y_position(y), x_Vel(vel) {}
};
vector<Deadline> deadlines;
void AddDeadline() {
    int x = SCREEN_WIDTH-gDeadline.GetWidth();
    int y = SCREEN_HEIGHT-gDeadline.GetHeight();
    int vel=2;
    Deadline newDeadline(x, y, vel);
    deadlines.push_back(newDeadline);
    deadlinetime=0;
    }
void UpdateDeadline(){
    for(int i=0; i<(int)deadlines.size(); i++){
        deadlines[i].x_position-=deadlines[i].x_Vel;
        if(deadlines[i].x_position<0){
            deadlines.erase(deadlines.begin()+i);
            i--;
        }
    }
    for( const auto &deadline: deadlines){
        gDeadline.render(deadline.x_position, deadline.y_position);
    }
}
void checktrungnhau( vector<FailScore> F, vector<Gift> A){
    for(int i=0; i<(int)A.size(); i++){
        if(A[i].x_position+gGift.GetWidth()>F[i].x_position || F[i].x_position+gFail.GetWidth()>A[i].x_position ){
            F.erase(F.begin() + i);
        }
    }
}


bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    // rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //check
        if( bottomA <= topB )
        {
            return false;
        }

        if( topA >= bottomB )
        {
            return false;
        }

        if( rightA <= leftB )
        {
            return false;
        }

        if( leftA >= rightB )
        {
            return false;
        }

        return true;
}
void Check_Character_Gift_Collision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)gifts.size(); i++) {
        SDL_Rect stoneRect = {gifts[i].x_position, gifts[i].y_position, gGift.GetWidth(),gGift.GetHeight()};
        if (checkCollision(characterRect, stoneRect)) {
            gifts.erase(gifts.begin() + i);
            score++;
            highscore=max(score, highscore);
            playCollisionSound_Character_Gift();
            i--;
        }
    }
}
void Check_Character_FailScore_Collision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)Fscores.size(); i++) {
        SDL_Rect stoneRect = {Fscores[i].x_position, Fscores[i].y_position, gFail.GetWidth(),gFail.GetHeight()};
        if (checkCollision(characterRect, stoneRect)) {
            youlose=true;
        }
    }
}
void CheckCharacter_DeadlineCollision(Character& character) {
    SDL_Rect characterRect = {character.Get_posx(), character.Get_posy(), character.GetWidth(), character.GetHeight()};
    for (int i = 0; i < (int)deadlines.size(); i++) {
        SDL_Rect DeadlineRect = {deadlines[i].x_position, deadlines[i].y_position, gDeadline.GetWidth(),gDeadline.GetHeight()};
        if(checkCollision(characterRect, DeadlineRect)){
            if(character.Get_vely()>0){
                deadlines.erase(deadlines.begin() + i);
                score++;
                playCollisionSound_Character_Gift();
                i--;
            }
            else
            {
                youlose=true;
            }
        }
        else if(characterRect.x>DeadlineRect.x+DeadlineRect.w){
            deadlines.erase(deadlines.begin() + i);
            score++;
            playCollisionSound_Character_Gift();
            i--;
        }
    }
}
void Load_High_Score(string path) {
    ifstream file(path);
    if (!file) {
        cerr << "Unable to open file";
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
        stringstream ss(line);
        ss >> highscore;
        cout << "Loaded High Score: " << highscore << endl;
    }

    file.close();
}

void Save_High_Score(string path) {
    ofstream file(path);
    if (!file) {
        cerr << "Unable to create/open file";
        return;
    }
    file << highscore;
    cout << "High Score saved: " << highscore << endl;
    file.close();
}


void Menu_m() {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, "Press M: Menu", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {20, 65, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void Show_Tutorial_GameOver() {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, "_Press ''P''  to replay_ ", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2-textSurface->w/2, SCREEN_HEIGHT/3+60, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void Show_Title() {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_Toturial, "A Day As A UET Student !", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2 - textSurface->w/2, textSurface->h, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void TryTheBest() {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_Toturial, "Try your best to break this record !", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2 - textSurface->w/2, SCREEN_HEIGHT/2 - textSurface->h/2, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}

void Show_Change_Level(){
        SDL_Color textColor = {255, 0, 255, 0};
        SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_Toturial, "SPEED UP!", textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect textRect = {SCREEN_WIDTH/2 - textSurface->w/2, SCREEN_HEIGHT/3, textSurface->w, textSurface->h};
        SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
}

void ShowTutorial() {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_Toturial, "Press ''Space'' To Play", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2 - textSurface->w/2, 3*SCREEN_HEIGHT/4 - textSurface->h/2, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface); // Free the surface after creating texture
}

void ShowScore(){
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, ("Score: " + to_string(score)).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {20, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void Show_High_Score(){
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, ("High Score: " + to_string(highscore)).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {20, 35, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void ShowScore_GameOver(){
    SDL_Color textColor ={255, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_GameOver, ("Score: " + to_string(score)).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2-(textSurface->w/2),SCREEN_HEIGHT/4-(textSurface->h/2)+30 , textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}
void Show_High_Score_Game_Over(){
    SDL_Color textColor = {255, 0, 0, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont_GameOver, (" Max Score: " + to_string(highscore)).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH/2-(textSurface->w/2),SCREEN_HEIGHT/4-(textSurface->h/2)+textSurface->h+30, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
}

bool init()
{	
    // Khởi tạo SDL
    bool success=true;	
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Khong the khoi tao SDL_Init" << SDL_GetError() << endl;
        return false;
    }

    // Khởi tạo SDL_ttf
    if (TTF_Init() == -1) {
        cout << "Khong the khoi tao TTF " << TTF_GetError() << endl;
        return false;
    }
    if (!loadFont()) {
        cout << "Khong load duoc Fonts" << endl;
        success = false;
    }

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout<<"Loi bool init: SDL_Init"<<endl<<SDL_GetError();
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow( "23021665_NGUYEN_THANH_PHUOC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            cout<<"Khong the khoi tao gWindow trong bool init"<<endl<< SDL_GetError();
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                cout<<"Khong the khoi tao gRenderer trong bool init"<<endl<<SDL_GetError() ;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                   cout<<"Khong the khoi tao hinh anh"<< IMG_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}
bool loadMedia(){
    bool success=true;
    ///Music
    ///
    ///
    ///Dai
    gBackgroundMusic_Menu=Mix_LoadMUS("music/BackGround_Menu.mp3");
    if (gBackgroundMusic_Menu==NULL)
    {
        cout << "Failed to load Background_menu music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    gBackgroundMusic=Mix_LoadMUS("music/Music_background.mp3");
    if (gBackgroundMusic==NULL)
    {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    
    /// Ngan music
    gCollisionSound_Character_Gift=Mix_LoadWAV("music/Ting_CharacterStone.mp3");
    if (gCollisionSound_Character_Gift==NULL)
    {
        cout << "Khong load duoc gCollisionSound trong LoadMedia Function" << Mix_GetError() << endl;
        success = false;
    }
    gLoseGame=Mix_LoadWAV("music/LoseGame.mp3");
    if (gLoseGame==NULL)
    {
        cout << "Khong load duoc gLoseGame_Music trong LoadMedia Function" << Mix_GetError() << endl;
        success = false;
    }
    gTutorial_Menu=Mix_LoadWAV("music/Tutorial_Menu.mp3");
    if (gTutorial_Menu==NULL)
    {
        cout << "Khong load duoc gTutorial_Menu Music trong LoadMedia Function" << Mix_GetError() << endl;
        success = false;
    }
    gWingame=Mix_LoadWAV("music/Wingame.mp3");
    if (gWingame==NULL)
    {
        cout << "Khong load duoc gWinGame_Music trong LoadMedia Function" << Mix_GetError() << endl;
        success = false;
    }
    gChoice=Mix_LoadWAV("music/Choice.mp3");
    if (gWingame==NULL)
    {
        cout << "Khong load duoc gChoice trong LoadMedia Function" << Mix_GetError() << endl;
        success = false;
    }
    
    ///
    ///
    ///Image
    if(!gFail.LoadImage("image/FinalF.png"))
    {
        cout<<"Khong load duoc F- score trong loadMedia";
        success=false;
    }
    
    if(!gDeadline.LoadImage("image/DEADLINE.png"))
    {
        cout<<"Khong load duoc Deadline trong loadMedia";
        success=false;
    }
    
    if(!gGift.LoadImage("image/A+.png"))
    {
        cout<<"Khong load duoc Ball trong LoadMedia Function";
        success=false;
    }
    if(!gBackGround.LoadImage("image/MoonUET_BackGround.jpeg"))
    {
        cout<<"Khong load duoc BackGround trong LoadMedia Function";
        success=false;
    }
    if( !gCharacter.LoadImage("image/main_animation.png" ))
    {
        cout<<"Khong load duoc Character trong LoadMedia Function";
        success = false;
    }
    gCharacter.setRealWidth(128);
    gCharacter.setRealHeight(128);
    if( !gGameOver.LoadImage("image/GameOver.jpg" ))
    {
        cout<<"Khong load duoc GameOver trong LoadMedia Function";
        success = false;
    }
    if( !gShowResultBang.LoadImage("image/ShowResultBang.jpeg" ))
    {
        cout<<"Khong load duoc gSHowResultBang trong LoadMedia Function";
        success = false;
    }
    if( !gRecord.LoadImage("image/Record.png" ))
    {
        cout<<"Khong load duoc Record trong LoadMedia Function";
        success = false;
    }
    if( !gYouFail.LoadImage("image/YOUFAIL.png" ))
    {
        cout<<"Khong load duoc YouFail trong LoadMedia Function";
        success = false;
    }
    
    
    
    
    /// Load Menu
    ///
    ///
     if( !gMenuBackGround.LoadImage("Menu/MenuBackGround.jpeg" ))
    {
        cout<<"Khong load duoc MenuBackGround trong LoadMedia Function";
        success = false;
    }
    if(!gStartGame.LoadImage("Menu/Start.png"))
    {
        cout<<"Khong load duoc StartGame trong LoadMedia Function";
        success=false;
    }
    if(!gHighScore.LoadImage("Menu/High.png"))
    {
        cout<<"Khong load duoc HighScore trong LoadMedia Function";
        success=false;
    }
    if(!gBack.LoadImage("Menu/Back.png"))
    {
        cout<<"Khong load duoc BackGame trong LoadMedia Function";
        success=false;
    }
    if(!gToturial.LoadImage("Menu/Toturial.png"))
    {
        cout<<"Khong load duoc BackGame trong LoadMedia Function";
        success=false;
    }
    if(!gToturial_text.LoadImage("Menu/Toturial_text.png"))
    {
        cout<<"Khong load duoc Toturial_text trong LoadMedia Function";
        success=false;
    }
    if(!gUeter.LoadImage("Menu/UETER.png"))
    {
        cout<<"Khong load duoc Toturial_text trong LoadMedia Function";
        success=false;
    }
    if(!gContinue.LoadImage("Menu/Continue.png"))
    {
        cout<<"Khong load duoc gContinue trong LoadMedia Function";
        success=false;
    }
    
    
    return success;
    
}
void close()
{
    //music_back
    Mix_FreeMusic(gBackgroundMusic);
    gBackgroundMusic = NULL;
    Mix_FreeMusic(gBackgroundMusic_Menu);
    gBackgroundMusic_Menu = NULL;
    //music_chunk
    Mix_FreeChunk(gCollisionSound_Character_Gift);
    gCollisionSound_Character_Gift=NULL;
    Mix_FreeChunk(gLoseGame);
    gLoseGame = NULL;
    Mix_FreeChunk(gTutorial_Menu);
    gTutorial_Menu = NULL;
    Mix_FreeChunk(gWingame);
    gWingame = NULL;
    Mix_FreeChunk(gChoice);
    gChoice = NULL;
    
    Mix_CloseAudio();
    Mix_Quit();
    
    //font
    closeFont();
    
    
    gFont=NULL;
    gFont_GameOver=NULL;
    gFont_Toturial=NULL;
    gFont_Record=NULL;
    gFont_Menu_m=NULL;

    //image
    gCharacter.free();
    gFail.free();
    gGameOver.free();
    gBackGround.free();
    gStartGame.free();
    gContinue.free();
    gRecord.free();
    gYouFail.free();
    gHighScore.free();
    gBack.free();
    gToturial.free();
    gToturial_text.free();
    gMenuBackGround.free();
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
int level =1;
void solveSpace(){
    if(space==false){
        ShowTutorial();
    }
    if(space==true ){
        timegift++;
        if(timegift==timefamegift){
            for(int i =0;i<level;i++){
                AddGift();
            }
          
            timegift=0;
        }
    deadlinetime+= rand()%2;
        if(deadlinetime>=timefamedeadline){
            AddDeadline();
            deadlinetime=0;
        }
        timeFail++;
        if(timeFail==timefameFail){
            for(int i =0;i<level;i++){
                AddFailScore();
            }
            timeFail=0;
        }
    }
    UpdateFailScore();
    UpdateDeadline();
    UpdateGift();
}

void PrintResultIcon(){
    if(score>=highscore){
        gRecord.render(SCREEN_WIDTH/2-gShowResultBang.GetWidth()/2, SCREEN_HEIGHT/14-25);
    }
    else
    {
        gYouFail.render(SCREEN_WIDTH/2-15, SCREEN_HEIGHT/14+10);
    }
}
bool gameOver(){
    if(youlose){
        level=1;
        stopBackgroundMusic();
        if(score>=highscore){
            playWinGame();
        }else{
            playLoseGame_Music();
        }
        bool quit=false;
        SDL_Event e;
        while(!quit )
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT){
                    youlose=false;
                    quit=true;
                }
                if(e.type==SDL_KEYDOWN &&  e.key.keysym.sym == SDLK_p) {
                    score=0;
                    space=false;
                    youlose=true;
                    quit=true;
                    Fscores.clear();
                    deadlines.clear();
                    gifts.clear();
                    
                }
            }
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            gGameOver.render(0,0);
            gShowResultBang.render(SCREEN_WIDTH/2-gShowResultBang.GetWidth()/2, SCREEN_HEIGHT/14);
            ShowScore_GameOver();
            Show_High_Score_Game_Over();
            Show_Tutorial_GameOver();
            PrintResultIcon();
            SDL_RenderPresent( gRenderer );
        }
    }
    return youlose;
}
bool quit_all=false;
void showMenu() {

    playBackgroundMusic_Menu();
    bool quit = false;
    bool back=false;
    bool showMax=false;
    bool showToturial=false;
    SDL_Event e;
    int start_x=SCREEN_WIDTH/2-gStartGame.GetWidth()/2;   int start_x_end=start_x+ gStartGame.GetWidth();
    int start_y=SCREEN_HEIGHT/4;                          int start_y_end=start_y+gStartGame.GetHeight();
    
    int high_x=SCREEN_WIDTH/2-gHighScore.GetWidth()/2;    int high_x_end=high_x+ gHighScore.GetWidth();
    int high_y=SCREEN_HEIGHT/4+gStartGame.GetHeight()+10; int high_y_end=high_y+ gHighScore.GetHeight();
    
    int toturial_x=SCREEN_WIDTH/2-gStartGame.GetWidth()/2;int toturial_x_end=toturial_x+gToturial.GetWidth();
    int toturial_y=SCREEN_HEIGHT/4+2*gStartGame.GetHeight()+20;int toturial_y_end=toturial_y+gToturial.GetHeight();
    
    int back_x=SCREEN_WIDTH/2-gStartGame.GetWidth()/2;int back_x_end=back_x+gBack.GetWidth();
    int back_y=SCREEN_HEIGHT-gBack.GetHeight();int back_y_end=back_y+gBack.GetHeight();
    
    while (!quit && !quit_all) {
        // Xử lý sự kiện cho menu
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit_all = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && back==false)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= start_x && x <= start_x_end && y >= start_y && y <= start_y_end) {
                    playChoice();
                    cout << "Start Game selected!" << endl;
                    quit = true;
                    times++;
                    stopBackgroundMusic();
                    if(times>1){
                        playBackgroundMusic();
                    }
                } else if (x >= high_x && x <= high_x_end&& y >= high_y && y <= high_y_end) {
                    // Thoát game
                    playChoice();
                    back=true;
                    showMax=true;
                    cout << "HighScore selected" << endl;
                    
                }else if(x >= toturial_x && x <= toturial_x_end && y >= toturial_y && y <= toturial_y_end) {
                    // Thoát game
                    playChoice();
                    cout << "Toturial selected" << endl;
                    back=true;
                    showToturial=true;
                }
            }
            if(showMax && back){
                if (e.type == SDL_MOUSEBUTTONDOWN) 
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    // Xác định nút được nhấp vào
                    if (x >= back_x && x <= back_x_end && y >= back_y && y <= back_y_end) 
                    {
                        playChoice();
                        cout<<"Back Selected";
                        back=false;
                        showMax=false;
                    }
                }
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                gMenuBackGround.render(0, 0);
                Show_High_Score_Game_Over();
                gBack.render(back_x, back_y);
                TryTheBest();
                SDL_RenderPresent(gRenderer);
               }
            else if(showToturial && back)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    // Xác định nút được nhấp vào
                    if (x >= back_x && x <= back_x_end && y >= back_y && y <= back_y_end) 
                    {
                        playChoice();
                        cout<<"Back Selected";
                        back=false;
                        showToturial=false;
                    }
                }
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                gMenuBackGround.render(0, 0);
                gToturial_text.render(SCREEN_WIDTH/2-gToturial_text.GetWidth()/2, SCREEN_HEIGHT/5);
                gBack.render(back_x, back_y);
                gUeter.render(SCREEN_WIDTH/9, SCREEN_HEIGHT-gUeter.GetHeight());
                SDL_RenderPresent(gRenderer);
                
            }
            else
            {
                gMenuBackGround.render(0, 0);
                if(space){
                    gContinue.render(start_x,start_y);
                }else{
                    gStartGame.render(start_x,start_y);
                }
                gHighScore.render(high_x,high_y);
                gToturial.render(toturial_x,toturial_y);
                Show_Title();
                SDL_RenderPresent(gRenderer);
                
            }
        }
    }
}
//int Vmax_Character=15;
//int Vjump=-17;
void Change_level(){
    if (score>=7 && score<14){
        level=2;
        for(int i=0; i<(int)Fscores.size(); i++){
                   Fscores[i].y_Vel= rand()%5+7;
        }
        for(int i=0; i<(int)deadlines.size(); i++){
                   deadlines[i].x_Vel= 4;
        }
        for(int i=0; i<(int)gifts.size(); i++){
                   gifts[i].y_Vel=rand()%5+7;
        }
    }else if(score>=14 && score<21){
        level=2;
        for(int i=0; i<(int)Fscores.size(); i++){
                   Fscores[i].y_Vel= rand()%5+9;
        }
        for(int i=0; i<(int)deadlines.size(); i++){
                   deadlines[i].x_Vel= 8;
        }
        for(int i=0; i<(int)gifts.size(); i++){
                   gifts[i].y_Vel=rand()%5+9;
        }
    }else if (score>=21 && score<=30){
        level=2;
        for(int i=0; i<(int)Fscores.size(); i++){
            Fscores[i].y_Vel= rand()%5+12;
        }
        for(int i=0; i<(int)deadlines.size(); i++){
            deadlines[i].x_Vel= 10;
        }
        for(int i=0; i<(int)gifts.size(); i++){
            gifts[i].y_Vel=rand()%5+12;
        }
    }else if(score>30){
        level=3;
        for(int i=0; i<(int)Fscores.size(); i++){
            Fscores[i].y_Vel= rand()%5+20;
        }
        for(int i=0; i<(int)deadlines.size(); i++){
            deadlines[i].x_Vel= 15;
        }
        for(int i=0; i<(int)gifts.size(); i++){
            gifts[i].y_Vel=rand()%5+20;
        }
    }
}
void Check_to_ShowChangeLevel(){
    bool check=false;
    if((score==7)||(score==14 )||(score==21)||(score==30)){
        check=true;
    }
    if(check){
        int timeshow=2;
        while(timeshow--){
            Show_Change_Level();
        }
    }
}
void play(){
        youlose=false;
        bool quit=false;
        SDL_Event e;
        Character character;
    
        while(!quit && !youlose)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_KEYDOWN &&  e.key.keysym.sym == SDLK_SPACE && space==false ) {
                    space=true;
                    playBackgroundMusic();
                    
                }
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
                {
                    showMenu();
                    SDL_Delay(1000);
                }
                if(e.type==SDL_QUIT){
                    quit=true;
                }
                character.Solve_Event(e);
            }
            Change_level();
            character.move();
            Check_Character_FailScore_Collision(character);
            Check_Character_Gift_Collision(character);
            CheckCharacter_DeadlineCollision(character);
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            gBackGround.render(0,0);
            solveSpace();
            character.render();
            ShowScore();
            Menu_m();
            Show_High_Score();
            Check_to_ShowChangeLevel();
            SDL_RenderPresent( gRenderer );
        }
}
int main(int agrc, char* argc[])
{
    bool quit=false;
    checktrungnhau(Fscores, gifts);
    cout<<SDL_GetBasePath();
    Load_High_Score("MaxScore.txt");
    if (!init())
    {
        cout<<"Fail to load init"<<endl;
    }
    else if(!initAudio()){
        cout<<"Fail to load music"<<endl;
    }
    else
    {
        if(!loadMedia())
        {
            cout<<"Fail to load Media"<<endl;
        }
        else
        {
            showMenu();
            if(!quit && !quit_all){
             do{
                    play();
                    Save_High_Score("MaxScore.txt");
                }while(gameOver());
            }
        }
    }
    close();
    return 0;
}
