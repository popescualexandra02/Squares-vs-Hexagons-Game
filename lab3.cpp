#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "random"

using namespace std;
using namespace m1;


Lab3::Lab3()
{
}

Lab3::~Lab3()
{
}

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> randDangerLine(1, 3);

std::random_device rd1;
std::mt19937 mt1(rd1());
std::uniform_real_distribution<float> randDistance(1300.0f, 1300.1f);

std::random_device rd2;
std::mt19937 mt2(rd2());
std::uniform_real_distribution<float> randTime(4.0f, 5.0f);

std::random_device rd3;
std::mt19937 mt3(rd3());
std::uniform_int_distribution<int> randDangerType(1, 40);

float dangers_x[42] = {};
float rand_time = randTime(mt2);
float rand_time2 = randTime(mt2);

int rand_line[42] = {};
int rand_type;
int see_danger[42] = {};

float x_soldier = 290;
float x_star = x_soldier + 10;
int stare = 0;
float scaleX = 0;
float scaleY = 0;
float scaleX2 = 0;
float scaleY2 = 0;
bool seeSoldier[10] = {};
double rot = 0;
bool x = true;
int Danger_Line = 0;
float randomX = 0;
float randomY = 0;
float randomX2 = 0;
float randomY2 = 0;
float randomX3 = 0;
float randomY3 = 0;
bool starRendered = false;
bool soldier1 = false;
bool soldier2 = false;
bool soldier3 = false;
bool soldier4 = false;
float move_x1 = 0;
float move_y1 = 0;
int realease[11] = {};
int realease2[11] = {};
int realease3[11] = {};
int realease4[11] = {};
int  ocupat[11] = {};
float time_now = 1;
float time_now2 = 1;
int activ[42] = {};
int act = 1;
float line = 0.0f;





float squareSide = 100;
float right_angle_length = 50;
float right_angle_width = 390;
float soldier_length = 25;
float soldier_width = 40;
float dangerSide = 35;
float starSide = 50;
float square_empty_length = 100;
float square_empty_width = 100;

typedef struct patrate {
    float x_soldat, y_soldat;
    int star;
    float x_star;
    float y_star;
    bool see_star;
    int star_cnt;
    int see_soldier;
    int shoot_star;
    float scale_x;
    float scale_y;
}patrate;
patrate patrat[10];

float x_star_coord[10] = {};

void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    //squares
    Mesh* square = object2D::CreateSquare("square", corner, squareSide, glm::vec3(0.14f, 0.55f, 0.14f), true);
    AddMeshToList(square);

    //right_angle
    Mesh* right_angle = object2D::CreateDreptunghi("right_angle", corner, right_angle_length, right_angle_width, glm::vec3(0.65f, 0.16f, 0.16f), true);
    AddMeshToList(right_angle);

    //soldier
    Mesh* soldier1 = object2D::CreateSoldier("soldier1", corner, soldier_length, soldier_width, glm::vec3(1, 0.08f, 0.58f), true);
    AddMeshToList(soldier1);
    Mesh* soldier2 = object2D::CreateSoldier("soldier2", corner, soldier_length, soldier_width, glm::vec3(0.73f, 0.34f, 0.83f), true);
    AddMeshToList(soldier2);
    Mesh* soldier3 = object2D::CreateSoldier("soldier3", corner, soldier_length, soldier_width, glm::vec3(1, 0.5f, 0.32f), true);
    AddMeshToList(soldier3);
    Mesh* soldier4 = object2D::CreateSoldier("soldier4", corner, soldier_length, soldier_width, glm::vec3(0, 0, 0.51f), true);
    AddMeshToList(soldier4);

    //danger
    Mesh* danger1 = object2D::CreateDanger("danger1", corner, dangerSide, glm::vec3(1, 0.08f, 0.58f), glm::vec3(1, 1, 0.58f), true);
    AddMeshToList(danger1);
    Mesh* danger2 = object2D::CreateDanger("danger2", corner, dangerSide, glm::vec3(0.73f, 0.34f, 0.83f), glm::vec3(1, 1, 0.58f), true);
    AddMeshToList(danger2);
    Mesh* danger3 = object2D::CreateDanger("danger3", corner, dangerSide, glm::vec3(1, 0.5f, 0.32f), glm::vec3(1, 1, 0.58f), true);
    AddMeshToList(danger3);
    Mesh* danger4 = object2D::CreateDanger("danger4", corner, dangerSide, glm::vec3(0, 0, 0.51f), glm::vec3(1, 1, 0.58f), true);
    AddMeshToList(danger4);

    //demo_stars
    Mesh* star1 = object2D::CreateStar("star1", corner, starSide, glm::vec3(0.4f, 0.6f, 0.93f), true);
    AddMeshToList(star1);

    //random_stars
    Mesh* star = object2D::CreateStar("star", corner, starSide, glm::vec3(0.2f, 0.8f, 0.53f), true);
    AddMeshToList(star);

    //stars
    Mesh* star_type1 = object2D::CreateStar("star_type1", corner, starSide, glm::vec3(1, 0.08f, 0.58f),  true);
    AddMeshToList(star_type1);
    Mesh* star_type2 = object2D::CreateStar("star_type2", corner, starSide, glm::vec3(0.73f, 0.34f, 0.83f), true);
    AddMeshToList(star_type2);
    Mesh* star_type3 = object2D::CreateStar("star_type3", corner, starSide, glm::vec3(1, 0.5f, 0.32f), true);
    AddMeshToList(star_type3);
    Mesh* star_type4 = object2D::CreateStar("star_type4", corner, starSide, glm::vec3(0, 0, 0.51f), true);
    AddMeshToList(star_type4);

    //empty
    Mesh* empty1 = object2D::CreateSquareEmpty("empty1", corner, square_empty_length,square_empty_width , glm::vec3(0.14f, 0.55f, 0.14f), true);
    AddMeshToList(empty1);

    Mesh* empty2 = object2D::CreateSquareEmpty("empty2", corner, square_empty_length, square_empty_width, glm::vec3(0.14f, 0.55f, 0.14f), true);
    AddMeshToList(empty2);

    Mesh* empty3 = object2D::CreateSquareEmpty("empty3", corner, square_empty_length, square_empty_width, glm::vec3(0.14f, 0.55f, 0.14f), true);
    AddMeshToList(empty3);

    Mesh* empty4 = object2D::CreateSquareEmpty("empty4", corner, square_empty_length, square_empty_width, glm::vec3(0.14f, 0.55f, 0.14f), true);
    AddMeshToList(empty4);

    //life
    Mesh* life1 = object2D::CreateSquare("life1", corner, squareSide, glm::vec3(0.65f, 0.16f, 0.16f), true);
    AddMeshToList(life1);
    Mesh* life2 = object2D::CreateSquare("life2", corner, squareSide, glm::vec3(0.65f, 0.16f, 0.16f), true);
    AddMeshToList(life2);
    Mesh* life3 = object2D::CreateSquare("life3", corner, squareSide, glm::vec3(0.65f, 0.16f, 0.16f), true);
    AddMeshToList(life3);

    //star
    for (int i = 1; i <= 9; i++) {
        patrat[i].star_cnt = 0;
        patrat[i].see_soldier = 0;
        patrat[i].shoot_star = 0;
        patrat[i].scale_x = 1;
        patrat[i].scale_y = 1;
    }
    x_star_coord[1] = x_star_coord[4] = x_star_coord[7] = 140.0f;
    x_star_coord[2] = x_star_coord[5] = x_star_coord[8] = 290.0f;
    x_star_coord[3] = x_star_coord[6] = x_star_coord[9] = 440.0f;

    patrat[1].x_star = 140;
    patrat[1].y_star = 80;

    patrat[2].x_star = 290;
    patrat[2].y_star = 80;

    patrat[3].x_star = 440;
    patrat[3].y_star = 80;

    patrat[4].x_star = 140;
    patrat[4].y_star = 220;

    patrat[5].x_star = 290;
    patrat[5].y_star = 220;

    patrat[6].x_star = 440;
    patrat[6].y_star = 220;

    patrat[7].x_star = 140;
    patrat[7].y_star = 370;

    patrat[8].x_star = 290;
    patrat[8].y_star = 370;

    patrat[9].x_star = 440;
    patrat[9].y_star = 370;

    for (int i = 1; i <= 9; i++) {
        patrat[i].see_star = true;
    }
}

void Lab3::Danger_appear(int type, int j, float line_y, float deltaTime ) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(dangers_x[j], line_y);
    modelMatrix *= transform2D::Rotate(0.3f) * transform2D::Translate(-17, -17);
    if (dangers_x[j] > 120 && see_danger[j] == 0) {

        dangers_x[j] -= 2 ;
    }if (dangers_x[j] <= 120) {
        activ[j] = 0;
    }

    if (type == 1) {
        if (see_danger[j] == 0) {
            RenderMesh2D(meshes["danger1"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type == 2) {
        if (see_danger[j] == 0) {
            RenderMesh2D(meshes["danger2"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type == 3) {
        if (see_danger[j] == 0) {
            RenderMesh2D(meshes["danger3"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type == 4) {
        if (see_danger[j] == 0) {
            RenderMesh2D(meshes["danger4"], shaders["VertexColor"], modelMatrix);
        }
    }
    
}

void Lab3::Star_Appear(glm::vec3 dangerPosition, int type, float deltaTimeSeconds, float line) {
    for (int i = 1; i <= 3; i++) {
        if (type >= 1 && type <= 10 && realease[i] == i && line == 40) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 10 && type <= 20 && realease2[i] == i && line == 40) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 20 && type <= 30 && realease3[i] == i && line == 40) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 30 && type <= 40 && realease4[i] == i && line == 40) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
    }
    
    for (int i = 4; i <= 6; i++) {
        if (type >= 1 && type <= 10 && realease[i] == i && line == 180) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 10 && type <= 20 && realease2[i] == i && line == 180) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 20 && type <= 30 && realease3[i] == i && line == 180) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 30 && type <= 40 && realease4[i] == i && line == 180) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
    }

    for (int i = 7; i <= 9; i++) {
        if (type >= 1 && type <= 10 && realease[i] == i && line == 330) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 10 && type <= 20 && realease2[i] == i && line == 330) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 20 && type <= 30 && realease3[i] == i && line == 330) {
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
        if (type > 30 && type <= 40 && realease4[i] == i && line == 330){
            Star_shoot(type, i, deltaTimeSeconds, dangerPosition);
        }
    }
}
void Lab3::Star_shoot(int type, int i, float deltaTimeSeconds, glm::vec3 dangerPosition) {
    patrat[i].see_star = true;
    patrat[i].x_star += 3;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(patrat[i].x_star, patrat[i].y_star);
    modelMatrix *= transform2D::Translate(0, -starSide / 2); // Translate to the star's center
    modelMatrix *= transform2D::Rotate(-2 * rot); // Apply the rotation around the center
    modelMatrix *= transform2D::Translate(0, +starSide / 2); // Translate back to the original position
    rot += 0.5f * deltaTimeSeconds;
    if (type >= 1 && type <= 10) {
        if (patrat[i].see_star) {
            RenderMesh2D(meshes["star_type1"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type > 10 && type <= 20) {
        if (patrat[i].see_star) {
            RenderMesh2D(meshes["star_type2"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type > 20 && type <= 30) {
        if (patrat[i].see_star) {
            RenderMesh2D(meshes["star_type3"], shaders["VertexColor"], modelMatrix);
        }
    }
    else if (type > 30 && type <= 40) {
        if (patrat[i].see_star) {
            RenderMesh2D(meshes["star_type4"], shaders["VertexColor"], modelMatrix);
        }
    }
    
    glm::vec3 starPosition(patrat[i].x_star, patrat[i].y_star, 0);
    if (glm::distance(starPosition, dangerPosition) < (starSide + dangerSide)) {
        patrat[i].x_star = x_star_coord[i];
        patrat[i].see_star = false;
        patrat[i].star_cnt += 1;
        see_danger[type] = 1;
        activ[type] = 0;
    }
}
void Lab3::Soldier_killed(glm::vec3 danger1Position, glm::vec3 danger2Position, glm::vec3 danger3Position, glm::vec3 soldierPosition, float line) {

    if (line == 20) {
        if (soldierPosition.x == 140) {
            if (glm::distance(soldierPosition, danger1Position) < (soldier_width + dangerSide)) {
                patrat[1].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 290) {
            if (glm::distance(soldierPosition, danger1Position) < (soldier_width + dangerSide)) {
                patrat[2].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 440) {
            if (glm::distance(soldierPosition, danger1Position) < (soldier_width + dangerSide)) {
                patrat[3].see_soldier = 1;
            }
        }
    }
    if (line == 160) {
        if (soldierPosition.x == 140) {
            if (glm::distance(soldierPosition, danger2Position) < (soldier_width + dangerSide)) {
                patrat[4].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 290) {
            if (glm::distance(soldierPosition, danger2Position) < (soldier_width + dangerSide)) {
                patrat[5].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 440) {
            if (glm::distance(soldierPosition, danger2Position) < (soldier_width + dangerSide)) {
                patrat[6].see_soldier = 1;
            }
        }

    }
    if (line == 310) {
        if (soldierPosition.x == 140) {
            if (glm::distance(soldierPosition, danger3Position) < (soldier_width + dangerSide)) {
                patrat[7].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 290) {
            if (glm::distance(soldierPosition, danger3Position) < (soldier_width + dangerSide)) {
                patrat[8].see_soldier = 1;
            }
        }
        if (soldierPosition.x == 440) {
            if (glm::distance(soldierPosition, danger3Position) < (soldier_width + dangerSide)) {
                patrat[9].see_soldier = 1;
            }
        }

    }
    
}

void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.64f, 0.85f, 0.9f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}



void Lab3::Update(float deltaTimeSeconds)
{
    //structura elemente 
    //soldat

    glm::vec3 soldat1Position = glm::vec3(0, 0, 0);
    glm::vec3 soldat2Position = glm::vec3(0, 0, 0);
    glm::vec3 soldat3Position = glm::vec3(0, 0, 0);
    glm::vec3 soldat4Position = glm::vec3(0, 0, 0);

    patrat[1].x_soldat = 140;
    patrat[1].y_soldat = 20;

    patrat[2].x_soldat = 290;
    patrat[2].y_soldat = 20;

    patrat[3].x_soldat = 440;
    patrat[3].y_soldat = 20;

    patrat[4].x_soldat = 140;
    patrat[4].y_soldat = 160;

    patrat[5].x_soldat = 290;
    patrat[5].y_soldat = 160;

    patrat[6].x_soldat = 440;
    patrat[6].y_soldat = 160;

    patrat[7].x_soldat = 140;
    patrat[7].y_soldat = 310;

    patrat[8].x_soldat = 290;
    patrat[8].y_soldat = 310;

    patrat[9].x_soldat = 440;
    patrat[9].y_soldat = 310;

    

    
    //squares
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 10);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 10);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 10);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 150);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 150);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 150);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 300);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 300);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 300);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    //right_angle

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 10);
    RenderMesh2D(meshes["right_angle"], shaders["VertexColor"], modelMatrix);

    //soldiers demo
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 520);
    RenderMesh2D(meshes["soldier1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(240, 520);
    RenderMesh2D(meshes["soldier2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(430, 520);
    RenderMesh2D(meshes["soldier3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(620, 520);
    RenderMesh2D(meshes["soldier4"], shaders["VertexColor"], modelMatrix);



    //demo_stars
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(40, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(230, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(280, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(470, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(610, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(660, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(710, 500);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    //life_stars
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(820, 540);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(870, 540);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(920, 540);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(970, 540);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1020, 540);
    RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);


    //empty
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 510);
    RenderMesh2D(meshes["empty1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 510);
    RenderMesh2D(meshes["empty2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(390, 510);
    RenderMesh2D(meshes["empty3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(580, 510);
    RenderMesh2D(meshes["empty4"], shaders["VertexColor"], modelMatrix);

    //life
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 550);
    RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(950, 550);
    RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1100, 550);
    RenderMesh2D(meshes["life3"], shaders["VertexColor"], modelMatrix);

    
    
    glm::vec3 danger1Position = glm::vec3(0, 0, 0);
    glm::vec3 danger2Position = glm::vec3(0, 0, 0);
    glm::vec3 danger3Position = glm::vec3(0, 0, 0);

    //random danger + active stars
       time_now+= deltaTimeSeconds;
       rand_time = randTime(mt2);
       if (time_now >= rand_time) {
           act = randDangerType(mt3);
           if (activ[act] != 1) {
               dangers_x[act] = randDistance(mt1);
               activ[act] = 1;
               time_now = 0;
           }
       }
       for (int j = 1; j <= 40; j++) {
           if (activ[j] == 1) {
               if (j >= 1 && j < 10) {
                   if (j >= 1 && j <= 3) {
                       line = 40;
                       Danger_appear( 1, j, 40, deltaTimeSeconds);
                       danger1Position = glm::vec3(dangers_x[j], 40, 0);
                       Star_Appear(danger1Position, j, deltaTimeSeconds, line);
                   }
                   if (j >= 4 && j <= 7) {
                       line = 180;
                       Danger_appear(1, j, 180, deltaTimeSeconds);
                       danger2Position = glm::vec3(dangers_x[j], 180, 0);
                       Star_Appear(danger2Position, j, deltaTimeSeconds, line);
                   }
                   if (j >= 8 && j <= 10) {
                       line = 330;
                       Danger_appear(1, j, 330, deltaTimeSeconds);
                       danger3Position = glm::vec3(dangers_x[j], 330, 0);
                       Star_Appear(danger3Position, j, deltaTimeSeconds,  line);
                   }
               }
               if (j > 10 && j <= 20) {
                   if (j >= 11 && j <= 13) {
                       line = 40;
                       Danger_appear(2, j, 40, deltaTimeSeconds);
                       danger1Position = glm::vec3(dangers_x[j], 40, 0);
                       Star_Appear(danger1Position, j, deltaTimeSeconds, line);
                   }
                   if (j >= 14 && j <= 16) {
                       line = 180;
                       Danger_appear(2, j, 180, deltaTimeSeconds);
                       danger2Position = glm::vec3(dangers_x[j], 180, 0);
                       Star_Appear(danger2Position, j, deltaTimeSeconds, line);

                   }
                   if (j >= 17 && j <= 20) {
                       line = 330;
                       Danger_appear(2, j, 330, deltaTimeSeconds);
                       danger3Position = glm::vec3(dangers_x[j], 330, 0);
                       Star_Appear(danger3Position, j, deltaTimeSeconds, line);
                   }
               }
               if (j >20 && j <= 30) {
                   if (j >= 21 && j <= 23) {                       line = 40;
                       Danger_appear(3, j, 40, deltaTimeSeconds);
                       danger1Position = glm::vec3(dangers_x[j], 40, 0);
                       Star_Appear(danger1Position, j, deltaTimeSeconds, line);

                   }
                   if (j >= 24 && j <= 27) {
                       line = 180;
                       Danger_appear(3, j, 180, deltaTimeSeconds);
                       danger2Position = glm::vec3(dangers_x[j], 180, 0);
                       Star_Appear(danger2Position, j, deltaTimeSeconds, line);

                   }
                   if (j >= 28 && j <= 30) {
                       line = 330;
                       Danger_appear(3, j, 330, deltaTimeSeconds);
                       danger3Position = glm::vec3(dangers_x[j], 330, 0);
                       Star_Appear(danger3Position, j, deltaTimeSeconds, line);
                   }
               }
               if (j > 30 && j <= 40) {
                   if (j >= 31 && j <= 34) {
                       line = 40;
                       Danger_appear(4, j, 40, deltaTimeSeconds);
                       danger1Position = glm::vec3(dangers_x[j], 40, 0);
                       Star_Appear(danger1Position, j, deltaTimeSeconds, line);

                   }
                   if (j >= 35 && j <= 37) {
                       line = 180;
                       Danger_appear( 4, j, 180, deltaTimeSeconds);
                       danger2Position = glm::vec3(dangers_x[j], 180, 0);
                       Star_Appear(danger2Position, j, deltaTimeSeconds, line);

                   }
                   if (j >= 38 && j <= 40) {
                       line = 330;
                       Danger_appear(4, j, 330, deltaTimeSeconds);
                       danger3Position = glm::vec3(dangers_x[j], 330, 0);
                       Star_Appear(danger3Position, j, deltaTimeSeconds, line);
                   }
               }
           }
       }

    //random stars
    
        if (!starRendered) {
            std::random_device rd5;
            std::mt19937 mt5(rd5());
            std::uniform_real_distribution<float> randX(100.0f, 800.0f);
            std::uniform_real_distribution<float> randY(100.0f, 500.0f);
            randomX = randX(mt5);
            randomY = randY(mt5);
            randomX2 = randX(mt5);
            randomY2 = randY(mt5);
            randomX3 = randX(mt5);
            randomY3 = randY(mt5);
            starRendered = true;
        }
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(randomX, randomY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(randomX2, randomY2);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(randomX3, randomY3);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    time_now2 = 0;
    


    //drag_and_drop

           //selectarea si deplasaerea unui soldat
    if (soldier1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move_x1, move_y1);
        RenderMesh2D(meshes["soldier1"], shaders["VertexColor"], modelMatrix);

    }
    if (soldier2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move_x1, move_y1);
        RenderMesh2D(meshes["soldier2"], shaders["VertexColor"], modelMatrix);

    }
    if (soldier3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move_x1, move_y1);
        RenderMesh2D(meshes["soldier3"], shaders["VertexColor"], modelMatrix);

    }
    if (soldier4) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(move_x1, move_y1);
        RenderMesh2D(meshes["soldier4"], shaders["VertexColor"], modelMatrix);

    }

    for (int i = 1; i <= 9; i++) {
        if (realease[i] == i) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(patrat[i].x_soldat, patrat[i].y_soldat);

            soldat1Position = glm::vec3(patrat[i].x_soldat, patrat[i].y_soldat, 0);
            Soldier_killed(danger1Position,danger2Position,danger3Position,soldat1Position, patrat[i].y_soldat);
            if (patrat[i].see_soldier == 1) {
                modelMatrix *= transform2D::Translate(20, 12.5f) * transform2D::Scale(scaleX, scaleY) * transform2D::Translate(-20, -12.5f);
                if (scaleY > 0) {
                    scaleX -= deltaTimeSeconds;
                    scaleY -= deltaTimeSeconds;
                }
            }
            if (scaleY <= 0) {
                scaleX = 1;
                scaleY = 1;
                realease[i] = 0;
                ocupat[i] = 0;
                seeSoldier[i] = false;
                patrat[i].see_soldier = 0;
                
            }
            RenderMesh2D(meshes["soldier1"], shaders["VertexColor"], modelMatrix);


        }
        if (realease2[i] == i) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(patrat[i].x_soldat, patrat[i].y_soldat);
            soldat2Position = glm::vec3(patrat[i].x_soldat, patrat[i].y_soldat, 0);
            Soldier_killed(danger1Position, danger2Position, danger3Position, soldat2Position, patrat[i].y_soldat);
            if (patrat[i].see_soldier == 1) {
                modelMatrix *= transform2D::Translate(20, 12.5f) * transform2D::Scale(patrat[i].scale_x, patrat[i].scale_y) * transform2D::Translate(-20, -12.5f);
                if (patrat[i].scale_y > 0) {
                    patrat[i].scale_x -= deltaTimeSeconds;
                    patrat[i].scale_y -= deltaTimeSeconds;
                }
                if (patrat[i].scale_y <= 0) {
                    patrat[i].scale_y = 1;
                    patrat[i].scale_x = 1;
                    realease2[i] = 0;
                    ocupat[i] = 0;
                    seeSoldier[i] = false;
                    patrat[i].see_soldier = 0;
                }
            }
            RenderMesh2D(meshes["soldier2"], shaders["VertexColor"], modelMatrix);
        }
        if (realease3[i] == i) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(patrat[i].x_soldat, patrat[i].y_soldat);
            soldat3Position = glm::vec3(patrat[i].x_soldat, patrat[i].y_soldat, 0);
            Soldier_killed(danger1Position, danger2Position, danger3Position, soldat3Position, patrat[i].y_soldat);
            if (patrat[i].see_soldier == 1) {
                modelMatrix *= transform2D::Translate(20, 12.5f) * transform2D::Scale(scaleX, scaleY) * transform2D::Translate(-20, -12.5f);
                if (scaleY < 5 && scaleY > 0) {
                    scaleX -= deltaTimeSeconds;
                    scaleY -= deltaTimeSeconds;
                }
                if (scaleY <= 0) {
                    scaleX = 1;
                    scaleY = 1;
                    realease3[i] = 0;
                    ocupat[i] = 0;
                    seeSoldier[i] = false;
                    patrat[i].see_soldier = 0;
                }
            }
            RenderMesh2D(meshes["soldier3"], shaders["VertexColor"], modelMatrix);
        }
        if (realease4[i] == i) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(patrat[i].x_soldat, patrat[i].y_soldat);
            soldat4Position = glm::vec3(patrat[i].x_soldat , patrat[i].y_soldat, 0);
            Soldier_killed(danger1Position, danger2Position, danger3Position, soldat4Position, patrat[i].y_soldat);
            if (patrat[i].see_soldier == 1) {
                modelMatrix *= transform2D::Translate(20, 12.5f) * transform2D::Scale(scaleX, scaleY) * transform2D::Translate(-20, -12.5f);
                if (scaleY < 5 && scaleY > 0) {
                    scaleX -= deltaTimeSeconds;
                    scaleY -= deltaTimeSeconds;
                }
                if (scaleY <= 0) {
                    scaleX = 1;
                    scaleY = 1;
                    realease4[i] = 0;
                    ocupat[i] = 0;
                    seeSoldier[i] = false;
                    patrat[i].see_soldier = 0;
                }
            }
            RenderMesh2D(meshes["soldier4"], shaders["VertexColor"], modelMatrix);
        }
    }
}



void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    move_x1 = mouseX;
    move_y1 = 700 - mouseY;
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    for (int i = 1; i < 10; i++) {
        printf("%d \n", ocupat[i]);
    }
    // Add mouse button press event
    if (button == 2) {
        //patrat1
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 600 && mouseY <= 700) {
            patrat[1].see_soldier = 1;
        }
        //patrat2
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 600 && mouseY <= 700) {
            patrat[2].see_soldier = 1;
        }
        //patrat 3
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 600 && mouseY <= 700) {
            patrat[3].see_soldier = 1;
        }
        //patrat 4
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 470 && mouseY <= 570) {
            patrat[4].see_soldier = 1;
        }
        //patrat5
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 470 && mouseY <= 570) {
            patrat[5].see_soldier = 1;
        }
        //patrat6
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 470 && mouseY <= 570) {
            patrat[6].see_soldier = 1;
        }
        //patrat7
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 320 && mouseY <= 420) {
            patrat[7].see_soldier = 1;
        }
        //patrat8
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 320 && mouseY <= 420) {
            patrat[8].see_soldier = 1;
        }
        //patrat9
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 320 && mouseY <= 420) {
            patrat[9].see_soldier = 1;
        }
    }
    if (button == 2) {
        //iau soldat1
        if (mouseX >= 10 && mouseX <= 100 && mouseY >= 100 && mouseY <= 200) {
            printf("iau soldat1\n");
            soldier1 = true;
        }
        //iau soldat2
        if (mouseX >= 200 && mouseX <= 300 && mouseY >= 100 && mouseY <= 200) {
            printf("iau soldat2\n");
            soldier2 = true;
        }
        //iau soldat3
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 100 && mouseY <= 200) {
            printf("iau soldat3\n");
            soldier3 = true;
        }
        //iau soldat4
        if (mouseX >= 600 && mouseX <= 700 && mouseY >= 100 && mouseY <= 200) {
            soldier4 = true;
            printf("iau soldat4\n");
        }

    }
    

 

}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event

    printf("%d %d\n", mouseX, mouseY);
    if (button == 2) {
        //patrat1
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 600 && mouseY <= 700) {
            if (soldier1) {
                if (ocupat[1] == 0) {
                    realease[1] = 1;
                    ocupat[1] = 1;
                }  
            }
            if (soldier2) {
                if (ocupat[1] == 0) {
                    realease2[1] = 1;
                    ocupat[1] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[1] == 0) {
                    realease3[1] = 1;
                    ocupat[1] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[1] == 0) {
                    realease4[1] = 1;
                    ocupat[1] =1;
                }
            }
        }

        //patrat2
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 600 && mouseY <= 700) {
            if (soldier1) {
                if (ocupat[2] == 0) {
                    realease[2] = 2;
                    ocupat[2] = 1;
                }
            }
            if (soldier2) {
                if (ocupat[2] == 0) {
                    realease2[2] = 2;
                    ocupat[2] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[2] == 0) {
                    realease3[2] = 2;
                    ocupat[2] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[2] == 0) {
                    realease4[2] = 2;
                    ocupat[2] = 1;
                }
            }
        }

        //patrat 3
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 600 && mouseY <= 700) {
            if (soldier1) {
                if (ocupat[3] == 0) {
                    realease[3] = 3;
                    ocupat[3] = 1;
                }
            }
            if (soldier2) {
                if (ocupat[3] == 0) {
                    realease2[3] = 3;
                    ocupat[3] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[3] == 0) {
                    realease3[3] = 3;
                    ocupat[3] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[3] == 0) {
                    realease4[3] = 3;
                    ocupat[3] = 1;
                }
            }
        }

        //patrat4
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 470 && mouseY <= 570) {
            if (soldier1) {
                
                if (ocupat[4] == 0) {
                    realease[4] = 4;
                    ocupat[4] = 1;
                }
            }
            if (soldier2) {
                
                if (ocupat[4] == 0) {
                    realease2[4] = 4;
                    ocupat[4] = 1;
                }
            }
            if (soldier3) {
                
                if (ocupat[4] == 0) {
                    realease3[4] = 4;
                    ocupat[4] = 1;
                }
            }
            if (soldier4) {
                
                if (ocupat[4] == 0) {
                    realease4[4] = 4;
                    ocupat[4] = 1;
                }
            }
        }

        //patrat5
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 470 && mouseY <= 570) {
            if (soldier1) {
                if (ocupat[5] == 0) {
                    realease[5] = 5;
                    ocupat[5] = 1;
                }
            }
            if (soldier2) {
                if (ocupat[5] == 0) {
                    realease2[5] = 5;
                    ocupat[5] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[5] == 0) {
                    realease3[5] = 5;
                    ocupat[5] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[5] == 0) {
                    realease4[5] = 5;
                    ocupat[5] = 1;
                }
            }
        }

        //patrat6
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 470 && mouseY <= 570) {
            if (soldier1) {
                if (ocupat[6] == 0) {
                    realease[6] = 6;
                    ocupat[6] = 1;
                }
                
            }
            if (soldier2) {
                if (ocupat[6] == 0) {
                    realease2[6] = 6;
                    ocupat[6] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[6] == 0) {
                    realease3[6] = 6;
                    ocupat[6] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[6] == 0) {
                    realease4[6] = 6;
                    ocupat[6] = 1;
                }
            }
        }
        //patrat7
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 320 && mouseY <= 420) {
            if (soldier1) {
                if (ocupat[7] == 0) {
                    realease[7] = 7;
                    ocupat[7] = 1;
                }
            }
            if (soldier2) {
                if (ocupat[7] == 0) {
                    realease2[7] = 7;
                    ocupat[7] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[7] == 0) {
                    realease3[7] = 7;
                    ocupat[7] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[7] == 0) {
                    realease4[7] = 7;
                    ocupat[7] = 1;
                }
            }
        }

        //patrat8
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 320 && mouseY <= 420) {
            if (soldier1) {
                if (ocupat[8] == 0) {
                    realease[8] = 8;
                    ocupat[8] = 1;
                }
            }
            if (soldier2) {
                if (ocupat[8] == 0) {
                    realease2[8] = 8;
                    ocupat[8] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[8] == 0) {
                    realease3[8] = 8;
                    ocupat[8] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[8] == 0) {
                    realease4[8] = 8;
                    ocupat[8] = 1;
                }
            }
        }

        //patrat9
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 320 && mouseY <= 420) {
            if (soldier1) {
                if (ocupat[9] == 0) {
                    realease[9] = 9;
                    ocupat[9] = 1;
                }
                
            }
            if (soldier2) {
                if (ocupat[9] == 0) {
                    realease2[9] = 9;
                    ocupat[9] = 1;
                }
            }
            if (soldier3) {
                if (ocupat[9] == 0) {
                    realease3[9] = 9;
                    ocupat[9] = 1;
                }
            }
            if (soldier4) {
                if (ocupat[9] == 0) {
                    realease4[9] = 9;
                    ocupat[9] = 1;
                }
            }
        }
        soldier1 = false;
        soldier2 = false;
        soldier3 = false;
        soldier4 = false;
    }
    

    
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
